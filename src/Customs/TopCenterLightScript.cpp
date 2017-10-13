/**
    @file TopCenterLightScript.cpp
    @brief This class contains all attributes and methods that manages the central light in the game.
    @copyright LGPL. MIT License.
*/

#include "Customs/TopCenterLightScript.hpp"
#include "Globals/EngineGlobals.hpp"

const int imagePositionX = 0;
const int imagePositionY = 0;
const int imageWidth = 832;
const int imageHeight = 64;

const int framePositionX = 0;
const int framePositionY = 0;
const int frameWidth = 64;
const int frameHeight = 64;

const int framesPerSecond = 9;

/**
    @brief Initializes CentralLightScript instance.
    @param[in] GameObject *owner - owns the component.
*/
TopCenterLightScript::TopCenterLightScript(GameObject *owner) : Script(owner) {

}

/**
    @brief Creates the animations in-game, with some of the gameobject
    properties.
*/
void TopCenterLightScript::Start() {

    CreateAnimations();

    // Gets the position.
    m_position = GetOwner()->GetPosition();
    m_animator = (Animator *)GetOwner()->GetComponent("Animator");
    m_input = InputSystem::GetInstance();
    m_gameController = m_input->GetGameController(0);
    GetOwner()->SetZoomProportion(Vector(0,0));
    auto map = SceneManager::GetInstance()->GetScene("Gameplay")->
               GetGameObject("Map");

    // verify if the map variable is instanced and set zoom.
    if(map) {
      GetOwner()->SetZoomProportion(Vector(map->originalWidth / GetOwner()->originalWidth,
                                           map->originalHeight / GetOwner()->originalHeight));
    }

}

/**
    @brief Positions the animations in-game, through the settings of frames,
    and image's position.
*/
void TopCenterLightScript::CreateAnimations() {

    // Creates the image.
    auto topCenterLightSprite = new Image("assets/topcenter.png", imagePositionX, imagePositionY, imageWidth, imageHeight);

    // Creates the animation of central light.
    auto topCenterLightAnimation = new Animation(GetOwner(), topCenterLightSprite);
    topCenterLightAnimation->AddFrame(new Frame(framePositionX, framePositionY, frameWidth, frameHeight));

    auto topCenterLightAnimator = new Animator(GetOwner());
    topCenterLightAnimation->SetFramesPerSecond(framesPerSecond);
    topCenterLightAnimator->AddAnimation("CENTRAL LIGHT ANIMATION",
                                         topCenterLightAnimation);


}

/**
    @brief Updates the animator component by looking for a previous
    light animation.
*/
void TopCenterLightScript::ComponentUpdate() {

    // Starting the animator of game.
    if(!m_animator->IsPlaying("CENTRAL LIGHT ANIMATION") && active) {
        m_animator->PlayAnimation("CENTRAL LIGHT ANIMATION");
    }
}

void TopCenterLightScript::FixedComponentUpdate() {

}
