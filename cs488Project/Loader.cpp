//
//  Loader.cpp
//  cs488Project
//
//  Created by Chang Zhou on 2018-11-12.
//  Copyright © 2018 none. All rights reserved.
//

#include "Loader.hpp"
#include <cs488-framework/OpenGLImport.hpp>
#include <lodepng/lodepng.h>
#include <iostream>

Loader::Loader() {
    // Initialize the storage arrays
    m_vaos.clear();
    m_vbos.clear();
    m_textures.clear();
}

Loader::~Loader() {
    // Loop through all the storage arrays and delete OpenGL variables
    
    while (m_vbos.size() > 0) {
        glDeleteBuffers(1, &m_vbos.back());
        m_vbos.pop_back();
    }
    
    while (m_vaos.size() > 0) {
        glDeleteVertexArrays(1, &m_vaos.back());
        m_vaos.pop_back();
    }
    
    while (m_textures.size() > 0)
    {
        glDeleteTextures(1, &m_textures.back());
        m_textures.pop_back();
    }
}

RawModel Loader::loadToVAO(std::vector<glm::vec3> vertices, std::vector<glm::vec2> textureCoords, std::vector<glm::vec3> normals, std::vector<int> indices, ShaderProgram &m_shader) {
    GLuint vaoID = createVao();
    int indicesSize = (int)indices.size();
    bindIndicesBuffer(indices.data(), indicesSize);
    storeDataInAttrList(m_shader.getAttribLocation("position"), 3, vertices.data(), (int)vertices.size() * sizeof(glm::vec3));
    storeDataInAttrList(m_shader.getAttribLocation("normal"), 3, normals.data(), (int)normals.size() * sizeof(glm::vec3));
    storeDataInAttrList(m_shader.getAttribLocation("textureCoords"), 2, textureCoords.data(), (int)textureCoords.size() * sizeof(glm::vec2));
    unbindVAO();
    return RawModel(vaoID, indicesSize);
}

RawModel Loader::loadToVAOSkybox(std::vector<glm::vec3> vertices, ShaderProgram &m_skybox_shader) {
    GLuint vaoID = createVao();
    int verticesSize = (int)vertices.size();
    storeDataInAttrList(m_skybox_shader.getAttribLocation("position"), 3, vertices.data(), (int)vertices.size() * sizeof(glm::vec3));
    unbindVAO();
    return RawModel(vaoID, verticesSize);
}

RawModel Loader::loadToVAOAimCross(std::vector<glm::vec2> vertices, ShaderProgram &simple_shader) {
    GLuint vaoID = createVao();
    int verticesSize = (int)vertices.size();
    storeDataInAttrList(simple_shader.getAttribLocation("position"), 2, vertices.data(), (int)vertices.size() * sizeof(glm::vec2));
    unbindVAO();
    return RawModel(vaoID, verticesSize);
}

GLuint Loader::loadCubeMap(std::vector<std::string> &fileNames, bool repeat) {
    GLuint texture;
    glGenTextures(1, &texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, texture);
 
    for (int i = 0; i < fileNames.size(); i++) {
        std::string &fileName = fileNames.at(i);
        unsigned width, height;
        std::vector<unsigned char> imageData;
        unsigned error = lodepng::decode(imageData, width, height, ("Assets/" + fileName + ".png").c_str());
        if (imageData.empty()) {
            std::cerr << lodepng_error_text(error) << fileName << std::endl;
        }
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData.data());
    }
    glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    if (!repeat)
    {
        // Tell OpenGL to clamp textures to the edge (so you don't get transparent gaps)
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    }
    m_textures.push_back(texture);
    return texture;
}


GLuint Loader::loadTexture(const std::string& fileName, bool repeat)
{
    GLuint texture;
    unsigned width, height;
    
    // Load image data
    std::vector<unsigned char> imageData;
    unsigned error = lodepng::decode(imageData, width, height, ("Assets/" + fileName + ".png").c_str());
    
    if (imageData.empty())
        std::cerr << lodepng_error_text(error) << fileName << std::endl;
    
    // Generate and bind a OpenGL texture
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    
    // How OpenGL will fill an area that's to big or to small
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    // Allow repeating textures for terrain
    if (!repeat)
    {
        // Tell OpenGL to clamp textures to the edge (so you don't get transparent gaps)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    }
    
    // Store the OpenGL texture data
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData.data());
    
    // Store the buffer in the list
    m_textures.push_back(texture);
    
    return texture;
}

GLuint Loader::createVao() {
    GLuint vaoID;
    glGenVertexArrays(1, &vaoID);
    m_vaos.push_back(vaoID);
    glBindVertexArray(vaoID);
    return vaoID;
}

void Loader::storeDataInAttrList(GLuint attributeNumber, int attributeSize, void *data, int dataSize) {
    GLuint vboID;
    glGenBuffers(1, &vboID);
    m_vbos.push_back(vboID);
    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glBufferData(GL_ARRAY_BUFFER, dataSize, data, GL_STATIC_DRAW);
    glVertexAttribPointer(attributeNumber, attributeSize, GL_FLOAT, GL_FALSE, 0, nullptr);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Loader::bindIndicesBuffer(int* indices, int& count) {
    GLuint vboID;
    glGenBuffers(1, &vboID);
    m_vbos.push_back(vboID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * count, indices, GL_STATIC_DRAW);
}
