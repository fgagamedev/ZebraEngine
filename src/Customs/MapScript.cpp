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

    //Do not remove the following lines or the zoom will bug
  CameraSystem::GetInstance()->SetAndMovePos_x(mapPosition->m_x*-1);
  CameraSystem::GetInstance()->SetAndMovePos_y(mapPosition->m_y*-1);
  this->mapSpeed=CameraSystem::GetInstance()->GetCameraSpeed();
  nakedMan = SceneManager::GetInstance()->GetScene("Gameplay")->GetGameObject("NakedMan");
  script = (NakedManScript *)nakedMan->GetComponent("NakedManScript");
  nakedManPosition = nakedMan->GetPosition();
   input = InputSystem::GetInstance();

}

void MapScript::ComponentUpdate() {


  if (input->GetKeyPressed(INPUT_P))
    shake=true;

 if (input->GetKeyPressed(INPUT_Z))
    CameraSystem::GetInstance()->Lock();

 //printf("%f\n",CameraSystem::GetInstance()->currentZoom);


  if(InputSystem::GetInstance()->GetKeyUp(INPUT_DOWN) && CameraSystem::GetInstance()->currentZoom > -75){
        CameraSystem::GetInstance()->ZoomOut(GetOwner()->originalWidth/4 + 1,nakedMan,SceneManager::GetInstance()->GetCurrentScene());
         CameraSystem::GetInstance()->ZoomIn(1,nakedMan,SceneManager::GetInstance()->GetCurrentScene());
        CameraSystem::GetInstance()->currentZoom -=25;
    }

  if(InputSystem::GetInstance()->GetKeyUp(INPUT_UP) && CameraSystem::GetInstance()->currentZoom < +75){
       CameraSystem::GetInstance()->ZoomIn(GetOwner()->originalWidth/4 +1,nakedMan,SceneManager::GetInstance()->GetCurrentScene());
       CameraSystem::GetInstance()->ZoomOut(1,nakedMan,SceneManager::GetInstance()->GetCurrentScene());
       CameraSystem::GetInstance()->currentZoom +=25;
    }

}



void MapScript::FixedComponentUpdate() {


  if(shake){
    //CameraShake(intensity,duration in seconds)
    CameraSystem::GetInstance()->CameraShake(8,1,SceneManager::GetInstance()->GetCurrentScene());
    if(!CameraSystem::GetInstance()->IsShaking())
    shake=false;
  }

}
