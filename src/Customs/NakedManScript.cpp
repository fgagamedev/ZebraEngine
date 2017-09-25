/**
    @file NakedManScript.cpp
    @brief Manages the functions of the player in the game.
    @copyright LGPL. MIT License.
*/

#include "Customs/NakedManScript.hpp"
#include "Customs/FirstBossController.hpp"
#include "Customs/AudioController.hpp"
#include "Customs/MapScript.hpp"
#include "Customs/SnowScript.hpp"
#include "Customs/RainScript.hpp"

#include <math.h>
#include <stdio.h>


bool NakedManScript::isZooming = false;

/**
    @brief Constructor of the class NakedManScript.
    @param[in] GameObject *owner - Owns the component.
*/
NakedManScript::NakedManScript(GameObject *owner) : Script(owner) {}

/**
    @brief Start the first definitions of the player.
*/
void NakedManScript::Start() {
    CreateAnimations();
    position = GetOwner()->GetPosition();
    animator = (Animator *)GetOwner()->GetComponent("Animator");
    input = InputSystem::GetInstance();
    CameraSystem::GetInstance()->SetCameraSpeed(walkSpeed);
    game_controller = input->GetGameController(0);

    auto map = SceneManager::GetInstance()->GetScene("Gameplay")
               ->GetGameObject("Map");
    if (map) {
		GetOwner()->SetZoomProportion(Vector(map->originalWidth
                                             / GetOwner()->originalWidth,
                                             map->originalHeight
                                             / GetOwner()->originalHeight));
	}

    nakedManCollider = new RectangleCollider(GetOwner(), Vector(0, 0),
	                                         GetOwner()->GetWidth(),
											 GetOwner()->GetHeight(), 0);
}

/**
    @brief Sets the direction of the player based on the mouse position
    or game controller.
*/
void NakedManScript::SetDirection() {
	// Get current mouse position
    mousePosition = input->GetMousePosition();

    if (!game_controller) {
        /*
            Detect if player is moving and looking in same direction
            based in x, y player's positions and x, y mouse positions.
        */
        mousePosition = input->GetMousePosition();
        if (mousePosition.first >= position->m_x && movements == 4){
            isMovingLooking = true;
        } else if (mousePosition.first > position->m_x && movements == 3) {
            isMovingLooking = false;
        }

        if (mousePosition.first <= position->m_x && movements == 3) {
            isMovingLooking = true;
        } else if (mousePosition.first < position->m_x && movements == 4) {
            isMovingLooking = false;
        }

        // y-axis
        if (mousePosition.second <= position->m_y && movements == 1) {
            isMovingLooking = true;
        } else if (mousePosition.second < position->m_y && movements == 2) {
            isMovingLooking = false;
        }

        if (mousePosition.second >= position->m_y && movements == 2) {
            if(mousePosition.second >= position->m_y && movements == 2) {
                isMovingLooking = true;
            } else if (mousePosition.second > position->m_y && movements == 1) {
                isMovingLooking = false;
            }

            // Diagonal 1
            if (mousePosition.first >= position->m_x && mousePosition.second
                <= position->m_y && movements == 6) {
                isMovingLooking = true;
            } else if (mousePosition.second > position->m_y && movements == 1) {
                isMovingLooking = false;
            }
        }

        // Diagonal 2
        if (mousePosition.first >= position->m_x && mousePosition.second
            >= position->m_y && movements == 8) {
            isMovingLooking = true;
        } else if (mousePosition.first >= position->m_x && mousePosition.second
            >= position->m_y && movements == 5) {
            isMovingLooking = false;
        }

        if (mousePosition.first <= position->m_x && mousePosition.second
            <= position->m_y && movements == 5) {
            isMovingLooking = true;
        } else if (mousePosition.first <= position->m_x && mousePosition.second
            <= position->m_y && movements == 8) {
            isMovingLooking = false;
        }
    } else {
        /*
            Detect if player is moving and looking in same direction
            based in x, y player's positions and x, y game controller positions.
        */
        if (game_controller->GetAxis(GC_INPUT_AXIS_RIGHTX) >= 800
            && movements == 4) {
            isMovingLooking = true;
        } else if (game_controller->GetAxis(GC_INPUT_AXIS_RIGHTX) > 800
            && movements == 3) {
            isMovingLooking = false;
        }

        if (game_controller->GetAxis(GC_INPUT_AXIS_RIGHTX) <=-800
            && movements == 3) {
            isMovingLooking = true;
        } else if (game_controller->GetAxis(GC_INPUT_AXIS_RIGHTX) < -800
                   && movements == 4) {
            isMovingLooking = false;
        }

        // Y-axis
        if (game_controller->GetAxis(GC_INPUT_AXIS_RIGHTY)
            <= -800 && movements == 1) {
            isMovingLooking = true;
        } else if (game_controller->GetAxis(GC_INPUT_AXIS_RIGHTY) < -800
                   && movements == 2) {
            isMovingLooking = false;
        }

        if (game_controller->GetAxis(GC_INPUT_AXIS_RIGHTY) >= 800
            && movements == 2) {
            isMovingLooking = true;
        } else if (game_controller->GetAxis(GC_INPUT_AXIS_RIGHTY) > 800
                   && movements == 1) {
            isMovingLooking = false;
        }

        // Diagonal 1
        if (game_controller->GetAxis(GC_INPUT_AXIS_RIGHTX) > 800
            && game_controller->GetAxis(GC_INPUT_AXIS_RIGHTY) <=-800
            && movements == 6) {
            isMovingLooking = true;
        } else if (game_controller->GetAxis(GC_INPUT_AXIS_RIGHTX) >= 800
                   && game_controller->GetAxis(GC_INPUT_AXIS_RIGHTY) <= -800
                   && movements == 7) {
            isMovingLooking = false;
        }

        if (game_controller->GetAxis(GC_INPUT_AXIS_RIGHTX) <= -800
            && game_controller->GetAxis(GC_INPUT_AXIS_RIGHTY) >= 800
            && movements == 7) {
            isMovingLooking = true;
        } else if (game_controller->GetAxis(GC_INPUT_AXIS_RIGHTX) <= -800
                   && game_controller->GetAxis(GC_INPUT_AXIS_RIGHTY) >= 800
                   && movements == 6) {
            isMovingLooking = false;
        }

        // Diagonal 2
        if (game_controller->GetAxis(GC_INPUT_AXIS_RIGHTX) >= 800
            && game_controller->GetAxis(GC_INPUT_AXIS_RIGHTY) >= 800
            && movements == 8) {
            isMovingLooking = true;
        } else if (game_controller->GetAxis(GC_INPUT_AXIS_RIGHTX) >= 800
                   && game_controller->GetAxis(GC_INPUT_AXIS_RIGHTY) >= 800
                   && movements == 5) {
            isMovingLooking = false;
        }
        if (game_controller->GetAxis(GC_INPUT_AXIS_RIGHTX) <= -800
            && game_controller->GetAxis(GC_INPUT_AXIS_RIGHTY) <= -800
            && movements == 5) {
            isMovingLooking = true;
        } else if (game_controller->GetAxis(GC_INPUT_AXIS_RIGHTX) <= -800
                   && game_controller->GetAxis(GC_INPUT_AXIS_RIGHTX) <= -800
                   && movements == 8) {
            isMovingLooking = false;
        }
    }
}

