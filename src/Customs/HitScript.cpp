/**
    @file HitScripr.cpp
    @brief Responsible for organizing sound effects script.
    @copyright MIT License.
*/

#include "Customs/HitScript.hpp"

#include "Globals/EngineGlobals.hpp"

const int imagePositionX = 0;
const int imagePositionY = 0;
const int imageWidth = 1024;
const int imageHeight = 1024;

const int framePositionX = 0;
const int framePositionY = 0;
const int frameWidth = 1024;
const int frameHeight = 1024;

/**
    @brief Constructor for the classe HitScript.
*/
HitScript::HitScript(GameObject *owner) : Script(owner) {

}

/**
    @brief Sets the initial definitions when starting the sound effect.
*/
void HitScript::Start() {

    // Creates the animations and the animator for the hit script.
    CreateAnimations();


    position = GetOwner()->GetPosition();

    animator = (Animator *)GetOwner()->GetComponent("Animator");

    // Get the inputs.
    input = InputSystem::GetInstance();

    GetOwner()->SetZoomProportion(Vector(0,0));

}

/**
    @brief Generates the animations on the hit script.
*/
void HitScript::CreateAnimations(){

    auto hitImage = new Image("assets/Sprites/Blood/blood4.png",imagePositionX, imagePositionY, imageWidth, imageHeight);

    auto firstHitAnimation= new Animation(GetOwner(),hitImage);

    firstHitAnimation->AddFrame(new Frame(framePositionX, framePositionY, frameWidth, frameHeight));

    // animator.
    auto hitAnimator = new Animator(GetOwner());
    hitAnimator->AddAnimation("firstHitAnimation",firstHitAnimation);

}

/**
    @brief Handles with changes on the component.
*/
void HitScript::ComponentUpdate() {

    if(hit){
        switch(hitLevel){
            case 0: //No hit
                hit = false;
                break;
            case 1://Hit 1          
                break;
            case 2:// Hit 2
                break;
            case 3:// Hit 3
                break;
        }
    }else {
        //nothing to do.
    }

    if(input->GetKeyDown(INPUT_I)){
        hit = true;
    } else {
        // nothing to do.
    }

}

void HitScript::FixedComponentUpdate() {

  position->m_x = 0;

  position->m_y = 0;
}
