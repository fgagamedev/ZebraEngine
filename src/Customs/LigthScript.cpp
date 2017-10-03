#include "Customs/LightScript.hpp"
#include "Globals/EngineGlobals.hpp"

LightScript::LightScript(GameObject *owner) : Script(owner) {}

/**
    @brief that function starts the light script. Create the animation,
    position, the animator and the input.
*/
void LightScript::Start() {
    // Create animations, define position and animator by gameobject.
    CreateAnimations();
    position = GetOwner()->GetPosition();
    animator = (Animator *)GetOwner()->GetComponent("Animator");
    input = InputSystem::GetInstance();
    // Not affected by zoom.
    GetOwner()->SetZoomProportion(Vector(0,0));
}

/**
    @brief that function creates the animations of the light script. Create the
    light image, the light animation and animator.
*/
void LightScript::CreateAnimations(){
    // Instantiating lightimage by image file and define its positons.
    auto lightImage = new Image("assets/luz.png",0,0,682, 512);

    // Instantiating light animation by gameobject components, image and play state.
    auto lightAnimation = new Animation(GetOwner(),lightImage );

    // Setting frames of light animation.
    lightAnimation->AddFrame(new Frame(0,0, 682, 512));

    // Instantiating animator, and setting its animation.
    auto lightAnimator = new Animator(GetOwner());
    lightAnimator->AddAnimation("lightAnimation", lightAnimation);
}

/**
    @brief that function updates the components of the light script. Create the player
    and get his instance, currante scene and object ("NakedMan")
*/
void LightScript::ComponentUpdate() {
    // Defining player.
    player = SceneManager::GetInstance()->GetCurrentScene()->GetGameObject("NakedMan");
    // Check for the player and its animator and input state.
    if (player) {
        if (play==1) {
            animator->PlayAnimation("lightAnimation");
        }

        if (input->GetKeyDown(INPUT_Y) && play==0) {
            play=1;
        }

        else if (input->GetKeyDown(INPUT_Y) && play==1) {
            play=0;
        }

    }
}

/**
    @brief that function fixs the components update of the light script. Check if
    there is a player and get his position x and y.
*/
void LightScript::FixedComponentUpdate() {
    // Check for the player's state, and if is true, sets its x and y positions.
    if (player) {
        position->m_x = player->GetPosition()->m_x - GetOwner()->GetWidth() / 2 + 40;
        position->m_y = player->GetPosition()->m_y - GetOwner()->GetHeight() / 2 + 40;
    }
}
