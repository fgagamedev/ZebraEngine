#include "Engine/CameraSystem.hpp"

#include "Customs/MapScript.hpp"

CameraSystem *CameraSystem::m_instance = nullptr;

CameraSystem::CameraSystem() {
    this->cameraSpeed = 32;
}

void CameraSystem::MoveUp(int speed, Scene *scene) {

    if (!scene) {
        return;
    }

    //Get all scene game objects
    m_gameObjects = scene->GetAllGameObjects();
    if (m_gameObjects.empty()) {
        return;
    }

    //Move all scene objects
    for (auto it = m_gameObjects.begin(); it != m_gameObjects.end(); it++) {

        (*it)->SetPosition(Vector((*it)->GetPosition()->m_x, (*it)->GetPosition()->m_y + speed));

        auto mapscript = (MapScript*)SceneManager::GetInstance()
           ->GetScene("Gameplay")
           ->GetGameObject("Map")
           ->GetComponent("MapScript");

        if (mapscript) {

            for (int i = 0; i < mapscript->leftWallsAmmount; i++) {
                mapscript->leftWalls[i].m_y = mapscript->leftWalls[i].m_y + speed;
            }

            for (int j = 0; j < mapscript->rightWallsAmmount; j++) {
                mapscript->rightWalls[j].m_y = mapscript->rightWalls[j].m_y + speed;
            }

            for (int k = 0; k < mapscript->upWallsAmmount; k++) {
                mapscript->upWalls[k].m_y = mapscript->upWalls[k].m_y + speed;
            }

            for (int l = 0; l < mapscript->downWallsAmmount; l++) {
                mapscript->downWalls[l].m_y = mapscript->downWalls[l].m_y + speed;
            }
        }
    }


    // mapscript->target.y += speed;

    // Set a new position
    worldCameraY = worldCameraY - speed;

}

void CameraSystem::MoveDown(int speed, Scene *scene) {

    if (!scene) {
        return;
    }

    m_gameObjects = scene->GetAllGameObjects();

    if (m_gameObjects.empty()) {
        return;
    }

    // Move all scene objects
    for (auto it = m_gameObjects.begin();it!=m_gameObjects.end();it++) {
    
        (*it)->SetPosition(Vector((*it)->GetPosition()->m_x ,(*it)->GetPosition()->m_y - speed));

        auto mapscript = (MapScript*)SceneManager::GetInstance()
               ->GetScene("Gameplay")
               ->GetGameObject("Map")
               ->GetComponent("MapScript");
                // mapscript->target.y-= speed;

        if (mapscript) {
            for (int i = 0; i < mapscript->leftWallsAmmount; i++) {
                mapscript->leftWalls[i].m_y = mapscript->leftWalls[i].m_y - speed;
            }

            for (int j = 0; j < mapscript->rightWallsAmmount; j++) {
                mapscript->rightWalls[j].m_y = mapscript->rightWalls[j].m_y - speed;
            }

            for (int k = 0; k < mapscript->upWallsAmmount; k++) {
                mapscript->upWalls[k].m_y = mapscript->upWalls[k].m_y - speed;
            }

            for (int l = 0; l < mapscript->downWallsAmmount;l ++) {
                mapscript->downWalls[l].m_y = mapscript->downWalls[l].m_y - speed;
            }
        }
    }


    //Move the camera
    worldCameraY = worldCameraY + speed;

}

