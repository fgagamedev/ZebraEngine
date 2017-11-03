/**
    @file FirstBossLifeScript.cpp
    @brief Manage the animations for the first boss central effect.
    @copyright MIT License.
*/

#include "Customs/FirstBossCentralEffectScript.hpp"

const int centralImageheight = 70;
const int centralImageWidth = 700;
const int animationPosition = 70;
const int frameCounter = 10;
const int bossXPosition = 5.575263158;
const int bossYPosition = 7.566428571;

/**
    @brief Constructor for the FirstBossCentralEffectScript class.
*/
FirstBossCentralEffectScript::FirstBossCentralEffectScript(GameObject *owner) :
                                                           Script(owner) {}

/**
    @brief Start the animation for the first boss central effect.
*/
void FirstBossCentralEffectScript::Start() {
    /*
        Creates the animations defining position the place to insert
        and the scene that will be inserted.
    */
    CreateAnimations();
    m_position = GetOwner()->GetPosition();
    m_animator = (Animator *)GetOwner() -> GetComponent("Animator");
    m_input = InputSystem::GetInstance();
    auto map = SceneManager::GetInstance() -> GetScene("Gameplay") -> GetGameObject("Map");
    
    // Checks for the map, and sets its properties.
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

    // Image Attacks.
    auto firstBossCentralImage1 = new Image("assets/centroboss11.png", 0, 0, 
                                            centralImageWidth, centralImageheight);

    // Surge Animation.
    auto firstBossCentralAnimation1 = new Animation(GetOwner(), firstBossCentralImage1);

    for (int counter = 0; counter < frameCounter; counter++) {
        firstBossCentralAnimation1->AddFrame(new Frame(counter * animationPosition, 0, 
                                                       animationPosition, centralImageheight));
        // Animator.
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

    // Checks the boss state.
    if (m_boss) {
        m_animator->PlayAnimation("firstBossCentralAnimation1");
    }
}

/**
    @brief Determine the boss position horizontally and vertically.
*/
void FirstBossCentralEffectScript::FixedComponentUpdate() {

    /*
        If the boss is initialized arrow to a new position for it
        according to the player's position.
    */

    // Checks the boss state.
    if (m_boss) {
        m_position->m_x = m_boss->GetPosition()->m_x + m_boss->GetWidth() / 2
                                             - GetOwner()->GetWidth() / 2
                                             + GetOwner()->GetWidth()
                                             / bossXPosition;
        m_position->m_y = m_boss->GetPosition()->m_y + m_boss->GetHeight() / 2
                                                - GetOwner()->GetHeight() / 2
                                                + GetOwner()->GetHeight()
                                                / bossYPosition;
    }
}
