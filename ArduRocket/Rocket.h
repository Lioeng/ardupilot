#pragma once

#include "AP_Vehicle.h"
#include "AP_HAL_Linux.h"

class Rocket : public AP_Vehicle {
public:
    Rocket();
    void init();
    void run();
    
private:
    void update_flight_stage();
    void update_attitude();
    void update_navigation();
    void update_servos();
    
    enum FlightStage {
        STAGE_LAUNCH,
        STAGE_BOOST,
        STAGE_COAST,
        STAGE_DESCENT,
        STAGE_LANDING
    };
    
    FlightStage current_stage;
    uint32_t stage_start_time;
};