//
//  TexturedModel.h
//  cs488Project
//
//  Created by Chang Zhou on 2018-11-15.
//  Copyright © 2018 none. All rights reserved.
//

#ifndef TexturedModel_hpp
#define TexturedModel_hpp

#include "RawModel.hpp"
#include "ModelTexture.hpp"

class TexturedModel {
public:
//    TexturedModel(RawModel& model, ModelTexture& texture, bool blendAlpha = false)
//    : m_rawModel(model), m_texture(texture), m_blendAlpha(blendAlpha) {}
    TexturedModel(RawModel& model, ModelTexture& texture)
    : m_rawModel(model), m_texture(texture) {}
    inline RawModel getRawModel() const { return m_rawModel; }
    inline ModelTexture getModelTexture() const { return m_texture; }
//    inline bool GetBlendAlpha() const { return m_blendAlpha; }
private:
    RawModel m_rawModel;
    ModelTexture m_texture;
//    bool m_blendAlpha;
};

#endif /* TexturedModel_h */
