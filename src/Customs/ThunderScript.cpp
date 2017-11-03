/**
    @file ThunderScript.cpp
    @brief Manage the thunders animations of the game.
    @copyright MIT License.
*/

#include "Customs/ThunderScript.hpp"

#include "Globals/EngineGlobals.hpp"

const int thunderWidth = 2952;
const int thunderHeight = 815;
const int blueFrameWidth = 100;
const int yellowFrameWidth = 59;
const int framePositionY = 135;
const int frameHeight = 267;
const int yellowCounter = 5;
const int blueCounter = 6;

/**
    @brief Constructor for the ThunderScript class.
    @param[in] owner
*/
ThunderScript::ThunderScript(GameObject *owner) : Script(owner) {}

/**
    @brief Start the animation for thunder in game.
*/
void ThunderScript::Start() {
    /*
        Creates the animations defining position the place to insert
        and the scene that will be inserted.
    */
    CreateAnimations();
    m_position = GetOwner()->GetPosition();
    m_animator = (Animator *)GetOwner()->GetComponent("Animator");
    m_input = InputSystem::GetInstance();
    GetOwner()->SetZoomProportion(Vector(0,0));
}

/**
    @brief Create animations of thunders with different colors.
*/
void ThunderScript::CreateAnimations() {
    //Image Thunder.
    auto thunderImage = new Image("assets/Sprites/dashes.png", 0, 0, thunderWidth, thunderHeight);

    // Animation thunder blue.
    auto thunderBlueAnimation = new Animation(GetOwner(), thunderImage);

    // Sets the frames for the blue thunder animation.
    for (int i = 0; i < blueCounter; i++) {
        thunderBlueAnimation->AddFrame(new Frame(i * 100, framePositionY, blueFrameWidth, frameHeight));
    }

    // Animation thunder wellow.
    auto thunderYellowAnimation = new Animation(GetOwner(),thunderImage);
    
    // Sets the frames for the yellow thunder animation.
    for (int i = 0; i < yellowCounter; i++) {
        thunderYellowAnimation->AddFrame(new Frame(555 + (i * yellowFrameWidth), framePositionY, 
                                                    yellowFrameWidth, frameHeight));
    }

    // Animator thunder.
    auto thunderAnimator = new Animator(GetOwner());

    thunderAnimator->AddAnimation("thunderBlueAnimation", thunderBlueAnimation);
    thunderAnimator->AddAnimation("thunderYellowAnimation",
                                  thunderYellowAnimation);
}

/**
    @brief Change the thunder animation based on the pressed button.
*/
void ThunderScript::ComponentUpdate() {
    // Checks the input status to set the blue animation.
    if (m_input->GetKeyDown(INPUT_1)) {
        m_animator->PlayAnimation("thunderBlueAnimation");
    }

    // Checks the input status to set the yellow animation.
    if (m_input->GetKeyDown(INPUT_2)) {
        m_animator->PlayAnimation("thunderYellowAnimation");
    } else {
        //nothing to do.
    }
}

/**
    @brief Do nothing.
*/
void ThunderScript::FixedComponentUpdate() {
}
