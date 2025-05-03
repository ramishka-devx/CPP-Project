#pragma once

#include <string>
#include <vector>
#include <map>
#include <stdexcept> 
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class Config {
public:
    Config(const std::string& configPath);
    
    // Simulation parameters
    double getFieldSize() const { return field_size; }
    double getFieldStrength() const { return initial_strength; }
    size_t getNumParticles() const { return num_particles; }
    double getTimeStep() const { return time_step; }
    size_t getNumSteps() const { return field_grid_size; }
    
    size_t getInitialThreads() const { return initial_threads; }
    double getInitialEnergy() const { return initial_energy; }
    double getMaxEnergy() const { return max_energy; }
    double getParticleRadius() const { return particle_radius; }
    double getInitialDecayRate() const { return initial_decay_rate; }
    double getTargetFPS() const { return target_fps; }
    int getGridWidth() const { return grid_width; }
    int getGridHeight() const { return grid_height; }
    const std::map<int, char>& getDensityMap() const { return density_map; }
    int getMaxDensityLevel() const { return max_density_level; }

private:
    double field_size;
    double field_strength;
    size_t num_particles;
    double time_step;
    size_t num_steps;
    
    size_t initial_threads;
    double initial_energy;
    double max_energy;
    double particle_radius;
    double initial_decay_rate;
    size_t field_grid_size;

    double target_fps;
    int grid_width;
    int grid_height;
    std::map<int, char> density_map;
    int max_density_level;
    
    void loadFromFile(const std::string& configPath);
}; 