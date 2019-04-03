// Fall 2018

#pragma once

#include <glm/glm.hpp>
#include "cs488-framework/CS488Window.hpp"
#include "cs488-framework/OpenGLImport.hpp"
#include "cs488-framework/ShaderProgram.hpp"
#include "RawModel.hpp"
#include "Loader.hpp"
#include "Render.hpp"
#include "MyEntity.hpp"
#include "FPSCamera.hpp"
#include "MasterRender.hpp"
#include "Terrain.hpp"
#include "MyBullet.hpp"
#include "BulletsManager.hpp"
#include "MyParticle.hpp"
#include "irrKlang.h"

class cs488Project : public CS488Window {
public:
    cs488Project();
    virtual ~cs488Project();
    
protected:
    virtual void init() override;
    virtual void appLogic() override;
    virtual void guiLogic() override;
    virtual void draw() override;
    virtual void cleanup() override;
    
//    virtual bool cursorEnterWindowEvent(int entered) override;
//    virtual bool mouseMoveEvent(double xPos, double yPos) override;
    virtual bool mouseButtonInputEvent(int button, int actions, int mods) override;
//    virtual bool mouseScrollEvent(double xOffSet, double yOffSet) override;
    virtual bool windowResizeEvent(int width, int height) override;
//    virtual bool keyInputEvent(int key, int action, int mods) override;
    
    void createShaderProgram();
    bool m_mouseButtonActive;
    ShaderProgram m_terrainShader;
    ShaderProgram m_shader;
    ShaderProgram m_weaponShader;
    ShaderProgram m_skyboxShader;
    ShaderProgram m_simpleShader;
    Loader *m_loader;
    Light *m_light;
    FPSCamera *m_camera;
    MyEntity *m_weapon;
    MyEntity *m_entity;
    BulletsManage *m_bullets_manager;
    irrklang::ISoundEngine *m_sound_engine;
    std::vector<MyEntity> m_bulletHoles;
    std::vector<MyEntity> m_wall;
    std::vector<MyBullet> m_bullets;
    std::vector<MyParticle> m_particles;
    std::vector<MyEntity> m_targets;

    Terrain *m_terrain;
    MasterRender *m_master_render;
    
//    // 2-component vector of floats.
//    // Represents mouse position in GL coordinates.
//    // Coordinates span [-1,1] along x and y directions within window.
//    glm::vec2 m_mouse_GL_coordinate;
//    
//    // True if mouse button is currently down.
//    bool m_mouseButtonActive;
};
