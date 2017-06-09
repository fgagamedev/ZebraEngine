#include "Customs/MapScript.h"

MapScript::MapScript(GameObject *owner) : Script(owner) {}

void MapScript::Start() {
  map = SceneManager::GetInstance()->GetScene("Gameplay")->GetGameObject("Map");

  mapPosition = map->GetPosition();
  this->mapSize_x = map->GetWidth();
  this->mapSize_y = map->GetHeight();
  this->proportion_x=0;
  this->proportion_y=0;

  CameraSystem::GetInstance()->SetPos_x(mapPosition->m_x*-1);
  CameraSystem::GetInstance()->SetPos_y(mapPosition->m_y*-1);
  CameraSystem::GetInstance()->SetCameraSpeed(17);

  this->mapSpeed=CameraSystem::GetInstance()->GetCameraSpeed();
  nakedMan = SceneManager::GetInstance()->GetScene("Gameplay")->GetGameObject("NakedMan");
  script = (NakedManScript *)nakedMan->GetComponent("NakedManScript");
  nakedManPosition = nakedMan->GetPosition();

}




void MapScript::ComponentUpdate() {}

void MapScript::FixedComponentUpdate() {

  if(InputSystem::GetInstance()->GetKeyPressed(INPUT_DOWN) &&  map->GetWidth()>=3072 &&  map->GetHeight()>=3072 ){
        CameraSystem::GetInstance()->ZoomOut(32,nakedMan);
    }

  if(InputSystem::GetInstance()->GetKeyPressed(INPUT_UP) &&  map->GetWidth()<=9216 &&  map->GetHeight()<=9216){
       CameraSystem::GetInstance()->ZoomIn(32,nakedMan);
    }

    if(InputSystem::GetInstance()->GetKeyPressed(INPUT_I))
        CameraSystem::GetInstance()->MoveUp(CameraSystem::GetInstance()->GetCameraSpeed());

    if(InputSystem::GetInstance()->GetKeyPressed(INPUT_J))
        CameraSystem::GetInstance()->MoveLeft(CameraSystem::GetInstance()->GetCameraSpeed());

    if(InputSystem::GetInstance()->GetKeyPressed(INPUT_K))
        CameraSystem::GetInstance()->MoveDown(CameraSystem::GetInstance()->GetCameraSpeed());

     if(InputSystem::GetInstance()->GetKeyPressed(INPUT_L))
        CameraSystem::GetInstance()->MoveRight(CameraSystem::GetInstance()->GetCameraSpeed());


  nakedManMovements = script->GetMovement();
  if (!nakedManMovements)
    return;

}
