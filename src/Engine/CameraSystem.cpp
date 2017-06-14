#include "Engine/CameraSystem.h"

  // static variables initialization
  CameraSystem *CameraSystem::m_instance = 0;
  Timer CameraSystem::timer;
  float CameraSystem::worldCamera_x=0;
  float CameraSystem::worldCamera_y=0;
  int CameraSystem::current_x=0;
  int CameraSystem::current_y=0;
  bool CameraSystem::isShaking=false;
  std::vector<GameObject *> CameraSystem::m_gameObjects;


CameraSystem::CameraSystem() {
  this->worldCamera_x=0;
  this->worldCamera_y=0;
  this->cameraSpeed=32;
}

void CameraSystem::MoveUp(int speed) {
  m_gameObjects = SceneManager::GetInstance()->GetCurrentScene()->GetAllGameObjects();
  if(m_gameObjects.empty())
    return;

  //Move all objects of the current scene
  for(auto it = m_gameObjects.begin();it!=m_gameObjects.end();it++)
    (*it)->SetPosition(Vector((*it)->GetPosition()->m_x ,(*it)->GetPosition()->m_y + speed));

  //Set a new position
  worldCamera_y= worldCamera_y - speed;
}

void CameraSystem::MoveDown(int speed) {
  m_gameObjects = SceneManager::GetInstance()->GetCurrentScene()->GetAllGameObjects();
  if(m_gameObjects.empty())
    return;
  //Move all objects of the current scene
  for(auto it = m_gameObjects.begin();it!=m_gameObjects.end();it++)
    (*it)->SetPosition(Vector((*it)->GetPosition()->m_x ,(*it)->GetPosition()->m_y - speed ));

  //Move the camera
  worldCamera_y+=speed;
}

void CameraSystem::MoveLeft(int speed) {
  m_gameObjects = SceneManager::GetInstance()->GetCurrentScene()->GetAllGameObjects();
  if(m_gameObjects.empty())
    return;
  //Move all objects of the current scene
  for(auto it = m_gameObjects.begin();it!=m_gameObjects.end();it++)
    (*it)->SetPosition(Vector((*it)->GetPosition()->m_x + speed ,(*it)->GetPosition()->m_y ));

   //Set new position
   worldCamera_x-=speed;
}
void CameraSystem::MoveRight(int speed){
  m_gameObjects = SceneManager::GetInstance()->GetCurrentScene()->GetAllGameObjects();
  if(m_gameObjects.empty())
    return;
  //Move all objects of the current scene
  for(auto it = m_gameObjects.begin();it!=m_gameObjects.end();it++)
    (*it)->SetPosition(Vector((*it)->GetPosition()->m_x - speed ,(*it)->GetPosition()->m_y ));

  //Move the camera
  worldCamera_x+=speed;
}

void CameraSystem::CameraShake(int intensity,float duration){
  static int last=0;
  timer.Update(EngineGlobals::fixed_update_interval);
  isShaking=true;
  if(timer.GetTime()>=duration*1000){
    isShaking=false;
   timer.Restart();
   return;
  }

  if(last==0){
  MoveRight(intensity);
  MoveUp(intensity);
  last=1;
  }
  else if(last==1){
  MoveLeft(intensity);
  MoveDown(intensity);
  last=0;
}



}
float CameraSystem::GetPos_x(){return worldCamera_x;}

float CameraSystem::GetPos_y(){return worldCamera_y;}

int CameraSystem::GetCameraSpeed(){return cameraSpeed;}

void CameraSystem::SetCameraSpeed(int speed){cameraSpeed=speed;}

void CameraSystem::SetPos_x(float x){
  if( (x >= (worldCamera_x - 20)) && (x <= (worldCamera_x + 20)) )
    return;
  if(worldCamera_x!=0){
    if((x - worldCamera_x) > 0)
      MoveRight(x - worldCamera_x);
    if((x - worldCamera_x) < 0)
      MoveLeft((x - worldCamera_x)*-1);
  }
  else
    worldCamera_x = x;
}

