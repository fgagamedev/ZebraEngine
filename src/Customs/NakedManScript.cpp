#include "Customs/NakedManScript.h"
#include <stdio.h>
bool NakedManScript::isZooming=false;

NakedManScript::NakedManScript(GameObject *owner) : Script(owner) {}

void NakedManScript::Start() {
  CreateAnimations();
  position = GetOwner()->GetPosition();
  animator = (Animator *)GetOwner()->GetComponent("Animator");
  input = InputSystem::GetInstance();
  GetOwner()->SetZoomProportion(Vector(128,128));
  CameraSystem::GetInstance()->SetCameraSpeed(walkSpeed);
}

void NakedManScript::SetDirection(){

mousePosition = input->GetMousePosition();


//if(input->GetMouseButtonPressed(M_INPUT_LEFT))
//x-axis
    if(mousePosition.first >= position->m_x && movements==4){
    isMovingLooking=true;
    }
    else if(mousePosition.first > position->m_x && movements==3){
    isMovingLooking=false;
    }

    if(mousePosition.first <= position->m_x && movements==3){
    isMovingLooking=true;
    }
    else if(mousePosition.first < position->m_x && movements==4){
    isMovingLooking=false;
    }
//y-axis
    if(mousePosition.second <= position->m_y && movements==1){
    isMovingLooking=true;
    }
    else if(mousePosition.second < position->m_y && movements==2){
    isMovingLooking=false;
    }

    if(mousePosition.second >= position->m_y && movements==2){
      isMovingLooking=true;
     }
     else if(mousePosition.second > position->m_y && movements==1){
       isMovingLooking=false;
     }
//Diagonal 1
    if(mousePosition.first >= position->m_x && mousePosition.second <= position->m_y && movements == 6){
    isMovingLooking=true;
    }
    else if(mousePosition.first >= position->m_x && mousePosition.second <= position->m_y && movements == 7){
    isMovingLooking=false;
    }

 if(mousePosition.first <= position->m_x && mousePosition.second >= position->m_y && movements == 7){
    isMovingLooking=true;
    }
    else if(mousePosition.first <= position->m_x && mousePosition.second >= position->m_y && movements == 6){
    isMovingLooking=false;
    }
//Diagonal 2

   if(mousePosition.first >= position->m_x && mousePosition.second >= position->m_y && movements == 8){
    isMovingLooking=true;
    }
    else if(mousePosition.first >= position->m_x && mousePosition.second >= position->m_y && movements == 5){
    isMovingLooking=false;
    }
    if(mousePosition.first <= position->m_x && mousePosition.second <= position->m_y && movements == 5){
    isMovingLooking=true;
    }
    else if(mousePosition.first <= position->m_x && mousePosition.second <= position->m_y && movements == 8){
    isMovingLooking=false;
    }






}

