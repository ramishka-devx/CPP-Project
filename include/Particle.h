#pragma once

#include <cmath>

class Particle {
public:
    Particle(double x, double y, double vx, double vy, double mass = 1.0);
    
    // Getters
    double getX() const { return x; }
    double getY() const { return y; }
    double getVx() const { return vx; }
    double getVy() const { return vy; }
    double getMass() const { return mass; }
    
    // Setters
    void setPosition(double newX, double newY);
    void setVelocity(double newVx, double newVy);
    
    // Physics methods
    void updatePosition(double dt);
    void applyForce(double fx, double fy, double dt);
    
    // Collision detection
    bool checkCollision(const Particle& other) const;
    void handleCollision(Particle& other);
    
private:
    double x, y;      // Position
    double vx, vy;    // Velocity
    double mass;      // Mass
    static constexpr double RADIUS = 0.5;  // Particle radius for collision detection
}; 