/**
    @brief Detect the keyboards that are being pressed to move the player.
*/
void NakedManScript::KeyBoardUpdate() {
    // Detect if zoom is required.
    if ((input->GetKeyPressed(INPUT_DOWN))
         || (input->GetKeyPressed(INPUT_UP))) {
        isZooming = true;
    }
    if ((input->GetKeyUp(INPUT_DOWN)) || (input->GetKeyUp(INPUT_UP))) {
        isZooming = false;
    }


    /*
        Define move direction and adjust player's image according
        to the direction he's looking and the presseds keys.
    */
    if (isMovingLooking) {
        if (input->GetKeyPressed(INPUT_W) && input->GetKeyPressed(INPUT_A)) {
            movements = 5;
            lastDirection = 5;
            animator->GetAnimation("Walk Side")->SetFlip(true, false);
            animator->PlayAnimation("Walk Side");
        } else if (input->GetKeyPressed(INPUT_W)
                   && input->GetKeyPressed(INPUT_D)) {
            movements = 6;
            lastDirection = 6;
            animator->GetAnimation("Walk Side")->SetFlip(false, false);
            animator->PlayAnimation("Walk Side");
        } else if (input->GetKeyPressed(INPUT_S)
                   && input->GetKeyPressed(INPUT_A)) {
            movements = 7;
            lastDirection = 7;
            animator->GetAnimation("Walk Side")->SetFlip(true, false);
            animator->PlayAnimation("Walk Side");
        } else if (input->GetKeyPressed(INPUT_S)
                   && input->GetKeyPressed(INPUT_D)) {
            movements = 8;
            lastDirection = 8;
            animator->GetAnimation("Walk Side")->SetFlip(false, false);
            animator->PlayAnimation("Walk Side");
        } else if (input->GetKeyPressed(INPUT_W)) {
            lastDirection = 0;
            movements = 1;
            animator->PlayAnimation("Walk Up");
        } else if (input->GetKeyPressed(INPUT_S)) {
            lastDirection = 1;
            movements = 2;
            animator->PlayAnimation("Walk Down");
        } else if (input->GetKeyPressed(INPUT_A)) {
            lastDirection = 3;
            movements = 3;
            animator->GetAnimation("Walk Side")->SetFlip(true, false);
            animator->PlayAnimation("Walk Side");
        } else if (input->GetKeyPressed(INPUT_D)) {
            lastDirection = 3;
            movements = 4;
            animator->GetAnimation("Walk Side")->SetFlip(false, false);
            animator->PlayAnimation("Walk Side");
        } else {
            if(lastDirection == 2) {
                animator->PlayAnimation("Stop Left");
            } else if (lastDirection == 3|| lastDirection == 6
                       || lastDirection == 7 || lastDirection == 5
                       || lastDirection == 5 || lastDirection == 8 ) {
                animator->PlayAnimation("Stop Right");
            } else if (lastDirection == 0) {
                animator->PlayAnimation("Stop Up");
            } else if (lastDirection == 1) {
                animator->PlayAnimation("Stop Down");
            }
        }
    } else {
        if (input->GetKeyPressed(INPUT_W) && input->GetKeyPressed(INPUT_A)) {
            movements = 5;
            lastDirection = 5;
            animator->GetAnimation("Back Walk Side")->SetFlip(false, false);
            animator->PlayAnimation("Back Walk Side");
        } else if (input->GetKeyPressed(INPUT_W)
                   && input->GetKeyPressed(INPUT_D)) {
            movements = 6;
            lastDirection = 6;
            animator->GetAnimation("Back Walk Side")->SetFlip(true, false);
            animator->PlayAnimation("Back Walk Side");
        } else if (input->GetKeyPressed(INPUT_S)
                   && input->GetKeyPressed(INPUT_A)) {
            movements = 7;
            lastDirection = 7;
            animator->GetAnimation("Back Walk Side")->SetFlip(false, false);
            animator->PlayAnimation("Back Walk Side");
        } else if (input->GetKeyPressed(INPUT_S)
                   && input->GetKeyPressed(INPUT_D)) {
            movements = 8;
            lastDirection = 8;
            animator->GetAnimation("Back Walk Side")->SetFlip(true, false);
            animator->PlayAnimation("Back Walk Side");
        } else if (input->GetKeyPressed(INPUT_W)) {
            lastDirection = 0;
            movements = 1;
            animator->PlayAnimation("Back Walk Down");
        } else if (input->GetKeyPressed(INPUT_S)) {
            lastDirection = 1;
            movements = 2;
            animator->PlayAnimation("Back Walk Up");
        } else if (input->GetKeyPressed(INPUT_A)) {
            lastDirection = 3;
            movements = 3;
            animator->GetAnimation("Back Walk Side")->SetFlip(false, false);
            animator->PlayAnimation("Back Walk Side");
        } else if (input->GetKeyPressed(INPUT_D)) {
            lastDirection = 3;
            movements = 4;
            animator->GetAnimation("Back Walk Side")->SetFlip(true, false);
            animator->PlayAnimation("Back Walk Side");
        } else {
            if (lastDirection == 0) {
                animator->PlayAnimation("Stop Down");
            } else if (lastDirection == 1) {
                animator->PlayAnimation("Stop Up");
            } else if (lastDirection == 2) {
                animator->PlayAnimation("Stop Left");
            } else if (lastDirection == 3) {
                animator->PlayAnimation("Stop Right");
            }
        }

        if (input->GetKeyDown(INPUT_L) && cameraLock == false) {
            cameraLock = true;
            deadzoneX = EngineGlobals::screen_width / 2;
            deadzoneY = EngineGlobals::screen_height / 2;
        } else if (input->GetKeyDown(INPUT_L) && cameraLock == true) {
            cameraLock = false;
            deadzoneX = EngineGlobals::screen_width;
            deadzoneY = EngineGlobals::screen_height;
            animator->StopAllAnimations();
        }
    }
}