void NakedManScript::CreateAnimations(){

  // animator
  auto nakedManAnimator = new Animator(GetOwner());

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
  for (int i = 1; i < 13; i++)
    walkSideAnimation->AddFrame(new Frame(i * 128, 0, 128, 128));

  auto walkUpAnimation = new Animation(GetOwner(), nakedManSprite);
  for (int i = 1; i < 13; i++)
    walkUpAnimation->AddFrame(new Frame(i * 128, 384, 128, 128));

  auto walkDownAnimation = new Animation(GetOwner(), nakedManSprite);
  for (int i = 1; i < 13; i++)
    walkDownAnimation->AddFrame(new Frame(i * 128, 256, 128, 128));


  nakedManAnimator->AddAnimation("Walk Side", walkSideAnimation);
  nakedManAnimator->AddAnimation("Walk Up", walkUpAnimation);
  nakedManAnimator->AddAnimation("Walk Down", walkDownAnimation);





  auto backwalkSideAnimation = new Animation(GetOwner(), nakedManSprite);
  for (int i = 12; i >0; i--)
    backwalkSideAnimation->AddFrame(new Frame(i * 128, 0, 128, 128));

  auto backwalkUpAnimation = new Animation(GetOwner(), nakedManSprite);
  for (int i = 12; i >0; i--)
    backwalkUpAnimation->AddFrame(new Frame(i * 128, 384, 128, 128));

  auto backwalkDownAnimation = new Animation(GetOwner(), nakedManSprite);
  for (int i = 12; i >0; i--)
    backwalkDownAnimation->AddFrame(new Frame(i * 128, 256, 128, 128));

      nakedManAnimator->AddAnimation("Back Walk Side", backwalkSideAnimation);
      nakedManAnimator->AddAnimation("Back Walk Up", backwalkUpAnimation);
      nakedManAnimator->AddAnimation("Back Walk Down", backwalkDownAnimation);



  nakedManAnimator->AddAnimation("Stop Down", StopDownAnimation);
  nakedManAnimator->AddAnimation("Stop Up", StopUpAnimation);
  nakedManAnimator->AddAnimation("Stop Left", StopLeftAnimation);
  nakedManAnimator->AddAnimation("Stop Right", StopRightAnimation);
}



