// Fall 2018

#include "cs488Project.hpp"
#include "cs488-framework/GlErrorCheck.hpp"

#include <iostream>

#include <imgui/imgui.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/io.hpp>
#include "ModelTexture.hpp"
#include "TexturedModel.hpp"
#include "ObjLoader.hpp"
#include "Light.hpp"
#include "Wall.hpp"

using namespace glm;
using namespace std;

//----------------------------------------------------------------------------------------
// Constructor
cs488Project::cs488Project()
{
    
}

//----------------------------------------------------------------------------------------
// Destructor
cs488Project::~cs488Project()
{
    
}

//----------------------------------------------------------------------------------------
/*
 * Called once, at program start.
 */
void cs488Project::init()
{
    // Set the background colour.
//    glClearColor(0.3, 0.5, 0.7, 1.0);
    
    createShaderProgram();
    m_sound_engine = irrklang::createIrrKlangDevice();
    m_loader = new Loader();
    m_light =  new Light(vec3(100, 100, 100), vec3(1, 1, 1));
    m_master_render = new MasterRender(m_windowWidth/m_windowHeight, m_shader, m_terrainShader, m_weaponShader, m_skyboxShader, m_simpleShader, m_loader);
    
    //weapon
    RawModel weapon_raw_model = OBJLoader::loadObjModel("Assets/gun.obj", *m_loader, m_weaponShader);
    ModelTexture weapon_texture = ModelTexture(m_loader->loadTexture("camo"), 0.2, 1);
    TexturedModel weapon_textured_model = TexturedModel(weapon_raw_model, weapon_texture);
    vec3 p(1, -1.5, -4);
    vec3 r(-0.1, 3.2 , 0);
    vec3 s(0.05, 0.05, 0.05);
    m_weapon = new MyEntity(weapon_textured_model, p, r, s);
    
    //wall
//    RawModel entity_raw_model = OBJLoader::loadObjModel("Assets/stall.obj", *m_loader, m_shader);
    RawModel wall_raw_model = Wall::generateSingleWallModel(m_shader, m_loader);
    ModelTexture entity_texture = ModelTexture(m_loader->loadTexture("wall2"), 0.2, 1);
//    TexturedModel entity_textured_model = TexturedModel(entity_raw_model, entity_texture);
    TexturedModel wall_textured_model = TexturedModel(wall_raw_model, entity_texture);
    vec3 wall_p1(10, 30, 100);
    vec3 wall_r1(0, 0, 0);
    vec3 wall_s1(1, 60, 180);
//    m_entity = new MyEntity(wall_textured_model, wall_p1, wall_r1, wall_s1);
    m_wall.push_back(MyEntity(wall_textured_model, wall_p1, wall_r1, wall_s1));
    vec3 wall_p2(100, 30, 10);
    vec3 wall_r2(0, 1.57, 0);
    m_wall.push_back(MyEntity(wall_textured_model, wall_p2, wall_r2, wall_s1));
    vec3 wall_p3(190, 30, 100);
    m_wall.push_back(MyEntity(wall_textured_model, wall_p3, wall_r1, wall_s1));
    vec3 wall_p4(100, 30, 190);
    m_wall.push_back(MyEntity(wall_textured_model, wall_p4, wall_r2, wall_s1));
    
    ModelTexture building_texture = ModelTexture(m_loader->loadTexture("wall1"), 0.2, 1);
    TexturedModel building_textured_model = TexturedModel(wall_raw_model, building_texture);
    vec3 wall_p5(65, 30, 65);
    vec3 wall_s3(40, 60, 40);
    m_wall.push_back(MyEntity(building_textured_model, wall_p5, wall_r1, wall_s3));
    vec3 wall_p6(135, 30, 65);
    m_wall.push_back(MyEntity(building_textured_model, wall_p6, wall_r1, wall_s3));
    vec3 wall_p7(65, 30, 135);
    m_wall.push_back(MyEntity(building_textured_model, wall_p7, wall_r1, wall_s3));
    vec3 wall_p8(135, 30, 135);
    m_wall.push_back(MyEntity(building_textured_model, wall_p8, wall_r1, wall_s3));
    
    //target
    RawModel target_raw_model = Wall::generateSingleTargetModel(m_shader, m_loader);
    ModelTexture target_texture = ModelTexture(m_loader->loadTexture("target"), 0.2, 1);
    TexturedModel target_textured_model = TexturedModel(target_raw_model, target_texture);
    vec3 target_p1(100, 7.5, 15);
    vec3 target_r1(0, 0, 0);
    vec3 target_s1(0.5, 15, 7.5);
    m_targets.push_back(MyEntity(target_textured_model, target_p1, target_r1, target_s1));
    vec3 target_p2(100, 7.5, 185);
    m_targets.push_back(MyEntity(target_textured_model, target_p2, target_r1, target_s1));
    vec3 target_p5(100, 7.5, 100);
    m_targets.push_back(MyEntity(target_textured_model, target_p5, target_r1, target_s1));
    
//    vec3 target_p1(90, 7.5, 15);

    
    
    m_camera = new FPSCamera(false, m_targets);

    ModelTexture terrainTexture = ModelTexture(m_loader->loadTexture("stone", true), 0, 1);
    m_terrain = new Terrain(0, 0, *m_loader, terrainTexture, m_terrainShader);
    
    m_bullets_manager = new BulletsManage(m_bullets);
}