/**
    @brief Detect the actions of the game controller to move the player.
*/
void NakedManScript::GameControllerUpdate() {
    isMovingLooking = true;

    // Calculate game controller angle in degrees
    gameControllerAngle = atan2 (game_controller->GetAxis(GC_INPUT_AXIS_RIGHTY)
                                 * -1, game_controller
                                 ->GetAxis(GC_INPUT_AXIS_RIGHTX)) * 180 / 3.14;
    if (abs(game_controller->GetAxis(GC_INPUT_AXIS_RIGHTY)) < 1000
            && abs(game_controller->GetAxis(GC_INPUT_AXIS_RIGHTX)) < 1000) {
        gameControllerAngle = 0;
    }
    if (gameControllerAngle < 0) {
        gameControllerAngle *= -1;
        gameControllerAngle = 180 + (180 - gameControllerAngle);
    }
    if (gameControllerAngle != 0) {
        gameControllerAngle = abs(360 - gameControllerAngle);
    }


    /*
        Define move direction and adjust player's image according
        to the direction he's looking and the game controller buttons actions.
    */
    if (isMovingLooking && dashController == 0) {
        if ((game_controller->GetAxis(GC_INPUT_AXIS_LEFTY) < -1000)
             && (game_controller->GetAxis(GC_INPUT_AXIS_LEFTX) < -1000)) {
            movements = 5;
            lastDirection = 5;
            animator->GetAnimation("Walk Side")->SetFlip(true, false);
            animator->PlayAnimation("Walk Side");
        } else if ((game_controller->GetAxis(GC_INPUT_AXIS_LEFTY) < -1000)
                    && (game_controller->GetAxis(GC_INPUT_AXIS_LEFTX) > 1000)) {
            movements = 6;
            lastDirection = 6;
            animator->GetAnimation("Walk Side")->SetFlip(false, false);
            animator->PlayAnimation("Walk Side");
        } else if ((game_controller->GetAxis(GC_INPUT_AXIS_LEFTY) > 1000)
                    && (game_controller->GetAxis(GC_INPUT_AXIS_LEFTX) < -1000)) {
            movements = 7;
            lastDirection = 7;
            animator->GetAnimation("Walk Side")->SetFlip(true, false);
            animator->PlayAnimation("Walk Side");
        } else if ((game_controller->GetAxis(GC_INPUT_AXIS_LEFTY) > 1000)
                    && (game_controller->GetAxis(GC_INPUT_AXIS_LEFTX) > 1000)) {
            movements = 8;
            lastDirection = 8;
            animator->GetAnimation("Walk Side")->SetFlip(false, false);
            animator->PlayAnimation("Walk Side");
        } else if (game_controller->GetAxis(GC_INPUT_AXIS_LEFTY) < -1000) {
            lastDirection = 0;
            movements = 1;
            animator->PlayAnimation("Walk Up");
        } else if (game_controller->GetAxis(GC_INPUT_AXIS_LEFTY) > 200) {
            lastDirection = 1;
            movements = 2;
            animator->PlayAnimation("Walk Down");
        } else if (game_controller->GetAxis(GC_INPUT_AXIS_LEFTX) < -200) {
            lastDirection = 3;
            movements = 3;
            animator->GetAnimation("Walk Side")->SetFlip(true, false);
            animator->PlayAnimation("Walk Side");
        } else if (game_controller->GetAxis(GC_INPUT_AXIS_LEFTX) > 200) {
            lastDirection = 3;
            movements = 4;
            animator->GetAnimation("Walk Side")->SetFlip(false, false);
            animator->PlayAnimation("Walk Side");
        } else {
            if(lastDirection == 2) {
                animator->PlayAnimation("Stop Left");
            } else if (lastDirection == 3 || lastDirection == 6
                       || lastDirection == 7 || lastDirection == 5
                       || lastDirection == 5 || lastDirection == 8 ) {
                animator->PlayAnimation("Stop Right");
            } else if (lastDirection == 0) {
                animator->PlayAnimation("Stop Up");
            } else if(lastDirection == 1) {
                animator->PlayAnimation("Stop Down");
            }
        }
    } else if (!isMovingLooking && dashController == 0) {
        if ((game_controller->GetAxis(GC_INPUT_AXIS_LEFTY) < -1000)
             && (game_controller->GetAxis(GC_INPUT_AXIS_LEFTX) < -1000)) {
            movements = 5;
            lastDirection = 5;
            animator->GetAnimation("Back Walk Side")->SetFlip(false, false);
            animator->PlayAnimation("Back Walk Side");
        } else if ((game_controller->GetAxis(GC_INPUT_AXIS_LEFTY) < -1000)
                    && (game_controller->GetAxis(GC_INPUT_AXIS_LEFTX) > 1000)) {
            movements = 6;
            lastDirection = 6;
            animator->GetAnimation("Back Walk Side")->SetFlip(true, false);
            animator->PlayAnimation("Back Walk Side");
        } else if ((game_controller->GetAxis(GC_INPUT_AXIS_LEFTY) > 1000)
                    && (game_controller->GetAxis(GC_INPUT_AXIS_LEFTX) < -1000)) {
            movements = 7;
            lastDirection = 7;
            animator->GetAnimation("Back Walk Side")->SetFlip(false, false);
            animator->PlayAnimation("Back Walk Side");
        } else if ((game_controller->GetAxis(GC_INPUT_AXIS_LEFTY) < -1000)
                    && (game_controller->GetAxis(GC_INPUT_AXIS_LEFTX) > 1000)) {
            movements = 8;
            lastDirection = 8;
            animator->GetAnimation("Back Walk Side")->SetFlip(true, false);
            animator->PlayAnimation("Back Walk Side");
        } else if ((game_controller->GetAxis(GC_INPUT_AXIS_LEFTY) < -1000)) {
            lastDirection = 0;
            movements = 1;
            animator->PlayAnimation("Back Walk Down");
        } else if ((game_controller->GetAxis(GC_INPUT_AXIS_LEFTY) > 1000)) {
            lastDirection = 1;
            movements = 2;
            animator->PlayAnimation("Back Walk Up");
        } else if ((game_controller->GetAxis(GC_INPUT_AXIS_LEFTX) < -1000)) {
            lastDirection = 3;
            movements = 3;
            animator->GetAnimation("Back Walk Side")->SetFlip(false, false);
            animator->PlayAnimation("Back Walk Side");
        } else if ((game_controller->GetAxis(GC_INPUT_AXIS_LEFTX) > 1000)) {
            lastDirection = 3;
            movements = 4;
            animator->GetAnimation("Back Walk Side")->SetFlip(true, false);
            animator->PlayAnimation("Back Walk Side");
        } else {
            if (lastDirection == 0 || lastDirection == 8) {
                animator->PlayAnimation("Stop Down");
            } else if (lastDirection == 1 || lastDirection == 7) {
                animator->PlayAnimation("Stop Up");
            } else if (lastDirection == 2 ) {
                animator->PlayAnimation("Stop Left");
            } else if (lastDirection == 3 || lastDirection == 5
                       || lastDirection == 6) {
                animator->PlayAnimation("Stop Right");
            }
        }
    }

    // Attack
    if (game_controller->GetButtonDown(GC_INPUT_X)) {
        printf("Attack\n");
    }

    // Dash
    if (game_controller->GetAxis(GC_INPUT_AXIS_TRIGGERLEFT)
        && dashController == 0) {
        animator->StopAllAnimations();
        animator->PlayAnimation("Right Dash");
    }
    dashController = game_controller->GetAxis(GC_INPUT_AXIS_TRIGGERLEFT);

    // Shoot gun
    if (game_controller->GetAxis( GC_INPUT_AXIS_TRIGGERRIGHT)
        && bulletController == 0 && gameControllerAngle != 0) {
        cout << "ammo: " << bulletNumber << endl;
        auto gameObjectBullet = (GameObject*)SceneManager::GetInstance()
                                             ->GetCurrentScene()
                                             ->GetGameObject("Bullet"
                                             + std::to_string(bulletNumber));
        gameObjectBullet->active = true;
        auto script = (PlayerAttackScript*)SceneManager::GetInstance()
                                           ->GetCurrentScene()
                                           ->GetGameObject("Bullet"
                                           + std::to_string(bulletNumber))
                                           ->GetComponent("PlayerAttackScript");
        script->SetShoot(true);

        bulletNumber--;

        // Reload gun.
        if (bulletNumber == 0) {
            bulletNumber = 10;
           // Wait delay reload time
        }
    }

    bulletController = game_controller->GetAxis( GC_INPUT_AXIS_TRIGGERRIGHT);

    // Back to menu.
    if (game_controller->GetButtonDown(GC_INPUT_BACK)) {
        auto var = (UIText *)SceneManager::GetInstance()
                                           ->GetScene("Main")
                                           ->GetGameObject("Play")
                                           ->GetComponent("UIText");
        var->SetText("Continue");
        SceneManager::GetInstance()->SetCurrentScene("Main");
    }
}