void CameraSystem::SetPos_y(float y){
  if( (y >= (worldCamera_y - 5)) && (y<= (worldCamera_y + 5)) )
    return;

  if(worldCamera_y!=0){
    if((y - worldCamera_y) > 0)
      MoveDown(y - worldCamera_y);
    if((y - worldCamera_y) < 0)
      MoveUp((y - worldCamera_y)*-1);
  }
  else
    worldCamera_y = y;
}


void CameraSystem::Reset(){
  worldCamera_x=0;
  worldCamera_y=0;
}



void CameraSystem::ZoomIn(int zoomSpeed,GameObject * objectToFollow) {
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
      (*it)->SetSize(map->GetWidth()/64,map->GetHeight()/64);
      (*it)->GetPosition()->m_x = ((proportion_x/100) * (map->GetWidth() + zoomSpeed)) - worldCamera_x;
      (*it)->GetPosition()->m_y = ((proportion_y/100) * (map->GetHeight() + zoomSpeed)) - worldCamera_y;
    }

  }

  map->SetSize(map->GetWidth() + zoomSpeed ,map->GetHeight() + zoomSpeed);
  if(x_pos_before < objectToFollow->GetPosition()->m_x){
    MoveRight(objectToFollow->GetPosition()->m_x - x_pos_before);
  }
  else if(x_pos_before > objectToFollow->GetPosition()->m_x){
    MoveLeft(x_pos_before - objectToFollow->GetPosition()->m_x);
  }
  if(y_pos_before < objectToFollow->GetPosition()->m_y){
    MoveDown(objectToFollow->GetPosition()->m_y - y_pos_before);
  }
  else if(y_pos_before > objectToFollow->GetPosition()->m_y){
    MoveDown(y_pos_before - objectToFollow->GetPosition()->m_y);
  }
}

void CameraSystem::ZoomOut(int zoomSpeed,GameObject * objectToFollow) {
  auto map = SceneManager::GetInstance()->GetScene("Gameplay")->GetGameObject("Map");
  if(!map)
  return;
  x_pos_before = objectToFollow->GetPosition()->m_x;
  y_pos_before = objectToFollow->GetPosition()->m_y;
  auto m_gameObjects = SceneManager::GetInstance()->GetCurrentScene()->GetAllGameObjects();
  for(auto it = m_gameObjects.begin(); it!=m_gameObjects.end(); it++ ){
    if((*it)->GetName()!="Map"){
      proportion_x = 100*(((*it)->GetPosition()->m_x + worldCamera_x)/(map->GetWidth()));
      proportion_y = 100*(((*it)->GetPosition()->m_y + worldCamera_y   )/(map->GetHeight()));
      (*it)->SetSize(map->GetWidth()/64,map->GetHeight()/64);
      (*it)->GetPosition()->m_x = ((proportion_x/100) * (map->GetWidth() - zoomSpeed)) - worldCamera_x;
      (*it)->GetPosition()->m_y = ((proportion_y/100) * (map->GetHeight() - zoomSpeed)) - worldCamera_y;
    }

  }
  map->SetSize(map->GetWidth() - zoomSpeed ,map->GetHeight() - zoomSpeed);
  if(x_pos_before < objectToFollow->GetPosition()->m_x){
    MoveRight(objectToFollow->GetPosition()->m_x - x_pos_before);
  }
  else if(x_pos_before > objectToFollow->GetPosition()->m_x){
    MoveLeft(x_pos_before - objectToFollow->GetPosition()->m_x);
  }
  if(y_pos_before < objectToFollow->GetPosition()->m_y){
    MoveUp(objectToFollow->GetPosition()->m_y - y_pos_before);
  }
  else if(y_pos_before > objectToFollow->GetPosition()->m_y){
    MoveUp(y_pos_before - objectToFollow->GetPosition()->m_y);
  }
}

bool CameraSystem::IsShaking(){return isShaking;}

CameraSystem * CameraSystem::GetInstance(){
  if (!m_instance)
    m_instance = new CameraSystem();
  return m_instance;
}

