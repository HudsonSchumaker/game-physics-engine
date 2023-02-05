#include "Particle.h"
#include <iostream>

Particle::Particle(float x, float y, float mass) {
    this->position = Vec2(x, y);
    this->mass = mass;
    if (mass != 0.0f) {
        this->invMass = 1.0f / mass;
    }
    else {
        this->invMass = 0.0f;
    }

    std::cout << "Particle constructor called!" << std::endl;
}

Particle::~Particle() {
    std::cout << "Particle destructor called!" << std::endl;
}

void Particle::AddForce(const Vec2& force) {
    sumForces += force;
}

void Particle::ClearForces() {
    sumForces = Vec2(0.0, 0.0);
}

void Particle::Integrate(float dt) {
    // Find the acceleration based on the forces that are being applied and the mass
    // acceleration = sumForces * invMass;
    acceleration = sumForces / mass;

    // Integrate the acceleration to find the new velocity
    velocity += acceleration * dt;

    // Integrate the velocity to find the new position
    position += velocity * dt;

    ClearForces();
}
