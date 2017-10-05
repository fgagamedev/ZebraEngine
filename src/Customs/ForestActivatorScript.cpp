#include "Customs/ForestActivatorScript.hpp"
#include "Globals/EngineGlobals.hpp"
#include "Customs/CentralLightScript3.hpp"

/**
    @file UIButton.cpp
    @brief Methods that manages(create and update) the forest script.
    @copyright LGPL. MIT License.
*/

// Constructor
ForestActivatorScript::ForestActivatorScript(GameObject *owner) : Script(owner) {}

/**
    @brief Initializes the forest script.
*/
void ForestActivatorScript::Start() {

    CreateAnimations();
    position = GetOwner()->GetPosition();
    animator = (Animator *)GetOwner()->GetComponent("Animator");
    input = InputSystem::GetInstance();
    gamecontroller = input->GetGameController(0);
    GetOwner()->SetZoomProportion(Vector(0,0));
    auto map = SceneManager::GetInstance()->GetScene("Gameplay")->GetGameObject("Map");
    if (map) {
        GetOwner()->SetZoomProportion(Vector(map->originalWidth/GetOwner()->originalWidth,
                                             map->originalHeight/GetOwner()->originalHeight));
    }
}

/**
    @brief Creates animations.
*/
void ForestActivatorScript::CreateAnimations() {
    // Sets the animations' image and its frames.
    auto forestactivatorSprite = new Image("assets/forestactivator.png",
                                            0, 0, 832, 64);
    auto forestactivatorAnimation = new Animation(GetOwner(),
                                                    forestactivatorSprite);
    for (int i = 0; i < 13; i++) {
        forestactivatorAnimation->AddFrame(new Frame(i * 64, 0, 64, 64));
    }

    auto forestactivatorAnimation2 = new Animation(GetOwner(), forestactivatorSprite);
    forestactivatorAnimation2->AddFrame(new Frame(12 * 64, 0, 64, 64));

    // Sets forest animations conditions.
    auto forestactivatorAnimator = new Animator(GetOwner());
    forestactivatorAnimation->SetFramesPerSecond(9);
    forestactivatorAnimator->AddAnimation("FOREST ACTIVATOR ANIMATION", forestactivatorAnimation);
    forestactivatorAnimator->AddAnimation("FOREST ACTIVATOR ANIMATION2", forestactivatorAnimation2);
}

/**
    @brief Updates the animations components.
*/
void ForestActivatorScript::ComponentUpdate() {
    // Starts animator
    if (!animator->IsPlaying("FOREST ACTIVATOR ANIMATION") && activate == 0 && runned == false) {
        animator->PlayAnimation("FOREST ACTIVATOR ANIMATION");
        activate = 1;
        runned = true;
    }

    if (runned && !animator->IsPlaying("FOREST ACTIVATOR ANIMATION")) {
        animator->PlayAnimation("FOREST ACTIVATOR ANIMATION2");
    }

    if (runned) {
        auto script = (CentralLightScript3*)SceneManager::GetInstance()
                                        ->GetCurrentScene()
                                        ->GetGameObject("CENTRAL LIGHT 3")
                                        ->GetComponent("CentralLightScript3");
        script->Activate();
    }
}

/**
    @brief Updates the animations components.
*/
void ForestActivatorScript::FixedComponentUpdate() {

}
