#include "Customs/FirstBossAttackScript.h"
#include "Customs/AudioController.h"

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

  if(desactivateObj)
  timerGone.Update(EngineGlobals::fixed_update_interval);
  
  CameraShakeAttack();
 

}

void FirstBossAttackScript::Attack(){
  


  if(m_surgeAnimation){
    CameraSystem::GetInstance()->CameraShake(8,3,SceneManager::GetInstance()->GetCurrentScene());
    animator->PlayAnimation("firstBossAttackSurgeAnimation");
    m_surgeAnimation = false;
    m_idleAnimation =  true;
    timerAnimation.Restart();
    //auto soundFX = (UISound *)GetOwner()->GetComponent("UISound");
    //soundFX->Play(0, -1);
    AudioController::GetInstance()->PlayAudio("secondAttackSound", 0);
    
    
  }
  if(m_idleAnimation && timerAnimation.GetTime()>=1*1000){
    animator->PlayAnimation("firstBossAttackIdleAnimation");
    //m_goneAnimation =  true;
    //timerAnimation.Restart();
  }
  if(m_goneAnimation){
    animator->PlayAnimation("firstBossAttackGoneAnimation");
    AudioController::GetInstance()->PlayAudio("fourthAttackSound", 0);
    m_goneAnimation = false;
    m_idleAnimation =  false;
    attack = false;
    m_surgeAnimation = true;
    desactivateObj = true;
    GetOwner()->active = false;

  }
  if(timerGone.GetTime()>=1*1000){

    timerGone.Restart();
    desactivateObj = false;
  }
  
}

void FirstBossAttackScript::CameraShakeAttack(){
  if(shake){
    //CameraShake(intensity,duration in seconds)
    CameraSystem::GetInstance()->CameraShake(8,1,SceneManager::GetInstance()->GetCurrentScene());
    if(!CameraSystem::GetInstance()->IsShaking())
    shake=false;
  }
}
