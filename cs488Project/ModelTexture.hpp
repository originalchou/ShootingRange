//
//  ModelTexture.h
//  cs488Project
//
//  Created by Chang Zhou on 2018-11-16.
//  Copyright © 2018 none. All rights reserved.
//

#ifndef ModelTexture_hpp
#define ModelTexture_hpp
//#include <GLFW/glfw3.h>

class ModelTexture {
public:
    ModelTexture(GLuint ID) {textureID = ID;}
    ModelTexture(GLuint ID, float reflectivity, float shineDamper)
    {
        textureID = ID;
        m_shineDamper = shineDamper;
        m_reflectivity = reflectivity;
    }
    inline GLuint getTextureID() {return textureID;}
    inline float getShineDamper() { return m_shineDamper; }
    inline void setShineDamper(float s) { m_shineDamper = s; }
    inline float getReflectivity() { return m_reflectivity; }
    inline void setReflectivity(float s) { m_reflectivity = s; }
private:
    GLuint textureID;
    float m_shineDamper;
    float m_reflectivity;
};

#endif /* ModelTexture_hpp */
