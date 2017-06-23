#include "Engine/CameraSystem.h"

CameraSystem *CameraSystem::m_instance = nullptr;

CameraSystem::CameraSystem() {
  this->cameraSpeed=32;
}

void CameraSystem::MoveUp(int speed,Scene * scene) {

  if(!scene)
  return;
//Get all scene game objects
  m_gameObjects = scene->GetAllGameObjects();
  if(m_gameObjects.empty())
    return;

  //Move all scene objects
  for(auto it = m_gameObjects.begin();it!=m_gameObjects.end();it++)
    (*it)->SetPosition(Vector((*it)->GetPosition()->m_x ,(*it)->GetPosition()->m_y + speed));

  //Set a new position
  worldCamera_y= worldCamera_y - speed;

}

void CameraSystem::MoveDown(int speed,Scene * scene) {

  if(!scene)
  return;

  m_gameObjects = scene->GetAllGameObjects();
  if(m_gameObjects.empty())
    return;
  //Move all scene objects
  for(auto it = m_gameObjects.begin();it!=m_gameObjects.end();it++)
    (*it)->SetPosition(Vector((*it)->GetPosition()->m_x ,(*it)->GetPosition()->m_y - speed ));

  //Move the camera
  worldCamera_y+=speed;

}

void CameraSystem::MoveLeft(int speed,Scene * scene) {

  if(!scene)
  return;

  m_gameObjects = scene->GetAllGameObjects();
  if(m_gameObjects.empty())
    return;
  //Move all scene objects
  for(auto it = m_gameObjects.begin();it!=m_gameObjects.end();it++)
    (*it)->SetPosition(Vector((*it)->GetPosition()->m_x + speed ,(*it)->GetPosition()->m_y ));

   //Set new position
   worldCamera_x-=speed;

}
void CameraSystem::MoveRight(int speed,Scene * scene){

  if(!scene)
  return;

  m_gameObjects = scene->GetAllGameObjects();
  if(m_gameObjects.empty())
    return;
  //Move all scene objects
  for(auto it = m_gameObjects.begin();it!=m_gameObjects.end();it++)
    (*it)->SetPosition(Vector((*it)->GetPosition()->m_x - speed ,(*it)->GetPosition()->m_y ));

  //Move the camera
  worldCamera_x+=speed;

}

void CameraSystem::CameraShake(int intensity,float duration,Scene * scene){

  if(!scene)
  return;

  static int last=0;
  timer.Update(EngineGlobals::fixed_update_interval);
  isShaking=true;
  if(timer.GetTime()>=duration*1000){
    isShaking=false;
   timer.Restart();
   return;
  }

  if(last==0){
  MoveRight(intensity,scene);
  MoveUp(intensity,scene);
  last=1;
  }
  else if(last==1){
  MoveLeft(intensity,scene);
  MoveDown(intensity,scene);
  last=0;
}



}
float CameraSystem::GetPos_x(){return worldCamera_x;}

float CameraSystem::GetPos_y(){return worldCamera_y;}

int CameraSystem::GetCameraSpeed(){return cameraSpeed;}

void CameraSystem::SetCameraSpeed(int speed){cameraSpeed=speed;}

void CameraSystem::SetAndMovePos_x(float x){worldCamera_x = x;}

void CameraSystem::SetAndMovePos_y(float y){worldCamera_y = y;}

void CameraSystem::Reset(){
  worldCamera_x=0;
  worldCamera_y=0;
}



