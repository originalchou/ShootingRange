//
//  BulletsManager.cpp
//  cs488Project
//
//  Created by Chang Zhou on 2018-11-28.
//  Copyright © 2018 none. All rights reserved.
//

#include "BulletsManager.hpp"
#include <iostream>
void BulletsManage::moveBullets(std::vector<MyEntity> &bulletHoles, std::vector<MyParticle> &particles, ShaderProgram &m_shader, Loader *m_loader, std::vector<MyEntity> &targets) {
    for (int i = 0; i < m_bullets.size(); i++) {
        MyBullet &bullet = m_bullets.at(i);
        for (int j = 0; j < 20; j++) {
            if (!bullet.moveBullet(bulletHoles, particles, m_shader, m_loader, targets)) {
                m_bullets.erase(m_bullets.begin()+i-1);
                break;
            }
        }
    }
}
