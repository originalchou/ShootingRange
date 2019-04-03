//
//  FPSCamera.cpp
//  cs488Project
//
//  Created by Chang Zhou on 2018-11-16.
//  Copyright © 2018 none. All rights reserved.
//

#include "FPSCamera.hpp"
#include <GLFW/glfw3.h>
#include <glm/gtx/transform.hpp>
#include <iostream>
#include "CheckHit.hpp"
#include <iostream>

FPSCamera::FPSCamera(bool freeRoam, std::vector<MyEntity> &targets)
: m_position(20, 10, 100), m_viewDirection(1, 0, 0), m_freeRoam(freeRoam), m_targets(targets)
{
    // Hide the cursor
    glfwSetInputMode(glfwGetCurrentContext(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}


FPSCamera::~FPSCamera()
{
}

void FPSCamera::update()
{
    // Get the mouse X and Y and update camera view
    double x, y;
    glfwGetCursorPos(glfwGetCurrentContext(), &x, &y);
    mouseUpdate(glm::vec2(x, y));
    
    move();
}

glm::mat4 FPSCamera::getViewMatrix() const
{
    // Create the view matrix with camera values
    return glm::lookAt(m_position, m_position + m_viewDirection, m_UP);
}


void FPSCamera::mouseUpdate(const glm::vec2 mousePosition)
{
    // Get distance and direction the mouse moved

    glm::vec2 mouseDelta = mousePosition - m_mousePosition;
    
    // If for some reason the mouse jumps a distance greater than 100, ignore it
    if (glm::length(mouseDelta) > 100)
    {
        m_mousePosition = mousePosition;
        return;
    }
    
    // Find the vector to rotate around vertically
    glm::vec3 vAxis = glm::cross(m_viewDirection, m_UP);
    // (Horizontal) Rotate around the UP axis using the distance the mouse moved in the X axis
    // (Vertical) Rotate around the vAxis using the distance the mouse moved in the Y axis
    // Then apply these rotations to the view direction and normalize
    m_viewDirection = glm::normalize(glm::mat3(
                                               glm::rotate(-mouseDelta.x * m_SENSITIVITY, m_UP) *
                                               glm::rotate(-mouseDelta.y * m_SENSITIVITY, vAxis)
                                               ) * m_viewDirection);
    m_mousePosition = mousePosition;
}

void FPSCamera::move()
{
    float multiplier = 1;
    glm::vec3 delta(0,0,0);
    // Hold shift to move faster
    if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
    multiplier = 10;
    // 4 movement directions
    if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_W) == GLFW_PRESS) {
        delta = m_SPEED * glm::vec3(m_viewDirection.x, m_freeRoam ? m_viewDirection.y : 0, m_viewDirection.z) * multiplier;
//        m_weapon->changePosition(m_SPEED * glm::vec3(m_viewDirection.x, m_freeRoam ? m_viewDirection.y : 0, m_viewDirection.z) * multiplier);
    }
    if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_S) == GLFW_PRESS) {
        delta = -m_SPEED * glm::vec3(m_viewDirection.x, m_freeRoam ? m_viewDirection.y : 0, m_viewDirection.z) * multiplier;
//        m_weapon->changePosition(-m_SPEED * glm::vec3(m_viewDirection.x, m_freeRoam ? m_viewDirection.y : 0, m_viewDirection.z) * multiplier);
    }
    if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_A) == GLFW_PRESS) {
        delta = -m_SPEED * glm::cross(m_viewDirection, m_UP) * multiplier;
//        m_weapon->changePosition(-m_SPEED * glm::cross(m_viewDirection, m_UP) * multiplier);
    }
    if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_D) == GLFW_PRESS) {
        delta = m_SPEED * glm::cross(m_viewDirection, m_UP) * multiplier;
//        m_weapon->changePosition(m_SPEED * glm::cross(m_viewDirection, m_UP) * multiplier);
    }
    if (!CheckHit::checkHit(m_position+delta, 3, m_targets, false)) {
        m_position += delta;
    }
    // Press escape to exit
    if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(glfwGetCurrentContext(), GL_TRUE);
}