//----------------------------------------------------------------------------------------
void cs488Project::createShaderProgram()
{
    m_shader.generateProgramObject();
    m_shader.attachVertexShader( getAssetFilePath("VertexShader.vs").c_str() );
    m_shader.attachFragmentShader( getAssetFilePath("FragmentShader.fs").c_str() );
    m_shader.link();
    
    m_terrainShader.generateProgramObject();
    m_terrainShader.attachVertexShader(getAssetFilePath("TerrainVertexShader.vs").c_str());
    m_terrainShader.attachFragmentShader(getAssetFilePath("TerrainFragmentShader.fs").c_str());
    m_terrainShader.link();
    
    m_weaponShader.generateProgramObject();
    m_weaponShader.attachVertexShader(getAssetFilePath("WeaponVertexShader.vs").c_str());
    m_weaponShader.attachFragmentShader(getAssetFilePath("WeaponFragmentShader.fs").c_str());
    m_weaponShader.link();
    
    m_skyboxShader.generateProgramObject();
    m_skyboxShader.attachVertexShader(getAssetFilePath("SkyboxVertexShader.vs").c_str());
    m_skyboxShader.attachFragmentShader(getAssetFilePath("SkyboxFragmentShader.fs").c_str());
    m_skyboxShader.link();
    
    m_simpleShader.generateProgramObject();
    m_simpleShader.attachVertexShader(getAssetFilePath("SimpleVertexShader.vs").c_str());
    m_simpleShader.attachFragmentShader(getAssetFilePath("SimpleFragmentShader.fs").c_str());
    m_simpleShader.link();
}

//----------------------------------------------------------------------------------------
/*
 * Called once per frame, before guiLogic().
 */
void cs488Project::appLogic()
{
    // Place per frame, application logic here ...
    m_camera->update();
    m_master_render->processTerrain(*m_terrain);
//    m_master_render->processEntity(*m_entity);
    m_bullets_manager->moveBullets(m_bulletHoles, m_particles, m_shader, m_loader, m_targets);
    for (int i = 0; i < m_bulletHoles.size(); i++) {
        MyEntity &bulletHoles = m_bulletHoles.at(i);
        bulletHoles.setLastFrame(bulletHoles.getLastFrame()-1);
        if(bulletHoles.getLastFrame() <= 0) {
            m_bulletHoles.erase(m_bulletHoles.begin()+i-1);
        } else {
            m_master_render->processEntity(bulletHoles);
        }
    }
    for (int i = 0; i < m_bullets.size(); i++) {
        MyBullet &bullet = m_bullets.at(i);
        m_master_render->processEntity(bullet);
    }
    for (MyEntity wall: m_wall) {
        m_master_render->processEntity(wall);
    }
    for (int i = 0; i < m_targets.size(); i++) {
        MyEntity &target = m_targets.at(i);
        if(!target.getHit()) {
            m_master_render->processEntity(target);
        }
    }
    for (int i = 0; i < m_particles.size(); i++) {
        MyParticle &particle = m_particles.at(i);
        particle.moveParticle();
        particle.setFrameLeft(particle.getFrameLeft()-1);
        if (particle.getFrameLeft() > 0) {
            m_master_render->processEntity(particle);
        } else {
            m_particles.erase(m_particles.begin() + i - 1);
        }
    }
    m_master_render->processWeapon(*m_weapon);
//    m_master_render->processEntity(*m_entity2);
}

