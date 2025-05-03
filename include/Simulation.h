#pragma once

#include <vector>
#include <memory>
#include "Particle.h"
#include "ContainmentField.h"
#include "ThreadManager.h"

class Simulation {
public:
    Simulation(double fieldSize, double fieldStrength, size_t numParticles);
    ~Simulation();

    // Initialize the simulation
    void initialize();

    // Run the simulation for a given number of steps
    void run(size_t numSteps, double dt);

    // Get simulation state
    const std::vector<Particle>& getParticles() const { return particles; }
    const ContainmentField& getField() const { return *field; }

    // Visualization
    void render() const;

private:
    std::vector<Particle> particles;
    std::unique_ptr<ContainmentField> field;
    ThreadManager threadManager;
    
    // Simulation parameters
    double timeStep;
    size_t numParticles;
    
    // Helper methods
    void updateParticles(double dt);
    void handleCollisions();
    void initializeParticles();
}; 