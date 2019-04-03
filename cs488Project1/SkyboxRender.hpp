//
//  SkyboxRender.hpp
//  cs488Project
//
//  Created by Chang Zhou on 2018-11-30.
//  Copyright © 2018 none. All rights reserved.
//

#ifndef SkyboxRender_hpp
#define SkyboxRender_hpp

#include <stdio.h>
#include "Loader.hpp"
#include "cs488-framework/ShaderProgram.hpp"
#include "RawModel.hpp"

class SkyboxRender {
public:
    SkyboxRender(Loader *m_loader, ShaderProgram &m_skybox_shader, glm::mat4 projectionM);
    virtual ~SkyboxRender();
    void render();
private:
    Loader *m_loader;
    ShaderProgram &m_skybox_shader;
    RawModel m_cube;
    GLuint texture;
};
#endif /* SkyboxRender_hpp */
