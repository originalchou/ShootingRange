//
//  ObjLoader.hpp
//  cs488Project
//
//  Created by Chang Zhou on 2018-11-17.
//  Copyright © 2018 none. All rights reserved.
//

#ifndef ObjLoader_hpp
#define ObjLoader_hpp

#include <cs488-framework/ShaderProgram.hpp>
#include <stdio.h>
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include "Loader.hpp"
#include "RawModel.hpp"

class OBJLoader {
public:
    static RawModel loadObjModel(const std::string& fileName, Loader& loader, ShaderProgram &m_shader);
};
#endif /* ObjLoader_hpp */