/**
    @brief Create the animations related with the player.
*/
void NakedManScript::CreateAnimations() {
    // Animator
    auto nakedManAnimator = new Animator(GetOwner());

    auto dashrightSprite = new Image("assets/dashright.png", 0, 0, 210, 27);

    auto dashrightAnimation = new Animation(GetOwner(), dashrightSprite);

    for (int i = 0; i < 5; i++) {
        dashrightAnimation->AddFrame(new Frame(i * 42, 27, 128, 128));
    }

    nakedManAnimator->AddAnimation("Right Dash", dashrightAnimation);

    dashrightAnimation->SetFramesPerSecond(10);

    auto nakedManSprite = new Image("assets/player.png", 0, 0, 1664, 512);

    auto StopDownAnimation = new Animation(GetOwner(), nakedManSprite);
    StopDownAnimation->AddFrame(new Frame(0, 256, 128, 128));

    auto StopRightAnimation = new Animation(GetOwner(), nakedManSprite);
    StopRightAnimation->AddFrame(new Frame(0, 0, 128, 128));

    auto StopLeftAnimation = new Animation(GetOwner(), nakedManSprite);
    StopLeftAnimation->AddFrame(new Frame(0, 128, 128, 128));

    auto StopUpAnimation = new Animation(GetOwner(), nakedManSprite);
    StopUpAnimation->AddFrame(new Frame(0, 384, 128, 128));

    auto walkSideAnimation = new Animation(GetOwner(), nakedManSprite);
    for (int i = 1; i < 13; i++) {
        walkSideAnimation->AddFrame(new Frame(i * 128, 0, 128, 128));
    }

    auto walkUpAnimation = new Animation(GetOwner(), nakedManSprite);
    for (int i = 1; i < 13; i++) {
        walkUpAnimation->AddFrame(new Frame(i * 128, 384, 128, 128));
    }

    auto walkDownAnimation = new Animation(GetOwner(), nakedManSprite);
    for (int i = 1; i < 13; i++) {
        walkDownAnimation->AddFrame(new Frame(i * 128, 256, 128, 128));
    }

    nakedManAnimator->AddAnimation("Walk Side", walkSideAnimation);
    nakedManAnimator->AddAnimation("Walk Up", walkUpAnimation);
    nakedManAnimator->AddAnimation("Walk Down", walkDownAnimation);

    auto backwalkSideAnimation = new Animation(GetOwner(), nakedManSprite);
    for (int i = 12; i > 0; i--) {
        backwalkSideAnimation->AddFrame(new Frame(i * 128, 0, 128, 128));
    }

    auto backwalkUpAnimation = new Animation(GetOwner(), nakedManSprite);
    for (int i = 12; i > 0; i--) {
        backwalkUpAnimation->AddFrame(new Frame(i * 128, 384, 128, 128));
    }

    auto backwalkDownAnimation = new Animation(GetOwner(), nakedManSprite);
    for (int i = 12; i > 0; i--) {
        backwalkDownAnimation->AddFrame(new Frame(i * 128, 256, 128, 128));
    }

    nakedManAnimator->AddAnimation("Back Walk Side", backwalkSideAnimation);
    nakedManAnimator->AddAnimation("Back Walk Up", backwalkUpAnimation);
    nakedManAnimator->AddAnimation("Back Walk Down", backwalkDownAnimation);
    nakedManAnimator->AddAnimation("Stop Down", StopDownAnimation);
    nakedManAnimator->AddAnimation("Stop Up", StopUpAnimation);
    nakedManAnimator->AddAnimation("Stop Left", StopLeftAnimation);
    nakedManAnimator->AddAnimation("Stop Right", StopRightAnimation);
}

