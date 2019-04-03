//
//  CheckHit.hpp
//  cs488Project
//
//  Created by Chang Zhou on 2018-11-26.
//  Copyright © 2018 none. All rights reserved.
//

#ifndef CheckHit_hpp
#define CheckHit_hpp

#include <stdio.h>
#include <glm/glm.hpp>
#include <vector>
#include "MyEntity.hpp"
class CheckHit {
public:
    static int checkHit(glm::vec3 pos, double boundSize, std::vector<MyEntity> &targets, bool hitByBullet);
private:
    static bool checkHitWithTarget(glm::vec3 pos, std::vector<MyEntity> &targets, double boundSize, bool hitByBullet);
};
#endif /* CheckHit_hpp */
