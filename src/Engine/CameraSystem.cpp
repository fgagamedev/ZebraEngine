#include "Engine/CameraSystem.hpp"
#include "Customs/MapScript.hpp"

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

      auto mapscript = (MapScript*)SceneManager::GetInstance()
                   ->GetScene("Gameplay")
                   ->GetGameObject("Map")
                   ->GetComponent("MapScript");

       if(mapscript){

      for(int i=0;i<mapscript->leftWallsAmmount;i++)
       mapscript->leftWalls[i].m_y+=speed;

      for(int j=0;j<mapscript->rightWallsAmmount;j++)
       mapscript->rightWalls[j].m_y+=speed;

      for(int k=0;k<mapscript->upWallsAmmount;k++)
       mapscript->upWalls[k].m_y+=speed;

      for(int l=0;l<mapscript->downWallsAmmount;l++)
       mapscript->downWalls[l].m_y+=speed;

      }



  //    mapscript->target.y += speed;

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

          auto mapscript = (MapScript*)SceneManager::GetInstance()
                       ->GetScene("Gameplay")
                       ->GetGameObject("Map")
                       ->GetComponent("MapScript");
         // mapscript->target.y-= speed;

      if(mapscript){

      for(int i=0;i<mapscript->leftWallsAmmount;i++)
       mapscript->leftWalls[i].m_y-=speed;

      for(int j=0;j<mapscript->rightWallsAmmount;j++)
       mapscript->rightWalls[j].m_y-=speed;

      for(int k=0;k<mapscript->upWallsAmmount;k++)
       mapscript->upWalls[k].m_y-=speed;

      for(int l=0;l<mapscript->downWallsAmmount;l++)
       mapscript->downWalls[l].m_y-=speed;

      }


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
          auto mapscript = (MapScript*)SceneManager::GetInstance()
                       ->GetScene("Gameplay")
                       ->GetGameObject("Map")
                       ->GetComponent("MapScript");
         // mapscript->target.x += speed;

              if(mapscript){

                for(int i=0;i<mapscript->leftWallsAmmount;i++)
                 mapscript->leftWalls[i].m_x+=speed;

                for(int j=0;j<mapscript->rightWallsAmmount;j++)
                 mapscript->rightWalls[j].m_x+=speed;

                for(int k=0;k<mapscript->upWallsAmmount;k++)
                 mapscript->upWalls[k].m_x+=speed;

                for(int l=0;l<mapscript->downWallsAmmount;l++)
                 mapscript->downWalls[l].m_x+=speed;

                }

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
        auto mapscript = (MapScript*)SceneManager::GetInstance()
                           ->GetScene("Gameplay")
                           ->GetGameObject("Map")
                           ->GetComponent("MapScript");
             // mapscript->target.x-= speed;

             if(mapscript){

                 for(int i=0;i<mapscript->leftWallsAmmount;i++)
                  mapscript->leftWalls[i].m_x-=speed;

                 for(int j=0;j<mapscript->rightWallsAmmount;j++)
                  mapscript->rightWalls[j].m_x-=speed;

                 for(int k=0;k<mapscript->upWallsAmmount;k++)
                  mapscript->upWalls[k].m_x-=speed;

                 for(int l=0;l<mapscript->downWallsAmmount;l++)
                  mapscript->downWalls[l].m_x-=speed;

                 }

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

        auto mapscript = (MapScript*)SceneManager::GetInstance()
         ->GetScene("Gameplay")
         ->GetGameObject("Map")
         ->GetComponent("MapScript");
          // mapscript->target.x-= speed;

          if(mapscript){
          for(int i=0;i<mapscript->leftWallsAmmount;i++){
          proportion_x = 100*((mapscript->leftWalls[i].m_x + worldCamera_x)/(map->GetWidth()));
          proportion_y = 100*((mapscript->leftWalls[i].m_y + worldCamera_y   )/(map->GetHeight()));

          mapscript->leftWalls[i].m_w = map->GetWidth()/((map->originalWidth/mapscript->leftWallsOriginal[i].m_w));//SHould be original
          mapscript->leftWalls[i].m_h = map->GetHeight()/((map->originalHeight/mapscript->leftWallsOriginal[i].m_h));

          mapscript->leftWalls[i].m_x = ((proportion_x/100) * (map->GetWidth() + zoomSpeed)) - worldCamera_x;
          mapscript->leftWalls[i].m_y = ((proportion_y/100) * (map->GetHeight() + zoomSpeed)) - worldCamera_y;
          }
          for(int j=0;j<mapscript->rightWallsAmmount;j++){

          proportion_x = 100*((mapscript->rightWalls[j].m_x + worldCamera_x)/(map->GetWidth()));
          proportion_y = 100*((mapscript->rightWalls[j].m_y + worldCamera_y   )/(map->GetHeight()));

          mapscript->rightWalls[j].m_w = map->GetWidth()/((map->originalWidth/mapscript->rightWallsOriginal[j].m_w));//SHould be original
          mapscript->rightWalls[j].m_h = map->GetHeight()/((map->originalHeight/mapscript->rightWallsOriginal[j].m_h));

          mapscript->rightWalls[j].m_x = ((proportion_x/100) * (map->GetWidth() + zoomSpeed)) - worldCamera_x;
          mapscript->rightWalls[j].m_y = ((proportion_y/100) * (map->GetHeight() + zoomSpeed)) - worldCamera_y;

          }

          for(int k=0;k<mapscript->upWallsAmmount;k++){

            proportion_x = 100*((mapscript->upWalls[k].m_x + worldCamera_x)/(map->GetWidth()));
            proportion_y = 100*((mapscript->upWalls[k].m_y + worldCamera_y   )/(map->GetHeight()));

            mapscript->upWalls[k].m_w = map->GetWidth()/((map->originalWidth/mapscript->upWallsOriginal[k].m_w));//SHould be original
            mapscript->upWalls[k].m_h = map->GetHeight()/((map->originalHeight/mapscript->upWallsOriginal[k].m_h));

            mapscript->upWalls[k].m_x = ((proportion_x/100) * (map->GetWidth() + zoomSpeed)) - worldCamera_x;
            mapscript->upWalls[k].m_y = ((proportion_y/100) * (map->GetHeight() + zoomSpeed)) - worldCamera_y;
          }

          for(int l=0;l<mapscript->downWallsAmmount;l++){
            proportion_x = 100*((mapscript->downWalls[l].m_x + worldCamera_x)/(map->GetWidth()));
            proportion_y = 100*((mapscript->downWalls[l].m_y + worldCamera_y   )/(map->GetHeight()));

            mapscript->downWalls[l].m_w = map->GetWidth()/((map->originalWidth/mapscript->downWallsOriginal[l].m_w));//SHould be original
            mapscript->downWalls[l].m_h = map->GetHeight()/((map->originalHeight/mapscript->downWallsOriginal[l].m_h));

            mapscript->downWalls[l].m_x = ((proportion_x/100) * (map->GetWidth() + zoomSpeed)) - worldCamera_x;
            mapscript->downWalls[l].m_y = ((proportion_y/100) * (map->GetHeight() + zoomSpeed)) - worldCamera_y;
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

        if((*it)->GetZoomProportion()->m_x!=0 && (*it)->GetZoomProportion()->m_y!=0){
          (*it)->SetSize(map->GetWidth()/(*it)->GetZoomProportion()->m_x,map->GetHeight()/(*it)->GetZoomProportion()->m_y);
          (*it)->GetPosition()->m_x = ((proportion_x/100) * (map->GetWidth() - zoomSpeed)) - worldCamera_x;
          (*it)->GetPosition()->m_y = ((proportion_y/100) * (map->GetHeight() - zoomSpeed)) - worldCamera_y;
        }
      }

    }

     auto mapscript = (MapScript*)SceneManager::GetInstance()
             ->GetScene("Gameplay")
             ->GetGameObject("Map")
             ->GetComponent("MapScript");
              // mapscript->target.x-= speed;

              if(mapscript){
              for(int i=0;i<mapscript->leftWallsAmmount;i++){
                proportion_x = 100*((mapscript->leftWalls[i].m_x + worldCamera_x)/(map->GetWidth()));
                proportion_y = 100*((mapscript->leftWalls[i].m_y + worldCamera_y   )/(map->GetHeight()));

                mapscript->leftWalls[i].m_w = map->GetWidth()/((map->originalWidth/mapscript->leftWallsOriginal[i].m_w));//SHould be original
                mapscript->leftWalls[i].m_h = map->GetHeight()/((map->originalHeight/mapscript->leftWallsOriginal[i].m_h));

                mapscript->leftWalls[i].m_x = ((proportion_x/100) * (map->GetWidth() - zoomSpeed)) - worldCamera_x;
                mapscript->leftWalls[i].m_y = ((proportion_y/100) * (map->GetHeight() - zoomSpeed)) - worldCamera_y;
              }
              for(int j=0;j<mapscript->rightWallsAmmount;j++){
                proportion_x = 100*((mapscript->rightWalls[j].m_x + worldCamera_x)/(map->GetWidth()));
                proportion_y = 100*((mapscript->rightWalls[j].m_y + worldCamera_y   )/(map->GetHeight()));

                mapscript->rightWalls[j].m_w = map->GetWidth()/((map->originalWidth/mapscript->rightWallsOriginal[j].m_w));//SHould be original
                mapscript->rightWalls[j].m_h = map->GetHeight()/((map->originalHeight/mapscript->rightWallsOriginal[j].m_h));

                mapscript->rightWalls[j].m_x = ((proportion_x/100) * (map->GetWidth() - zoomSpeed)) - worldCamera_x;
                mapscript->rightWalls[j].m_y = ((proportion_y/100) * (map->GetHeight() - zoomSpeed)) - worldCamera_y;
              }

              for(int k=0;k<mapscript->upWallsAmmount;k++){
               proportion_x = 100*((mapscript->upWalls[k].m_x + worldCamera_x)/(map->GetWidth()));
               proportion_y = 100*((mapscript->upWalls[k].m_y + worldCamera_y   )/(map->GetHeight()));

               mapscript->upWalls[k].m_w = map->GetWidth()/((map->originalWidth/mapscript->upWallsOriginal[k].m_w));//SHould be original
               mapscript->upWalls[k].m_h = map->GetHeight()/((map->originalHeight/mapscript->upWallsOriginal[k].m_h));

               mapscript->upWalls[k].m_x = ((proportion_x/100) * (map->GetWidth() - zoomSpeed)) - worldCamera_x;
               mapscript->upWalls[k].m_y = ((proportion_y/100) * (map->GetHeight() - zoomSpeed)) - worldCamera_y;
              }

              for(int l=0;l<mapscript->downWallsAmmount;l++){

                proportion_x = 100*((mapscript->downWalls[l].m_x + worldCamera_x)/(map->GetWidth()));
                proportion_y = 100*((mapscript->downWalls[l].m_y + worldCamera_y   )/(map->GetHeight()));

                mapscript->downWalls[l].m_w = map->GetWidth()/((map->originalWidth/mapscript->downWallsOriginal[l].m_w));//SHould be original
                mapscript->downWalls[l].m_h = map->GetHeight()/((map->originalHeight/mapscript->downWallsOriginal[l].m_h));

                mapscript->downWalls[l].m_x = ((proportion_x/100) * (map->GetWidth() - zoomSpeed)) - worldCamera_x;
                mapscript->downWalls[l].m_y = ((proportion_y/100) * (map->GetHeight() - zoomSpeed)) - worldCamera_y;}

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