void CameraSystem::MoveLeft(int speed,Scene *scene) {

    if (!scene) {
        return;
    }

    m_gameObjects = scene->GetAllGameObjects();

    if (m_gameObjects.empty()) {
        return;
    }

    //Move all scene objects
    for (auto it = m_gameObjects.begin();it != m_gameObjects.end(); it++) {
    
        (*it)->SetPosition(Vector((*it)->GetPosition()->m_x + speed ,(*it)->GetPosition()->m_y ));
        auto mapscript = (MapScript*)SceneManager::GetInstance()
                   ->GetScene("Gameplay")
                   ->GetGameObject("Map")
                   ->GetComponent("MapScript");
         // mapscript->target.x += speed;

        if (mapscript) {
            for (int i = 0; i < mapscript->leftWallsAmmount; i++) {
                mapscript->leftWalls[i].m_x = mapscript->leftWalls[i].m_x + speed;
            }

            for (int j = 0; j < mapscript->rightWallsAmmount; j++) {
                mapscript->rightWalls[j].m_x = mapscript->rightWalls[j].m_x + speed;
            }

            for (int k = 0; k < mapscript->upWallsAmmount; k++) {
                mapscript->upWalls[k].m_x = mapscript->upWalls[k].m_x + speed;
            }

            for (int l = 0; l < mapscript->downWallsAmmount; l++) {
                mapscript->downWalls[l].m_x = mapscript->downWalls[l].m_x + speed;
            }
        }
    }

    //Set new position
    worldCameraX = worldCameraX - speed;

}

void CameraSystem::MoveRight(int speed, Scene *scene) {

    if(!scene) {
        return;
    }

    m_gameObjects = scene->GetAllGameObjects();

    if(m_gameObjects.empty()) {
        return;
    }

    //Move all scene objects
    for(auto it = m_gameObjects.begin();it!=m_gameObjects.end();it++){
        
        (*it)->SetPosition(Vector((*it)->GetPosition()->m_x - speed ,(*it)->GetPosition()->m_y));

        auto mapscript = (MapScript*)SceneManager::GetInstance()
                           ->GetScene("Gameplay")
                           ->GetGameObject("Map")
                           ->GetComponent("MapScript");
                            // mapscript->target.x-= speed;

        if(mapscript){
            for(int i = 0; i < mapscript->leftWallsAmmount; i++) {
                mapscript->leftWalls[i].m_x = mapscript->leftWalls[i].m_x - speed;
            }

            for(int j = 0; j < mapscript->rightWallsAmmount; j++) {
                mapscript->rightWalls[j].m_x = mapscript->rightWalls[j].m_x - speed;
            }

            for(int k = 0; k < mapscript->upWallsAmmount;k++ ) {
                mapscript->upWalls[k].m_x = mapscript->upWalls[k].m_x - speed;
            }

            for(int l = 0; l < mapscript->downWallsAmmount;l ++) {
                mapscript->downWalls[l].m_x = mapscript->downWalls[l].m_x - speed;
            }
        }
    }

    //Move the camera
    worldCameraX = worldCameraX + speed;

}

void CameraSystem::CameraShake(int intensity, float duration, Scene *scene) {

    if(!scene){
        return;
    }

    static int last = 0;
    timer.Update(EngineGlobals::fixed_update_interval);
    isShaking = true;

    if(timer.GetTime() >= duration * 1000) {
        isShaking = false;
        timer.Restart();
        return;
    }

    if(last == 0){
        MoveRight(intensity, scene);
        MoveUp(intensity, scene);
        last = 1;
    }else if(last == 1){
        MoveLeft(intensity, scene);
        MoveDown(intensity, scene);
        last = 0;
    }
}

float CameraSystem::GetPositionX() {
    return worldCameraX;

}

float CameraSystem::GetPositionY() {
    return worldCameraY;
}

int CameraSystem::GetCameraSpeed() {
    return cameraSpeed;
}

void CameraSystem::SetCameraSpeed(int speed) {
    cameraSpeed = speed;
}

void CameraSystem::SetAndMovePos_x(float x) {
    worldCameraX = x;
}

void CameraSystem::SetAndMovePos_y(float y) {
    worldCameraY = y;
}

void CameraSystem::Reset() {
    worldCameraX = 0;
    worldCameraY = 0;
}

