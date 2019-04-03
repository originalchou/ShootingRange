//
//  ParticlesGenerator.cpp
//  cs488Project
//
//  Created by Chang Zhou on 2018-11-30.
//  Copyright © 2018 none. All rights reserved.
//

#include "ParticlesGenerator.hpp"
#include "Wall.hpp"
#include <glm/gtx/transform.hpp>

void ParticlesGenerator::generateParticles(std::vector<MyParticle> &particles, glm::vec3 pos, glm::vec3 normal, ShaderProgram &m_shader, Loader *m_loader) {
    RawModel particle_raw_model = Wall::generateSingleWallModel(m_shader, m_loader);
    ModelTexture particle_texture = ModelTexture(m_loader->loadTexture("brown"), 0.2, 1);
    TexturedModel particle_textured_model = TexturedModel(particle_raw_model, particle_texture);
    glm::vec3 speed = glm::normalize(normal);
    glm::vec3 speed1 = glm::vec3(speed.x * 0.01, (speed.y+30) * 0.01, speed.z * 0.01);
    glm::mat4 rotate1 = glm::rotate(1.0f, glm::vec3(0, 1, 0));
    glm::mat4 rotate2 = glm::rotate(-1.0f, glm::vec3(0, 1, 0));
    glm::vec3 speed2(rotate1 * glm::vec4(speed1, 0.0f));
    glm::vec3 speed3(rotate2 * glm::vec4(speed1, 0.0f));
    glm::vec3 p(pos.x, pos.y, pos.z);
    glm::vec3 r(0.0, 0.0, 0.0);
    glm::vec3 s(0.5, 0.5, 0.5);
    particles.push_back(MyParticle(particle_textured_model, p, r, s, speed1));
    particles.push_back(MyParticle(particle_textured_model, p, r, s, speed3));
    particles.push_back(MyParticle(particle_textured_model, p, r, s, speed2));
}
