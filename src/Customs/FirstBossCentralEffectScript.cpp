#include "Customs/FirstBossCentralEffectScript.h"

FirstBossCentralEffectScript::FirstBossCentralEffectScript(GameObject *owner) : Script(owner) {}

void FirstBossCentralEffectScript::Start() {

  CreateAnimations();
  position = GetOwner()->GetPosition();
  animator = (Animator *)GetOwner()->GetComponent("Animator");
  input = InputSystem::GetInstance();
  GetOwner()->SetZoomProportion(Vector(175,175));

}
void FirstBossCentralEffectScript::CreateAnimations(){

  auto firstBossCentralImage1 = new Image("assets/centroboss11.png",0,0,700, 70);

    auto firstBossCentralAnimation1= new Animation(GetOwner(),firstBossCentralImage1 );
      for (int i = 0; i < 10; i++)
        firstBossCentralAnimation1->AddFrame(new Frame(i * 70,0, 70, 70));

     // animator
      auto firstBossAnimator = new Animator(GetOwner());
      firstBossAnimator->AddAnimation("firstBossCentralAnimation1", firstBossCentralAnimation1);

}


void FirstBossCentralEffectScript::ComponentUpdate() {
animator->PlayAnimation("firstBossCentralAnimation1");
}
void FirstBossCentralEffectScript::FixedComponentUpdate() {
 position->m_x  =  SceneManager::GetInstance()->GetCurrentScene()->GetGameObject("FirstBoss")->GetPosition()->m_x +
   SceneManager::GetInstance()->GetCurrentScene()->GetGameObject("FirstBoss")->GetWidth()/2-30;
 position->m_y  =  SceneManager::GetInstance()->GetCurrentScene()->GetGameObject("FirstBoss")->GetPosition()->m_y +
 SceneManager::GetInstance()->GetCurrentScene()->GetGameObject("FirstBoss")->GetHeight()/2 - 20;

}
