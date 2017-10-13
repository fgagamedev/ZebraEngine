/**
    @file Renderer.cpp
    @brief Manages renderings of images on the screen.
    @copyright LGPL. MIT License.
*/

#include "Engine/GameObject.hpp"
#include "Engine/GraphicsSystem.hpp"

#include "Components/Renderer.hpp"
#include "Globals/ComponentTypes.hpp"
#include "Log/log.hpp"

#include <math.h>

/**
    @brief Update the images informations on the screen.
*/
void Renderer::ComponentUpdate() {
    // Draw the component.
    std::pair<int, int> sizes =
        std::make_pair(GetOwner()->GetWidth(), GetOwner()->GetHeight());
        GraphicsSystem::GetInstance()->Draw(m_image, m_position, sizes);
}

/**
    @brief  Constructor for the class Renderer.
    @param[in] owner - Owns the component.
    @param[in] img
*/
Renderer::Renderer(GameObject *owner, Image *image) : Component(owner, C_DRAW) {
    m_image = image;

    m_position = GetOwner()->GetPosition();

    // Detect null image
    if (!m_image) {
        // Return error
        ERROR("Null image on renderer");
    }
}

/**
    @brief Destructor for the class Renderer.
*/
Renderer::~Renderer() {
    delete m_image;
}

/**
    @brief Do nothing.
*/
void Renderer::Start() {

}

/**
    @brief Rotate the image towards the calculated angle.
    @param[in] point
*/
void Renderer::RotateTowards(Vector *point) {
    // Calculate arc tangent in degrees.
    double angles = 0.0;
    angles = atan2(point->m_y - m_position->m_y, point->m_x - m_position->m_x);
    angles = angles * 180 / 3.1415;

    // Keep angles in 0 to 360 range
    if (angles < 0) {
        angles = 360 - (-angles);
    }

    Rotate(angles);
}

/**
    @brief Rotate the image.
    @param[in] angles - Angles of the image.
*/
void Renderer::Rotate(double angles) {
    GetImage()->Rotate(angles);
}
