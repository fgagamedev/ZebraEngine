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

  auto firstBossAttackImage = new Image("assets/firstBossAttack.png",0,0,600, 151);

  auto firstBossAttackAnimation= new Animation(GetOwner(),firstBossAttackImage );
  for (int i = 0; i < 15; i++){
    firstBossAttackAnimation->AddFrame(new Frame(i * 40, 0, 40, 151));
  }
  // animator
  auto firstBossAttackAnimator = new Animator(GetOwner());
  firstBossAttackAnimator->AddAnimation("firstBossAttackAnimation", firstBossAttackAnimation);
}


void FirstBossAttackScript::ComponentUpdate() {
auto vec = Vector(firstBossAttackCollider->GetRectanglePoint().m_x,firstBossAttackCollider->GetRectanglePoint().m_y);
GraphicsSystem::GetInstance()->DrawFillRectangle(vec, GetOwner()->GetWidth(), GetOwner()->GetHeight(), 255,0,0,100);

  boss = SceneManager::GetInstance()->GetCurrentScene()->GetGameObject("FirstBoss");

  if(boss)
    animator->PlayAnimation("firstBossAttackAnimation");
}
void FirstBossAttackScript::FixedComponentUpdate() {
  if(boss){}
}
