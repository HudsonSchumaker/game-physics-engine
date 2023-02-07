#include "World.h"
#include "Constants.h"
#include "CollisionDetection.h"
#include <iostream>

World::World(float gravity) {
    G = -gravity;
    std::cout << "World constructor called!" << std::endl;
}

World::~World() {
    for (auto body: bodies) {
        delete body;
    }
    std::cout << "World destructor called!" << std::endl;
}

void World::AddBody(Body* body) {
    bodies.push_back(body);
}

std::vector<Body*>& World::GetBodies() {
    return bodies;
}

void World::AddForce(const Vec2& force) {
    forces.push_back(force);
}

void World::AddTorque(float torque) {
    torques.push_back(torque);
}

void World::Update(float dt) {
    // Loop all bodies of the world applying forces
    for (auto body: bodies) {
        // Apply the weight force to all bodies
        Vec2 weight = Vec2(0.0, body->mass * G * PIXELS_PER_METER);
        body->AddForce(weight);

        // Apply forces to all bodies
        for (auto force: forces) {
            body->AddForce(force);
        }

        // Apply torque to all bodies
        for (auto torque: torques) {
            body->AddTorque(torque);
        }
    }

    // Update all the bodies in the world (integrating and transforming vertices)
    for (auto body: bodies) {
        body->Update(dt);
    }

    // Collision detection and resolution for all bodies of the world
    for (int n = 0; n < 10; n++) {
        CheckCollisions();
    }
}

void World::CheckCollisions() {
    // Check all the bodies with all other bodies detecting collisions
    for (int i = 0; i <= bodies.size() - 1; i++) {
        for (int j = i + 1; j < bodies.size(); j++) {
            Body* a = bodies[i];
            Body* b = bodies[j];
            a->isColliding = false;
            b->isColliding = false;
            
            Contact contact;
            if (CollisionDetection::IsColliding(a, b, contact)) {
                // Resolve the collision
                contact.ResolveCollision();
            }
        }
    }
}
