//
//  MasterRender.hpp
//  cs488Project
//
//  Created by Chang Zhou on 2018-11-17.
//  Copyright © 2018 none. All rights reserved.
//

#ifndef MasterRender_hpp
#define MasterRender_hpp

#include <map>
#include "cs488-framework/ShaderProgram.hpp"
#include "Light.hpp"
#include "FPSCamera.hpp"
#include "MyEntity.hpp"
#include "Render.hpp"
#include "WeaponRender.hpp"
#include "TexturedModel.hpp"
#include "TerrainRender.hpp"
#include "SkyboxRender.hpp"
#include "Loader.hpp"
#include "AimCrossRender.hpp"

class MasterRender {
public:
    MasterRender(float aspectRatio, ShaderProgram &m_basicShader, ShaderProgram &m_terrainShader, ShaderProgram &m_weaponShader, ShaderProgram &m_skybox_shader, ShaderProgram &m_simple_shader, Loader *loader);
    virtual ~MasterRender();
    void render(Light& light, FPSCamera &camera);
    void processEntity(MyEntity &entity);
    void processTerrain(Terrain &terrain);
    void processWeapon(MyEntity &weapon);
private:
    const float m_FOV = 70;
    const float m_NEAR_PLANE = 0.1f;
    const float m_FAR_PLANE = 1000.0f;
    const float RED = 0.135;
    const float GREEN = 0.206;
    const float BLUE = 0.250;
    glm::mat4 m_projectionMatrix;
    ShaderProgram &m_basicShader;
    ShaderProgram &m_terrainShader;
    ShaderProgram &m_weaponShader;
    ShaderProgram &m_skyboxShader;
    ShaderProgram &m_simpleShader;
    Render m_entityRenderer;
    TerrainRender m_terrainRender;
    WeaponRender m_weaponRender;
    SkyboxRender m_skyboxRender;
    AimCrossRender m_aimCrossRender;
    
    std::vector<Terrain> terrains;
    MyEntity *m_weapon;
    tMap m_entities;
};

#endif /* MasterRender_hpp */
