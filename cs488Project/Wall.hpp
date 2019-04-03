//
//  Wall.hpp
//  cs488Project
//
//  Created by Chang Zhou on 2018-11-26.
//  Copyright © 2018 none. All rights reserved.
//

#ifndef Wall_hpp
#define Wall_hpp

#include "cs488-framework/ShaderProgram.hpp"
#include <stdio.h>
#include "RawModel.hpp"
#include "Loader.hpp"
class Wall {
public:
    static RawModel generateSingleWallModel(ShaderProgram &m_shader, Loader *loader);
    static RawModel generateSingleTargetModel(ShaderProgram &m_shader, Loader *loader);
};
#endif /* Wall_hpp */
