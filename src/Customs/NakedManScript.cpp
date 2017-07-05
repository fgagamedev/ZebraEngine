#include "Customs/NakedManScript.h"
#include "Customs/FirstBossController.h"
#include "Customs/MapScript.h"
#include <stdio.h>
bool NakedManScript::isZooming=false;

NakedManScript::NakedManScript(GameObject *owner) : Script(owner) {}

void NakedManScript::Start() {
  CreateAnimations();
  position = GetOwner()->GetPosition();
  animator = (Animator *)GetOwner()->GetComponent("Animator");
  input = InputSystem::GetInstance();
  CameraSystem::GetInstance()->SetCameraSpeed(walkSpeed);
 

  auto map = SceneManager::GetInstance()->GetScene("Gameplay")->GetGameObject("Map");
  if(map) GetOwner()->SetZoomProportion(Vector(map->originalWidth/GetOwner()->originalWidth,map->originalHeight/GetOwner()->originalHeight));
  nakedManCollider = new RectangleCollider(GetOwner(), Vector(0, 0), GetOwner()->GetWidth(), GetOwner()->GetHeight(), 0);

  FirstBossController::GetInstance();
}

void NakedManScript::SetDirection(){
mousePosition = input->GetMousePosition();


//if(input->GetMouseButtonPressed(M_INPUT_LEFT))
//x-axis
    if(mousePosition.first >= position->m_x && movements==4){
    isMovingLooking=true;
    }
    else if(mousePosition.first > position->m_x && movements==3){
    isMovingLooking=false;
    }

    if(mousePosition.first <= position->m_x && movements==3){
    isMovingLooking=true;
    }
    else if(mousePosition.first < position->m_x && movements==4){
    isMovingLooking=false;
    }
//y-axis
    if(mousePosition.second <= position->m_y && movements==1){
    isMovingLooking=true;
    }
    else if(mousePosition.second < position->m_y && movements==2){
    isMovingLooking=false;
    }

    if(mousePosition.second >= position->m_y && movements==2){
      isMovingLooking=true;
     }
     else if(mousePosition.second > position->m_y && movements==1){
       isMovingLooking=false;
     }
//Diagonal 1
    if(mousePosition.first >= position->m_x && mousePosition.second <= position->m_y && movements == 6){
    isMovingLooking=true;
    }
    else if(mousePosition.first >= position->m_x && mousePosition.second <= position->m_y && movements == 7){
    isMovingLooking=false;
    }

 if(mousePosition.first <= position->m_x && mousePosition.second >= position->m_y && movements == 7){
    isMovingLooking=true;
    }
    else if(mousePosition.first <= position->m_x && mousePosition.second >= position->m_y && movements == 6){
    isMovingLooking=false;
    }
//Diagonal 2

   if(mousePosition.first >= position->m_x && mousePosition.second >= position->m_y && movements == 8){
    isMovingLooking=true;
    }
    else if(mousePosition.first >= position->m_x && mousePosition.second >= position->m_y && movements == 5){
    isMovingLooking=false;
    }
    if(mousePosition.first <= position->m_x && mousePosition.second <= position->m_y && movements == 5){
    isMovingLooking=true;
    }
    else if(mousePosition.first <= position->m_x && mousePosition.second <= position->m_y && movements == 8){
    isMovingLooking=false;
    }






}

