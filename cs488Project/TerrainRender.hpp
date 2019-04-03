//
//  TerrainRender.hpp
//  cs488Project
//
//  Created by Chang Zhou on 2018-11-17.
//  Copyright © 2018 none. All rights reserved.
//

#ifndef TerrainRender_hpp
#define TerrainRender_hpp

#include <stdio.h>
#include <glm/glm.hpp>
#include "cs488-framework/ShaderProgram.hpp"
#include "Terrain.hpp"

class TerrainRender {
public:
    TerrainRender(ShaderProgram &terrainShader, glm::mat4 projectionM);
    virtual ~TerrainRender();
    
    void render(std::vector<Terrain> &terrains);
private:
    ShaderProgram& m_terrainShader;
    void bindTerrain(Terrain &terrain);
    void unbindTerrain();
    void renderTerrain(Terrain &terrain);
};
#endif /* TerrainRender_hpp */
