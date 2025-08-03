/*
  ArduRocket – Arduino-based Rocket Flight Computer
  -------------------------------------------------
  Handles pre-launch checks, ascent tracking, apogee detection,
  parachute deployment, and data logging.

  Tested on Arduino Nano (ATmega328p, 16 MHz, 5 V).

  Required libraries (install via Library Manager):
    • Adafruit BMP280 Library (+ Adafruit Unified Sensor)
    • MPU6050 by Electronic Cats (or Jeff Rowberg's library)
    • SD (built-in)
    • Servo (built-in)
    • optional: LoRa by Sandeep Mistry
*/

#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <Servo.h>
#include <Adafruit_BMP280.h>
#include <MPU6050.h>

// ----------------------- Pin Definitions ----------------------- //
const uint8_t PIN_SD_CS  = 10; // SD card Chip-Select
const uint8_t PIN_SERVO  = 6;  // Servo signal (parachute)
const uint8_t PIN_BUZZER = 3;  // Optional piezo buzzer

// ----------------------- Flight Parameters ---------------------- //
const float    APOGEE_THRESHOLD_MPS = 3.0f;   // m/s downward (negative) velocity
const uint32_t MIN_FLIGHT_MS        = 2000;   // ignore apogee detection before 2 s
const uint32_t SERVO_DEPLOY_MS      = 300;    // ms to hold servo at deploy angle

// ----------------------- Globals -------------------------------- //
Adafruit_BMP280 bmp;   // Barometer
MPU6050         mpu;   // IMU
Servo           chute;
File            logFile;

float altFilt = 0.0f;  // low-pass altitude
float velFilt = 0.0f;  // low-pass vertical velocity
uint32_t tPrev = 0;

enum FlightState : uint8_t { PRELAUNCH, ASCENT, APOGEE_HOLD, DESCENT, LANDED };
FlightState state = PRELAUNCH;
uint32_t launchMillis = 0;

// ----------------------- Helpers -------------------------------- //
[[noreturn]] void panic(const __FlashStringHelper *msg) {
  Serial.println(msg);
  while (true) {
    tone(PIN_BUZZER, 2000, 150);
    delay(300);
  }
}

void logHeader() {
  logFile.println(F("time_ms,pressure_Pa,alt_m,ax,ay,az,gx,gy,gz,state"));
  logFile.flush();
}

void logData(uint32_t t, float P, float alt, int16_t ax, int16_t ay, int16_t az, int16_t gx, int16_t gy, int16_t gz) {
  logFile.print(t);           logFile.print(',');
  logFile.print(P, 2);        logFile.print(',');
  logFile.print(alt, 2);      logFile.print(',');
  logFile.print(ax);          logFile.print(',');
  logFile.print(ay);          logFile.print(',');
  logFile.print(az);          logFile.print(',');
  logFile.print(gx);          logFile.print(',');
  logFile.print(gy);          logFile.print(',');
  logFile.print(gz);          logFile.print(',');
  logFile.println(state);
  if (!(t % 100)) logFile.flush();
}

static inline float lowPass(float prev, float current, float alpha) {
  return prev + alpha * (current - prev);
}

void deployChute() {
  chute.write(90);      // release latch
  delay(SERVO_DEPLOY_MS);
  chute.write(0);       // reset servo
  tone(PIN_BUZZER, 3000, 400);
}

// ----------------------- Setup ---------------------------------- //
void setup() {
  Serial.begin(115200);
  pinMode(PIN_BUZZER, OUTPUT);

  // Servo
  chute.attach(PIN_SERVO);
  chute.write(0);   // latch closed

  // BMP280
  if (!bmp.begin()) panic(F("BMP280 not found"));
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,
                  Adafruit_BMP280::SAMPLING_X2,   // temperature
                  Adafruit_BMP280::SAMPLING_X16,  // pressure
                  Adafruit_BMP280::FILTER_X16,
                  Adafruit_BMP280::STANDBY_MS_0_5);

  // MPU6050
  Wire.begin();
  if (!mpu.begin()) panic(F("MPU6050 not found"));

  // SD card
  if (!SD.begin(PIN_SD_CS))  panic(F("SD init failed"));
  char fname[13];
  uint16_t idx = 0;
  do {
    snprintf(fname, sizeof(fname), "LOG%04u.CSV", idx++);
  } while (SD.exists(fname) && idx < 10000);
  logFile = SD.open(fname, FILE_WRITE);
  if (!logFile) panic(F("Log file open failed"));
  logHeader();

  Serial.println(F("ArduRocket ready – awaiting launch."));
  tPrev = millis();
}

// ----------------------- Loop ----------------------------------- //
void loop() {
  uint32_t now = millis();
  float P = bmp.readPressure();
  float alt = bmp.readAltitude();

  int16_t ax, ay, az, gx, gy, gz;
  mpu.getAcceleration(&ax, &ay, &az);
  mpu.getRotation(&gx, &gy, &gz);

  // Estimate velocity (finite diff) + low-pass
  float dt = (now - tPrev) / 1000.0f;
  tPrev = now;
  float altLP = lowPass(altFilt, alt, 0.1f);
  float vel    = (altLP - altFilt) / max(dt, 0.001f);
  velFilt      = lowPass(velFilt, vel, 0.1f);
  altFilt      = altLP;

  // ---------------- State machine ---------------- //
  switch (state) {
    case PRELAUNCH:
      if (velFilt > 2.0f) {               // simple lift-off detection
        state = ASCENT;
        launchMillis = now;
        tone(PIN_BUZZER, 2500, 200);
      }
      break;

    case ASCENT:
      if (velFilt < -APOGEE_THRESHOLD_MPS && (now - launchMillis) > MIN_FLIGHT_MS) {
        state = APOGEE_HOLD;
        deployChute();
      }
      break;

    case APOGEE_HOLD:
      if ((now - launchMillis) > (MIN_FLIGHT_MS + 4000)) {
        state = DESCENT;
      }
      break;

    case DESCENT:
      if (abs(velFilt) < 0.5f && altFilt < 5.0f) {
        state = LANDED;
        tone(PIN_BUZZER, 1500, 1200);
      }
      break;

    case LANDED:
      if (now % 5000 < 30) tone(PIN_BUZZER, 1000, 80);
      break;
  }

  logData(now, P, alt, ax, ay, az, gx, gy, gz);

  // Print to Serial every 200 ms
  if (!(now % 200)) {
    Serial.print(F("State:")); Serial.print(state);
    Serial.print(F(" Alt:"));   Serial.print(altFilt);
    Serial.print(F(" Vel:"));   Serial.println(velFilt);
  }
}