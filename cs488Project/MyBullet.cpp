//
//  MyBullet.cpp
//  cs488Project
//
//  Created by Chang Zhou on 2018-11-28.
//  Copyright © 2018 none. All rights reserved.
//

#include "MyBullet.hpp"
#include "CheckHit.hpp"
#include <iostream>
#include "GenerateBulletHole.hpp"
#include "ParticlesGenerator.hpp"

bool MyBullet::moveBullet(std::vector<MyEntity> &bulletHoles, std::vector<MyParticle> &particles, ShaderProgram &m_shader, Loader *m_loader, std::vector<MyEntity> &targets) {
    bool ret = true;
    glm::vec3 oldPos(m_position);
    m_position = m_position + glm::vec3(0.2, 0.2, 0.2) * m_direction;
    int hitTarget = CheckHit::checkHit(m_position, 0.5, targets, true);
    if (hitTarget == 1) {
        ret = false;
        if (!ret && m_position.y < 60) {
            GenerateBulletHole::generateHole(bulletHoles, oldPos, -m_direction, m_shader, m_loader, false);
            ParticlesGenerator::generateParticles(particles, oldPos, -m_direction, m_shader, m_loader);
        }
    } else if (hitTarget == 2) {
        ret = false;
        if (!ret && m_position.y < 60) {
            GenerateBulletHole::generateHole(bulletHoles, oldPos, -m_direction, m_shader, m_loader, true);
            ParticlesGenerator::generateParticles(particles, oldPos, -m_direction, m_shader, m_loader);
        }
    }
    if (m_position.x > 200 || m_position.z > 200 || m_position.y > 100) {
        ret = false;
    }
    return ret;
}
