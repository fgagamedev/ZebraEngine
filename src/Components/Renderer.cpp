#include "Engine/GameObject.hpp"
#include "Engine/GraphicsSystem.hpp"

#include "Components/Renderer.hpp"
#include "Globals/ComponentTypes.hpp"
#include "Log/log.hpp"

#include <math.h>

/**
    @file Renderer.cpp
    @brief Manages renderings of images on the screen.
    @copyright LGPL. MIT License.
*/

/**
    @brief Update the images informations on the screen.
*/
void Renderer::ComponentUpdate() {
    std::pair<int, int> sizes = 
        std::make_pair(GetOwner()->GetWidth(), GetOwner()->GetHeight());
        GraphicsSystem::GetInstance()->Draw(m_image, m_position, sizes);
}

/**
    @brief  Constructor for the class Renderer.
    @param[in] owner - Owns the component.
    @param[in] img
*/
Renderer::Renderer(GameObject *owner, Image *img) : Component(owner, C_DRAW) {
    m_image = img;

    m_position = GetOwner()->GetPosition();

    if (!m_image) {
        ERROR("Null image on renderer");
    }
}

/**
    @brief Destructor for the class Renderer.
*/
Renderer::~Renderer() { delete m_image; }

/**
    @brief Initializes the renderer.
*/
void Renderer::Start() {}

/**
    @brief Rotate the image towards the calculated angle.
    @param[in] point
*/
void Renderer::RotateTowards(Vector *point) {
    double angles = 0;
    angles = atan2(point->m_y - m_position->m_y, point->m_x - m_position->m_x);
    angles = angles * 180 / 3.1415;
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
