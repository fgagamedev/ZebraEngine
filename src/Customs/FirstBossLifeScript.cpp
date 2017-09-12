#include "Customs/FirstBossLifeScript.hpp"
#include "Globals/EngineGlobals.hpp"

/**
    @file FirstBossLifeScript.cpp
    @brief Manage the first boss life.
    @copyright MIT License.
*/

/**
    @brief Constructor of the FirstBossLifeScript class.
*/
FirstBossLifeScript::FirstBossLifeScript(GameObject *owner) : Script(owner) {}

/**
    @brief Start the script that control the life of the first boss.
*/
void FirstBossLifeScript::Start() {
    position = GetOwner()->GetPosition();
    GetOwner()->SetZoomProportion(Vector(0,0));
}

/**
    @brief Control the lifebar of the first boss.
*/
void FirstBossLifeScript::ComponentUpdate() {
    auto firstBossLifeRenderer = (RectangleRenderer*)GetOwner()->
                                  GetComponent("RectangleRenderer");
    int actualLife = firstBossLifeRenderer->GetWidth();
    if (hit && actualLife > 0) {
        cout << "hit" << endl;
        cout << actualLife << endl;
        firstBossLifeRenderer->SetWidth(actualLife - 10);
        hit = false;
    }
    if (actualLife <= 0) {
        FirstBossController::GetInstance()->ActivateCreditsAnimation();
        FirstBossController::GetInstance()->DeactivateLifeBars();
    }
}

/**
    @brief Set the position of the first boss's lifebar.
*/
void FirstBossLifeScript::FixedComponentUpdate() {
    position->m_x = 650;
    position->m_y = 10;
}