/**
    @brief Update the components of the player.
*/
void NakedManScript::ComponentUpdate() {
    auto script2 = (RainScript *)SceneManager::GetInstance()
                                ->GetCurrentScene()
                                ->GetGameObject("Rain")
                                ->GetComponent("RainScript");
    auto script3 = (SnowScript *)SceneManager::GetInstance()
                                ->GetCurrentScene()
                                ->GetGameObject("Snow")
                                ->GetComponent("SnowScript");

    if ((CameraSystem::GetInstance()->worldCameraY < 3435)
         && (CameraSystem::GetInstance()->worldCameraX > 3410)
         && (CameraSystem::GetInstance()->worldCameraX < 3500)) {
        script2->play = 1;
    }
    if ((CameraSystem::GetInstance()->worldCameraY > 3435)
         && (CameraSystem::GetInstance()->worldCameraX > 3410)
         && (CameraSystem::GetInstance()->worldCameraX < 3500)) {
        script2->play = 0;
    }
    //3835 3910
    if ((CameraSystem::GetInstance()->worldCameraX < 3315)
         && (CameraSystem::GetInstance()->worldCameraY > 3860)) {
        script3->play = 1;
    }
    if ((CameraSystem::GetInstance()->worldCameraX > 3315)
         && (CameraSystem::GetInstance()->worldCameraY > 3860)) {
        script3->play = 0;
    }

    SetDirection();
    walkSpeed = fixedWalkSpeed;
    Animations();
    MovementsSounds();

    // Back to menu.
    if (InputSystem::GetInstance()->GetKeyUp(INPUT_ESCAPE)) {
        SDLSystem::GetInstance()->SetRunning(false);
    }

    // Shoot gun.
    if (InputSystem::GetInstance()->GetKeyDown(INPUT_SPACE)) {
        Shoot();
    }

    if (input->GetKeyDown(INPUT_L) && cameraLock == false) {
        cameraLock = true;
        deadzoneX = EngineGlobals::screen_width / 2;
        deadzoneY = EngineGlobals::screen_height / 2;
    } else if (input->GetKeyDown(INPUT_L) && cameraLock == true) {
        cameraLock = false;
        deadzoneX = EngineGlobals::screen_width;
        deadzoneY = EngineGlobals::screen_height;
        animator->StopAllAnimations();
    }

    walkSpeed = fixedWalkSpeed;
    movements = 0;

    game_controller = input->GetGameController(0);
    if (!game_controller) {
        KeyBoardUpdate();
    } else {
        GameControllerUpdate();
        gameControllerActivated = true;
    }
    SetDirection();
}

