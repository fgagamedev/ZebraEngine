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


  //Second Attack
  auto firstBossFallAnimation= new Animation(GetOwner(),firstBossJumpImage );
  for (int i = 5; i > 0; i--){
    firstBossFallAnimation->AddFrame(new Frame(i * 236,0, 236, 406));
    firstBossFallAnimation->AddFrame(new Frame(i * 236,0, 236, 406)); 
   
  }



  // animator
  auto firstBossAnimator = new Animator(GetOwner());
  firstBossAnimator->AddAnimation("firstBossAnimation", firstBossAnimation);
  firstBossAnimator->AddAnimation("firstBossJumpAnimation", firstBossJumpAnimation);
  firstBossAnimator->AddAnimation("firstBossFallAnimation", firstBossFallAnimation);


}


void FirstBossScript::ComponentUpdate() {
  //Debug Collider
  //auto vec = Vector(firstBossCollider->GetRectanglePoint().m_x,firstBossCollider->GetRectanglePoint().m_y);
  //GraphicsSystem::GetInstance()->DrawFillRectangle(vec, GetOwner()->GetWidth(), GetOwner()->GetHeight(), 255,0,0,100);
  
  if(!SecondAttack && !SecondAttackFall){
    animator->PlayAnimation("firstBossAnimation"); //Idle animation
    
  }

  if(input->GetKeyPressed(INPUT_N)){
    SecondAttack = true;
    animator->PlayAnimation("firstBossJumpAnimation");
  }


  
    

   
    
  //animator->PlayAnimation("firstBossJumpAnimation");
  
    

}


void FirstBossScript::FixedComponentUpdate() {
  
  if(FirstAttack)
    timerFirstAttackCooldown.Update(EngineGlobals::fixed_update_interval);
  
  if(goneFirstAttack)
    timerFirstAttackGone.Update(EngineGlobals::fixed_update_interval);
 
  if(SecondAttack)
    timerSecondAttack.Update(EngineGlobals::fixed_update_interval);

  if(SecondAttackFall)
    timerSecondAttackFall.Update(EngineGlobals::fixed_update_interval);


  timerAttackCooldown.Update(EngineGlobals::fixed_update_interval);
  
  Attack();


  if(shake){
    //CameraShake(intensity,duration in seconds)
    CameraSystem::GetInstance()->CameraShake(8,1,SceneManager::GetInstance()->GetCurrentScene());
    if(!CameraSystem::GetInstance()->IsShaking())
    shake=false;
  }
}

void FirstBossScript::Attack(){


  if(GetOwner()->active){
    //rand first attack or second attack
    
    
    if(timerAttackCooldown.GetTime() >= 8*1000){ // chosse new number
      randNum = rand() % 2;
      timerAttackCooldown.Restart();
      //randNumber = 1;
      cout << randNum << endl;
    }

    


    if(randNum == 0 && SecondAttackFall ==  false){
      cout << "First Attack" << endl;
      SecondAttack = true;
      animator->PlayAnimation("firstBossJumpAnimation");
    }

    if(randNum ==  1){
      cout << "Second Attack" << endl;
      FirstAttack = true;
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
      
    }

    if((timerSecondAttack.GetTime() >= 0.5*1000) && SecondAttack ){
      if(GetOwner()->GetPosition()->m_y > -1900){
        Vector *newPosition = GetOwner()->GetPosition();
         
        newPosition->m_y = newPosition->m_y - 90;
        GetOwner()->SetPosition(*newPosition);
        
      }else{
        SecondAttack = false;
        SecondAttackFall = true;
        timerSecondAttack.Restart();
      }
    }
    if(timerSecondAttackFall.GetTime() >= 2*1000  && SecondAttackFall){



      //player position
     //Get player Position
      player =  SceneManager::GetInstance()->GetCurrentScene()->GetGameObject("NakedMan");
      playerPosition.m_x  =  player->GetPosition()->m_x -  160;
      playerPosition.m_y  =  player->GetPosition()->m_y -  450;
      cout << "flag" << endl;

      std::cout << playerPosition.m_x << "  "  << playerPosition.m_y << std::endl;
      
      GetOwner()->m_position->m_x = playerPosition.m_x;
      if(GetOwner()->m_position->m_y < playerPosition.m_y){
        GetOwner()->m_position->m_y += 90;
        shake = true;
        animator->PlayAnimation("firstBossFallAnimation"); 
      }else{
        SecondAttackFall = false;
        shake = false;
      }

      

    }
    //if(randNumber){
    //}else{
        /** Second Attack **/ 
//      SecondAttack = true;
//      animator->PlayAnimation("firstBossJumpAnimation");
    //}


   



  }
  

 
 

}