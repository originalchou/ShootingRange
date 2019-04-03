//
//  Wall.cpp
//  cs488Project
//
//  Created by Chang Zhou on 2018-11-26.
//  Copyright © 2018 none. All rights reserved.
//

#include "Wall.hpp"
#include <vector>
#include <glm/glm.hpp>
RawModel Wall::generateSingleWallModel(ShaderProgram &m_shader, Loader *loader) {
    std::vector<glm::vec3> triangleVertices = {
        // Construct equalaterial triangle
        //front
        glm::vec3(-0.5f, 0.5f, -0.5f),
        glm::vec3(-0.5f, -0.5f, -0.5f),
        glm::vec3(0.5f, -0.5f, -0.5f),
        glm::vec3(0.5f, 0.5f, -0.5f),
        //left
        glm::vec3(-0.5f, 0.5f, 0.5f),
        glm::vec3(-0.5f, -0.5f, 0.5f),
        glm::vec3(-0.5f, -0.5f, -0.5f),
        glm::vec3(-0.5f, 0.5f, -0.5f),
        //right
        glm::vec3(0.5f, 0.5f, -0.5f),
        glm::vec3(0.5f, -0.5f, -0.5f),
        glm::vec3(0.5f, -0.5f, 0.5f),
        glm::vec3(0.5f, 0.5f, 0.5f),
        //back
        glm::vec3(0.5f, 0.5f, 0.5f),
        glm::vec3(0.5f, -0.5f, 0.5f),
        glm::vec3(-0.5f, -0.5f, 0.5f),
        glm::vec3(-0.5f, 0.5f, 0.5f),
        
        glm::vec3(-0.5f, 0.5f, 0.5f),
        glm::vec3(-0.5f, 0.5f, -0.5f),
        glm::vec3(0.5f, 0.5f, -0.5f),
        glm::vec3(0.5f, 0.5f, 0.5f),
        
        glm::vec3(-0.5f, -0.5f, 0.5f),
        glm::vec3(-0.5f, -0.5f, -0.5f),
        glm::vec3(0.5f, -0.5f, -0.5f),
        glm::vec3(0.5f, -0.5f, 0.5f)
    };
    
    std::vector<int> indices = {
        0,1,3,
        3,1,2,
        
        4,5,7,
        7,5,6,
        
        8,9,11,
        11,9,10,
        
        12,13,15,
        15,13,14,
        
        16,17,19,
        19,17,18,
        
        20,21,23,
        23,21,22
    };
    
    std::vector<glm::vec3> normals = {
        glm::vec3(0, 0, -1),
        glm::vec3(0, 0, -1),
        glm::vec3(0, 0, -1),
        glm::vec3(0, 0, -1),
        
        glm::vec3(-1, 0, 0),
        glm::vec3(-1, 0, 0),
        glm::vec3(-1, 0, 0),
        glm::vec3(-1, 0, 0),

        glm::vec3(1, 0, 0),
        glm::vec3(1, 0, 0),
        glm::vec3(1, 0, 0),
        glm::vec3(1, 0, 0),

        glm::vec3(0, 0, 1),
        glm::vec3(0, 0, 1),
        glm::vec3(0, 0, 1),
        glm::vec3(0, 0, 1),

        glm::vec3(0, 1, 0),
        glm::vec3(0, 1, 0),
        glm::vec3(0, 1, 0),
        glm::vec3(0, 1, 0),

        glm::vec3(0, -1, 0),
        glm::vec3(0, -1, 0),
        glm::vec3(0, -1, 0),
        glm::vec3(0, -1, 0)

//        glm::vec3(1, 0, 0),
//        glm::vec3(1, 0, 0),
//        
//        glm::vec3(1, 0, 0),
//        glm::vec3(1, 0, 0)
        
//        glm::vec3(0, 1, 0),
//        glm::vec3(0, 1, 0),
//        glm::vec3(0, 1, 0),
//        glm::vec3(0, 1, 0),
//        glm::vec3(0, -1, 0),
//        glm::vec3(0, -1, 0),
//        glm::vec3(0, -1, 0),
//        glm::vec3(0, -1, 0)
    };
    
    std::vector<glm::vec2> textureCoords = {
        glm::vec2(0, 0),
        glm::vec2(0, 1),
        glm::vec2(1, 1),
        glm::vec2(1, 0),
        
        glm::vec2(0, 0),
        glm::vec2(0, 1),
        glm::vec2(1, 1),
        glm::vec2(1, 0),
        
        glm::vec2(0, 0),
        glm::vec2(0, 1),
        glm::vec2(1, 1),
        glm::vec2(1, 0),
        
        glm::vec2(0, 0),
        glm::vec2(0, 1),
        glm::vec2(1, 1),
        glm::vec2(1, 0),
        
        glm::vec2(0, 0),
        glm::vec2(0, 1),
        glm::vec2(1, 1),
        glm::vec2(1, 0),
        
        glm::vec2(0, 0),
        glm::vec2(0, 1),
        glm::vec2(1, 1),
        glm::vec2(1, 0)
    };
    return loader->loadToVAO(triangleVertices, textureCoords, normals, indices, m_shader);
}