/**
    @brief Detect if the player is moving.
*/
void NakedManScript::MovementsSounds() {
	// Set walking value based on pressed keys.
    if (input->GetKeyPressed(INPUT_W) || input->GetKeyPressed(INPUT_A)
        || input->GetKeyPressed(INPUT_S) || input->GetKeyPressed(INPUT_D)) {
        if (!walking) {
            walking = true;
        }
    } else {
        walking = false;
    }
}

/**
    @brief Update the components of the player.
*/
void NakedManScript::FixedComponentUpdate() {
    GameCollisionCheck();
    WallCollisionResolution();
    StartFirstBoss();
    if (!lockplayerMovements) {
        Movements();
    }

    ReloadGun();
    PlayerLife();

    if (endBossFight) {
        FirstBossController::GetInstance()->EndBossFight();

        // Posit player on spawn
        int xPos, yPos;
        xPos = EngineGlobals::screen_width / 2 - 96 / 2;
        yPos = EngineGlobals::screen_height / 2 - 96 / 2;

        FirstBossController::GetInstance()->PositPlayer(Vector(xPos, yPos ));
        CameraSystem::GetInstance()->MoveRight(200,SceneManager::GetInstance()->GetCurrentScene());
        endBossFight =  false;
    }
}

/**
    @brief Detect the amount of player's life to recover it or end the fight
    with the boss.
*/
void NakedManScript::PlayerLife() {
    // Recover life.
    if (life < 100 && !endBossFight) {
        lifeRecover.Update(EngineGlobals::fixed_update_interval);
        cout << life << endl;
        if(lifeRecover.GetTime() >= 0.5 * 1000) {
            life ++;
            lifeRecover.Restart();
        }
    }
    
    // Detect when player dies.
    if(life <= 0) {
        endBossFight = true;
        /*
            Stop boss fight
            Desactivate boos fight
            Posit player outside boss fight
        */
    }
}

