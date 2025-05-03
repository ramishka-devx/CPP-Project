cmake_minimum_required(VERSION 3.10)
project(ParticleSimulation VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find required packages
find_package(nlohmann_json REQUIRED)

# Add source files
set(SOURCES
    src/main.cpp
    src/Particle.cpp
    src/ContainmentField.cpp
    src/Simulation.cpp
    src/ThreadManager.cpp
    src/Config.cpp
)

# Add header files
set(HEADERS
    include/Particle.h
    include/ContainmentField.h
    include/Simulation.h
    include/ThreadManager.h
    include/Config.h
)

# Create executable
add_executable(quantum_simulator_app ${SOURCES} ${HEADERS})

# Include directories
target_include_directories(quantum_simulator_app PRIVATE include)

# Link libraries
target_link_libraries(quantum_simulator_app PRIVATE nlohmann_json::nlohmann_json)

# Copy config file to build directory
configure_file(config.json ${CMAKE_CURRENT_BINARY_DIR}/config.json COPYONLY)