void NakedManScript::CreateAnimations(){

  // animator
  auto nakedManAnimator = new Animator(GetOwner());

 auto nakedManSprite = new Image("assets/player.png", 0, 0, 1664, 512);

  auto StopDownAnimation = new Animation(GetOwner(), nakedManSprite);
    StopDownAnimation->AddFrame(new Frame(0, 256, 128, 128));

  auto StopRightAnimation = new Animation(GetOwner(), nakedManSprite);
         StopRightAnimation->AddFrame(new Frame(0, 0, 128, 128));

  auto StopLeftAnimation = new Animation(GetOwner(), nakedManSprite);
        StopLeftAnimation->AddFrame(new Frame(0, 128, 128, 128));

  auto StopUpAnimation = new Animation(GetOwner(), nakedManSprite);
        StopUpAnimation->AddFrame(new Frame(0, 384, 128, 128));



 auto walkSideAnimation = new Animation(GetOwner(), nakedManSprite);
  for (int i = 1; i < 13; i++)
    walkSideAnimation->AddFrame(new Frame(i * 128, 0, 128, 128));

  auto walkUpAnimation = new Animation(GetOwner(), nakedManSprite);
  for (int i = 1; i < 13; i++)
    walkUpAnimation->AddFrame(new Frame(i * 128, 384, 128, 128));

  auto walkDownAnimation = new Animation(GetOwner(), nakedManSprite);
  for (int i = 1; i < 13; i++)
    walkDownAnimation->AddFrame(new Frame(i * 128, 256, 128, 128));


  nakedManAnimator->AddAnimation("Walk Side", walkSideAnimation);
  nakedManAnimator->AddAnimation("Walk Up", walkUpAnimation);
  nakedManAnimator->AddAnimation("Walk Down", walkDownAnimation);



  auto backwalkSideAnimation = new Animation(GetOwner(), nakedManSprite);
  for (int i = 12; i >0; i--)
    backwalkSideAnimation->AddFrame(new Frame(i * 128, 0, 128, 128));

  auto backwalkUpAnimation = new Animation(GetOwner(), nakedManSprite);
  for (int i = 12; i >0; i--)
    backwalkUpAnimation->AddFrame(new Frame(i * 128, 384, 128, 128));

  auto backwalkDownAnimation = new Animation(GetOwner(), nakedManSprite);
  for (int i = 12; i >0; i--)
    backwalkDownAnimation->AddFrame(new Frame(i * 128, 256, 128, 128));

  nakedManAnimator->AddAnimation("Back Walk Side", backwalkSideAnimation);
  nakedManAnimator->AddAnimation("Back Walk Up", backwalkUpAnimation);
  nakedManAnimator->AddAnimation("Back Walk Down", backwalkDownAnimation);
  nakedManAnimator->AddAnimation("Stop Down", StopDownAnimation);
  nakedManAnimator->AddAnimation("Stop Up", StopUpAnimation);
  nakedManAnimator->AddAnimation("Stop Left", StopLeftAnimation);
  nakedManAnimator->AddAnimation("Stop Right", StopRightAnimation);
}

