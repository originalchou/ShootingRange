//
//  TerrainRender.cpp
//  cs488Project
//
//  Created by Chang Zhou on 2018-11-17.
//  Copyright © 2018 none. All rights reserved.
//

#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "TerrainRender.hpp"
#include "Math.hpp"

TerrainRender::TerrainRender(ShaderProgram &terrainShader, glm::mat4 projectionM):m_terrainShader(terrainShader) {
    m_terrainShader.enable();
    GLint uniformLocation_projectionMatrix = m_terrainShader.getUniformLocation("projection");
    glUniformMatrix4fv(uniformLocation_projectionMatrix, 1, GL_FALSE,
                       glm::value_ptr(projectionM));
    m_terrainShader.disable();
}

TerrainRender::~TerrainRender(){}

void TerrainRender::render(std::vector<Terrain> &terrains) {
    for (Terrain& terrain : terrains) {
        bindTerrain(terrain);
        renderTerrain(terrain);
        unbindTerrain();
    }
}

void TerrainRender::bindTerrain(Terrain &terrain) {
    RawModel model = terrain.getModel();
    ModelTexture texture = terrain.getTexture();
    glBindVertexArray(model.getVaoID());
    glEnableVertexAttribArray(m_terrainShader.getAttribLocation("position"));
    glEnableVertexAttribArray(m_terrainShader.getAttribLocation("normal"));
    glEnableVertexAttribArray(m_terrainShader.getAttribLocation("textureCoords"));
    GLint uniformLocation_shineDamper = m_terrainShader.getUniformLocation("shineDamper");
    GLint uniformLocation_reflectivity = m_terrainShader.getUniformLocation("reflectivity");
    glUniform1f(uniformLocation_shineDamper, texture.getShineDamper());
    glUniform1f(uniformLocation_reflectivity, texture.getReflectivity());
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture.getTextureID());
}

void TerrainRender::unbindTerrain() {
    glDisableVertexAttribArray(m_terrainShader.getAttribLocation("position"));
    glDisableVertexAttribArray(m_terrainShader.getAttribLocation("normal"));
    glDisableVertexAttribArray(m_terrainShader.getAttribLocation("textureCoords"));
    glBindVertexArray(0);
}

void TerrainRender::renderTerrain(Terrain &terrain) {
    glm::vec3 p(terrain.getX(), 0.0, terrain.getZ());
    glm::vec3 r(0, 0, 0);
    glm::vec3 s(1, 1, 1);
    glm::mat4 transM = Maths::createTransformMatrix(p, r, s);
    GLint uniformLocation_modelMatrix = m_terrainShader.getUniformLocation("transform");
    glUniformMatrix4fv(uniformLocation_modelMatrix, 1, GL_FALSE,
                       glm::value_ptr(transM));
    glDrawElements(GL_TRIANGLES, terrain.getModel().getVertexCount(), GL_UNSIGNED_INT, 0);
}
