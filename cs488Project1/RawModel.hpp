//
//  RawModel.h
//  cs488Project
//
//  Created by Chang Zhou on 2018-11-12.
//  Copyright © 2018 none. All rights reserved.
//

#ifndef RawModel_hpp
#define RawModel_hpp
#include <GLFW/glfw3.h>

class RawModel
{
public:
    RawModel(){};
    RawModel(GLuint &vaoID, int &vertexCount) : m_vaoID(vaoID), m_vertexCount(vertexCount) {}
    
    inline GLuint getVaoID() { return m_vaoID; }
    inline int getVertexCount() { return m_vertexCount; }
private:
    GLuint m_vaoID;
    int m_vertexCount;
};

#endif /* RawModel_h */
