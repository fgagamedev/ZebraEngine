#include "Customs/NakedManScript.h"
bool NakedManScript::isZooming=false;

NakedManScript::NakedManScript(GameObject *owner) : Script(owner) {}

void NakedManScript::Start() {
  position = GetOwner()->GetPosition();
  animator = (Animator *)GetOwner()->GetComponent("Animator");
  input = InputSystem::GetInstance();
}

void NakedManScript::ComponentUpdate() {
  static int lastDirection=1;
  // movement animation and input detection
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



}

void NakedManScript::FixedComponentUpdate() {


  if(shake){
    //CameraShake(intensity,duration in seconds)
    CameraSystem::CameraShake(4,0.3);
    if(!CameraSystem::IsShaking())
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




  if (position->m_x + SceneManager::GetInstance()->GetScene("Gameplay")->GetGameObject("NakedMan")->GetWidth() >= deadzone_x){
    if(isZooming){
      CameraSystem::GetInstance()->MoveRight(2);
      }
    else{
      CameraSystem::GetInstance()->MoveRight(walkSpeed);
     }
  }

  if (position->m_x <= deadzone_x){
    if(isZooming){
      CameraSystem::GetInstance()->MoveLeft(2);
    }
    else{
      CameraSystem::GetInstance()->MoveLeft(walkSpeed);
    }

  }

   if (position->m_y + SceneManager::GetInstance()->GetScene("Gameplay")->GetGameObject("NakedMan")->GetHeight()>= deadzone_y){
     if(isZooming){
       CameraSystem::GetInstance()->MoveDown(2);
     }
     else{
       CameraSystem::GetInstance()->MoveDown(walkSpeed);
     }
   }

   if (position->m_y <= deadzone_y){
     if(isZooming){
       CameraSystem::GetInstance()->MoveUp(2);
     }
     else{
       CameraSystem::GetInstance()->MoveUp(walkSpeed);
     }

   }
}
