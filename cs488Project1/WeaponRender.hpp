//
//  WeaponRender.hpp
//  cs488Project
//
//  Created by Chang Zhou on 2018-11-25.
//  Copyright © 2018 none. All rights reserved.
//

#ifndef WeaponRender_hpp
#define WeaponRender_hpp

#include <stdio.h>
#include <map>
#include <glm/gtx/transform.hpp>
#include <cs488-framework/ShaderProgram.hpp>
#include "RawModel.hpp"
#include "TexturedModel.hpp"
#include "MyEntity.hpp"
#include "FPSCamera.hpp"


class WeaponRender {
public:
    WeaponRender(ShaderProgram &m_weapon_shader, glm::mat4 projectionM);
    virtual ~WeaponRender();
    void render(MyEntity &weapon, FPSCamera &camera);
private:
    
    ShaderProgram &m_weapon_shader;
    void bindTexturedModel(TexturedModel texturedModel);
    void unbindTexturedModel();
};
#endif /* WeaponRender_hpp */
