//
//  Render.hpp
//  cs488Project
//
//  Created by Chang Zhou on 2018-11-14.
//  Copyright © 2018 none. All rights reserved.
//

#ifndef Render_hpp
#define Render_hpp

#include <map>
#include <glm/gtx/transform.hpp>
#include <cs488-framework/ShaderProgram.hpp>
#include "RawModel.hpp"
#include "TexturedModel.hpp"
#include "MyEntity.hpp"

struct tmCompare {
public:
    bool operator() (const TexturedModel& t1, const TexturedModel& t2) const
    {
        return ((t1.getRawModel().getVaoID() < t2.getRawModel().getVaoID()) ||
                (t1.getModelTexture().getTextureID() < t2.getModelTexture().getTextureID()));
    }
};

typedef std::map<TexturedModel, std::vector<MyEntity>, tmCompare> tMap;

class Render {
public:
    Render(ShaderProgram &m_shader, glm::mat4 projectionM);
    virtual ~Render();
    void render(tMap &entities);
private:
    
    ShaderProgram &m_shader;
    void bindTexturedModel(TexturedModel texturedModel);
    void unbindTexturedModel();
    void renderEntity(MyEntity &entity);
};
#endif /* Render_hpp */