void NakedManScript::ComponentUpdate() {
SetDirection();

walkSpeed = 15;
  movements = 0;

  if((input->GetKeyPressed(INPUT_DOWN)) || (input->GetKeyPressed(INPUT_UP)))
    isZooming=true;

  if((input->GetKeyUp(INPUT_DOWN)) || (input->GetKeyUp(INPUT_UP)))
    isZooming=false;

  if((input->GetKeyDown(INPUT_V)) && (!isMovingLooking)){
    isMovingLooking=true;
  }
  else if((input->GetKeyDown(INPUT_V)) && (isMovingLooking)){
    isMovingLooking=false;
  }
if(isMovingLooking){

    if (input->GetKeyPressed(INPUT_W) && input->GetKeyPressed(INPUT_A)) {
        movements=5;
        lastDirection=5;
        animator->GetAnimation("Walk Side")->SetFlip(true, false);
        animator->PlayAnimation("Walk Side");
     }
     else if (input->GetKeyPressed(INPUT_W) && input->GetKeyPressed(INPUT_D)) {
        movements=6;
        lastDirection=6;
        animator->GetAnimation("Walk Side")->SetFlip(false, false);
       animator->PlayAnimation("Walk Side");
     }
     else if (input->GetKeyPressed(INPUT_S) && input->GetKeyPressed(INPUT_A)) {
        movements=7;
        lastDirection=7;
        animator->GetAnimation("Walk Side")->SetFlip(true, false);
        animator->PlayAnimation("Walk Side");
     }
     else if (input->GetKeyPressed(INPUT_S) && input->GetKeyPressed(INPUT_D)) {
       movements=8;
       lastDirection=8;
       animator->GetAnimation("Walk Side")->SetFlip(false, false);
       animator->PlayAnimation("Walk Side");
     }

  else if (input->GetKeyPressed(INPUT_W)) {
    lastDirection=0;
    movements = 1;
    animator->PlayAnimation("Walk Up");

  } else if (input->GetKeyPressed(INPUT_S)) {
    lastDirection=1;
    movements = 2;
    animator->PlayAnimation("Walk Down");
  } else if (input->GetKeyPressed(INPUT_A)) {
   lastDirection=3;
    movements = 3;
    animator->GetAnimation("Walk Side")->SetFlip(true, false);
    animator->PlayAnimation("Walk Side");
  } else if (input->GetKeyPressed(INPUT_D)) {
    lastDirection=3;
    movements = 4;
    animator->GetAnimation("Walk Side")->SetFlip(false, false);
    animator->PlayAnimation("Walk Side");
  } else {

    if(lastDirection==0) {
    animator->PlayAnimation("Stop Up");
    }
    else if(lastDirection==1) {
    animator->PlayAnimation("Stop Down");
    }
    else if(lastDirection==2) {
    animator->PlayAnimation("Stop Left");
    }
    else if(lastDirection==3) {
    animator->PlayAnimation("Stop Right");
    }

  }
}

else{
 if (input->GetKeyPressed(INPUT_W) && input->GetKeyPressed(INPUT_A)) {
        movements=5;
        lastDirection=5;
        animator->GetAnimation("Back Walk Side")->SetFlip(false, false);
        animator->PlayAnimation("Back Walk Side");
     }
     else if (input->GetKeyPressed(INPUT_W) && input->GetKeyPressed(INPUT_D)) {
        movements=6;
        lastDirection=6;
        animator->GetAnimation("Back Walk Side")->SetFlip(true, false);
       animator->PlayAnimation("Back Walk Side");
     }
     else if (input->GetKeyPressed(INPUT_S) && input->GetKeyPressed(INPUT_A)) {
        movements=7;
        lastDirection=7;
        animator->GetAnimation("Back Walk Side")->SetFlip(false, false);
        animator->PlayAnimation("Back Walk Side");
     }
     else if (input->GetKeyPressed(INPUT_S) && input->GetKeyPressed(INPUT_D)) {
       movements=8;
       lastDirection=8;
       animator->GetAnimation("Back Walk Side")->SetFlip(true, false);
       animator->PlayAnimation("Back Walk Side");
     }
else if (input->GetKeyPressed(INPUT_W)) {
    lastDirection=0;
    movements = 1;
    animator->PlayAnimation("Back Walk Down");

  } else if (input->GetKeyPressed(INPUT_S)) {
    lastDirection=1;
    movements = 2;
    animator->PlayAnimation("Back Walk Up");
  } else if (input->GetKeyPressed(INPUT_A)) {
   lastDirection=3;
    movements = 3;
    animator->GetAnimation("Back Walk Side")->SetFlip(false, false);
    animator->PlayAnimation("Back Walk Side");
  } else if (input->GetKeyPressed(INPUT_D)) {
    lastDirection=3;
    movements = 4;
    animator->GetAnimation("Back Walk Side")->SetFlip(true, false);
    animator->PlayAnimation("Back Walk Side");
  } else {

    if(lastDirection==0) {
    animator->PlayAnimation("Stop Down");
    }
    else if(lastDirection==1) {
    animator->PlayAnimation("Stop Up");
    }
    else if(lastDirection==2) {
    animator->PlayAnimation("Stop Left");
    }
    else if(lastDirection==3) {
    animator->PlayAnimation("Stop Right");
    }

  }

}
  if (InputSystem::GetInstance()->GetKeyUp(INPUT_ESCAPE)) {
    auto var = (UIText *)SceneManager::GetInstance()
                   ->GetScene("Main")
                   ->GetGameObject("Play")
                   ->GetComponent("UIText");
    var->SetText("Continue");
    SceneManager::GetInstance()->SetCurrentScene("Main");
  }


  if (input->GetKeyPressed(INPUT_P))
    shake=true;


 if(input->GetKeyDown(INPUT_L) && cameraLock==false) {
       cameraLock=true;
       deadzone_x = EngineGlobals::screen_width / 2;
       deadzone_y = EngineGlobals::screen_height / 2;
     }
 else if(input->GetKeyDown(INPUT_L) && cameraLock==true){
  cameraLock=false;
      deadzone_x = EngineGlobals::screen_width;
      deadzone_y = EngineGlobals::screen_height;
  animator->StopAllAnimations();
 }
}
void NakedManScript::FixedComponentUpdate() {

  if(shake){
    //CameraShake(intensity,duration in seconds)
    CameraSystem::GetInstance()->CameraShake(8,1,SceneManager::GetInstance()->GetCurrentScene());
    if(!CameraSystem::GetInstance()->IsShaking())
    shake=false;
  }

  if (movements==5){
  walkSpeed = walkSpeed*0.70710;
 position->m_y -= walkSpeed;
 position->m_x -= walkSpeed;

  }

  else if (movements==6){
    walkSpeed = walkSpeed*0.70710;
    position->m_y -= walkSpeed;
    position->m_x += walkSpeed;

  }

  else if (movements==7){
    walkSpeed = walkSpeed*0.70710;
  position->m_y += walkSpeed;
  position->m_x -= walkSpeed;

  }

  else if (movements==8){
    walkSpeed = walkSpeed*0.70710;
    position->m_y += walkSpeed;
    position->m_x += walkSpeed;
  }
  else if (movements==1){
    position->m_y -= walkSpeed;
  }

  else if (movements==2){
    position->m_y += walkSpeed;
  }

  else if (movements==3){
    position->m_x -= walkSpeed;
  }

  else if (movements==4){
    position->m_x += walkSpeed;
  }



if(cameraLock){
    if (position->m_x + GetOwner()->GetWidth() >= deadzone_x){
      if(isZooming){
        CameraSystem::GetInstance()->MoveRight(2,SceneManager::GetInstance()->GetCurrentScene());
        }
      else{
        CameraSystem::GetInstance()->MoveRight(walkSpeed,SceneManager::GetInstance()->GetCurrentScene());
       }
    }

    if (position->m_x <= deadzone_x){
      if(isZooming){
        CameraSystem::GetInstance()->MoveLeft(2,SceneManager::GetInstance()->GetCurrentScene());
      }
      else{
        CameraSystem::GetInstance()->MoveLeft(walkSpeed,SceneManager::GetInstance()->GetCurrentScene());
      }

    }

     if (position->m_y + GetOwner()->GetWidth() >= deadzone_y){
       if(isZooming){
          CameraSystem::GetInstance()->MoveDown(2,SceneManager::GetInstance()->GetCurrentScene());
       }
       else{
         CameraSystem::GetInstance()->MoveDown(walkSpeed,SceneManager::GetInstance()->GetCurrentScene());
       }
     }

     if (position->m_y <= deadzone_y){
       if(isZooming){
         CameraSystem::GetInstance()->MoveUp(2,SceneManager::GetInstance()->GetCurrentScene());
       }
       else{
         CameraSystem::GetInstance()->MoveUp(walkSpeed,SceneManager::GetInstance()->GetCurrentScene());
       }

     }
}

else{




 if (position->m_x + GetOwner()->GetWidth() >= deadzone_x){
      if(isZooming){
        CameraSystem::GetInstance()->MoveRight(2,SceneManager::GetInstance()->GetCurrentScene());
        }
      else{
        CameraSystem::GetInstance()->MoveRight(walkSpeed,SceneManager::GetInstance()->GetCurrentScene());
       }
    }

        if (position->m_x <= 0){
          if(isZooming){
            CameraSystem::GetInstance()->MoveLeft(2,SceneManager::GetInstance()->GetCurrentScene());
          }
          else{
            CameraSystem::GetInstance()->MoveLeft(walkSpeed,SceneManager::GetInstance()->GetCurrentScene());
          }

        }


          if (position->m_y + GetOwner()->GetWidth() >= deadzone_y){
               if(isZooming){
                  CameraSystem::GetInstance()->MoveDown(2,SceneManager::GetInstance()->GetCurrentScene());
               }
               else{
                 CameraSystem::GetInstance()->MoveDown(walkSpeed,SceneManager::GetInstance()->GetCurrentScene());
               }
             }

             if (position->m_y <= 0){
               if(isZooming){
                 CameraSystem::GetInstance()->MoveUp(2,SceneManager::GetInstance()->GetCurrentScene());
               }
               else{
                 CameraSystem::GetInstance()->MoveUp(walkSpeed,SceneManager::GetInstance()->GetCurrentScene());
               }

             }










}







}