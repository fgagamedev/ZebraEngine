#include "Customs/FirstBossScript.h"

FirstBossScript::FirstBossScript(GameObject *owner) : Script(owner) {}

void FirstBossScript::Start() {

  CreateAnimations();
  position = GetOwner()->GetPosition();
  animator = (Animator *)GetOwner()->GetComponent("Animator");
  input = InputSystem::GetInstance();
  auto map = SceneManager::GetInstance()->GetScene("Gameplay")->GetGameObject("Map");
  if(map) GetOwner()->SetZoomProportion(Vector(map->originalWidth/GetOwner()->originalWidth,map->originalHeight/GetOwner()->originalHeight));
  firstBossCollider = new RectangleCollider(GetOwner(), Vector(0, 0), GetOwner()->GetWidth(), GetOwner()->GetHeight(), 0);
}
void FirstBossScript::CreateAnimations(){

  auto firstBossImage = new Image("assets/boss1.png",0,0,1896, 324);
  auto firstBossJumpImage = new Image("assets/boss1_jump.png",0,0,1180, 406);


  auto firstBossAnimation= new Animation(GetOwner(),firstBossImage );
  for (int i = 0; i < 8; i++)
    firstBossAnimation->AddFrame(new Frame(i * 237,0, 237, 406));


  auto firstBossJumpAnimation= new Animation(GetOwner(),firstBossJumpImage );
  for (int i = 0; i < 5; i++){
    firstBossJumpAnimation->AddFrame(new Frame(i * 236,0, 236, 406));
    firstBossJumpAnimation->AddFrame(new Frame(i * 236,0, 236, 406)); 
    if(i==4){
      for(int animMulti = 0 ; i < 8 ; i++){
        firstBossJumpAnimation->AddFrame(new Frame(i * 236,0, 236, 406));
        firstBossJumpAnimation->AddFrame(new Frame(i * 236,0, 236, 406)); 
      }
    }   
  }



  // animator
  auto firstBossAnimator = new Animator(GetOwner());
      
      firstBossAnimator->AddAnimation("firstBossAnimation", firstBossAnimation);
      firstBossAnimator->AddAnimation("firstBossJumpAnimation", firstBossJumpAnimation);


}


void FirstBossScript::ComponentUpdate() {
  //Debug Collider
  //auto vec = Vector(firstBossCollider->GetRectanglePoint().m_x,firstBossCollider->GetRectanglePoint().m_y);
  //GraphicsSystem::GetInstance()->DrawFillRectangle(vec, GetOwner()->GetWidth(), GetOwner()->GetHeight(), 255,0,0,100);
  
  if(!SecondAttack){
    animator->PlayAnimation("firstBossAnimation"); //Idle animation
    
  }


  if((timerSecondAttack.GetTime() >= 0.5*1000) && SecondAttack ){
     if(GetOwner()->GetPosition()->m_y > -1900){
      Vector *newPosition = GetOwner()->GetPosition();
       
      newPosition->m_y = newPosition->m_y - 90;
      GetOwner()->SetPosition(*newPosition);
    }
  }
  if(timerSecondAttack.GetTime() >= 1*1000){
      SecondAttack = false;

    }
    

   
    
  //animator->PlayAnimation("firstBossJumpAnimation");
  
    

}


void FirstBossScript::FixedComponentUpdate() {
  

    timerFirstAttackCooldown.Update(EngineGlobals::fixed_update_interval);
  
  if(goneFirstAttack)
    timerFirstAttackGone.Update(EngineGlobals::fixed_update_interval);
 
  if(SecondAttack)
    timerSecondAttack.Update(EngineGlobals::fixed_update_interval);


  timerAttackCooldown.Update(EngineGlobals::fixed_update_interval);
  Attack();
}

void FirstBossScript::Attack(){


  if(GetOwner()->active){
    //rand first attack or second attack
    

    if(timerAttackCooldown.GetTime() >= 10*1000){ // chosse new number
      //int randNum = rand() % 2;
      randNumber = 1;
      //timerFirstAttackCooldown.Restart();
    }
    
    //if(randNumber){
      //FirstAttack = true;
      /** First Attack **/
      if(timerFirstAttackCooldown.GetTime() >= 2*1000 && firstAttackCounter < 3){

        FirstBossController::GetInstance()->FirstAttackSurge();
        timerFirstAttackCooldown.Restart();
        firstAttackCounter++;
        //delay for next sord
      }
      if(firstAttackCounter == 3){ //Activate timer to gone tentacle
        goneFirstAttack = true;
      }

      if(timerFirstAttackGone.GetTime() >= 2*1000){ //wait 6 seconds to make attack gone
        FirstBossController::GetInstance()->FirstAttackGone();
      
        firstAttackCounter = 0;
        goneFirstAttack = false;
        timerFirstAttackGone.Restart();
        timerFirstAttackCooldown.Restart();
       
      }
    //}else{
        /** Second Attack **/ 
//      SecondAttack = true;
//      animator->PlayAnimation("firstBossJumpAnimation");
    //}


   



  }
  

 
 

}