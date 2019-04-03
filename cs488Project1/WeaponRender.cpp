//
//  WeaponRender.cpp
//  cs488Project
//
//  Created by Chang Zhou on 2018-11-25.
//  Copyright © 2018 none. All rights reserved.
//

#include "WeaponRender.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include "Math.hpp"
#include "MyEntity.hpp"
WeaponRender::WeaponRender(ShaderProgram &m_weapon_shader, glm::mat4 projectionM): m_weapon_shader(m_weapon_shader) {
    m_weapon_shader.enable();
    GLint uniformLocation_projectionMatrix = m_weapon_shader.getUniformLocation("projection");
    glUniformMatrix4fv(uniformLocation_projectionMatrix, 1, GL_FALSE,
                       glm::value_ptr(projectionM));
    m_weapon_shader.disable();
}

WeaponRender::~WeaponRender(){}

void WeaponRender::render(MyEntity &weapon, FPSCamera &camera) {
    bindTexturedModel(weapon.getModel());
    glm::vec3 p = weapon.getPosition();
    glm::vec3 r = weapon.getRotation();
    glm::vec3 s = weapon.getScale();
    glm::mat4 transM = Maths::createTransformMatrix(p, r, s);
    GLint uniformLocation_modelMatrix = m_weapon_shader.getUniformLocation("transform");
    glUniformMatrix4fv(uniformLocation_modelMatrix, 1, GL_FALSE,
                       glm::value_ptr(transM));
    GLint uniformLocation_camPosition = m_weapon_shader.getUniformLocation("camPosition");
    glUniform3f(uniformLocation_camPosition, camera.getPosition().x, camera.getPosition().y, camera.getPosition().z);
    glDrawElements(GL_TRIANGLES, weapon.getModel().getRawModel().getVertexCount(), GL_UNSIGNED_INT, 0);
    unbindTexturedModel();
}

void WeaponRender::bindTexturedModel(TexturedModel texturedModel) {
    RawModel model = texturedModel.getRawModel();
    ModelTexture texture = texturedModel.getModelTexture();
    glBindVertexArray(model.getVaoID());
    glEnableVertexAttribArray(m_weapon_shader.getAttribLocation("position"));
    glEnableVertexAttribArray(m_weapon_shader.getAttribLocation("normal"));
    glEnableVertexAttribArray(m_weapon_shader.getAttribLocation("textureCoords"));
    GLint uniformLocation_shineDamper = m_weapon_shader.getUniformLocation("shineDamper");
    GLint uniformLocation_reflectivity = m_weapon_shader.getUniformLocation("reflectivity");
    glUniform1f(uniformLocation_shineDamper, texture.getShineDamper());
    glUniform1f(uniformLocation_reflectivity, texture.getReflectivity());
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texturedModel.getModelTexture().getTextureID());
}

void WeaponRender::unbindTexturedModel() {
    glDisableVertexAttribArray(m_weapon_shader.getAttribLocation("position"));
    glDisableVertexAttribArray(m_weapon_shader.getAttribLocation("normal"));
    glDisableVertexAttribArray(m_weapon_shader.getAttribLocation("textureCoords"));
    glBindVertexArray(0);
}
