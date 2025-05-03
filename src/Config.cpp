#include "Config.h"
#include <fstream>
#include <stdexcept>

Config::Config(const std::string& configPath) {
    loadFromFile(configPath);
}

void Config::loadFromFile(const std::string& configPath) {
    std::ifstream file(configPath);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open config file: " + configPath);
    }

    json config;
    try {
        file >> config;
    } catch (const json::parse_error& e) {
        throw std::runtime_error("Failed to parse config file: " + std::string(e.what()));
    }

    // Load simulation parameters
    fieldSize = config.value("field_size", 10.0);
    fieldStrength = config.value("field_strength", 1.0);
    numParticles = config.value("num_particles", 100);
    timeStep = config.value("time_step", 0.01);
    numSteps = config.value("num_steps", 1000);
} 