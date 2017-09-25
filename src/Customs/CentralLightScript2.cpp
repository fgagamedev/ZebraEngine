#include "Customs/CentralLightScript2.hpp"
#include "Globals/EngineGlobals.hpp"

/**
    @file CentralLightScript.cpp
    @brief Methods that manages the central light during the game.
    @copyright LGPL. MIT License.
*/


/**
    @brief Initializes CentralLightScript instance.
    @param[in] GameObject *owner - owns the component.
*/
CentralLightScript2::CentralLightScript2(GameObject *owner) : Script(owner) {}


/**
    @brief Creates the animations in-game, with some of the gameobject properties.
*/
void CentralLightScript2::Start() {
    CreateAnimations();
    position = GetOwner()->GetPosition();
    animator = (Animator *)GetOwner()->GetComponent("Animator");
    input = InputSystem::GetInstance();
    gamecontroller = input->GetGameController(0);
    GetOwner()->SetZoomProportion(Vector(0,0));
    auto map = SceneManager::GetInstance()->GetScene("Gameplay")->GetGameObject("Map");

    if(map) GetOwner()->SetZoomProportion(Vector(map->originalWidth/GetOwner()->originalWidth,map->originalHeight/GetOwner()->originalHeight));
}

/**
    @brief Positions the animations in-game, through the settings of frames, and image's position.
*/
void CentralLightScript2::CreateAnimations(){
    // sets the image of the little square placed on the map, where the player has to go to
    auto centrallightSprite = new Image("assets/centro1.png", 0, 0,832, 64);
    auto centrallightAnimation = new Animation(GetOwner(), centrallightSprite);
    centrallightAnimation->AddFrame(new Frame(0, 0, 64, 64));

    auto centrallightAnimator = new Animator(GetOwner());
    centrallightAnimation->SetFramesPerSecond(9);
    centrallightAnimator->AddAnimation("CENTRAL LIGHT ANIMATION", centrallightAnimation);
}

/**
    @brief Updates the animator component by looking for a previous light animation.
*/
void CentralLightScript2::ComponentUpdate() {
    if(!animator->IsPlaying("CENTRAL LIGHT ANIMATION") && active){
        animator->PlayAnimation("CENTRAL LIGHT ANIMATION");
    }
}

/**
    @brief Updates the animator component.
*/
void CentralLightScript2::FixedComponentUpdate() {

}
