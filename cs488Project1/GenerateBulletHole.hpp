//
//  GenerateBulletHole.hpp
//  cs488Project
//
//  Created by Chang Zhou on 2018-11-28.
//  Copyright © 2018 none. All rights reserved.
//

#ifndef GenerateBulletHole_hpp
#define GenerateBulletHole_hpp

#include <stdio.h>
#include <vector>
#include <glm/glm.hpp>
#include <cs488-framework/ShaderProgram.hpp>
#include "MyEntity.hpp"
#include "Loader.hpp"
class GenerateBulletHole {
public:
    static void generateHole(std::vector<MyEntity> &bulletHoles, glm::vec3 pos, glm::vec3 normal, ShaderProgram &m_shader, Loader *m_loader, bool hitTarget);
};
#endif /* GenerateBulletHole_hpp */
