#pragma once

#include "AP_Param/AP_Param.h"

class Parameters {
public:
    enum {
        k_param_vehicle = 257,
        k_param_rocket_launch_delay = 1000,
        k_param_rocket_boost_duration = 1001,
        k_param_rocket_coast_duration = 1002,
        k_param_rocket_descent_duration = 1003,
        k_param_rocket_max_altitude = 1004,
        k_param_rocket_thrust_curve = 1005,
        k_param_rocket_fin_gain = 1006,
        k_param_rocket_tvc_gain = 1007,
    };

    AP_Int8 vehicle;
    AP_Int16 rocket_launch_delay;
    AP_Int16 rocket_boost_duration;
    AP_Int16 rocket_coast_duration;
    AP_Int16 rocket_descent_duration;
    AP_Int32 rocket_max_altitude;
    AP_Float rocket_thrust_curve;
    AP_Float rocket_fin_gain;
    AP_Float rocket_tvc_gain;
};