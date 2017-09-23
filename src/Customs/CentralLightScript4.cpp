/**
    @file CentralLightScript4.cpp
    @brief This class contains all attributes and methods that manages the central light in the game.
    @copyright LGPL. MIT License.
*/

#include "Customs/CentralLightScript4.hpp"
#include "Globals/EngineGlobals.hpp"

/**
    @brief Initializes CentralLightScript instance.
    @param[in] GameObject *owner - owns the component.
*/
CentralLightScript4::CentralLightScript4(GameObject *owner) : Script(owner) {

}

/**
    @brief Creates the animations in-game, with some of the gameobject
    properties.
*/
void CentralLightScript4::Start() {

    CreateAnimations();

    // Gets the position.
    position = GetOwner()->GetPosition();
    animator = (Animator *)GetOwner()->GetComponent("Animator");
    input = InputSystem::GetInstance();
    gamecontroller = input->GetGameController(0);
    GetOwner()->SetZoomProportion(Vector(0,0));
    auto map = SceneManager::GetInstance()->GetScene("Gameplay")->
               GetGameObject("Map");
    if(map) {
      GetOwner()->SetZoomProportion(Vector(map->originalWidth/GetOwner()->originalWidth,
                                           map->originalHeight/GetOwner()->originalHeight));
    }

}

/**
    @brief Positions the animations in-game, through the settings of frames,
    and image's position.
*/
void CentralLightScript4::CreateAnimations() {

    // Creates the image.
    auto centrallightSprite = new Image("assets/centro2.png", 0, 0,832, 64);

    // Creates the animation of central light.
    auto centrallightAnimation = new Animation(GetOwner(), centrallightSprite);
    centrallightAnimation->AddFrame(new Frame(0, 0, 64, 64));

    auto centrallightAnimator = new Animator(GetOwner());
    centrallightAnimation->SetFramesPerSecond(9);
    centrallightAnimator->AddAnimation("CENTRAL LIGHT ANIMATION",
                                     centrallightAnimation);


}

/**
    @brief Updates the animator component by looking for a previous
    light animation.
*/
void CentralLightScript4::ComponentUpdate() {

    if(!animator->IsPlaying("CENTRAL LIGHT ANIMATION") && active)
    animator->PlayAnimation("CENTRAL LIGHT ANIMATION");

}

void CentralLightScript4::FixedComponentUpdate() {

}
