//
//  MyBullet.hpp
//  cs488Project
//
//  Created by Chang Zhou on 2018-11-28.
//  Copyright © 2018 none. All rights reserved.
//

#ifndef MyBullet_hpp
#define MyBullet_hpp

#include "Loader.hpp"
#include <stdio.h>
#include "MyEntity.hpp"
#include "MyParticle.hpp"

class MyBullet: public MyEntity {
public:
    MyBullet(TexturedModel& model, glm::vec3& position, glm::vec3& rotation, glm::vec3& scale, glm::vec3& direction)
    : MyEntity(model, position, rotation, scale), m_direction(direction) {}
    bool moveBullet(std::vector<MyEntity> &bulletHoles, std::vector<MyParticle> &particles, ShaderProgram &m_shader, Loader *m_loader, std::vector<MyEntity> &targets);
    void setDirection(glm::vec3 direction) { m_direction = direction; }
    glm::vec3 getDirection() { return m_direction; }
private:
    glm::vec3 m_direction;
};
#endif /* MyBullet_hpp */
