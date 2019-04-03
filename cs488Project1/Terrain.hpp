//
//  Terrain.hpp
//  cs488Project
//
//  Created by Chang Zhou on 2018-11-17.
//  Copyright © 2018 none. All rights reserved.
//

#ifndef Terrain_hpp
#define Terrain_hpp

#include <stdio.h>
#include "RawModel.hpp"
#include "ModelTexture.hpp"
#include "Loader.hpp"
#include "cs488-framework/ShaderProgram.hpp"

class Terrain {
public:
    Terrain(int gridX, int gridZ, Loader& loader, ModelTexture texture, ShaderProgram &terrainShader);
    virtual ~Terrain();
    
    inline float getX() { return m_x; }
    inline float getZ() { return m_z; }
    inline RawModel getModel() { return m_model; }
    inline ModelTexture getTexture() { return m_texture; }
private:
    const float SIZE = 200;
    const int VERTEX_COUNT = 128;
    float m_x, m_z;
    RawModel m_model;
    ModelTexture m_texture;
    RawModel generateTerrain(Loader& loader);
    ShaderProgram &m_terrainShader;
};

#endif /* Terrain_hpp */
