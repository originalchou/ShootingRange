//
//  Light.hpp
//  cs488Project
//
//  Created by Chang Zhou on 2018-11-17.
//  Copyright © 2018 none. All rights reserved.
//

#ifndef Light_hpp
#define Light_hpp
#include <glm/glm.hpp>

class Light {
public:
    Light(glm::vec3 p, glm::vec3 c) : m_position(p), m_color(c) {}
    
    inline glm::vec3 getPosition() {
        return m_position;
    }
    inline void setPosition(glm::vec3 p) {
        m_position = p;
    }
    inline glm::vec3 getColor() {
        return m_color;
    }
    inline void setColor(glm::vec3 c) {
        m_color = c;
    }
private:
    glm::vec3 m_position;
    glm::vec3 m_color;
};

#endif /* Light_hpp */
