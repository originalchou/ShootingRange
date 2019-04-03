//
//  ParticlesGenerator.hpp
//  cs488Project
//
//  Created by Chang Zhou on 2018-11-30.
//  Copyright © 2018 none. All rights reserved.
//

#ifndef ParticlesGenerator_hpp
#define ParticlesGenerator_hpp

#include <stdio.h>
#include <vector>
#include <glm/glm.hpp>
#include <cs488-framework/ShaderProgram.hpp>
#include "Loader.hpp"
#include "MyParticle.hpp"

class ParticlesGenerator {
public:
    static void generateParticles(std::vector<MyParticle> &particles, glm::vec3 pos, glm::vec3 normal, ShaderProgram &m_shader, Loader *m_loader);
};
#endif /* ParticlesGenerator_hpp */