void CameraSystem::ZoomIn(int zoomSpeed,GameObject * objectToFollow,Scene * scene) {

  auto map = SceneManager::GetInstance()->GetScene("Gameplay")->GetGameObject("Map");
    if(!map)
      return;
    x_pos_before = objectToFollow->GetPosition()->m_x;
    y_pos_before = objectToFollow->GetPosition()->m_y;
    this->cameraSpeed = zoomSpeed;
    auto m_gameObjects = SceneManager::GetInstance()->GetCurrentScene()->GetAllGameObjects();
    for(auto it = m_gameObjects.begin(); it!=m_gameObjects.end(); it++ ){
      if((*it)->GetName()!="Map"){
        proportion_x = 100*(((*it)->GetPosition()->m_x + worldCamera_x)/(map->GetWidth()));
        proportion_y = 100*(((*it)->GetPosition()->m_y + worldCamera_y   )/(map->GetHeight()));
        //if getzoomProportion==(0,0) the object wont be affected by the zoom
        if((*it)->GetZoomProportion()->m_x!=0,(*it)->GetZoomProportion()->m_y!=0){

          (*it)->SetSize(map->GetWidth()/(*it)->GetZoomProportion()->m_x,map->GetHeight()/(*it)->GetZoomProportion()->m_y);
          (*it)->GetPosition()->m_x = ((proportion_x/100) * (map->GetWidth() + zoomSpeed)) - worldCamera_x;
          (*it)->GetPosition()->m_y = ((proportion_y/100) * (map->GetHeight() + zoomSpeed)) - worldCamera_y;
        }
      }

    }

    map->SetSize(map->GetWidth() + zoomSpeed ,map->GetHeight() + zoomSpeed);
    if(x_pos_before < objectToFollow->GetPosition()->m_x){
      MoveRight(objectToFollow->GetPosition()->m_x - x_pos_before,scene);
    }
    else if(x_pos_before > objectToFollow->GetPosition()->m_x){
      MoveLeft(x_pos_before - objectToFollow->GetPosition()->m_x,scene);
    }
    if(y_pos_before < objectToFollow->GetPosition()->m_y){
      MoveDown(objectToFollow->GetPosition()->m_y - y_pos_before,scene);
    }
    else if(y_pos_before > objectToFollow->GetPosition()->m_y){
      MoveDown(y_pos_before - objectToFollow->GetPosition()->m_y,scene);
    }

}

void CameraSystem::ZoomOut(int zoomSpeed,GameObject * objectToFollow,Scene * scene) {
  auto map = SceneManager::GetInstance()->GetScene("Gameplay")->GetGameObject("Map");
    if(!map)
    return;
    x_pos_before = objectToFollow->GetPosition()->m_x;
    y_pos_before = objectToFollow->GetPosition()->m_y;
        this->cameraSpeed = zoomSpeed;
    auto m_gameObjects = SceneManager::GetInstance()->GetCurrentScene()->GetAllGameObjects();
    for(auto it = m_gameObjects.begin(); it!=m_gameObjects.end(); it++ ){
      if((*it)->GetName()!="Map"){

        proportion_x = 100*(((*it)->GetPosition()->m_x + worldCamera_x)/(map->GetWidth()));
        proportion_y = 100*(((*it)->GetPosition()->m_y + worldCamera_y   )/(map->GetHeight()));

        if((*it)->GetZoomProportion()->m_x!=0,(*it)->GetZoomProportion()->m_y!=0){
          (*it)->SetSize(map->GetWidth()/(*it)->GetZoomProportion()->m_x,map->GetHeight()/(*it)->GetZoomProportion()->m_y);
          (*it)->GetPosition()->m_x = ((proportion_x/100) * (map->GetWidth() - zoomSpeed)) - worldCamera_x;
          (*it)->GetPosition()->m_y = ((proportion_y/100) * (map->GetHeight() - zoomSpeed)) - worldCamera_y;
        }
      }

    }

    map->SetSize(map->GetWidth() - zoomSpeed ,map->GetHeight() - zoomSpeed);
    if(x_pos_before < objectToFollow->GetPosition()->m_x){
      MoveRight(objectToFollow->GetPosition()->m_x - x_pos_before,scene);
    }
    else if(x_pos_before > objectToFollow->GetPosition()->m_x){
      MoveLeft(x_pos_before - objectToFollow->GetPosition()->m_x,scene);
    }
    if(y_pos_before < objectToFollow->GetPosition()->m_y){
      MoveUp(objectToFollow->GetPosition()->m_y - y_pos_before,scene);
    }
    else if(y_pos_before > objectToFollow->GetPosition()->m_y){
      MoveUp(y_pos_before - objectToFollow->GetPosition()->m_y,scene);
    }

}


CameraSystem * CameraSystem::GetInstance(){
  if (!m_instance)
    m_instance = new CameraSystem();
  return m_instance;
}

