/**
    @file FirstBossAttackScript.cpp
    @brief  Manage the animations for the first boss attack effect.
    @copyright MIT License.
*/

#include "Customs/FirstBossAttackScript.hpp"
#include "Customs/AudioController.hpp"

/**
    @brief Constructor for the FirstBossAttackScript class.
*/
FirstBossAttackScript::FirstBossAttackScript(GameObject *owner) : Script(owner) {

}

/**
    @brief Start the animation for the first boss attack effect.
*/
void FirstBossAttackScript::Start() {
    /*
        Creates the animations defining position the place to insert
        and the scene that will be inserted.
    */
    CreateAnimations();
    m_position = GetOwner()->GetPosition();
    m_animator = (Animator *)GetOwner()->GetComponent("Animator");
    m_input = InputSystem::GetInstance();
    auto map = SceneManager::GetInstance()->
                             GetScene("Gameplay")->GetGameObject("Map");

    // Checks map status to set its properties.
    if (map) GetOwner()->SetZoomProportion(
                       Vector(map->originalWidth/GetOwner()->originalWidth,
                              map->originalHeight/GetOwner()->originalHeight));
    m_firstBossAttackCollider = new RectangleCollider(GetOwner(), Vector(0, 0),
                                                   GetOwner()->GetWidth(),
                                                   GetOwner()->GetHeight(), 0);
}

/**
    @brief Create the first boss attack effect animations.
*/
void FirstBossAttackScript::CreateAnimations() {

    //Image Attacks.
    auto firstBossAttackImage = new Image("assets/firstBossAttack.png",0,0,600,
                                          151);
    //Surge Animation.
    auto firstBossAttackSurgeAnimation = new Animation(GetOwner(),
                                                       firstBossAttackImage);

    // Sets the frames for the first boss animation.
    for (int counter = 0; counter < 15; counter++) {
        firstBossAttackSurgeAnimation->AddFrame(new Frame(counter * 40, 0,
                                                            40, 151));
    }

    //Idle Animation.
    auto firstBossAttackIdleAnimation = new Animation(GetOwner(),
                                                      firstBossAttackImage);
    firstBossAttackIdleAnimation->AddFrame(new Frame(14 * 40, 0, 40, 151));

    //Gone Animation.
    auto firstBossAttackGoneAnimation = new Animation(GetOwner(),
                                                    firstBossAttackImage );

    // Sets the frames for the gone boss attack animation.
    for (int counter = 14; counter != 0; counter--) {
        firstBossAttackGoneAnimation->AddFrame(new Frame(counter * 40, 0,
                                                                   40, 151));
    }


    //Animator of boss attack.
    auto firstBossAttackAnimator = new Animator(GetOwner());
    //Surge Animator of boss attack.
    firstBossAttackAnimator->AddAnimation("firstBossAttackSurgeAnimation",
                                             firstBossAttackSurgeAnimation);
    //Idle Animator of boss attack.
    firstBossAttackAnimator->AddAnimation("firstBossAttackIdleAnimation",
                                            firstBossAttackIdleAnimation);
    //Gone Animator of boss attack.
    firstBossAttackAnimator->AddAnimation("firstBossAttackGoneAnimation",
                                            firstBossAttackGoneAnimation);
}

/**
    @brief Start a boss attack animation  if he is in the scene.
    If the attack is inactive, it is active.

*/
void FirstBossAttackScript::ComponentUpdate() {
    /*
        Checks if the attack variable is true,
        if it starts the attack function.
    */

    // Checks the attack status.
    if(attack) {
       Attack();
    }

    // Checks the input system status set the attack status.
    if(InputSystem::GetInstance()->GetKeyUp(INPUT_M) && attack == false){
        attack = true;
    }

}

/**
    @brief Determine the time of attack os boss.
*/
void FirstBossAttackScript::FixedComponentUpdate() {
    timerAnimation.Update(EngineGlobals::fixed_update_interval);

    // Checks the status of the deasactivateobject.
    if (deactivateObj){
        timerGone.Update(EngineGlobals::fixed_update_interval);
    }

    CameraShakeAttack();
}

/**
    @brief Creates the attack by setting the animation.
*/
void FirstBossAttackScript::Attack() {
    /*
        Starts an attack, causes the camera to shake, restarts the attack time,
        and sets the sound effect.
    */

    // Checks surge animation status to set its properties.
    if (m_surgeAnimation) {
        CameraSystem::GetInstance()->CameraShake(8,3, SceneManager::GetInstance()
                                                 -> GetCurrentScene());
        m_animator -> PlayAnimation("firstBossAttackSurgeAnimation");
        m_surgeAnimation = false;
        m_idleAnimation = true;
        timerAnimation.Restart();
        AudioController::GetInstance()->PlayAudio("secondAttackSound", 0);

    }

    // Compares the idle animation, to activate the animator.
    if (m_idleAnimation && timerAnimation.GetTime() >= 1 * 1000) {
        m_animator -> PlayAnimation("firstBossAttackIdleAnimation");
    }

    // Checks gone animation status to set its properties.
    if (goneAnimation) {
        m_animator->PlayAnimation("firstBossAttackGoneAnimation");
        AudioController::GetInstance() -> PlayAudio("fourthAttackSound", 0);
        goneAnimation = false;
        m_idleAnimation = false;
        attack = false;
        m_surgeAnimation = true;
        deactivateObj = true;
        GetOwner()->active = false;
    }

    // Compares the timer gone animation to update the desactivateobj.
    if(timerGone.GetTime() >= 1 * 1000) {
        timerGone.Restart();
        deactivateObj = false;
    }
}

void FirstBossAttackScript::CameraShakeAttack(){
    // Creates the effect that makes the camera shake.

    // Checks shake status to update its properties.
    if (cameraShake) {
        CameraSystem::GetInstance() -> CameraShake(8, 1, SceneManager::GetInstance()
                                                   -> GetCurrentScene());
        if (!CameraSystem::GetInstance() -> IsShaking()){
            cameraShake = false;
        }
  }
}
