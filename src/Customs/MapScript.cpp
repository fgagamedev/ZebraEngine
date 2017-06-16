#include "Customs/MapScript.h"
#include <stdio.h>
MapScript::MapScript(GameObject *owner) : Script(owner) {}

void MapScript::Start() {

  map = SceneManager::GetInstance()->GetScene("Gameplay")->GetGameObject("Map");

  mapPosition = map->GetPosition();
  this->mapSize_x = map->GetWidth();
  this->mapSize_y = map->GetHeight();
  this->proportion_x=0;
  this->proportion_y=0;
//printf("x antes = %f",CameraSystem::GetInstance()->GetPos_x());
//printf("y antes = %f",CameraSystem::GetInstance()->GetPos_y());
    //Do not remove the following lines or the zoom will bug
  CameraSystem::GetInstance()->SetAndMovePos_x(mapPosition->m_x*-1);
  CameraSystem::GetInstance()->SetAndMovePos_y(mapPosition->m_y*-1);
  //

//printf("x depois = %f",CameraSystem::GetInstance()->GetPos_x());
//printf("y depois = %f",CameraSystem::GetInstance()->GetPos_y());
  this->mapSpeed=CameraSystem::GetInstance()->GetCameraSpeed();
  nakedMan = SceneManager::GetInstance()->GetScene("Gameplay")->GetGameObject("NakedMan");
  script = (NakedManScript *)nakedMan->GetComponent("NakedManScript");
  nakedManPosition = nakedMan->GetPosition();

}

void MapScript::ComponentUpdate() {}

void MapScript::FixedComponentUpdate() {


  if(InputSystem::GetInstance()->GetKeyPressed(INPUT_DOWN) &&  map->GetWidth()>=6144 &&  map->GetHeight()>=6144 ){
        CameraSystem::GetInstance()->ZoomOut(100,nakedMan,SceneManager::GetInstance()->GetCurrentScene());
    }

  if(InputSystem::GetInstance()->GetKeyPressed(INPUT_UP) &&  map->GetWidth()<=18432 &&  map->GetHeight()<=18432){
       CameraSystem::GetInstance()->ZoomIn(100,nakedMan,SceneManager::GetInstance()->GetCurrentScene());
    }

    if(InputSystem::GetInstance()->GetKeyPressed(INPUT_I))
        CameraSystem::GetInstance()->MoveUp(CameraSystem::GetInstance()->GetCameraSpeed(),SceneManager::GetInstance()->GetCurrentScene());

    if(InputSystem::GetInstance()->GetKeyPressed(INPUT_J))
        CameraSystem::GetInstance()->MoveLeft(CameraSystem::GetInstance()->GetCameraSpeed(),SceneManager::GetInstance()->GetCurrentScene());

    if(InputSystem::GetInstance()->GetKeyPressed(INPUT_K))
        CameraSystem::GetInstance()->MoveDown(CameraSystem::GetInstance()->GetCameraSpeed(),SceneManager::GetInstance()->GetCurrentScene());

     if(InputSystem::GetInstance()->GetKeyPressed(INPUT_L))
        CameraSystem::GetInstance()->MoveRight(CameraSystem::GetInstance()->GetCameraSpeed(),SceneManager::GetInstance()->GetCurrentScene());



}
