//
//  BulletsManager.hpp
//  cs488Project
//
//  Created by Chang Zhou on 2018-11-28.
//  Copyright © 2018 none. All rights reserved.
//

#ifndef BulletsManager_hpp
#define BulletsManager_hpp

#include "Loader.hpp"
#include "MyBullet.hpp"
#include <stdio.h>
#include <vector>
#include <glm/glm.hpp>
class BulletsManage{
public:
    BulletsManage(std::vector<MyBullet> &bullets): m_bullets(bullets) {};
    void moveBullets(std::vector<MyEntity> &bulletHoles, std::vector<MyParticle> &particles, ShaderProgram &m_shader, Loader *m_loader, std::vector<MyEntity> &targets);

private:
    std::vector<MyBullet> &m_bullets;
};
#endif /* BulletsManager_hpp */
