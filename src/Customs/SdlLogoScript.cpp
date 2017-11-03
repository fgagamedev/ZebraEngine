/**
    @file SdlLogoScript.hpp
    @brief Responsible for creating the Simple DirectMedia Layer 
           script at the beginning of the game.
    @copyright MIT License.
*/

#include "Customs/SdlLogoScript.hpp"

#include "Globals/EngineGlobals.hpp"

const int imageSDLPositionX = 0;
const int imageSDLPositionY = 0;
const int imageSDLWidth = 5115;
const int imageSDLHeight = 512;

const int frameSDL1PositionX = 341;
const int frameSDL1PositionY = 0;
const int frameSDL1Width = 341;
const int frameSDL1Height = 256;

const int frameSDL2PositionX = 341;
const int frameSDL2PositionY = 256;
const int frameSDL2Width = 341;
const int frameSDL2Height = 256;

SdlLogoScript::SdlLogoScript(GameObject *owner) : Script(owner) {

}

/**
    @brief Creates the animations of the sdl logo presentation, with some of the gameobject
    properties.
*/
void SdlLogoScript::Start() {

    CreateAnimations();

    position = GetOwner()->GetPosition();

    animator = (Animator *)GetOwner()->GetComponent("Animator");

    input = InputSystem::GetInstance();
    
    GetOwner()->SetZoomProportion(Vector(0,0));
    INFO("Logo script SDL started");
}

/**
    @brief Positions the animations SDL in start game, through the settings of frames,
    and image's position.
*/
void SdlLogoScript::CreateAnimations(){

    auto sdl_LogoSprite = new Image("assets/introsdl.png", imageSDLPositionX, 
                                   imageSDLPositionY, imageSDLWidth, imageSDLHeight);
    auto sdlAnimation = new Animation(GetOwner(), sdl_LogoSprite);

    for (int i = 0; i < 15; i++){
        sdlAnimation->AddFrame(new Frame(i * frameSDL1PositionX, frameSDL1PositionY, 
                                        frameSDL1Width, frameSDL1Height));
        for (i = 0; i < 15; i++){
            sdlAnimation->AddFrame(new Frame(i * frameSDL2PositionX, frameSDL2PositionY, 
                                            frameSDL2Width, frameSDL2Height));
        }
    }
    
    auto sdlAnimator = new Animator(GetOwner());
    sdlAnimation->SetFramesPerSecond(9);
    sdlAnimator->AddAnimation("SDL ANIMATION", sdlAnimation);
    INFO("Create Animations SDL");
}

/**
    @brief Updates the animator component by looking for a previous
    light animation.
*/
void SdlLogoScript::ComponentUpdate() {

}
void SdlLogoScript::FixedComponentUpdate() {

    time.Update(1);

    if(time.GetTime()>=130){
        animator->PlayAnimation("SDL ANIMATION");
    }
    if(time.GetTime()>=230){
        animator->StopAllAnimations();
    }

}
