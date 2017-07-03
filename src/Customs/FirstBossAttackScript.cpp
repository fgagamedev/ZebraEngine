#include "Customs/FirstBossAttackScript.h"

FirstBossAttackScript::FirstBossAttackScript(GameObject *owner) : Script(owner) {}

void FirstBossAttackScript::Start() {

  CreateAnimations();
  position = GetOwner()->GetPosition();
  animator = (Animator *)GetOwner()->GetComponent("Animator");
  input = InputSystem::GetInstance();
  auto map = SceneManager::GetInstance()->GetScene("Gameplay")->GetGameObject("Map");
  if(map) GetOwner()->SetZoomProportion(Vector(map->originalWidth/GetOwner()->originalWidth,map->originalHeight/GetOwner()->originalHeight));
  firstBossAttackCollider = new RectangleCollider(GetOwner(), Vector(0, 0), GetOwner()->GetWidth(), GetOwner()->GetHeight(), 0);

}
void FirstBossAttackScript::CreateAnimations(){

  //Image Attacks
  auto firstBossAttackImage = new Image("assets/firstBossAttack.png",0,0,600, 151);
  int i;
  //Surge Animation
  auto firstBossAttackSurgeAnimation= new Animation(GetOwner(),firstBossAttackImage );
  for (i = 0; i < 15; i++){
    firstBossAttackSurgeAnimation->AddFrame(new Frame(i * 40, 0, 40, 151));
  }

  //Idle Animation
  auto firstBossAttackIdleAnimation= new Animation(GetOwner(),firstBossAttackImage );
  firstBossAttackIdleAnimation->AddFrame(new Frame(14 * 40, 0, 40, 151));

  //Gone Animation
  auto firstBossAttackGoneAnimation= new Animation(GetOwner(),firstBossAttackImage );
  for ( i = 14; i != 0; i--){
    firstBossAttackGoneAnimation->AddFrame(new Frame(i * 40, 0, 40, 151));
  }


  //Animator
  auto firstBossAttackAnimator = new Animator(GetOwner());
  firstBossAttackAnimator->AddAnimation("firstBossAttackSurgeAnimation", firstBossAttackSurgeAnimation); //Surge Animator
  firstBossAttackAnimator->AddAnimation("firstBossAttackIdleAnimation", firstBossAttackIdleAnimation); //Idle Animator
  firstBossAttackAnimator->AddAnimation("firstBossAttackGoneAnimation", firstBossAttackGoneAnimation); //Gone Animator
}


void FirstBossAttackScript::ComponentUpdate() {

  

  if(attack){

     Attack();
  }
  
  if(InputSystem::GetInstance()->GetKeyUp(INPUT_M) && attack == false){// attack
     //FirstBossController::GetInstance()->PositTentacle();
      attack = true;
      //FirstBossController::GetInstance()->PositTentacle(1);
      //FirstBossController::GetInstance()->PositTentacle();
      //m_surgeAnimation = true;
      //Attack();
     
     
  }

  
  //Debug
  //auto vec = Vector(firstBossAttackCollider->GetRectanglePoint().m_x,firstBossAttackCollider->GetRectanglePoint().m_y);
  //GraphicsSystem::GetInstance()->DrawFillRectangle(vec, GetOwner()->GetWidth(), GetOwner()->GetHeight(), 255,0,0,100);

 
    
}
void FirstBossAttackScript::FixedComponentUpdate() {


  timerAnimation.Update(EngineGlobals::fixed_update_interval);
  
 

}

void FirstBossAttackScript::Attack(){
  


  if(m_surgeAnimation){
    animator->PlayAnimation("firstBossAttackSurgeAnimation");
    m_surgeAnimation = false;
    m_idleAnimation =  true;
    timerAnimation.Restart();
    
  }
  if(m_idleAnimation && timerAnimation.GetTime()>=1*1000){
    animator->PlayAnimation("firstBossAttackIdleAnimation");
    
    m_goneAnimation =  true;
    //timerAnimation.Restart();
  }
  if(m_goneAnimation && timerAnimation.GetTime() >= attackDuration*1000){
    animator->PlayAnimation("firstBossAttackGoneAnimation");
    m_goneAnimation = false;
    m_idleAnimation =  false;
    attack = false;
    m_surgeAnimation = true;
  }
  
}