void CameraSystem::ZoomIn(int zoomSpeed, GameObject *objectToFollow, Scene *scene) {

    auto map = SceneManager::GetInstance()->GetScene("Gameplay")->GetGameObject("Map");

    if (!map) {
        return;
    }

    beforePositionX = objectToFollow->GetPosition()->m_x;
    beforePositionY = objectToFollow->GetPosition()->m_y;
    this->cameraSpeed = zoomSpeed;

    auto m_gameObjects = SceneManager::GetInstance()->GetCurrentScene()->GetAllGameObjects();

    for (auto it = m_gameObjects.begin(); it!=m_gameObjects.end(); it++ ) {
        if ((*it)->GetName()!="Map") {
            proportionX = 100*(((*it)->GetPosition()->m_x + worldCameraX) / (map->GetWidth()));
            proportionY = 100*(((*it)->GetPosition()->m_y + worldCameraY) / (map->GetHeight()));
            //if getzoomProportion==(0,0) the object wont be affected by the zoom

            if((*it)->GetZoomProportion()->m_x != 0, (*it)->GetZoomProportion()->m_y != 0) {
                (*it)->SetSize(map->GetWidth() / (*it)->GetZoomProportion()->m_x, map->GetHeight() / (*it)->GetZoomProportion()->m_y);
                (*it)->GetPosition()->m_x = ((proportionX/100) * (map->GetWidth() + zoomSpeed)) - worldCameraX;
                (*it)->GetPosition()->m_y = ((proportionY/100) * (map->GetHeight() + zoomSpeed)) - worldCameraY;
            }
        }
    }

    auto mapscript = (MapScript*)SceneManager::GetInstance()
                    ->GetScene("Gameplay")
                    ->GetGameObject("Map")
                    ->GetComponent("MapScript");
                    // mapscript->target.x-= speed;

    if(mapscript) {
        for(int i = 0; i < mapscript->leftWallsAmmount; i++) {
            proportionX = 100 * ((mapscript->leftWalls[i].m_x + worldCameraX) / (map->GetWidth()));
            proportionY = 100 * ((mapscript->leftWalls[i].m_y + worldCameraY) / (map->GetHeight()));

            mapscript->leftWalls[i].m_w = map->GetWidth()/((map->originalWidth/mapscript->leftWallsOriginal[i].m_w));//SHould be original
            mapscript->leftWalls[i].m_h = map->GetHeight()/((map->originalHeight/mapscript->leftWallsOriginal[i].m_h));

            mapscript->leftWalls[i].m_x = ((proportionX/100) * (map->GetWidth() + zoomSpeed)) - worldCameraX;
            mapscript->leftWalls[i].m_y = ((proportionY/100) * (map->GetHeight() + zoomSpeed)) - worldCameraY;
        }

        for(int j = 0; j < mapscript->rightWallsAmmount; j++){
            proportionX = 100 * ((mapscript->rightWalls[j].m_x + worldCameraX) / (map->GetWidth()));
            proportionY = 100 * ((mapscript->rightWalls[j].m_y + worldCameraY) / (map->GetHeight()));

            mapscript->rightWalls[j].m_w = map->GetWidth() / ((map->originalWidth/mapscript->rightWallsOriginal[j].m_w));//SHould be original
            mapscript->rightWalls[j].m_h = map->GetHeight() / ((map->originalHeight/mapscript->rightWallsOriginal[j].m_h));

            mapscript->rightWalls[j].m_x = ((proportionX/100) * (map->GetWidth() + zoomSpeed)) - worldCameraX;
            mapscript->rightWalls[j].m_y = ((proportionY/100) * (map->GetHeight() + zoomSpeed)) - worldCameraY;
        }

        for(int k = 0; k < mapscript->upWallsAmmount; k++){
            proportionX = 100 * ((mapscript->upWalls[k].m_x + worldCameraX) / (map->GetWidth()));
            proportionY = 100 * ((mapscript->upWalls[k].m_y + worldCameraY) / (map->GetHeight()));

            mapscript->upWalls[k].m_w = map->GetWidth() / ((map->originalWidth/mapscript->upWallsOriginal[k].m_w));//SHould be original
            mapscript->upWalls[k].m_h = map->GetHeight() / ((map->originalHeight/mapscript->upWallsOriginal[k].m_h));

            mapscript->upWalls[k].m_x = ((proportionX/100) * (map->GetWidth() + zoomSpeed)) - worldCameraX;
            mapscript->upWalls[k].m_y = ((proportionY/100) * (map->GetHeight() + zoomSpeed)) - worldCameraY;
        }

        for(int l = 0; l < mapscript->downWallsAmmount; l++){
            proportionX = 100 * ((mapscript->downWalls[l].m_x + worldCameraX) / (map->GetWidth()));
            proportionY = 100 * ((mapscript->downWalls[l].m_y + worldCameraY) / (map->GetHeight()));

            mapscript->downWalls[l].m_w = map->GetWidth() / ((map->originalWidth/mapscript->downWallsOriginal[l].m_w));//SHould be original
            mapscript->downWalls[l].m_h = map->GetHeight() / ((map->originalHeight/mapscript->downWallsOriginal[l].m_h));

            mapscript->downWalls[l].m_x = ((proportionX/100) * (map->GetWidth() + zoomSpeed)) - worldCameraX;
            mapscript->downWalls[l].m_y = ((proportionY/100) * (map->GetHeight() + zoomSpeed)) - worldCameraY;
        }

    }

    map->SetSize(map->GetWidth() + zoomSpeed, map->GetHeight() + zoomSpeed);

    if(beforePositionX < objectToFollow->GetPosition()->m_x){
        MoveRight(objectToFollow->GetPosition()->m_x - beforePositionX,scene);
    }else if(beforePositionX > objectToFollow->GetPosition()->m_x){
        MoveLeft(beforePositionX - objectToFollow->GetPosition()->m_x,scene);
    }

    if(beforePositionY < objectToFollow->GetPosition()->m_y){
        MoveDown(objectToFollow->GetPosition()->m_y - beforePositionY,scene);
    }else if(beforePositionY > objectToFollow->GetPosition()->m_y){
        MoveDown(beforePositionY - objectToFollow->GetPosition()->m_y,scene);
    }

}

