/**
    @file FirstBossLifeBorderScript.cpp
    @brief Class that defines methods and attributes for
    activating the first boss life border script.
    @copyright LGPL. MIT License.
*/

#include "Customs/FirstBossLifeBorderScript.hpp"

/**
    @brief Initializes irstBossLifeBorderScript instance.
    @param[in] GameObject *owner - owns the component.
*/
FirstBossLifeBorderScript::FirstBossLifeBorderScript(GameObject *owner) :
    Script(owner) {}


/**
    @brief Start the animation for the first boss life border effect.
*/
void FirstBossLifeBorderScript::Start() {

    CreateAnimations();

    // Creates the animator.
    animator = (Animator *)GetOwner()->GetComponent("Animator");
    input = InputSystem::GetInstance();
    position = GetOwner()->GetPosition();
    GetOwner()->SetZoomProportion(Vector(0,0));
    firstBossAttackCollider = new RectangleCollider(GetOwner(), Vector(0, 0),
                                                  GetOwner()->GetWidth(),
                                                  GetOwner()->GetHeight(), 0);

}

/**
    @brief Create the first boss life border effect animations.
*/
void FirstBossLifeBorderScript::CreateAnimations() {

    // Creates the image.
    auto firstBossLifeBorderImage = new Image("assets/Barra_Life_Boss.png",0,0,
                                                                    996, 171);

    // Creates the animation
    auto firstBossLifeBorderAnimation = new Animation(GetOwner(),
                                        firstBossLifeBorderImage );
    for (int column = 0; column < 19; column++) {
        for (int row = 0 ; row < 3 ; row++) {
            firstBossLifeBorderAnimation->AddFrame(new Frame(row * 332,
                                                       column * 9, 332, 9));
    }
  }


    // Creates and add the animator.
    auto firstBossLifeBorderAnimator = new Animator(GetOwner());
    firstBossLifeBorderAnimator->AddAnimation("firstBossLifeBorderAnimation",
                                                firstBossLifeBorderAnimation);
}

/**
    @brief Updates the component of boss life border.
*/
void FirstBossLifeBorderScript::ComponentUpdate() {

}

/**
    @brief Updates the animator component and boss position.
*/
void FirstBossLifeBorderScript::FixedComponentUpdate() {
    animator->PlayAnimation("firstBossLifeBorderAnimation");

    // Sets the position x.
    position->m_x = 646;

    // Sets the position y.
    position->m_y = 10;
}
