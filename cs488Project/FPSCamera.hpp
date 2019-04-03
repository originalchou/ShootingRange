//
//  FPSCamera.hpp
//  cs488Project
//
//  Created by Chang Zhou on 2018-11-16.
//  Copyright © 2018 none. All rights reserved.
//

#ifndef FPSCamera_hpp
#define FPSCamera_hpp

#include <stdio.h>
#include <glm/glm.hpp>
#include "MyEntity.hpp"
#include <vector>

class FPSCamera
{
public:
    FPSCamera(bool freeRoam, std::vector<MyEntity> &targets);
    virtual ~FPSCamera();
    
    void update();
    glm::mat4 getViewMatrix() const;
    
    inline glm::vec3 getPosition() { return m_position; }
    inline glm::vec3 getDirection() {return m_viewDirection; }
private:
    const glm::vec3 m_UP = glm::vec3(0, 1, 0);
    const float m_SENSITIVITY = 0.005f;
    const float m_SPEED = 0.13f;
    bool m_freeRoam;
    glm::vec3 m_position;
    glm::vec3 m_viewDirection;
    glm::vec2 m_mousePosition;
    std::vector<MyEntity> &m_targets;
    void mouseUpdate(const glm::vec2 mousePosition);
    void move();
};
#endif /* FPSCamera_hpp */
