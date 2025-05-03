#pragma once

#include <vector>
#include <memory>
#include <mutex>
#include "Particle.h"

struct Config;

class Particle;

class ContainmentField {
public:
    ContainmentField(double size, double fieldStrength);
    ~ContainmentField();

    double getSize() const { return size; }
    double getFieldStrength() const { return fieldStrength; }

    bool isParticleContained(const Particle& particle) const;
    double getContainmentForce(const Particle& particle) const;

    void setFieldStrength(double strength);

    double getFieldEnergy() const;
    void update(double dt);

    void setDecayRate(double rate);
    double getDecayRate() const;

    void calculateForces(std::vector<Particle>& particles, double dt);

private:
    double size;
    double fieldStrength;
    double fieldEnergy;
    double decayRate;
    const size_t GRID_SIZE;
    std::vector<double> fieldData;

    struct EnergyPulse {
        double x, y;
        double strength;
        double lifetime;
    };
    std::vector<EnergyPulse*> energyPulses;

    mutable std::mutex fieldMutex;

    void initializeField();

    double calculateForceMagnitude(double distance) const;
    void applyBoundaryForce(Particle& particle, double dt) const;
}; 