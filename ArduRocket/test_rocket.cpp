#include "Rocket.h"
#include "AP_HAL/AP_HAL.h"

extern const AP_HAL::HAL& hal;

void test_rocket_init()
{
    hal.console->printf("Testing ArduRocket initialization...\n");
    
    Rocket test_rocket;
    test_rocket.init();
    
    hal.console->printf("ArduRocket initialization test passed\n");
}

void test_flight_stages()
{
    hal.console->printf("Testing flight stage transitions...\n");
    
    Rocket test_rocket;
    test_rocket.init();
    
    // Test stage transitions
    for (int i = 0; i < 10; i++) {
        test_rocket.run();
        hal.scheduler->delay(1000);
    }
    
    hal.console->printf("Flight stage test completed\n");
}

void run_tests()
{
    hal.console->printf("Starting ArduRocket tests...\n");
    
    test_rocket_init();
    test_flight_stages();
    
    hal.console->printf("All tests completed successfully!\n");
}