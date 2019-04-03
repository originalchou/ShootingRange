//
//  GenerateBulletHole.cpp
//  cs488Project
//
//  Created by Chang Zhou on 2018-11-28.
//  Copyright © 2018 none. All rights reserved.
//

#include "GenerateBulletHole.hpp"
#include "RawModel.hpp"
#include "ModelTexture.hpp"
#include "TexturedModel.hpp"
void GenerateBulletHole::generateHole(std::vector<MyEntity> &bulletHoles, glm::vec3 pos, glm::vec3 normal, ShaderProgram &m_shader, Loader *m_loader, bool hitTarget) {
    glm::vec3 nv1(glm::normalize(glm::cross(glm::vec3(1,0,0), normal)));
    glm::vec3 nv2(glm::normalize(glm::cross(nv1, normal)));
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> texturecoords = {
        glm::vec2(0,0),
        glm::vec2(0,1),
        glm::vec2(1,1),
        glm::vec2(1,0)
    };
    std::vector<int>indices = {
        0,1,2,
        2,3,0
    };

    vertices.push_back(glm::vec3(pos + nv1));
    vertices.push_back(glm::vec3(pos - nv2));
    vertices.push_back(glm::vec3(pos - nv1));
    vertices.push_back(glm::vec3(pos + nv2));
    
    normals.push_back(normal);
    normals.push_back(normal);
    normals.push_back(normal);
    normals.push_back(normal);
    
    RawModel hole_raw_model = m_loader->loadToVAO(vertices, texturecoords, normals, indices, m_shader);
    ModelTexture hole_texture = ModelTexture(m_loader->loadTexture("bullethole"), 0.2, 1);
    TexturedModel hole_textured_model = TexturedModel(hole_raw_model, hole_texture);
    glm::vec3 p(0.0, 0.0, 0.0);
    glm::vec3 r(0.0, 0.0, 0.0);
    glm::vec3 s(1.0, 1.0, 1.0);
    MyEntity hole(hole_textured_model, p, r, s);
    if (hitTarget) {
        hole.setLastFrame(1);
    }
    bulletHoles.push_back(hole);
}
