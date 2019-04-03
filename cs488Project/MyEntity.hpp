//
//  Entity.h
//  cs488Project
//
//  Created by Chang Zhou on 2018-11-16.
//  Copyright © 2018 none. All rights reserved.
//

#ifndef MyEntity_hpp
#define MyEntity_hpp
#include <glm/glm.hpp>
#include "TexturedModel.hpp"
#include <vector>

class MyEntity {
public:
    MyEntity(TexturedModel& model, glm::vec3& position, glm::vec3& rotation, glm::vec3& scale)
    : m_model(model), m_position(position), m_rotation(rotation), m_scale(scale) {}
    
    inline void changePosition(glm::vec3 position){ m_position += position; }
    inline void changeRotation(glm::vec3 rotation) { m_rotation += rotation; }
    inline void changeScale(glm::vec3 scale) { m_scale += scale; }
    
    inline TexturedModel getModel() { return m_model; }
    inline glm::vec3 getPosition() { return m_position; }
    inline glm::vec3 getRotation() { return m_rotation; }
    inline glm::vec3 getScale() { return m_scale; }
    inline int getLastFrame() { return m_lastFrame; }
    inline bool getHit() { return m_hit; }
    
    inline void setModel(TexturedModel model) { m_model = model; }
    inline void setPosition(glm::vec3 position) { m_position = position; }
    inline void setRotation(glm::vec3 rotation) { m_rotation = rotation; }
    inline void setScale(glm::vec3 scale) { m_scale = scale; }
    inline void setLastFrame(int frameLeft) { m_lastFrame = frameLeft; }
    inline void setHit(bool hit) { m_hit = hit; }
protected:
    TexturedModel m_model;
    glm::vec3 m_position;
    glm::vec3 m_rotation;
    glm::vec3 m_scale;
    int m_lastFrame = 300;
    bool m_hit = false;
};

#endif /* MyEntity_hpp */
