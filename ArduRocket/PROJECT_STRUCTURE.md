# ArduRocket Project Structure

## Overview
This document describes the structure and organization of the ArduRocket project.

## Directory Structure

```
ArduRocket/
├── Rocket.cpp              # Main entry point
├── Rocket.h                # Main class header
├── Rocket_impl.cpp         # Implementation file
├── Parameters.h            # Parameter definitions
├── Parameters.cpp          # Parameter implementation
├── wscript                 # Build configuration
├── README.md               # Project overview
├── Documentation.md        # Technical documentation
├── ReleaseNotes.txt        # Release information
├── version.h               # Version definitions
├── test_rocket.cpp         # Test functions
├── example_config.txt      # Example configuration
├── build.sh                # Build script
├── simulate.sh             # Simulation script
├── .gitignore              # Git ignore rules
└── PROJECT_STRUCTURE.md    # This file
```

## File Descriptions

### Core Files
- **Rocket.cpp**: Main entry point that initializes and runs the rocket
- **Rocket.h**: Header file defining the Rocket class and flight stages
- **Rocket_impl.cpp**: Implementation of rocket control logic and flight stage management

### Configuration Files
- **Parameters.h/cpp**: Parameter system for rocket configuration
- **wscript**: Build system configuration for WAF
- **example_config.txt**: Example parameter configuration

### Documentation
- **README.md**: Project overview and quick start guide
- **Documentation.md**: Detailed technical documentation
- **ReleaseNotes.txt**: Version history and release information
- **PROJECT_STRUCTURE.md**: This file

### Build and Test
- **build.sh**: Automated build script
- **simulate.sh**: SITL simulation script
- **test_rocket.cpp**: Test functions for development
- **.gitignore**: Git ignore rules

### Version Control
- **version.h**: Version number definitions
- **.gitignore**: Specifies files to ignore in version control

## Build System Integration

The project integrates with the main ArduPilot build system:

1. **wscript**: Defines build configuration and dependencies
2. **Makefile**: Updated to include 'rocket' as a vehicle type
3. **GitHub Actions**: Automated build and test workflow

## Development Workflow

1. **Setup**: Clone repository and install dependencies
2. **Build**: Use `./ArduRocket/build.sh` or `make rocket`
3. **Test**: Use `./ArduRocket/simulate.sh` for SITL testing
4. **Configure**: Modify parameters in Mission Planner
5. **Deploy**: Flash to compatible hardware

## Integration Points

- **AP_Vehicle**: Inherits from base vehicle class
- **AP_Param**: Uses parameter system for configuration
- **AP_HAL**: Uses hardware abstraction layer
- **Libraries**: Integrates with ArduPilot libraries

## Future Structure

As the project grows, additional directories may be added:

```
ArduRocket/
├── modes/                  # Flight mode implementations
├── control/                # Control algorithms
├── navigation/             # Navigation and guidance
├── recovery/               # Recovery system code
├── sensors/                # Sensor-specific code
├── actuators/              # Actuator control code
└── tests/                  # Comprehensive test suite
```