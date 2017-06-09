#include "Customs/NakedManScript.h"

NakedManScript::NakedManScript(GameObject *owner) : Script(owner) {}

void NakedManScript::Start() {
  position = GetOwner()->GetPosition();
  animator = (Animator *)GetOwner()->GetComponent("Animator");
  input = InputSystem::GetInstance();
}

void NakedManScript::ComponentUpdate() {
static int lastDirection=1;
  // movement animation and input detection
  movements = movements & 0x00;
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

          if(lastDirection==0){
          animator->PlayAnimation("Stop Up");
          }
          else if(lastDirection==1){
          animator->PlayAnimation("Stop Down");
          }
          else if(lastDirection==2){
          animator->PlayAnimation("Stop Left");
          }
          else if(lastDirection==3){
          animator->PlayAnimation("Stop Right");
          }

    //  animator->StopAllAnimations();

  }

  if (InputSystem::GetInstance()->GetKeyUp(INPUT_ESCAPE)) {
    auto var = (UIText *)SceneManager::GetInstance()
                   ->GetScene("Main")
                   ->GetGameObject("Play")
                   ->GetComponent("UIText");
    var->SetText("Continue");
    SceneManager::GetInstance()->SetCurrentScene("Main");
  }
  /*
     if (InputSystem::GetInstance()->GetKeyUp(INPUT_UP)) {
        SceneManager::GetInstance()->SetCurrentScene("CatchAll");
      }
*/


}

void NakedManScript::FixedComponentUpdate() {


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




      if (position->m_x + 64 >= deadzone_x)
      CameraSystem::GetInstance()->MoveRight(walkSpeed);

      if (position->m_x <= deadzone_x - 200)
      CameraSystem::GetInstance()->MoveLeft(walkSpeed);

      if (position->m_y + 64 >= deadzone_y)
       CameraSystem::GetInstance()->MoveDown(walkSpeed);
      if (position->m_y <= deadzone_y - 200)
        CameraSystem::GetInstance()->MoveUp(walkSpeed);

}
