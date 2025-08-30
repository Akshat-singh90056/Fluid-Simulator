#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <iostream>

class Particle
{

public:
    Particle();
    ~Particle();

    void update(float dt);
    void grid();
    void boundryCollision();
    void setBounds(float width, float height);

    float &GetRadius() { return radius; }
    std::vector<glm::vec2> &GetPositions() { return position; }

    bool running = false;
    float alpha = 1.0f;
    float blurry = 0.0f;
    const float GRAVITY = 9.8f;
    int numOfParticels = 1;
    float particleSize = 0.16f;
    float particeleSpacing = 1.0f;
    float damping = 0.99f;
    float spacing = 0;

    
    private:
    std::vector<glm::vec2> position;
    std::vector<glm::vec2> velocite;
    
    float radius = 1.0f;
    float worldWidth;
    float worldHeight;
    
};