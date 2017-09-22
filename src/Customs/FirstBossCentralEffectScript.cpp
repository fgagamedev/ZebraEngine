/**
    @file FirstBossLifeScript.cpp
    @brief Manage the animations for the first boss central effect.
    @copyright MIT License.
*/

#include "Customs/FirstBossCentralEffectScript.hpp"

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
    m_position = GetOwner()->GetPosition();
    m_animator = (Animator *)GetOwner() -> GetComponent("Animator");
    m_input = InputSystem::GetInstance();
    auto map = SceneManager::GetInstance() -> GetScene("Gameplay") -> GetGameObject("Map");
    if (map) {
        GetOwner()->SetZoomProportion(Vector(map -> originalWidth / GetOwner()
                                             -> originalWidth, map
                                             -> originalHeight / GetOwner() -> originalHeight));
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
    m_boss = SceneManager::GetInstance()->GetCurrentScene()->
    GetGameObject("FirstBoss");
    if (m_boss) {
        m_animator->PlayAnimation("firstBossCentralAnimation1");
    }
}

/**
    @brief Determine the boss position horizontally and vertically.
*/
void FirstBossCentralEffectScript::FixedComponentUpdate() {
    if (m_boss) {
        m_position->m_x = m_boss->GetPosition()->m_x + m_boss->GetWidth() / 2
                                             - GetOwner()->GetWidth() / 2
                                             + GetOwner()->GetWidth()
                                             / 5.575263158;
        m_position->m_y = m_boss->GetPosition()->m_y + m_boss->GetHeight() / 2
                                                - GetOwner()->GetHeight() / 2
                                                + GetOwner()->GetHeight()
                                                / 7.566428571;
    }
}