/**
    @brief Allow the player to shoot if he has bullets.
*/
void NakedManScript::Shoot() {
    if (bulletNumber > 0) {
        auto gameObjectBullet = (GameObject *)SceneManager::GetInstance()
                                              ->GetCurrentScene()
                                              ->GetGameObject("Bullet"
                                              + std::to_string(bulletNumber));
        gameObjectBullet->active = true;

        auto script = (PlayerAttackScript *)SceneManager::GetInstance()
                                            ->GetCurrentScene()
                                            ->GetGameObject("Bullet"
                                            + std::to_string(bulletNumber))
                                            ->GetComponent("PlayerAttackScript");
        script->SetShoot(true);
        bulletNumber--;
    }
}

/**
    @brief Reloads the player's gun based on number of shots or time.
*/
void NakedManScript::ReloadGun() {
    if (bulletNumber == 0) {
        timerReload.Update(EngineGlobals::fixed_update_interval);
    }

    // Time in seconds
    if (timerReload.GetTime() >= 2 * 1000) {
        bulletNumber = 10;
        timerReload.Restart();
    }
}

/**
    @brief Constantly update the animations based on collisions and time.
*/
void NakedManScript::Animations() {
    if (m_hit) {
        m_hitFrames++;
        timerHit.Update(EngineGlobals::fixed_update_interval);

        if (m_hitFrames >= 7) {
            animator->StopAllAnimations();
            if (m_hitFrames >= 12) {
                m_hitFrames = 0;
            }
        }
    }

    if (timerHit.GetTime() >= 1 * 1000) {
        m_hit =  false;
        timerHit.Restart();
    }
}

/**
    @brief Define the direction in which the player will move based
    on the pressed keys or the game controller buttons actions.
*/
void NakedManScript::Movements() {
    if (movements == 5) {
        walkSpeed = walkSpeed * 0.70710;
        position->m_y -= walkSpeed;
        position->m_x -= walkSpeed;
    } else if (movements == 6) {
        walkSpeed = walkSpeed*0.70710;
        position->m_y -= walkSpeed;
        position->m_x += walkSpeed;
    } else if (movements == 7) {
        walkSpeed = walkSpeed * 0.70710;
        position->m_y += walkSpeed;
        position->m_x -= walkSpeed;
    } else if (movements == 8) {
        walkSpeed = walkSpeed * 0.70710;
        position->m_y += walkSpeed;
        position->m_x += walkSpeed;
    } else if (movements == 1) {
        position->m_y -= walkSpeed;
    } else if (movements == 2) {
        position->m_y += walkSpeed;
    } else if (movements == 3){
        position->m_x -= walkSpeed;
    } else if (movements == 4){
        position->m_x += walkSpeed;
    }

    if (cameraLock) {
        // Mount deadzode on x++
        if (position->m_x + GetOwner()->GetWidth() >= deadzoneX) { 
            if (isZooming) {
                CameraSystem::GetInstance()->MoveRight(2,
                                                       SceneManager::GetInstance()
                                                       ->GetCurrentScene());
            } else {
                CameraSystem::GetInstance()->MoveRight(walkSpeed,
                                                       SceneManager::GetInstance()
                                                       ->GetCurrentScene());
            }
        }

        // Mount deadzode on x-
        if (position->m_x <= deadzoneX) { 
            if (isZooming) {
                CameraSystem::GetInstance()->MoveLeft(2,
                                                      SceneManager::GetInstance()
                                                      ->GetCurrentScene());
            } else {
                CameraSystem::GetInstance()->MoveLeft(walkSpeed,
                                                      SceneManager::GetInstance()
                                                      ->GetCurrentScene());
            }
        }

        // Mount deadzode on y++
        if (position->m_y + GetOwner()->GetWidth() >= deadzoneY) { 
            if (isZooming) {
                CameraSystem::GetInstance()->MoveDown(2,
                                                      SceneManager::GetInstance()
                                                      ->GetCurrentScene());
            } else {
                CameraSystem::GetInstance()->MoveDown(walkSpeed,
                                                      SceneManager::GetInstance()
                                                      ->GetCurrentScene());
            }
        }

        // Mount deadzode on y--
        if (position->m_y <= deadzoneY) { 
            if (isZooming) {
                CameraSystem::GetInstance()->MoveUp(2,
                                                    SceneManager::GetInstance()
                                                    ->GetCurrentScene());
            } else {
                CameraSystem::GetInstance()->MoveUp(walkSpeed,
                                                    SceneManager::GetInstance()
                                                    ->GetCurrentScene());
            }
        }

    } else {
        if (position->m_x + GetOwner()->GetWidth() >= deadzoneX) {
            if (isZooming) {
                CameraSystem::GetInstance()->MoveRight(2,
                                                       SceneManager::GetInstance()
                                                       ->GetCurrentScene());
            } else {
                CameraSystem::GetInstance()->MoveRight(walkSpeed,
                                                       SceneManager::GetInstance()
                                                       ->GetCurrentScene());
            }
        }

        if (position->m_x <= 0) {
            if (isZooming) {
                CameraSystem::GetInstance()->MoveLeft(2,
                                                      SceneManager::GetInstance()
                                                      ->GetCurrentScene());
            } else {
                CameraSystem::GetInstance()->MoveLeft(walkSpeed,
                                                      SceneManager::GetInstance()
                                                      ->GetCurrentScene());
            }
        }

        if (position->m_y + GetOwner()->GetWidth() >= deadzoneY) {
            if (isZooming) {
                CameraSystem::GetInstance()->MoveDown(2,
                                                      SceneManager::GetInstance()
                                                      ->GetCurrentScene());
            } else {
                CameraSystem::GetInstance()->MoveDown(walkSpeed,
                                                      SceneManager::GetInstance()
                                                      ->GetCurrentScene());
            }
        }
    }

    if (position->m_y <= 0) {
        if (isZooming) {
            CameraSystem::GetInstance()->MoveUp(2,
                                                SceneManager::GetInstance()
                                                ->GetCurrentScene());
        } else {
            CameraSystem::GetInstance()->MoveUp(walkSpeed,
                                                SceneManager::GetInstance()
                                                ->GetCurrentScene());
        }
    }
}

