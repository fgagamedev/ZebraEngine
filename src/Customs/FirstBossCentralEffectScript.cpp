#include "Customs/FirstBossCentralEffectScript.hpp"

/**
    @file FirstBossLifeScript.cpp
    @brief Manage the animations for the first boss central effect.
    @copyright MIT License.
*/

/**
    @brief Constructor for the FirstBossCentralEffectScript class.
*/
FirstBossCentralEffectScript::FirstBossCentralEffectScript(GameObject *owner) :
Script(owner) {}

/**
    @brief Start the animation for the first boss central effect.
*/
void FirstBossCentralEffectScript::Start() {
    CreateAnimations();
    position = GetOwner()->GetPosition();
    animator = (Animator *)GetOwner()->GetComponent("Animator");
    input = InputSystem::GetInstance();
    auto map = SceneManager::GetInstance()->
    GetScene("Gameplay")->GetGameObject("Map");
    if (map) {
        GetOwner()->SetZoomProportion(Vector
                            (map->originalWidth/GetOwner()->originalWidth,
                             map->originalHeight/GetOwner()->originalHeight));
    }
}

/**
    @brief Create the first boss central effect animations.
*/
void FirstBossCentralEffectScript::CreateAnimations() {
    auto firstBossCentralImage1 = new Image("assets/centroboss11.png", 0, 0,
                                            700, 70);
    auto firstBossCentralAnimation1 = new Animation(GetOwner(),
                                                    firstBossCentralImage1);
    for (int counter = 0; counter < 10; counter++) {
        firstBossCentralAnimation1->AddFrame(new Frame(counter * 70,0,
                                                       70, 70));
        // animator
        auto firstBossAnimator = new Animator(GetOwner());
        firstBossAnimator->AddAnimation("firstBossCentralAnimation1",
                                        firstBossCentralAnimation1);
    }
}

/**
    @brief Start a boss animation if he is in the scene.
*/
void FirstBossCentralEffectScript::ComponentUpdate() {
    boss = SceneManager::GetInstance()->GetCurrentScene()->
    GetGameObject("FirstBoss");
    if (boss) {
        animator->PlayAnimation("firstBossCentralAnimation1");
    }
}

/**
    @brief Determine the boss position horizontally and vertically.
*/
void FirstBossCentralEffectScript::FixedComponentUpdate() {
    if (boss) {
        position->m_x = boss->GetPosition()->m_x + boss->GetWidth() / 2
                                             - GetOwner()->GetWidth() / 2
                                             + GetOwner()->GetWidth()
                                             / 5.575263158;
        position->m_y = boss->GetPosition()->m_y + boss->GetHeight() / 2
                                                - GetOwner()->GetHeight() / 2
                                                + GetOwner()->GetHeight()
                                                / 7.566428571;
    }
}
