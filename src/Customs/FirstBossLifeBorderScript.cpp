/**
    @file FirstBossLifeBorderScript.cpp
    @brief Class that defines methods and attributes for
    activating the first boss life border script.
    @copyright LGPL. MIT License.
*/

#include "Customs/FirstBossLifeBorderScript.hpp"

const float vectorAxisX = 0;
const float vectorAxisY = 0;

const int imageBorderPositionX = 0;
const int imageBorderPositionY = 0;
const int imageBorderWidth = 996;
const int imageBorderHeight = 171;

const int frameBorderPositionX = 332;
const int frameBorderPositionY = 9;
const int frameBorderWidth = 332;
const int frameBorderHeight = 9;

const int maxColumn = 19;
const int maxRow = 3;

/**
    @brief Initializes irstBossLifeBorderScript instance.
    @param[in] GameObject *owner - owns the component.
*/
FirstBossLifeBorderScript::FirstBossLifeBorderScript(GameObject *owner) :
    Script(owner) {

    }


/**
    @brief Start the animation for the first boss life border effect.
*/
void FirstBossLifeBorderScript::Start() {

    CreateAnimations();

    // Creates the animator.
    animator = (Animator *)GetOwner()->GetComponent("Animator");
    input = InputSystem::GetInstance();
    position = GetOwner()->GetPosition();
    GetOwner()->SetZoomProportion(Vector(vectorAxisX, vectorAxisY));
    firstBossAttackCollider = new RectangleCollider(GetOwner(), Vector(vectorAxisX, vectorAxisY),
                                                  GetOwner()->GetWidth(),
                                                  GetOwner()->GetHeight(), 0);

}

/**
    @brief Create the first boss life border effect animations.
*/
void FirstBossLifeBorderScript::CreateAnimations() {

    // Creates the image.
    auto firstBossLifeBorderImage = new Image("assets/boss_life_bar.png",imageBorderPositionX,
                                              imageBorderPositionY, imageBorderWidth, imageBorderHeight);

    // Creates the animation
    auto firstBossLifeBorderAnimation = new Animation(GetOwner(),
                                        firstBossLifeBorderImage );
    // Creates the boss's life bar
    for (int column = 0; column < maxColumn; column++) {
        for (int row = 0 ; row < maxRow ; row++) {
            firstBossLifeBorderAnimation->AddFrame(new Frame(row * frameBorderPositionX,
                                                       column * frameBorderPositionY, frameBorderWidth, frameBorderHeight));
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
