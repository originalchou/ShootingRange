//
//  Loader.hpp
//  cs488Project
//
//  Created by Chang Zhou on 2018-11-12.
//  Copyright © 2018 none. All rights reserved.
//

#ifndef Loader_hpp
#define Loader_hpp

#include "cs488-framework/ShaderProgram.hpp"
#include <stdio.h>
#include <vector>
#include <glm/glm.hpp>
#include "RawModel.hpp"

class Loader {
public:
    Loader();
    virtual ~Loader();
    
//    RawModel LoadToVAO(std::vector<glm::vec3> vertices, std::vector<glm::vec3> normals, std::vector<int> indices);
    RawModel loadToVAO(std::vector<glm::vec3> vertices, std::vector<glm::vec2> textureCoords, std::vector<glm::vec3>normals, std::vector<int> indices, ShaderProgram &m_shader);
    RawModel loadToVAOSkybox(std::vector<glm::vec3> positions, ShaderProgram &m_skybox_shader);
    RawModel loadToVAOAimCross(std::vector<glm::vec2> vertices, ShaderProgram &simple_shader);
    GLuint loadTexture(const std::string& fileName, bool repeat = false);
    GLuint loadCubeMap(std::vector<std::string> &fileNames, bool repeat);
    inline void unbindVAO() { glBindVertexArray(0); }
private:
    std::vector<GLuint> m_vaos;
    std::vector<GLuint> m_vbos;
    std::vector<GLuint> m_textures;
    GLuint createVao();
    void storeDataInAttrList(GLuint attributeNumber, int attributeSize, void *data, int dataSize);
    void bindIndicesBuffer(int* indices, int& count);
};
#endif /* Loader_hpp */
