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

void NakedManScript::CreateAnimations(){

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

  // animator
  auto nakedManAnimator = new Animator(GetOwner());

  nakedManAnimator->AddAnimation("Walk Side", walkSideAnimation);
  nakedManAnimator->AddAnimation("Walk Up", walkUpAnimation);
  nakedManAnimator->AddAnimation("Walk Down", walkDownAnimation);
  nakedManAnimator->AddAnimation("Stop Down", StopDownAnimation);
  nakedManAnimator->AddAnimation("Stop Up", StopUpAnimation);
  nakedManAnimator->AddAnimation("Stop Left", StopLeftAnimation);
  nakedManAnimator->AddAnimation("Stop Right", StopRightAnimation);
}



void NakedManScript::ComponentUpdate() {

  static int lastDirection=1;

  movements = 0;

  if((input->GetKeyPressed(INPUT_DOWN)) || (input->GetKeyPressed(INPUT_UP)))
    isZooming=true;

  if((input->GetKeyUp(INPUT_DOWN)) || (input->GetKeyUp(INPUT_UP)))
    isZooming=false;

  if (input->GetKeyPressed(INPUT_W)) {
    lastDirection=0;
    movements = 1;
    animator->PlayAnimation("Walk Up");

  } else if (input->GetKeyPressed(INPUT_S)) {
    lastDirection=1;
    movements = 2;
    animator->PlayAnimation("Walk Down");
  } else if (input->GetKeyPressed(INPUT_A)) {
    lastDirection=2;
    movements = 3;
    animator->GetAnimation("Walk Side")->SetFlip(true, false);
    animator->PlayAnimation("Walk Side");
    lastDirection=3;
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

  if (movements==1){
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
