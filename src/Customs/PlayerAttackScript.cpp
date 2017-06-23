#include "Customs/PlayerAttackScript.h"
#include "Globals/EngineGlobals.h"

PlayerAttackScript::PlayerAttackScript(GameObject *owner) : Script(owner) {}
void PlayerAttackScript::Start() {

  CreateAnimations();
  position = GetOwner()->GetPosition();
  animator = (Animator *)GetOwner()->GetComponent("Animator");
  input = InputSystem::GetInstance();
   auto map = SceneManager::GetInstance()->GetScene("Gameplay")->GetGameObject("Map");
    if(map) GetOwner()->SetZoomProportion(Vector(map->originalWidth/GetOwner()->originalWidth,map->originalHeight/GetOwner()->originalHeight));
  player =  SceneManager::GetInstance()->GetCurrentScene()->GetGameObject("NakedMan");

}
void PlayerAttackScript::CreateAnimations(){


// Renderer
  auto bulletImage = new Image("assets/Sprites/green_bullet.png",0,0,124, 124);
  auto bulletRenderer = new Renderer(GetOwner(), bulletImage);
/*
  auto thunderBlueAnimation= new Animation(GetOwner(),thunderImage );
  for (int i = 0; i < 6; i++)
    thunderBlueAnimation->AddFrame(new Frame(i * 100,135, 100, 267));

  auto thunderYellowAnimation= new Animation(GetOwner(),thunderImage );
  for (int i = 0; i < 5; i++)
    thunderYellowAnimation->AddFrame(new Frame(555 + (i * 59),135, 59, 267));

    
  // animator
      auto thunderAnimator = new Animator(GetOwner());

      thunderAnimator->AddAnimation("thunderBlueAnimation", thunderBlueAnimation);
      thunderAnimator->AddAnimation("thunderYellowAnimation", thunderYellowAnimation);
*/
}


void PlayerAttackScript::ComponentUpdate() {

     player =  SceneManager::GetInstance()->GetCurrentScene()->GetGameObject("NakedMan");
     if(player){
         playerPosition.m_x  =  player->GetPosition()->m_x +  player->GetWidth()/2;
         playerPosition.m_y  =  player->GetPosition()->m_y +  player->GetHeight()/2;

         mousePosition.m_x = input->GetMousePosition().first;
         mousePosition.m_y = input->GetMousePosition().second;


        if(input->GetKeyDown(INPUT_SPACE)){

          angle = playerPosition.GetAngleRadians(mousePosition);
          bulletVelocity.m_x = bulletSpeed * cos(angle);
          bulletVelocity.m_y = bulletSpeed * sin(angle);
          position->m_x = playerPosition.m_x;
          position->m_y = playerPosition.m_y;
          shoot = true;
        }
    }

    if(shoot==false){
    //animator->StopAllAnimations();
    }

}
void PlayerAttackScript::FixedComponentUpdate() { 

    bulletSpeed = bulletSpeed;
    position->m_y += bulletVelocity.m_y;
    position->m_x += bulletVelocity.m_x;

}
