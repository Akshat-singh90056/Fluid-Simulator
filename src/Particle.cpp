#include "Particle.h"
#include <cmath>
#include "game.h"

Particle::Particle()
{
    position.push_back({0.0f, 0.0f});

    radius = 0.2f;

    velocite.push_back({0.0f, 0.0f});
}

Particle::~Particle()
{
}

void Particle::update(float dt)
{
    if (running)
    {
        for (int i = 0; i < position.size(); i++)
        {
            // 1. Apply gravity to velocity
            velocite[i].y += GRAVITY * dt;

            // 2. Update position using velocity
            position[i].y += velocite[i].y * dt;
        }
    }
}

void Particle::grid()
{

    position.clear();
    velocite.clear();

    int particles_per_row = (int)sqrt(numOfParticels);
    int particles_per_col = (numOfParticels - 1) / (particles_per_row + 1); // Ceiling division
    float spacing = particleSize * 2 + particeleSpacing;

    for (int i = 0; i < numOfParticels; i++)
    {
        float x = (i % particles_per_row - particles_per_row / 2.0f + 0.5f) * spacing;
        float y = (i / particles_per_row - particles_per_col / 2.0f + 0.5f) * spacing;
        position.push_back({x, y});
        velocite.push_back({0.0f, 0.0f});
    }
}

void Particle::boundryCollision()
{
    float worldLeft   = -(worldWidth  / 2.0f);
    float worldRight  =  (worldWidth  / 2.0f);
    float worldBottom = -(worldHeight / 2.0f);
    float worldTop    =  (worldHeight / 2.0f);

    float margin = radius;

    for (int i = 0; i < position.size(); i++)
    {
        // Left wall
        if (position[i].x - margin < worldLeft)
        {
            position[i].x = worldLeft + margin;
            velocite[i].x *= -damping;
        }

        // Right wall
        if (position[i].x + margin > worldRight)
        {
            position[i].x = worldRight - margin;
            velocite[i].x *= -damping;
        }

        // Bottom wall
        if (position[i].y - margin < worldBottom)
        {
            position[i].y = worldBottom + margin;
            velocite[i].y *= -damping;
        }

        // Top wall
        if (position[i].y + margin > worldTop)
        {
            position[i].y = worldTop - margin;
            velocite[i].y *= -damping;
        }
    }
}


void Particle::setBounds(float width, float height)
{
    worldWidth = width;
    worldHeight = height;
}