//
//  ObjLoader.cpp
//  cs488Project
//
//  Created by Chang Zhou on 2018-11-17.
//  Copyright © 2018 none. All rights reserved.
//

#include "ObjLoader.hpp"
#include "ObjDecoder.hpp"
#include <stdio.h>
#include <iostream>

RawModel OBJLoader::loadObjModel(const std::string &fileName, Loader &loader, ShaderProgram &m_shader) {
    std::vector<glm::vec3> positions, normals;
    std::vector<glm::vec2> uvCoords;
    std::vector<int> indices;
    ObjDecoder::decode(fileName.c_str(), positions, normals, uvCoords, indices);
    return loader.loadToVAO(positions, uvCoords, normals, indices, m_shader);
}
