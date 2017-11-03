#include "Customs/LeftCenterLightScript.hpp"
#include "Globals/EngineGlobals.hpp"

/**
    @file LeftCenterLightScript.cpp
    @brief Methods that manages the central light during the game.
    @copyright LGPL. MIT License.
*/

const int framesPerSecond = 9;
const int imagePlacing = 64;

/**
    @brief Initializes CentralLightScript instance.
    @param[in] GameObject *owner - owns the component.
*/
LeftCenterLightScript::LeftCenterLightScript(GameObject *owner) : Script(owner) {}


/**
    @brief Creates the animations in-game, with some of the gameobject properties.
*/
void LeftCenterLightScript::Start() {
    CreateAnimations();
    position = GetOwner()->GetPosition();
    animator = (Animator *)GetOwner()->GetComponent("Animator");
    input = InputSystem::GetInstance();
    gamecontroller = input->GetGameController(0);
    GetOwner()->SetZoomProportion(Vector(0,0));
    auto map = SceneManager::GetInstance()->GetScene("Gameplay")->GetGameObject("Map");

    // If map variable is initialized, sets its configs.
    if (map) {
        GetOwner()->SetZoomProportion(Vector(map->originalWidth/GetOwner()
                                                    ->originalWidth,map
                                                    ->originalHeight/GetOwner()
                                                    ->originalHeight));
    }
}

/**
    @brief Positions the animations in-game, through the settings of frames, and image's position.
*/
void LeftCenterLightScript::CreateAnimations(){
    // Sets the image of the little square placed on the map, where the player has to go to
    auto centrallightSprite = new Image("assets/left_center.png", 0, 0, imagePlacing * 13, imagePlacing);
    auto centrallightAnimation = new Animation(GetOwner(), centrallightSprite);
    centrallightAnimation->AddFrame(new Frame(0, 0, imagePlacing, imagePlacing));

    // Sets the animations' conditions.
    auto centrallightAnimator = new Animator(GetOwner());
    centrallightAnimation->SetFramesPerSecond(framesPerSecond);
    centrallightAnimator->AddAnimation("CENTRAL LIGHT ANIMATION", centrallightAnimation);
}

/**
    @brief Updates the animator component by looking for a previous light animation.
*/
void LeftCenterLightScript::ComponentUpdate() {
    if(!animator->IsPlaying("CENTRAL LIGHT ANIMATION") && active){
        animator->PlayAnimation("CENTRAL LIGHT ANIMATION");
    }
}

/**
    @brief Updates the animator component.
*/
void LeftCenterLightScript::FixedComponentUpdate() {

}
