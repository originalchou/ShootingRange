//
//  Math.hpp
//  cs488Project
//
//  Created by Chang Zhou on 2018-11-16.
//  Copyright © 2018 none. All rights reserved.
//

#ifndef Math_hpp
#define Math_hpp

#include <stdio.h>
#include <glm/glm.hpp>

class Maths {
public:
    static glm::mat4 createTransformMatrix(glm::vec3& translation, glm::vec3& rotation, glm::vec3& scale);
};

#endif /* Math_hpp */
