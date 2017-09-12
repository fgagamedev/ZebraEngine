#include "Customs/FirstBossScript.hpp"
/**
    @file FirstBossScript.cpp
    @brief Creates and handles with the first boss behavior.
    @copyright MIT License.
*/

/**
    @brief Constructor for the class FirstBossScript.
*/
FirstBossScript::FirstBossScript(GameObject *owner) : Script(owner) {}

void FirstBossScript::Start() {

    CreateAnimations();

    position = GetOwner()->GetPosition();
    animator = (Animator *)GetOwner()->GetComponent("Animator");
    input = InputSystem::GetInstance();
    auto map = SceneManager::GetInstance()->GetScene("Gameplay")->GetGameObject("Map");

    if (map) {
        GetOwner()->SetZoomProportion(Vector(
                            map->originalWidth/GetOwner()->originalWidth,
                            map->originalHeight/GetOwner()->originalHeight));
        firstBossCollider = new RectangleCollider(GetOwner(),
                                                  Vector(0, 0),
                                                  GetOwner()->GetWidth(),
                                                  GetOwner()->GetHeight(), 0);
    }
}

/**
    @brief Creates logic behind the firs boss animations to be shown during the
    game.
*/
void FirstBossScript::CreateAnimations() {

    auto firstBossImage = new Image("assets/boss1.png",0,0,1896, 324);
    auto firstBossJumpImage = new Image("assets/boss1_jump.png",0,0,1180, 406);

    auto firstBossAnimation = new Animation(GetOwner(),firstBossImage);
    for (int i = 0; i < 8; i++) {
        firstBossAnimation->AddFrame(new Frame(i * 237,0, 237, 406));
    }

    auto firstBossJumpAnimation = new Animation(GetOwner(),firstBossJumpImage);
    for (int i = 0; i < 5; i++) {
        firstBossJumpAnimation->AddFrame(new Frame(i * 236,0, 236, 406));
        firstBossJumpAnimation->AddFrame(new Frame(i * 236,0, 236, 406));

        if (i == 4) {
            for (int animMulti = 0 ; i < 8 ; i++) {
                firstBossJumpAnimation->AddFrame(new Frame(i * 236,0, 236, 406));
                firstBossJumpAnimation->AddFrame(new Frame(i * 236,0, 236, 406));
            }
        }
    }

    // Second Attack
    auto firstBossFallAnimation = new Animation(GetOwner(),firstBossJumpImage);
    for (int i = 5; i > 0; i--) {
        firstBossFallAnimation->AddFrame(new Frame(i * 236, 0, 236, 406));
        firstBossFallAnimation->AddFrame(new Frame(i * 236, 0, 236, 406));
    }

    // Animator
    auto firstBossAnimator = new Animator(GetOwner());
    firstBossAnimator->AddAnimation("firstBossAnimation", firstBossAnimation);
    firstBossAnimator->AddAnimation("firstBossJumpAnimation",
                                    firstBossJumpAnimation);
    firstBossAnimator->AddAnimation("firstBossFallAnimation",
                                    firstBossFallAnimation);
}

/**
    @brief Decides what happens to the boss depending on the game's circumstances.
*/
void FirstBossScript::ComponentUpdate() {

    if (!SecondAttack && !SecondAttackFall) {
        //Idle animation
        animator->PlayAnimation("firstBossAnimation");
    }

    if (input->GetKeyPressed(INPUT_N)) {
        SecondAttack = true;
        animator->PlayAnimation("firstBossJumpAnimation");
    }
}

/**
    @brief Handles with the boss behavior depending on which attack is being shot.
*/
void FirstBossScript::FixedComponentUpdate() {
    if (FirstAttack) {
        timerFirstAttackCooldown.Update(EngineGlobals::fixed_update_interval);
    }

    if (goneFirstAttack) {
        timerFirstAttackGone.Update(EngineGlobals::fixed_update_interval);
    }

    if (SecondAttack) {
        timerSecondAttack.Update(EngineGlobals::fixed_update_interval);
    }

    if (SecondAttackFall) {
        timerSecondAttackFall.Update(EngineGlobals::fixed_update_interval);
    }

    timerAttackCooldown.Update(EngineGlobals::fixed_update_interval);

    Attack();

    if (shake) {
        // CameraShake(intensity, duration in seconds)
        CameraSystem::GetInstance()->CameraShake(8,1,
                                SceneManager::GetInstance()->GetCurrentScene());
        if (!CameraSystem::GetInstance()->IsShaking()) {
            shake = false;
        }
    }
}

/**
    @brief Manages the shot's position and its behavior, the time it takes to
    happen, etc.
*/
void FirstBossScript::Attack() {
    if (GetOwner()->active) {
        // Rand first attack or second attack
        if (timerAttackCooldown.GetTime() >= 9*1000) {
            // Choose a new number
            randNum = rand() % 2;
            timerAttackCooldown.Restart();
            cout << randNum << endl;
        }

        if (randNum == 0 && SecondAttackFall == false) {
            SecondAttack = true;
            animator->PlayAnimation("firstBossJumpAnimation");
        }

        if (randNum == 1) {
            FirstAttack = true;
            // First Attack
            if (timerFirstAttackCooldown.GetTime() >= 2*1000
                    && firstAttackCounter < 3) {
                FirstBossController::GetInstance()->FirstAttackSurge();
                timerFirstAttackCooldown.Restart();
                firstAttackCounter++;
                // Delay for next sord
            }
            if (firstAttackCounter == 3) {
                // Activate timer to gone tentacle
                goneFirstAttack = true;
            }

            // Wait 6 seconds to make attack gone
            if (timerFirstAttackGone.GetTime() >= 2*1000) {
                FirstBossController::GetInstance()->FirstAttackGone();

                firstAttackCounter = 0;
                goneFirstAttack = false;
                timerFirstAttackGone.Restart();
                timerFirstAttackCooldown.Restart();
                randNum = -1;
            }
        }

        if ((timerSecondAttack.GetTime() >= 0.5*1000) && SecondAttack) {
            if (GetOwner()->GetPosition()->m_y > -1900) {
                Vector *newPosition = GetOwner()->GetPosition();

                newPosition->m_y = newPosition->m_y - 90;
                GetOwner()->SetPosition(*newPosition);
            } else {
                SecondAttack = false;
                SecondAttackFall = true;
                timerSecondAttack.Restart();
            }
        }

        if (timerSecondAttackFall.GetTime() >= 2*1000 && SecondAttackFall) {
            // Get player Position
            player = SceneManager::GetInstance()->GetCurrentScene()->GetGameObject("NakedMan");
            playerPosition.m_x = player->GetPosition()->m_x - 160;
            playerPosition.m_y = player->GetPosition()->m_y - 450;
            cout << "flag" << endl;

            std::cout << playerPosition.m_x << "  " << playerPosition.m_y << std::endl;

            GetOwner()->m_position->m_x = playerPosition.m_x;
            if (GetOwner()->m_position->m_y < playerPosition.m_y) {
                GetOwner()->m_position->m_y += 90;
                shake = true;
                animator->PlayAnimation("firstBossFallAnimation");
            } else {
                SecondAttackFall = false;
                shake = false;
                randNum = -1;
            }
        }
    }
}
