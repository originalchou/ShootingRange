//
//  CheckHit.cpp
//  cs488Project
//
//  Created by Chang Zhou on 2018-11-26.
//  Copyright © 2018 none. All rights reserved.
//

#include "CheckHit.hpp"
int CheckHit::checkHit(glm::vec3 pos, double boundSize, std::vector<MyEntity> &targets, bool hitByBullet) {
    int ret = 0;
    double bound = boundSize;
    double camPos_bound_max_x = pos.x + bound;
    double camPos_bound_max_z = pos.z + bound;
    double camPos_bound_min_x = pos.x - bound;
    double camPos_bound_min_z = pos.z - bound;
    //wall
    if (camPos_bound_max_x > 190 || camPos_bound_max_z > 190) {
        ret = 1;
    }
    if (camPos_bound_min_x < 10 || camPos_bound_min_z < 10) {
        ret = 1;
    }
    
    //internal wall 65,65 135,65 65,135 135,135
    if (camPos_bound_max_x > 45 && camPos_bound_min_x < 85 && camPos_bound_max_z > 45 && camPos_bound_min_z < 85) {
        ret = 1;
    }
    if (camPos_bound_max_x > 115 && camPos_bound_min_x < 155 && camPos_bound_max_z > 45 && camPos_bound_min_z < 85) {
        ret = 1;
    }
    if (camPos_bound_max_x > 45 && camPos_bound_min_x < 85 && camPos_bound_max_z > 115 && camPos_bound_min_z < 155) {
        ret = 1;
    }
    if (camPos_bound_max_x > 115 && camPos_bound_min_x < 155 && camPos_bound_max_z > 115 && camPos_bound_min_z < 155) {
        ret = 1;
    }
    if (pos.y < 0) {
        ret = 1;
    }
    if (!checkHitWithTarget(pos, targets, boundSize, hitByBullet)) {
        ret = 2;
    }
    
//    maxx1 > minx2 && minx1 < maxx2 && maxy1 > miny1 && miny1 < maxy2
    return ret;
}

bool CheckHit::checkHitWithTarget(glm::vec3 pos, std::vector<MyEntity> &targets, double boundSize, bool hitByBullet) {
    bool ret = true;
    double bound = boundSize;
    double pos_bound_max_x = pos.x + bound;
    double pos_bound_max_y = pos.y + bound;
    double pos_bound_max_z = pos.z + bound;
    double pos_bound_min_x = pos.x - bound;
    double pos_bound_min_z = pos.z - bound;
    double pos_bound_min_y = pos.y - bound;
    for (int i = 0; i < targets.size(); i++) {
        MyEntity &target = targets.at(i);
        double target_max_x = target.getPosition().x + 0.5;
        double target_max_z = target.getPosition().z + 3.25;
        double target_min_x = target.getPosition().x - 0.5;
        double target_min_z = target.getPosition().z - 3.25;
        if (target.getHit()) {
            continue;
        }
        if (pos_bound_max_x > target_min_x && pos_bound_min_x < target_max_x && pos_bound_max_z > target_min_z && pos_bound_min_z < target_max_z
            && pos_bound_max_y > 0 && pos_bound_min_y < 15) {
            ret = false;
            if (hitByBullet) {
                target.setHit(true);
            }
        }
    }
    return ret;
}
