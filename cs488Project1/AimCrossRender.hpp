//
//  AimCrossRender.hpp
//  cs488Project
//
//  Created by Chang Zhou on 2018-12-02.
//  Copyright © 2018 none. All rights reserved.
//

#ifndef AimCrossRender_hpp
#define AimCrossRender_hpp

#include <stdio.h>
#include "Loader.hpp"
#include "glm/glm.hpp"

class AimCrossRender {
public:
    AimCrossRender(Loader *m_loader, ShaderProgram &simple_shader);
    virtual ~AimCrossRender(){};
    void render();
private:
    Loader *m_loader;
    ShaderProgram &m_simple_shader;
    RawModel m_cross;
};

#endif /* AimCrossRender_hpp */
