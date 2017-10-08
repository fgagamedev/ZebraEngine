/**
    @file BulletCounterScript.cpp
    @brief Manages the bullet counting.
    @copyright LGPL. MIT License.
*/

#include "Customs/BulletCounterScript.hpp"
#include "Globals/EngineGlobals.hpp"

/**
    @brief Constructor of the class BulletCounterScript.
    @param[in] GameObject *owner - Owns the component.
*/
BulletCounterScript::BulletCounterScript(GameObject *owner) : Script(owner) {

}

/**
    @brief Starts the Bullet Counter position.
*/
void BulletCounterScript::Start() {
    counter_position = GetOwner()->GetPosition();
    GetOwner()->SetZoomProportion(Vector(0, 0));
}

/**
    @brief Updates the Bullet Counter informations.
*/
void BulletCounterScript::ComponentUpdate() {
    // Get player's component number of bullets.
    auto nakedManScript = (NakedManScript *)SceneManager::GetInstance()
                          ->GetCurrentScene()
                          ->GetGameObject("NakedMan")
                          ->GetComponent("NakedManScript");
    m_numberBullet = nakedManScript->bulletNumber;

    // Update the text of the left number of bullets.
    auto counterText = (UIText *)GetOwner()->GetComponent("UIText");
    counterText->SetText(std::to_string(m_numberBullet));
}

/**
    @brief Set the Bullet Counter's x and y positions.
*/
void BulletCounterScript::FixedComponentUpdate() {
    counter_position->m_x = 900;
    counter_position->m_y = 700;
}