void NakedManScript::ComponentUpdate() {




auto vec = Vector(nakedManCollider->GetRectanglePoint().m_x,nakedManCollider->GetRectanglePoint().m_y);
GraphicsSystem::GetInstance()->DrawFillRectangle(vec, GetOwner()->GetWidth(), GetOwner()->GetHeight(), 255,0,0,100);


SetDirection();

walkSpeed = fixedWalkSpeed;
  movements = 0;

  if((input->GetKeyPressed(INPUT_DOWN)) || (input->GetKeyPressed(INPUT_UP)))
    isZooming=true;
  if((input->GetKeyUp(INPUT_DOWN)) || (input->GetKeyUp(INPUT_UP)))
    isZooming=false;



  if((input->GetKeyDown(INPUT_V)) && (!isMovingLooking)){
    isMovingLooking=true;
  }else if((input->GetKeyDown(INPUT_V)) && (isMovingLooking)){
    isMovingLooking=false;
  }

if(isMovingLooking){

    if (input->GetKeyPressed(INPUT_W) && input->GetKeyPressed(INPUT_A)) {
        movements=5;
        lastDirection=5;
        animator->GetAnimation("Walk Side")->SetFlip(true, false);
        animator->PlayAnimation("Walk Side");
     }
     else if (input->GetKeyPressed(INPUT_W) && input->GetKeyPressed(INPUT_D)) {
        movements=6;
        lastDirection=6;
        animator->GetAnimation("Walk Side")->SetFlip(false, false);
       animator->PlayAnimation("Walk Side");
     }
     else if (input->GetKeyPressed(INPUT_S) && input->GetKeyPressed(INPUT_A)) {
        movements=7;
        lastDirection=7;
        animator->GetAnimation("Walk Side")->SetFlip(true, false);
        animator->PlayAnimation("Walk Side");
     }
     else if (input->GetKeyPressed(INPUT_S) && input->GetKeyPressed(INPUT_D)) {
       movements=8;
       lastDirection=8;
       animator->GetAnimation("Walk Side")->SetFlip(false, false);
       animator->PlayAnimation("Walk Side");
     }

  else if (input->GetKeyPressed(INPUT_W)) {
    lastDirection=0;
    movements = 1;
    animator->PlayAnimation("Walk Up");

  } else if (input->GetKeyPressed(INPUT_S)) {
    lastDirection=1;
    movements = 2;
    animator->PlayAnimation("Walk Down");
  } else if (input->GetKeyPressed(INPUT_A)) {
   lastDirection=3;
    movements = 3;
    animator->GetAnimation("Walk Side")->SetFlip(true, false);
    animator->PlayAnimation("Walk Side");
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
}else{
 if (input->GetKeyPressed(INPUT_W) && input->GetKeyPressed(INPUT_A)) {
        movements=5;
        lastDirection=5;
        animator->GetAnimation("Back Walk Side")->SetFlip(false, false);
        animator->PlayAnimation("Back Walk Side");
     }
     else if (input->GetKeyPressed(INPUT_W) && input->GetKeyPressed(INPUT_D)) {
        movements=6;
        lastDirection=6;
        animator->GetAnimation("Back Walk Side")->SetFlip(true, false);
       animator->PlayAnimation("Back Walk Side");
     }
     else if (input->GetKeyPressed(INPUT_S) && input->GetKeyPressed(INPUT_A)) {
        movements=7;
        lastDirection=7;
        animator->GetAnimation("Back Walk Side")->SetFlip(false, false);
        animator->PlayAnimation("Back Walk Side");
     }
     else if (input->GetKeyPressed(INPUT_S) && input->GetKeyPressed(INPUT_D)) {
       movements=8;
       lastDirection=8;
       animator->GetAnimation("Back Walk Side")->SetFlip(true, false);
       animator->PlayAnimation("Back Walk Side");
     }
else if (input->GetKeyPressed(INPUT_W)) {
    lastDirection=0;
    movements = 1;
    animator->PlayAnimation("Back Walk Down");

  } else if (input->GetKeyPressed(INPUT_S)) {
    lastDirection=1;
    movements = 2;
    animator->PlayAnimation("Back Walk Up");
  } else if (input->GetKeyPressed(INPUT_A)) {
   lastDirection=3;
    movements = 3;
    animator->GetAnimation("Back Walk Side")->SetFlip(false, false);
    animator->PlayAnimation("Back Walk Side");
  } else if (input->GetKeyPressed(INPUT_D)) {
    lastDirection=3;
    movements = 4;
    animator->GetAnimation("Back Walk Side")->SetFlip(true, false);
    animator->PlayAnimation("Back Walk Side");
  } else {

    if(lastDirection==0) {
    animator->PlayAnimation("Stop Down");
    }
    else if(lastDirection==1) {
    animator->PlayAnimation("Stop Up");
    }
    else if(lastDirection==2) {
    animator->PlayAnimation("Stop Left");
    }
    else if(lastDirection==3) {
    animator->PlayAnimation("Stop Right");
    }

  }

}
  //Sair para o Menu
  if (InputSystem::GetInstance()->GetKeyUp(INPUT_ESCAPE)) {
    /*
    auto var = (UIText *)SceneManager::GetInstance()
                   ->GetScene("Main")
                   ->GetGameObject("Play")
                   ->GetComponent("UIText");
    var->SetText("Continue");
    */
    //SceneManager::GetInstance()->SetCurrentScene("Main");
    SDLSystem::GetInstance()->SetRunning(false);
  }

  //Shoot gun
  if (InputSystem::GetInstance()->GetKeyDown(INPUT_SPACE)) {
      
      cout << "ammo: " << bulletNumber << endl;
      
      auto gameObjectBullet = (GameObject*)SceneManager::GetInstance()
                   ->GetCurrentScene()
                   ->GetGameObject("Bullet" + std::to_string(bulletNumber));
      gameObjectBullet->active = true;

      auto script = (PlayerAttackScript*)SceneManager::GetInstance()
                   ->GetCurrentScene()
                   ->GetGameObject("Bullet" + std::to_string(bulletNumber))
                   ->GetComponent("PlayerAttackScript");
      script->SetShoot(true);

      
                 

      bulletNumber--;
      

      /** Reload **/ 
      if(bulletNumber == 0){
        bulletNumber = 10; 
        //wait delay reload time
        
      }
    
    
  }


  if(input->GetKeyDown(INPUT_L) && cameraLock==false) {
       cameraLock=true;
       deadzone_x = EngineGlobals::screen_width / 2;
       deadzone_y = EngineGlobals::screen_height / 2;
  }else if(input->GetKeyDown(INPUT_L) && cameraLock==true){
  cameraLock=false;
      deadzone_x = EngineGlobals::screen_width;
      deadzone_y = EngineGlobals::screen_height;
  animator->StopAllAnimations();
  }
}

void NakedManScript::FixedComponentUpdate() {

printf("x = %f\ny = %f\n\n",position->m_x,position->m_y);
printf("x = %f\ny = %f\n\n",position->m_x + CameraSystem::GetInstance()->GetPos_x()-3500,position->m_y+ CameraSystem::GetInstance()->GetPos_y()-3800);


    GameCollisionCheck();
    WallCollisionResolution();


    //GameCollisionCheck();
    StartFirstBoss();
    Movements();


    
}


void NakedManScript::Movements(){

  if (movements==5){
    walkSpeed = walkSpeed*0.70710;
    position->m_y -= walkSpeed;
    position->m_x -= walkSpeed;

  }else if (movements==6){
    walkSpeed = walkSpeed*0.70710;
    position->m_y -= walkSpeed;
    position->m_x += walkSpeed;

  }else if (movements==7){
    walkSpeed = walkSpeed*0.70710;
    position->m_y += walkSpeed;
    position->m_x -= walkSpeed;

  }else if (movements==8){
    walkSpeed = walkSpeed*0.70710;
    position->m_y += walkSpeed;
    position->m_x += walkSpeed;
  }else if (movements==1){

    position->m_y -= walkSpeed;
  }else if (movements==2){

    position->m_y += walkSpeed;
  }else if (movements==3){

    position->m_x -= walkSpeed;
  }else if (movements==4){

    position->m_x += walkSpeed;
  }

  if(cameraLock){

    if (position->m_x + GetOwner()->GetWidth() >= deadzone_x){ //Mount deadzode on x++
      if(isZooming){
        CameraSystem::GetInstance()->MoveRight(2,SceneManager::GetInstance()->GetCurrentScene());
      }else{
        CameraSystem::GetInstance()->MoveRight(walkSpeed,SceneManager::GetInstance()->GetCurrentScene());
      }
    }

    if (position->m_x <= deadzone_x){ //Mount deadzode on x-
      if(isZooming){
        CameraSystem::GetInstance()->MoveLeft(2,SceneManager::GetInstance()->GetCurrentScene());
      }else{
        CameraSystem::GetInstance()->MoveLeft(walkSpeed,SceneManager::GetInstance()->GetCurrentScene());
      }
    }

    if (position->m_y + GetOwner()->GetWidth() >= deadzone_y){ //Mount deadzode on y++
      if(isZooming){
        CameraSystem::GetInstance()->MoveDown(2,SceneManager::GetInstance()->GetCurrentScene());
      }else{
        CameraSystem::GetInstance()->MoveDown(walkSpeed,SceneManager::GetInstance()->GetCurrentScene());
      }
    }

    if (position->m_y <= deadzone_y){//Mount deadzode on y--
      if(isZooming){
        CameraSystem::GetInstance()->MoveUp(2,SceneManager::GetInstance()->GetCurrentScene());
      }else{
        CameraSystem::GetInstance()->MoveUp(walkSpeed,SceneManager::GetInstance()->GetCurrentScene());
      }

    }
  
  }else{
    
    if (position->m_x + GetOwner()->GetWidth() >= deadzone_x){
      if(isZooming){
        CameraSystem::GetInstance()->MoveRight(2,SceneManager::GetInstance()->GetCurrentScene());
      }else{
        CameraSystem::GetInstance()->MoveRight(walkSpeed,SceneManager::GetInstance()->GetCurrentScene());
      }
    }

    if (position->m_x <= 0){
      if(isZooming){
        CameraSystem::GetInstance()->MoveLeft(2,SceneManager::GetInstance()->GetCurrentScene());
      }else{
        CameraSystem::GetInstance()->MoveLeft(walkSpeed,SceneManager::GetInstance()->GetCurrentScene());
      }
    }

    if (position->m_y + GetOwner()->GetWidth() >= deadzone_y){
      if(isZooming){
        CameraSystem::GetInstance()->MoveDown(2,SceneManager::GetInstance()->GetCurrentScene());
      }else{
        CameraSystem::GetInstance()->MoveDown(walkSpeed,SceneManager::GetInstance()->GetCurrentScene());
      }
    }


  }



    if (position->m_y <= 0){
      if(isZooming){
        CameraSystem::GetInstance()->MoveUp(2,SceneManager::GetInstance()->GetCurrentScene());
      }else{
        CameraSystem::GetInstance()->MoveUp(walkSpeed,SceneManager::GetInstance()->GetCurrentScene());
      }
    }


}

void NakedManScript::GameCollisionCheck() {

    auto script = (HitScript*)SceneManager::GetInstance()
                   ->GetScene("Gameplay")
                   ->GetGameObject("Hit")
                   ->GetComponent("HitScript");
  
  if(m_hitFrameController){
    m_hitFrames++;
    std::cout << m_hitFrames << std::endl;
  }
  if(m_hitFrames> 20){
     script->play = 0;
     m_hitFrames = 0;
  }

  for (auto obj : GetOwner()->GetCollisions()) {
    if (obj->GetTag() == "Bullet") {
      cout << "Bullet Colider" << endl;
      GetOwner()->ClearCollisions();
      
    }else if(obj->GetTag() == "FirstBoss"){
      cout << "Boss Colider" << endl;
      GetOwner()->ClearCollisions();
    }else if(obj->GetTag() == "FirstBossAtack"){
      cout << "Boss Atack Colider" << endl;
      script->play = 1;
      m_hitFrameController = true;
      
      GetOwner()->ClearCollisions();
    }
   
  }
}


void NakedManScript::StartFirstBoss(){
  
  //cout << position->m_y << endl;
  if(input->GetKeyDown(INPUT_X)) {
    cout << "X: " <<CameraSystem::GetInstance()->worldCamera_x << endl;
    cout << "Y: " <<CameraSystem::GetInstance()->worldCamera_y << endl;
  }
  //cout << SceneManager::GetInstance()->GetCurrentScene()->GetName() <<  endl;
  
  if( (CameraSystem::GetInstance()->worldCamera_x < 980)){
    if(CameraSystem::GetInstance()->currentZoom > -50){ //Take zoom out 2 times
      CameraSystem::GetInstance()->ZoomOut(SceneManager::GetInstance()->GetCurrentScene()->GetGameObject("Map")->originalWidth/4 + 1,GetOwner(),SceneManager::GetInstance()->GetCurrentScene());
      CameraSystem::GetInstance()->ZoomIn(1,GetOwner(),SceneManager::GetInstance()->GetCurrentScene());
      CameraSystem::GetInstance()->currentZoom -=25;

      FirstBossController::GetInstance()->ActivateBoss();
      FirstBossController::GetInstance()->ActivateInsideBossFx();
      //zoom = false;
      
    }
   
  }

}


void NakedManScript::WallCollisionResolution(){

    auto mapscript = (MapScript*)SceneManager::GetInstance()->GetScene("Gameplay")->GetGameObject("Map")->GetComponent("MapScript");
    if(mapscript)
        mapscript->DetectWallCollision(GetOwner());
}

  /*
  if( (CameraSystem::GetInstance()->worldCamera_x > 980) && CameraSystem::GetInstance()->currentZoom ){
    if(zoom){
      CameraSystem::GetInstance()->ZoomOut(SceneManager::GetInstance()->GetCurrentScene()->GetGameObject("Map")->originalWidth/4 + 1,GetOwner(),SceneManager::GetInstance()->GetCurrentScene());
      CameraSystem::GetInstance()->ZoomIn(1,GetOwner(),SceneManager::GetInstance()->GetCurrentScene());
      CameraSystem::GetInstance()->currentZoom -=25;
      zoom = false;
      
    }
   
  }
  */
 



