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
BulletCounterScript::BulletCounterScript(GameObject *owner) : Script(owner) {}

/**
    @brief Starts the Bullet Counter position.
*/
void BulletCounterScript::Start() {
    position = GetOwner()->GetPosition();
    GetOwner()->SetZoomProportion(Vector(0,0));
}

/**
    @brief Updates the Bullet Counter informations.
*/
void BulletCounterScript::ComponentUpdate() {
    // Player component
    auto nakedManScript = (NakedManScript *)SceneManager::GetInstance()
                          ->GetCurrentScene()
                          ->GetGameObject("NakedMan")
                          ->GetComponent("NakedManScript");

    m_numberBullet = nakedManScript->bulletNumber;

    // Text component to updates the text of the Bullet Counter
    auto var = (UIText *)GetOwner()->GetComponent("UIText");
    var->SetText(std::to_string(m_numberBullet));
}

/**
    @brief Sets the Bullet Counter's x and y positions.
*/
void BulletCounterScript::FixedComponentUpdate() {
    position->m_x = 900;
    position->m_y = 700;
}
