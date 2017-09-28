#include "Customs/CentralLightScript1.hpp"
#include "Customs/ForestActivatorScript2.hpp"
#include "Globals/EngineGlobals.hpp"

ForestActivatorScript2::ForestActivatorScript2(GameObject *owner) : Script(owner) {

}

/**
    @brief that function starts the activion of the forest 2. Create the animation,
    position, animator, controller, input and the map.
*/
void ForestActivatorScript2::Start() {
    /*
        Create animations, define position, animator through gameobject.
        Defines map and sets its zoom proportion vector using width and height.
        Sets the joystick.
    */
    CreateAnimations();
    position = GetOwner()->GetPosition();
    animator = (Animator *)GetOwner()->GetComponent("Animator");
    input = InputSystem::GetInstance();
    gamecontroller = input->GetGameController(0);
    GetOwner()->SetZoomProportion(Vector(0,0));
    auto map = SceneManager::GetInstance()->GetScene("Gameplay")->GetGameObject("Map");
    // Check for map, and if exists, sets its map on a vector.
    if (map) {
        GetOwner()->SetZoomProportion(Vector(map->originalWidth/GetOwner()->originalWidth,map->originalHeight/GetOwner()->originalHeight));
    }
}

/**
    @brief that function create the animations for the forest. Create the image of
    the forest and the animation of the forest.
*/
void ForestActivatorScript2::CreateAnimations(){
    // Instantiating forest activator Sprite image and its position.
    auto forestactivatorSprite = new Image("assets/forestactivator.png", 0, 0,832, 64);

    // Instantiating forest activator animation by gameobject components, and setting its image and frame.
    auto forestactivatorAnimation = new Animation(GetOwner(), forestactivatorSprite);
    for (int i = 0; i < 13; i++) {
        forestactivatorAnimation->AddFrame(new Frame(i * 64, 0, 64, 64));
    }

    // Instantiating forest activator animation2, by gameobject, and setting its image and animation.
    auto forestactivatorAnimation2 = new Animation(GetOwner(), forestactivatorSprite);
    forestactivatorAnimation2->AddFrame(new Frame(12 * 64, 0, 64, 64));

    // Instantiating animator, setting its animation and frames per second.
    auto forestactivatorAnimator = new Animator(GetOwner());
    forestactivatorAnimation->SetFramesPerSecond(9);
    //forestactivatorAnimation2->SetFramesPerSecond(1);
    forestactivatorAnimator->AddAnimation("FOREST ACTIVATOR ANIMATION", forestactivatorAnimation);
    forestactivatorAnimator->AddAnimation("FOREST ACTIVATOR ANIMATION2", forestactivatorAnimation2);
}

/**
    @brief that function updates the components of the forest two.
*/
void ForestActivatorScript2::ComponentUpdate() {
    // Check the animator's state, and ifs true, play animation and activate it. 
    if (!animator->IsPlaying("FOREST ACTIVATOR ANIMATION") && activate==0 && runned==false) {
        animator->PlayAnimation("FOREST ACTIVATOR ANIMATION");
        activate=1;
        runned=true;
    }

    // Check if runned and something diferent of animator is playing and active the animattion of the forest.
    if (runned && !animator->IsPlaying("FOREST ACTIVATOR ANIMATION")) {
        animator->PlayAnimation("FOREST ACTIVATOR ANIMATION2");
    }

    // Checking script running state, and ifs true, activate the script.
    if (runned) {
        auto script = (CentralLightScript1*)SceneManager::GetInstance()->
                       GetCurrentScene()->GetGameObject("CENTRAL LIGHT 1")->
                       GetComponent("CentralLightScript1");
        script->Activate();
    }
}

/**
    @brief that function fixs the components updates of the forest two.
*/
void ForestActivatorScript2::FixedComponentUpdate() {

}
