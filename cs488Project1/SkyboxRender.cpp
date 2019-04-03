//
//  SkyboxRender.cpp
//  cs488Project
//
//  Created by Chang Zhou on 2018-11-30.
//  Copyright © 2018 none. All rights reserved.
//

#include "SkyboxRender.hpp"
#include <glm/gtc/type_ptr.hpp>

SkyboxRender::SkyboxRender(Loader *m_loader, ShaderProgram &m_skybox_shader, glm::mat4 projectionM): m_loader(m_loader), m_skybox_shader(m_skybox_shader) {
    m_skybox_shader.enable();
    GLint uniformLocation_projectionMatrix = m_skybox_shader.getUniformLocation("projectionMatrix");
    glUniformMatrix4fv(uniformLocation_projectionMatrix, 1, GL_FALSE,
                       glm::value_ptr(projectionM));
    m_skybox_shader.disable();
    float size = 500.0f;
    std::vector<std::string> fileNames = {
        "right", "left", "top", "bottom", "back", "front"
    };
    std::vector<glm::vec3> vertices = {
        glm::vec3(-size,  size, -size),
        glm::vec3(-size,  -size, -size),
        glm::vec3(size,  -size, -size),
        glm::vec3(size,  -size, -size),
        glm::vec3(size,  size, -size),
        glm::vec3(-size,  size, -size),
        
        glm::vec3(-size,  -size, size),
        glm::vec3(-size,  -size, -size),
        glm::vec3(-size,  size, -size),
        glm::vec3(-size,  size, -size),
        glm::vec3(-size,  size, size),
        glm::vec3(-size,  -size, size),
        
        glm::vec3(size,  -size, -size),
        glm::vec3(size,  -size, size),
        glm::vec3(size,  size, size),
        glm::vec3(size,  size, size),
        glm::vec3(size,  size, -size),
        glm::vec3(size,  -size, -size),
        
        glm::vec3(-size,  -size, size),
        glm::vec3(-size,  size, size),
        glm::vec3(size,  size, size),
        glm::vec3(size,  size, size),
        glm::vec3(size,  -size, size),
        glm::vec3(-size,  -size, size),
        
        glm::vec3(-size,  size, -size),
        glm::vec3(size,  size, -size),
        glm::vec3(size,  size, size),
        glm::vec3(size,  size, size),
        glm::vec3(-size,  size, size),
        glm::vec3(-size,  size, -size),
        
        glm::vec3(-size,  -size, -size),
        glm::vec3(-size,  -size, size),
        glm::vec3(size,  -size, -size),
        glm::vec3(size,  -size, -size),
        glm::vec3(-size,  -size, size),
        glm::vec3(size,  -size, size)
    };
    m_cube = m_loader->loadToVAOSkybox(vertices, m_skybox_shader);
    texture = m_loader->loadCubeMap(fileNames, false);
}

SkyboxRender::~SkyboxRender(){}

void SkyboxRender::render() {
    m_skybox_shader.enable();
    glBindVertexArray(m_cube.getVaoID());
    glEnableVertexAttribArray(m_skybox_shader.getAttribLocation("position"));
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, texture);
    glDrawArrays(GL_TRIANGLES, 0, m_cube.getVertexCount());
    glDisableVertexAttribArray(m_skybox_shader.getAttribLocation("position"));
    glBindVertexArray(0);
    m_skybox_shader.disable();
}
