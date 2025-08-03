# ArduRocket – Arduino-based Rocket Flight Computer

## Overview
ArduRocket is an open-source, budget-friendly flight computer for model rockets based on the Arduino platform. It handles the full flight sequence:

1. Pre-launch health checks
2. Data logging (altitude, acceleration, attitude)
3. Apogee detection
4. Parachute deployment via servo
5. Optional telemetry down-link (e.g. LoRa)

Designed for makers, educators, and rocketry hobbyists, ArduRocket provides reliable flight operations while remaining easy to understand and extend.

---

## Features
* BMP280 barometric sensor for altitude estimation (≈1 m resolution)
* MPU6050 6-DoF IMU for acceleration and attitude
* MicroSD card logging (CSV)
* Servo-based parachute deployment
* State-machine architecture with clearly defined flight phases
* Optional LoRa telemetry module (e.g. SX1278) – hooks already in code
* Runs on any 5 V Arduino (Pro Mini, Nano, Uno, etc.)

---

## Bill of Materials (BoM)
| Qty | Item | Typical Part No. |
|-----|------|------------------|
| 1 | Arduino Nano / Pro Mini / Uno | – |
| 1 | BMP280 barometric sensor | GY-BMP280-3.3 |
| 1 | MPU6050 IMU | GY-521 |
| 1 | MicroSD card module (5 V tolerant) | – |
| 1 | MicroSD card | – |
| 1 | 9 g servo (parachute) | SG90 |
| 1 | N-channel MOSFET + igniter wiring (optional engine ignition) | IRLZ44N |
| 1 | 3.7 V Li-Po OR 2-cell Li-ion pack | – |
| – | Assorted resistors, headers, wiring | – |

Optional:
* LoRa module (e.g. Ra-01, SX1278) and antenna
* Piezo buzzer for audible beeps

---

## Wiring Summary
| Arduino Pin | Module | Notes |
|-------------|--------|-------|
| `A4` / `SDA` | BMP280 & MPU6050 | I²C |
| `A5` / `SCL` | BMP280 & MPU6050 | I²C |
| `D10` | SD Module CS | SPI CS |
| `D11` | SD MOSI | SPI |
| `D12` | SD MISO | SPI |
| `D13` | SD SCK | SPI |
| `D6`  | Servo signal | PWM |
| `D2`  | LoRa NSS (optional) | SPI CS |
| `D3`  | Buzzer (optional) | – |

Adjust pins in `ArduRocket.ino` if needed.

---

## Getting Started
1. Clone this repository and open `ArduRocket/ArduRocket.ino` in the Arduino IDE.
2. Install the required libraries via *Sketch → Include Library → Manage Libraries…*:
   * **Adafruit BMP280 Library**
   * **Adafruit Unified Sensor** (dependency)
   * **MPU6050** by Electronic Cats (or Jeff Rowberg)
   * **SD** (built-in for AVR boards)
   * **Servo** (built-in)
   * *(optional)* **LoRa** by Sandeep Mistry
3. Select your board & port and upload.
4. Open the Serial Monitor at 115 200 baud to observe runtime data.

---

## Flight Phases
```
┌────────────┐       ┌─────────┐       ┌──────────────┐
│ PRELAUNCH  │ ───▶ │ ASCENT  │ ───▶ │ APOGEE_HOLD  │
└────────────┘       └─────────┘       └──────────────┘
                                           │
                                           ▼
                                    ┌──────────┐
                                    │ DESCENT  │
                                    └──────────┘
                                           │
                                           ▼
                                    ┌─────────┐
                                    │ LANDED  │
                                    └─────────┘
```
Transitions are automatic based on sensor data. See comments inside `ArduRocket.ino`.

---

## Data Logging
A new CSV file (e.g. `LOG0001.CSV`) is created on the SD card each power-up containing:
```
time_ms, pressure_Pa, alt_m, ax, ay, az, gx, gy, gz, state
```
Import into Excel, MATLAB, or Python for post-flight analysis.

---

## Repository Layout
```
ArduRocket/
 ├── ArduRocket.ino   # main sketch
 ├── README.md        # documentation
 ├── LICENSE          # MIT license
 ├── .gitignore       # ignore patterns
 └── docs/
      └── wiring.png  # wiring diagram (placeholder)
```
Feel free to add KiCad, Fritzing, or STL files under `docs/`.

---

## Contributing
Pull requests are welcome! Open an issue for ideas or questions.

---

## License
Released under the MIT License. See `LICENSE` for details.