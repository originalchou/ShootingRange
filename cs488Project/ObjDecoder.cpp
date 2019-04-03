//
//  ObjLoader.cpp
//  cs488Project
//
//  Created by Chang Zhou on 2018-11-17.
//  Copyright © 2018 none. All rights reserved.
//
#include "cs488-framework/Exception.hpp"
#include "ObjDecoder.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstring>



//---------------------------------------------------------------------------------------
void ObjDecoder::decode(
                            const char * objFilePath,
                            std::vector<glm::vec3> & positions,
                            std::vector<glm::vec3> & normals,
                            std::vector<glm::vec2> & uvCoords,
                            std::vector<int> & indices
                            ) {
    
    // Empty containers, and start fresh before inserting data from .obj file
    positions.clear();
    normals.clear();
    uvCoords.clear();
    indices.clear();
    
    std::ifstream in(objFilePath, std::ios::in);
    in.exceptions(std::ifstream::badbit);
    
    if (!in) {
        std::stringstream errorMessage;
        errorMessage << "Unable to open .obj file " << objFilePath
        << " within method ObjFileDecoder::decode" << std::endl;
        
        throw Exception(errorMessage.str().c_str());
    }
    
    std::string currentLine;
    int positionIndexA, positionIndexB, positionIndexC;
    int normalIndexA, normalIndexB, normalIndexC;
    int uvCoordIndexA, uvCoordIndexB, uvCoordIndexC;
    std::vector<glm::vec3> temp_normals;
    std::vector<glm::vec2> temp_uvCoords;
    
    
    while (!in.eof()) {
        try {
            getline(in, currentLine);
        } catch (const std::ifstream::failure &e) {
            in.close();
            std::stringstream errorMessage;
            errorMessage << "Error calling getline() -- " << e.what() << std::endl;
            throw Exception(errorMessage.str());
        }
        if (currentLine.substr(0, 2) == "o ") {
            // Get entire line excluding first 2 chars.
            std::istringstream s(currentLine.substr(2));
            
            
        } else if (currentLine.substr(0, 2) == "v ") {
            // Vertex data on this line.
            // Get entire line excluding first 2 chars.
            std::istringstream s(currentLine.substr(2));
            glm::vec3 vertex;
            s >> vertex.x;
            s >> vertex.y;
            s >> vertex.z;
            positions.push_back(vertex);
            
        } else if (currentLine.substr(0, 3) == "vn ") {
            // Normal data on this line.
            // Get entire line excluding first 2 chars.
            std::istringstream s(currentLine.substr(2));
            glm::vec3 normal;
            s >> normal.x;
            s >> normal.y;
            s >> normal.z;
            temp_normals.push_back(normal);
            
        } else if (currentLine.substr(0, 3) == "vt ") {
            // Texture coordinate data on this line.
            // Get entire line excluding first 2 chars.
            std::istringstream s(currentLine.substr(2));
            glm::vec2 textureCoord;
            s >> textureCoord.x;
            s >> textureCoord.y;
            textureCoord.y = 1 - textureCoord.y;
            temp_uvCoords.push_back(textureCoord);
            
        } else if (currentLine.substr(0, 2) == "f ") {
            if (indices.size() == 0) {
                normals.resize(positions.size());
                uvCoords.resize(positions.size());
            }
            
            // Line contains indices of the pattern vertex/uv-cord/normal.
            sscanf(currentLine.c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d",
                   &positionIndexA, &uvCoordIndexA, &normalIndexA,
                   &positionIndexB, &uvCoordIndexB, &normalIndexB,
                   &positionIndexC, &uvCoordIndexC, &normalIndexC);
            // .obj file uses indices that start at 1, so subtract 1 so they start at 0.
            uvCoordIndexA--;
            uvCoordIndexB--;
            uvCoordIndexC--;
            positionIndexA--;
            positionIndexB--;
            positionIndexC--;
            normalIndexA--;
            normalIndexB--;
            normalIndexC--;
            
            int vA = positionIndexA;
            indices.push_back(vA);
            uvCoords[vA] = temp_uvCoords[uvCoordIndexA];
            normals[vA] = temp_normals[normalIndexA];
            
            int vB = positionIndexB;
            indices.push_back(vB);
            uvCoords[vB] = temp_uvCoords[uvCoordIndexB];
            normals[vB] = temp_normals[normalIndexB];
            
            int vC = positionIndexC;
            indices.push_back(vC);
            uvCoords[vC] = temp_uvCoords[uvCoordIndexC];
            normals[vC] = temp_normals[normalIndexC];
        }
    }
    
    in.close();
}
