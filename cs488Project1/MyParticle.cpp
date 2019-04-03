//
//  MyParticle.cpp
//  cs488Project
//
//  Created by Chang Zhou on 2018-11-30.
//  Copyright © 2018 none. All rights reserved.
//

#include "MyParticle.hpp"
void MyParticle::moveParticle() {
    m_position += m_speed;
    m_speed.y -= gravityEffect;
}
