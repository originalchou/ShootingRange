//
//  MyParticle.hpp
//  cs488Project
//
//  Created by Chang Zhou on 2018-11-30.
//  Copyright © 2018 none. All rights reserved.
//

#ifndef MyParticle_hpp
#define MyParticle_hpp

#include <stdio.h>
#include "MyEntity.hpp"

class MyParticle: public MyEntity {
public:
    MyParticle(TexturedModel& model, glm::vec3& position, glm::vec3& rotation, glm::vec3& scale, glm::vec3& speed)
    : MyEntity(model, position, rotation, scale), m_speed(speed) {}
    glm::vec3 getSpeed() { return m_speed; }
    void setSpeed(glm::vec3 speed) { m_speed = speed; }
    void setFrameLeft(int newFrameLeft) { frameLeft = newFrameLeft; }
    int getFrameLeft() { return frameLeft; }
    void moveParticle();
private:
    glm::vec3 m_speed;
    double gravityEffect = 0.01;
    int frameLeft = 90;
};
#endif /* MyParticle_hpp */
