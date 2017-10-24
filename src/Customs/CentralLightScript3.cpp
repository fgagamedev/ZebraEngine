/**
	@file CentralLightScript3.cpp
	@brief Responsible for the light animation during the menu
    screen in center os screen.
	@copyright MIT License.
*/
#include "Customs/CentralLightScript3.hpp"
#include "Globals/EngineGlobals.hpp"

// Central light script start
const int gameControllerIndex = 0;
const float vectorZoomProportionAxisX = 0;
const float vectorZoomProportionAxisY = 0;

// Create animations
const int imageLightSpritePositionX = 0;
const int imageLightSpritePositionY = 0;
const int imageLightSpriteWidth = 832;
const int imageLightSpriteHeight = 64;

const int frameLightAnimationPositionX = 0;
const int frameLightAnimationPositionY = 0;
const int frameLightAnimationWidth = 64;
const int frameLightAnimationHeight = 64;

/**
    @brief Constructor for the classe CentralLightScript3.
*/
CentralLightScript3::CentralLightScript3(GameObject *owner) : Script(owner) {

}

/**
    @brief Sets the initial definitions when starting the animation.
*/
void CentralLightScript3::Start() {

    // Creates the animations and the animator for the script.
    CreateAnimations();

    m_position = GetOwner()->GetPosition();

    m_animator = (Animator *)GetOwner()->GetComponent("Animator");

    // Get the inputs.
    m_input = InputSystem::GetInstance();

    m_gamecontroller = m_input->GetGameController(gameControllerIndex);

    GetOwner()->SetZoomProportion(Vector(vectorZoomProportionAxisX, vectorZoomProportionAxisY));

    auto map = SceneManager::GetInstance()->GetScene("Gameplay")->GetGameObject("Map");

    if(map) GetOwner()->SetZoomProportion(Vector(map->originalWidth / 
                                                 GetOwner()->originalWidth, 
                                                 map->originalHeight / 
                                                 GetOwner()->originalHeight));

}

/**
    @brief Generates the animations on the screen.
*/
void CentralLightScript3::CreateAnimations(){

    // Create the animation.
    auto centrallightSprite = new Image("assets/centro3.png", imageLightSpritePositionX, 
                                        imageLightSpritePositionY, imageLightSpriteWidth, imageLightSpriteHeight);

    auto centrallightAnimation = new Animation(GetOwner(), centrallightSprite);

    centrallightAnimation->AddFrame(new Frame( frameLightAnimationPositionX, 
                                               frameLightAnimationPositionY, frameLightAnimationWidth, 
                                               frameLightAnimationHeight));

    // Create the animator.
    auto centrallightAnimator = new Animator(GetOwner());

    // Number of frames to add per second.
    centrallightAnimation->SetFramesPerSecond(9);
    centrallightAnimator->AddAnimation("CENTRAL LIGHT ANIMATION", centrallightAnimation);


}

/**
    @brief Handles with changes on the component.
*/
void CentralLightScript3::ComponentUpdate() {

    if(!m_animator->IsPlaying("CENTRAL LIGHT ANIMATION") && m_active){
        m_animator->PlayAnimation("CENTRAL LIGHT ANIMATION");
    }
}


void CentralLightScript3::FixedComponentUpdate() {

}