/**
    @brief Check the collisions that occur during the game.
*/
void NakedManScript::GameCollisionCheck() {
    for (auto obj : GetOwner()->GetCollisions()) {
        if (obj->GetTag() == "Bullet") {
            GetOwner()->ClearCollisions();
        } else if (obj->GetTag() == "FirstBoss") {
            cout << "Boss Colider" << endl;
            if (obj->active) {
                m_hit = true;
                life --;
            }
            GetOwner()->ClearCollisions();
        } else if (obj->GetTag() == "FirstBossAtack") {
            cout << "Boss Atack Colider" << endl;
            if (obj->active) {
                m_hit = true;
                life --;
            }
            GetOwner()->ClearCollisions();
        }
    }
}

/**
    @brief Start the first boss depending on the position of the Camera
    of the game.
*/
void NakedManScript::StartFirstBoss() {
    if (input->GetKeyDown(INPUT_X)) {
        cout << "X: " << CameraSystem::GetInstance()->worldCameraX << endl;
        cout << "Y: " << CameraSystem::GetInstance()->worldCameraY << endl;
    }

    if (!bossFight) {
        if ((CameraSystem::GetInstance()->worldCameraX < 500)) {
            CameraSystem::GetInstance()->ZoomOut(SceneManager::GetInstance()
                                                 ->GetCurrentScene()
                                                 ->GetGameObject("Map")
                                                 ->originalWidth / 4 + 1,
                                                 GetOwner(),
                                                 SceneManager::GetInstance()
                                                 ->GetCurrentScene());
            CameraSystem::GetInstance()->ZoomIn(1, GetOwner(),
                                                SceneManager::GetInstance()
                                                ->GetCurrentScene());
            CameraSystem::GetInstance()->currentZoom -= 25;

            CameraSystem::GetInstance()->ZoomOut(SceneManager::GetInstance()
                                                 ->GetCurrentScene()
                                                 ->GetGameObject("Map")
                                                 ->originalWidth / 4 + 1,
                                                 GetOwner(),
                                                 SceneManager::GetInstance()
                                                 ->GetCurrentScene());
            CameraSystem::GetInstance()->ZoomIn(1, GetOwner(),
                                                SceneManager::GetInstance()
                                                ->GetCurrentScene());
            CameraSystem::GetInstance()->currentZoom -= 25;

            FirstBossController::GetInstance()->ActivateBoss();
            FirstBossController::GetInstance()->ActivateInsideBossFx();
            FirstBossController::GetInstance()->ActivateLifeBars();

            AudioController::GetInstance()->StopAudio("mainSound");

            AudioController::GetInstance()->PlayAudio("bossBattleSound", -1);
            bossFight = true;
        }
    }
}

/**
    @brief Detect collisions between the player and the wall.
*/
void NakedManScript::WallCollisionResolution() {
    auto mapscript = (MapScript *)SceneManager::GetInstance()
                                  ->GetScene("Gameplay")
                                  ->GetGameObject("Map")
                                  ->GetComponent("MapScript");
    if (mapscript) {
        mapscript->DetectWallCollision(GetOwner());
    }
}
