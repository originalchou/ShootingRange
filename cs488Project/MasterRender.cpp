//
//  MasterRender.cpp
//  cs488Project
//
//  Created by Chang Zhou on 2018-11-17.
//  Copyright © 2018 none. All rights reserved.
//
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include "MasterRender.hpp"
#include "cs488-framework/CS488Window.hpp"


MasterRender::MasterRender(float aspectRatio, ShaderProgram &basicShader, ShaderProgram &terrainShader, ShaderProgram &weaponShader, ShaderProgram &skyboxShader, ShaderProgram &simpleShader, Loader *loader)
: m_basicShader(basicShader), m_terrainShader(terrainShader), m_weaponShader(weaponShader), m_skyboxShader(skyboxShader), m_simpleShader(simpleShader),
m_projectionMatrix(glm::perspective(m_FOV, aspectRatio, m_NEAR_PLANE, m_FAR_PLANE)),
m_entityRenderer(Render(m_basicShader, m_projectionMatrix)),
m_weaponRender(WeaponRender(m_weaponShader, m_projectionMatrix)),
m_skyboxRender(SkyboxRender(loader, skyboxShader, m_projectionMatrix)),
m_aimCrossRender(AimCrossRender(loader, simpleShader)),
m_terrainRender(TerrainRender(m_terrainShader, m_projectionMatrix)) {
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glClearColor(RED, GREEN, BLUE, 0);
//    glEnable(GL_CULL_FACE);
//    glCullFace(GL_BACK);
    //antialias
//    glEnable(GL_MULTISAMPLE);
}

MasterRender::~MasterRender(){}

void MasterRender::render(Light& light, FPSCamera &camera)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    m_basicShader.enable();
    GLint uniformLocation_lightPositionVec = m_basicShader.getUniformLocation("lightPosition");
    glm::vec3 lightPosition = light.getPosition();
    glUniform3f(uniformLocation_lightPositionVec, lightPosition.x, lightPosition.y, lightPosition.z);
    GLint uniformLocation_lightColourVec = m_basicShader.getUniformLocation("lightColour");
    glm::vec3 lightColour = light.getColor();
    glUniform3f(uniformLocation_lightColourVec, lightColour.x, lightColour.y, lightColour.z);
    GLint uniformLocation_skyColourVec = m_basicShader.getUniformLocation("skyColor");
    glUniform3f(uniformLocation_skyColourVec, RED, GREEN, BLUE);
    GLint uniformLocation_viewMatrix = m_basicShader.getUniformLocation("view");
    glUniformMatrix4fv(uniformLocation_viewMatrix, 1, GL_FALSE,
                       glm::value_ptr(camera.getViewMatrix()));
    m_entityRenderer.render(m_entities);
    m_basicShader.disable();
    
    m_terrainShader.enable();
    uniformLocation_lightPositionVec = m_terrainShader.getUniformLocation("lightPosition");
    glUniform3f(uniformLocation_lightPositionVec, lightPosition.x, lightPosition.y, lightPosition.z);
    uniformLocation_lightColourVec = m_terrainShader.getUniformLocation("lightColour");
    glUniform3f(uniformLocation_lightColourVec, lightColour.x, lightColour.y, lightColour.z);
    uniformLocation_skyColourVec = m_terrainShader.getUniformLocation("skyColor");
    glUniform3f(uniformLocation_skyColourVec, RED, GREEN, BLUE);
    uniformLocation_viewMatrix = m_terrainShader.getUniformLocation("view");
    glUniformMatrix4fv(uniformLocation_viewMatrix, 1, GL_FALSE,
                       glm::value_ptr(camera.getViewMatrix()));
    m_terrainRender.render(terrains);
    m_terrainShader.disable();
    
    m_weaponShader.enable();
    uniformLocation_lightPositionVec = m_weaponShader.getUniformLocation("lightPosition");
    glUniform3f(uniformLocation_lightPositionVec, lightPosition.x, lightPosition.y, lightPosition.z);
    uniformLocation_lightColourVec = m_weaponShader.getUniformLocation("lightColour");
    glUniform3f(uniformLocation_lightColourVec, lightColour.x, lightColour.y, lightColour.z);
//    uniformLocation_viewMatrix = m_terrainShader.getUniformLocation("view");
//    glUniformMatrix4fv(uniformLocation_viewMatrix, 1, GL_FALSE,
//                       glm::value_ptr(camera.getViewMatrix()));
    m_weaponRender.render(*m_weapon, camera);
    m_weaponShader.disable();
    
    m_skyboxShader.enable();
    uniformLocation_viewMatrix = m_skyboxShader.getUniformLocation("view");
    glUniformMatrix4fv(uniformLocation_viewMatrix, 1, GL_FALSE,
                       glm::value_ptr(camera.getViewMatrix()));
    m_skyboxRender.render();
    m_skyboxShader.disable();
    
    m_simpleShader.enable();
    m_aimCrossRender.render();
    m_simpleShader.disable();
    
    m_entities.clear();
    terrains.clear();
}

void MasterRender::processEntity(MyEntity &entity) {
    TexturedModel texturedModel = entity.getModel();
    m_entities.insert(tMap::value_type(texturedModel, std::vector<MyEntity>()));
    m_entities[texturedModel].push_back(entity);
}

void MasterRender::processTerrain(Terrain &terrain) {
    terrains.push_back(terrain);
}

void MasterRender::processWeapon(MyEntity &weapon) {
    m_weapon = &weapon;
}

