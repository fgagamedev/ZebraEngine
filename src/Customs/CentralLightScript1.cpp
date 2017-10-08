/**
	@file CentralLightScript1.cpp
	@brief Responsible for the light animation during the menu screen.
	@copyright MIT License.
*/
#include "Customs/CentralLightScript1.hpp"
#include "Globals/EngineGlobals.hpp"

/**
    @brief Constructor for the classe CentralLightScript1.
*/
CentralLightScript1::CentralLightScript1(GameObject *owner) : Script(owner) {}

/**
    @brief Sets the initial definitions when starting the animation.
*/
void CentralLightScript1::Start() {
    // Creates the animations and the animator for the script.
    CreateAnimations();
    m_position = GetOwner()->GetPosition();
    m_animator = (Animator *)GetOwner()->GetComponent("Animator");
    // Get the inputs.
    m_input = InputSystem::GetInstance();
    m_gameController = m_input->GetGameController(0);
    // Set the zoom and get the map of the scene.
    GetOwner()->SetZoomProportion(Vector(0,0));
    auto map = SceneManager::GetInstance()->GetScene("Gameplay")->GetGameObject("Map");
    // Check if the map from the scene exists.
    if (map) {
        // Set the zoom for the map.
        GetOwner()->SetZoomProportion(Vector(map->originalWidth/GetOwner()->
               originalWidth,map->originalHeight / GetOwner()->originalHeight));
    }
}

/**
    @brief Generates the animations on the screen.
*/
void CentralLightScript1::CreateAnimations() {
    // Create the animation.
    auto centrallightSprite = new Image("assets/centro4.png", 0, 0, 832, 64);
    auto centrallightAnimation = new Animation(GetOwner(), centrallightSprite);
    centrallightAnimation->AddFrame(new Frame(0, 0, 64, 64));

    // Create the animator.
    auto centrallightAnimator = new Animator(GetOwner());
    centrallightAnimation->SetFramesPerSecond(9);
    centrallightAnimator->AddAnimation("CENTRAL LIGHT ANIMATION",
                                       centrallightAnimation);
}

/**
    @brief Handles with changes on the component.
*/
void CentralLightScript1::ComponentUpdate() {
    // Play the CENTRAL LIGHT ANIMATION if isn't being played and is active.
    if (!m_animator->IsPlaying("CENTRAL LIGHT ANIMATION") && m_active) {
        // Play the animation CENTRAL LIGHT ANIMATION
        m_animator->PlayAnimation("CENTRAL LIGHT ANIMATION");
    }
}

void CentralLightScript1::FixedComponentUpdate() {}
