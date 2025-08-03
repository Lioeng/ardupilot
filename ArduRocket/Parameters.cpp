#include "Parameters.h"
#include "AP_Param/AP_Param.h"

const AP_Param::GroupInfo Parameters::var_info[] = {
    // @Param: VEHICLE
    // @DisplayName: Vehicle type
    // @Description: Vehicle type
    // @Values: 0:None,1:Rocket
    // @User: Standard
    AP_GROUPINFO("VEHICLE", 0, Parameters, vehicle, 1),

    // @Param: LAUNCH_DELAY
    // @DisplayName: Launch delay
    // @Description: Delay before launch in milliseconds
    // @Units: ms
    // @Range: 0 10000
    // @User: Standard
    AP_GROUPINFO("LAUNCH_DELAY", 1, Parameters, rocket_launch_delay, 5000),

    // @Param: BOOST_DURATION
    // @DisplayName: Boost duration
    // @Description: Duration of boost phase in milliseconds
    // @Units: ms
    // @Range: 1000 60000
    // @User: Standard
    AP_GROUPINFO("BOOST_DURATION", 2, Parameters, rocket_boost_duration, 30000),

    // @Param: COAST_DURATION
    // @DisplayName: Coast duration
    // @Description: Duration of coast phase in milliseconds
    // @Units: ms
    // @Range: 1000 300000
    // @User: Standard
    AP_GROUPINFO("COAST_DURATION", 3, Parameters, rocket_coast_duration, 60000),

    // @Param: DESCENT_DURATION
    // @DisplayName: Descent duration
    // @Description: Duration of descent phase in milliseconds
    // @Units: ms
    // @Range: 1000 60000
    // @User: Standard
    AP_GROUPINFO("DESCENT_DURATION", 4, Parameters, rocket_descent_duration, 30000),

    // @Param: MAX_ALTITUDE
    // @DisplayName: Maximum altitude
    // @Description: Maximum target altitude in meters
    // @Units: m
    // @Range: 100 10000
    // @User: Standard
    AP_GROUPINFO("MAX_ALTITUDE", 5, Parameters, rocket_max_altitude, 1000),

    // @Param: THRUST_CURVE
    // @DisplayName: Thrust curve
    // @Description: Thrust curve coefficient
    // @Range: 0.1 2.0
    // @User: Standard
    AP_GROUPINFO("THRUST_CURVE", 6, Parameters, rocket_thrust_curve, 1.0),

    // @Param: FIN_GAIN
    // @DisplayName: Fin control gain
    // @Description: Gain for fin control surfaces
    // @Range: 0.1 5.0
    // @User: Standard
    AP_GROUPINFO("FIN_GAIN", 7, Parameters, rocket_fin_gain, 1.0),

    // @Param: TVC_GAIN
    // @DisplayName: Thrust vectoring gain
    // @Description: Gain for thrust vectoring control
    // @Range: 0.1 5.0
    // @User: Standard
    AP_GROUPINFO("TVC_GAIN", 8, Parameters, rocket_tvc_gain, 1.0),

    AP_GROUPEND
};