void CameraSystem::ZoomOut(int zoomSpeed, GameObject *objectToFollow, Scene *scene){
  
    auto map = SceneManager::GetInstance()->GetScene("Gameplay")->GetGameObject("Map");
    if(!map){
        return;
    }

    beforePositionX = objectToFollow->GetPosition()->m_x;
    beforePositionY = objectToFollow->GetPosition()->m_y;
    
    this->cameraSpeed = zoomSpeed;

    auto m_gameObjects = SceneManager::GetInstance()->GetCurrentScene()->GetAllGameObjects();

    for(auto it = m_gameObjects.begin(); it!=m_gameObjects.end(); it++){
        if((*it)->GetName()!="Map"){
            proportionX = 100*(((*it)->GetPosition()->m_x + worldCameraX)/(map->GetWidth()));
            proportionY = 100*(((*it)->GetPosition()->m_y + worldCameraY)/(map->GetHeight()));

            if((*it)->GetZoomProportion()->m_x!=0 && (*it)->GetZoomProportion()->m_y!=0){
                (*it)->SetSize(map->GetWidth()/(*it)->GetZoomProportion()->m_x,map->GetHeight()/(*it)->GetZoomProportion()->m_y);
                (*it)->GetPosition()->m_x = ((proportionX/100) * (map->GetWidth() - zoomSpeed)) - worldCameraX;
                (*it)->GetPosition()->m_y = ((proportionY/100) * (map->GetHeight() - zoomSpeed)) - worldCameraY;
            }
        }

    }

    auto mapscript = (MapScript*)SceneManager::GetInstance()
             ->GetScene("Gameplay")
             ->GetGameObject("Map")
             ->GetComponent("MapScript");
              // mapscript->target.x-= speed;

    if(mapscript){
        for(int i = 0; i<mapscript->leftWallsAmmount; i++){
            proportionX = 100 * ((mapscript->leftWalls[i].m_x + worldCameraX) / (map->GetWidth()));
            proportionY = 100 * ((mapscript->leftWalls[i].m_y + worldCameraY) / (map->GetHeight()));

            mapscript->leftWalls[i].m_w = map->GetWidth()/((map->originalWidth/mapscript->leftWallsOriginal[i].m_w));//SHould be original
            mapscript->leftWalls[i].m_h = map->GetHeight()/((map->originalHeight/mapscript->leftWallsOriginal[i].m_h));

            mapscript->leftWalls[i].m_x = ((proportionX/100) * (map->GetWidth() - zoomSpeed)) - worldCameraX;
            mapscript->leftWalls[i].m_y = ((proportionY/100) * (map->GetHeight() - zoomSpeed)) - worldCameraY;
        }

        for(int j = 0; j < mapscript->rightWallsAmmount; j++){
            proportionX = 100 * ((mapscript->rightWalls[j].m_x + worldCameraX) / (map->GetWidth()));
            proportionY = 100 * ((mapscript->rightWalls[j].m_y + worldCameraY) / (map->GetHeight()));

            mapscript->rightWalls[j].m_w = map->GetWidth()/((map->originalWidth/mapscript->rightWallsOriginal[j].m_w));//SHould be original
            mapscript->rightWalls[j].m_h = map->GetHeight()/((map->originalHeight/mapscript->rightWallsOriginal[j].m_h));

            mapscript->rightWalls[j].m_x = ((proportionX/100) * (map->GetWidth() - zoomSpeed)) - worldCameraX;
            mapscript->rightWalls[j].m_y = ((proportionY/100) * (map->GetHeight() - zoomSpeed)) - worldCameraY;
        }

        for(int k = 0; k < mapscript->upWallsAmmount; k++){
            proportionX = 100 * ((mapscript->upWalls[k].m_x + worldCameraX) / (map->GetWidth()));
            proportionY = 100 * ((mapscript->upWalls[k].m_y + worldCameraY) / (map->GetHeight()));

            mapscript->upWalls[k].m_w = map->GetWidth()/((map->originalWidth/mapscript->upWallsOriginal[k].m_w));//SHould be original
            mapscript->upWalls[k].m_h = map->GetHeight()/((map->originalHeight/mapscript->upWallsOriginal[k].m_h));

            mapscript->upWalls[k].m_x = ((proportionX/100) * (map->GetWidth() - zoomSpeed)) - worldCameraX;
            mapscript->upWalls[k].m_y = ((proportionY/100) * (map->GetHeight() - zoomSpeed)) - worldCameraY;
        }

        for(int l = 0; l < mapscript->downWallsAmmount; l++){
            proportionX = 100 * ((mapscript->downWalls[l].m_x + worldCameraX) / (map->GetWidth()));
            proportionY = 100 * ((mapscript->downWalls[l].m_y + worldCameraY) / (map->GetHeight()));

            mapscript->downWalls[l].m_w = map->GetWidth()/((map->originalWidth/mapscript->downWallsOriginal[l].m_w));//SHould be original
            mapscript->downWalls[l].m_h = map->GetHeight()/((map->originalHeight/mapscript->downWallsOriginal[l].m_h));

            mapscript->downWalls[l].m_x = ((proportionX/100) * (map->GetWidth() - zoomSpeed)) - worldCameraX;
            mapscript->downWalls[l].m_y = ((proportionY/100) * (map->GetHeight() - zoomSpeed)) - worldCameraY;
        }

    }

    map->SetSize(map->GetWidth() - zoomSpeed ,map->GetHeight() - zoomSpeed);

    if(beforePositionX < objectToFollow->GetPosition()->m_x){
        MoveRight(objectToFollow->GetPosition()->m_x - beforePositionX,scene);
    }else if(beforePositionX > objectToFollow->GetPosition()->m_x){
        MoveLeft(beforePositionX - objectToFollow->GetPosition()->m_x,scene);
    }

    if(beforePositionY < objectToFollow->GetPosition()->m_y){
        MoveUp(objectToFollow->GetPosition()->m_y - beforePositionY,scene);
    }else if(beforePositionY > objectToFollow->GetPosition()->m_y){
        MoveUp(beforePositionY - objectToFollow->GetPosition()->m_y,scene);
    }
}

CameraSystem *CameraSystem::GetInstance(){
    if (!m_instance){
        m_instance = new CameraSystem();
    }
    return m_instance;
}