//----------------------------------------------------------------------------------------
/*
 * Called once per frame, after appLogic(), but before the draw() method.
 */
void cs488Project::guiLogic()
{
//    static bool firstRun(true);
//    if (firstRun) {
//        ImGui::SetNextWindowPos(ImVec2(50, 50));
//        firstRun = false;
//    }
//
//    static bool showDebugWindow(true);
//    ImGuiWindowFlags windowFlags(ImGuiWindowFlags_AlwaysAutoResize);
//    float opacity(0.5f);
//
//    ImGui::Begin("Shape Properties", &showDebugWindow, ImVec2(100,100), opacity,
//                 windowFlags);
//    // Create Button, and check if it was clicked:
//    if( ImGui::Button( "Quit Application" ) ) {
//        glfwSetWindowShouldClose(m_window, GL_TRUE);
//    }
//    if( ImGui::Button( "Reset" ) ) {
//        resetVariables();
//    }
//
//    // Retrieve red color component from slider and store in the first element of
//    // m_shape_color.
//    ImGui::SliderFloat("Red Channel", &m_shape_color.r, 0.0f, 1.0f);
//
//    // Add more gui elements here here ...
//    ImGui::SliderFloat("Green Channel", &m_shape_color.g, 0.0f, 1.0f);
//    ImGui::SliderFloat("Blue Channel", &m_shape_color.b, 0.0f, 1.0f);
//
//    // m_shape_rotation
//    ImGui::SliderFloat("Rotation", &m_shape_rotation, 0.0f, 2.0f*PI);
//
//    ImGui::Text( "Framerate: %.1f FPS", ImGui::GetIO().Framerate );
//
//    ImGui::End();
}

//----------------------------------------------------------------------------------------
/*
 * Called once per frame, after guiLogic().
 */
void cs488Project::draw()
{

    m_master_render->render(*m_light, *m_camera);
    CHECK_GL_ERRORS;
}

//----------------------------------------------------------------------------------------
/*
 * Called once, after program is signaled to terminate.
 */
void cs488Project::cleanup()
{
    
}

//----------------------------------------------------------------------------------------
/*
 * Event handler.  Handles window resize events.
 */
bool cs488Project::windowResizeEvent(int width, int height) {
    bool eventHandled(false);
    
    // Fill in with event handling code...
    
    return eventHandled;
}

bool cs488Project::mouseButtonInputEvent(int button, int actions, int mods) {
    bool eventHandled(false);
    
    // Fill in with event handling code...
    
    if (actions == GLFW_PRESS) {
        if (!ImGui::IsMouseHoveringAnyWindow()) {
            //generate bullet
            m_mouseButtonActive = true;
            RawModel bullet_raw_model = Wall::generateSingleWallModel(m_shader, m_loader);
            ModelTexture bullet_texture = ModelTexture(m_loader->loadTexture("brown"), 0.2, 1);
            vec3 bullet_p(m_camera->getPosition().x, m_camera->getPosition().y, m_camera->getPosition().z);
            vec3 bullet_r(0, 0, 0);
            vec3 bullet_s(0.5, 0.5, 0.5);
            TexturedModel bullet_textured_model = TexturedModel(bullet_raw_model, bullet_texture);
            vec3 direction(m_camera->getDirection());
            MyBullet bullet_temp(bullet_textured_model, bullet_p, bullet_r, bullet_s, direction);
            m_bullets.push_back(bullet_temp);
            m_sound_engine->play2D("Assets/gunshot.wav");
        }
    }
    
    if (actions == GLFW_RELEASE) {
        m_mouseButtonActive = false;
    }
    
    return eventHandled;
}
