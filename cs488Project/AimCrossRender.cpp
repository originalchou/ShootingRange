//
//  AimCrossRender.cpp
//  cs488Project
//
//  Created by Chang Zhou on 2018-12-02.
//  Copyright © 2018 none. All rights reserved.
//

#include "AimCrossRender.hpp"
AimCrossRender::AimCrossRender(Loader *m_loader, ShaderProgram &simple_shader):m_loader(m_loader), m_simple_shader(simple_shader) {
    std::vector<glm::vec2> vertices = {
        glm::vec2(0, 0),
        glm::vec2(0, 0.05),
        glm::vec2(0, 0),
        glm::vec2(0, -0.05),
        glm::vec2(0, 0),
        glm::vec2(0.05, 0),
        glm::vec2(0, 0),
        glm::vec2(-0.05, 0)
    };
    m_cross = m_loader->loadToVAOAimCross(vertices, simple_shader);
}

void AimCrossRender::render() {
    m_simple_shader.enable();
    glBindVertexArray(m_cross.getVaoID());
    glEnableVertexAttribArray(m_simple_shader.getAttribLocation("position"));
    glDrawArrays(GL_LINES, 0, m_cross.getVertexCount());
    glDisableVertexAttribArray(m_simple_shader.getAttribLocation("position"));
    glBindVertexArray(0);
    m_simple_shader.disable();
}