RawModel Wall::generateSingleTargetModel(ShaderProgram &m_shader, Loader *loader) {
    std::vector<glm::vec3> triangleVertices = {
        // Construct equalaterial triangle
        //front
        glm::vec3(-0.5f, 0.5f, -0.5f),
        glm::vec3(-0.5f, -0.5f, -0.5f),
        glm::vec3(0.5f, -0.5f, -0.5f),
        glm::vec3(0.5f, 0.5f, -0.5f),
        //left
        glm::vec3(-0.5f, 0.5f, 0.5f),
        glm::vec3(-0.5f, -0.5f, 0.5f),
        glm::vec3(-0.5f, -0.5f, -0.5f),
        glm::vec3(-0.5f, 0.5f, -0.5f),
        //right
        glm::vec3(0.5f, 0.5f, -0.5f),
        glm::vec3(0.5f, -0.5f, -0.5f),
        glm::vec3(0.5f, -0.5f, 0.5f),
        glm::vec3(0.5f, 0.5f, 0.5f),
        //back
        glm::vec3(0.5f, 0.5f, 0.5f),
        glm::vec3(0.5f, -0.5f, 0.5f),
        glm::vec3(-0.5f, -0.5f, 0.5f),
        glm::vec3(-0.5f, 0.5f, 0.5f),
        
        glm::vec3(-0.5f, 0.5f, 0.5f),
        glm::vec3(-0.5f, 0.5f, -0.5f),
        glm::vec3(0.5f, 0.5f, -0.5f),
        glm::vec3(0.5f, 0.5f, 0.5f),
        
        glm::vec3(-0.5f, -0.5f, 0.5f),
        glm::vec3(-0.5f, -0.5f, -0.5f),
        glm::vec3(0.5f, -0.5f, -0.5f),
        glm::vec3(0.5f, -0.5f, 0.5f)
    };
    
    std::vector<int> indices = {
        0,1,3,
        3,1,2,
        
        4,5,7,
        7,5,6,
        
        8,9,11,
        11,9,10,
        
        12,13,15,
        15,13,14,
        
        16,17,19,
        19,17,18,
        
        20,21,23,
        23,21,22
    };
    
    std::vector<glm::vec3> normals = {
        glm::vec3(0, 0, -1),
        glm::vec3(0, 0, -1),
        glm::vec3(0, 0, -1),
        glm::vec3(0, 0, -1),
        
        glm::vec3(-1, 0, 0),
        glm::vec3(-1, 0, 0),
        glm::vec3(-1, 0, 0),
        glm::vec3(-1, 0, 0),
        
        glm::vec3(1, 0, 0),
        glm::vec3(1, 0, 0),
        glm::vec3(1, 0, 0),
        glm::vec3(1, 0, 0),
        
        glm::vec3(0, 0, 1),
        glm::vec3(0, 0, 1),
        glm::vec3(0, 0, 1),
        glm::vec3(0, 0, 1),
        
        glm::vec3(0, 1, 0),
        glm::vec3(0, 1, 0),
        glm::vec3(0, 1, 0),
        glm::vec3(0, 1, 0),
        
        glm::vec3(0, -1, 0),
        glm::vec3(0, -1, 0),
        glm::vec3(0, -1, 0),
        glm::vec3(0, -1, 0)
        
        //        glm::vec3(1, 0, 0),
        //        glm::vec3(1, 0, 0),
        //
        //        glm::vec3(1, 0, 0),
        //        glm::vec3(1, 0, 0)
        
        //        glm::vec3(0, 1, 0),
        //        glm::vec3(0, 1, 0),
        //        glm::vec3(0, 1, 0),
        //        glm::vec3(0, 1, 0),
        //        glm::vec3(0, -1, 0),
        //        glm::vec3(0, -1, 0),
        //        glm::vec3(0, -1, 0),
        //        glm::vec3(0, -1, 0)
    };
    
    std::vector<glm::vec2> textureCoords = {
        glm::vec2(0, 0),
        glm::vec2(0, 0),
        glm::vec2(0, 0),
        glm::vec2(0, 0),
        
        glm::vec2(0, 0),
        glm::vec2(0, 1),
        glm::vec2(1, 1),
        glm::vec2(1, 0),

        glm::vec2(0, 0),
        glm::vec2(0, 1),
        glm::vec2(1, 1),
        glm::vec2(1, 0),

        glm::vec2(0, 0),
        glm::vec2(0, 0),
        glm::vec2(0, 0),
        glm::vec2(0, 0),
        
        glm::vec2(0, 0),
        glm::vec2(0, 0),
        glm::vec2(0, 0),
        glm::vec2(0, 0),

        glm::vec2(0, 0),
        glm::vec2(0, 0),
        glm::vec2(0, 0),
        glm::vec2(0, 0)
    };
    return loader->loadToVAO(triangleVertices, textureCoords, normals, indices, m_shader);
}
