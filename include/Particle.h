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

    float & GetRadius(){return radius;}
    std::vector<glm::vec2> & GetPositions() {return position;}
    

private:
    std::vector<glm::vec2> position;
    std::vector<glm::vec2> velocite;
    float radius = 1.0f;
};