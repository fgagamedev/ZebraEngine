#include "Customs/PlayerAttackScript.h"
#include "Globals/EngineGlobals.h"

PlayerAttackScript::PlayerAttackScript(GameObject *owner) : Script(owner) {}
void PlayerAttackScript::Start() {

  CreateAnimations();
  position = GetOwner()->GetPosition();
  animator = (Animator *)GetOwner()->GetComponent("Animator");
  input = InputSystem::GetInstance();
  GetOwner()->SetZoomProportion(Vector(0,0));

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

   
      

    if(input->GetKeyDown(INPUT_SPACE)){
      //animator->PlayAnimation("thunderBlueAnimation");


      //Get player position
      Vector *playerPosition = SceneManager::GetInstance()
                                    ->GetScene("Gameplay")
                                    ->GetGameObject("NakedMan")
                                    ->GetPosition();

      //Get mouse position
      std::pair<int, int> mousePosition =InputSystem::GetInstance()->GetMousePosition();


      //Move Bullet to player position
      position->m_x=playerPosition->m_x;
      position->m_y=playerPosition->m_y;
      shoot = true;

    }

  

    else{
    //animator->StopAllAnimations();
    }

}
void PlayerAttackScript::FixedComponentUpdate() { 

  if(shoot == true){ 

    //TODO calcular vetor da bala e aplicar a velocidade

    //bulletSpeed = bulletSpeed*0.70710;
    //position->m_y -= walkSpeed;
    //position->m_x += walkSpeed;

  }
}
