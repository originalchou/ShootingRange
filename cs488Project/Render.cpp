//
//  Render.cpp
//  cs488Project
//
//  Created by Chang Zhou on 2018-11-14.
//  Copyright © 2018 none. All rights reserved.
//
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include "Math.hpp"
#include "Render.hpp"
#include "MyEntity.hpp"

Render::Render(ShaderProgram &m_shader, glm::mat4 projectionM): m_shader(m_shader) {
    m_shader.enable();
    GLint uniformLocation_projectionMatrix = m_shader.getUniformLocation("projection");
    glUniformMatrix4fv(uniformLocation_projectionMatrix, 1, GL_FALSE,
                       glm::value_ptr(projectionM));
    m_shader.disable();
}

Render::~Render(){}

void Render::render(tMap &entities) {
    for (auto &key: entities) {
        bindTexturedModel(key.first);
        for (MyEntity entity : key.second) {
            renderEntity(entity);
        }
        unbindTexturedModel();
    }
}

void Render::bindTexturedModel(TexturedModel texturedModel) {
    RawModel model = texturedModel.getRawModel();
    ModelTexture texture = texturedModel.getModelTexture();
    glBindVertexArray(model.getVaoID());
    glEnableVertexAttribArray(m_shader.getAttribLocation("position"));
    glEnableVertexAttribArray(m_shader.getAttribLocation("normal"));
    glEnableVertexAttribArray(m_shader.getAttribLocation("textureCoords"));
    GLint uniformLocation_shineDamper = m_shader.getUniformLocation("shineDamper");
    GLint uniformLocation_reflectivity = m_shader.getUniformLocation("reflectivity");
    glUniform1f(uniformLocation_shineDamper, texture.getShineDamper());
    glUniform1f(uniformLocation_reflectivity, texture.getReflectivity());
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texturedModel.getModelTexture().getTextureID());
}

void Render::unbindTexturedModel() {
    glDisableVertexAttribArray(m_shader.getAttribLocation("position"));
    glDisableVertexAttribArray(m_shader.getAttribLocation("normal"));
    glDisableVertexAttribArray(m_shader.getAttribLocation("textureCoords"));
    glBindVertexArray(0);
}

void Render::renderEntity(MyEntity &entity) {
    glm::vec3 p = entity.getPosition();
    glm::vec3 r = entity.getRotation();
    glm::vec3 s = entity.getScale();
    glm::mat4 transM = Maths::createTransformMatrix(p, r, s);
    GLint uniformLocation_modelMatrix = m_shader.getUniformLocation("transform");
    glUniformMatrix4fv(uniformLocation_modelMatrix, 1, GL_FALSE,
                       glm::value_ptr(transM));
    glDrawElements(GL_TRIANGLES, entity.getModel().getRawModel().getVertexCount(), GL_UNSIGNED_INT, 0);
}
