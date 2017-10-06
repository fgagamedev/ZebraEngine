/*
    @file CameraSystem.cpp
    @brief Class that manages the game image,
    including the scenes the zoom and speed that the screen moves.
    @copyright LGPL. MIT License.
*/

#include "Engine/CameraSystem.hpp"

#include "Customs/MapScript.hpp"

CameraSystem *CameraSystem::m_instance = nullptr;

/*
    @brief Sets the camera's default speed.
*/
CameraSystem::CameraSystem() {
    this->m_cameraSpeed = 32;
}

/*
    @brief Guides the camera to accompany the character when moving up.
    @param[in] speed Stores the character's current speed.
    @param[in] scene Pointer that points to the current scene.
*/
void CameraSystem::MoveUp(int speed, Scene *scene) {

    // Check if is diferent of scene and return.
    if (!scene) {
        return;
    } // Check if is diferent of scene.

    // Get all scene game objects.
    m_gameObjects = scene->GetAllGameObjects();
    if (m_gameObjects.empty()) {
        return;
    }

    // Move all scene objects.
    for (auto it = m_gameObjects.begin(); it != m_gameObjects.end(); it++) {
        (*it)->SetPosition(Vector((*it)->GetPosition()->m_x, (*it)->GetPosition()->m_y + speed));
    } // Move scene.

    auto mapscript = (MapScript*)SceneManager::GetInstance()
                       ->GetScene("Gameplay")
                       ->GetGameObject("Map")
                       ->GetComponent("MapScript");

    // Checks if the mapscript variable was instantiated.
    if (mapscript) {

        // Updates the amount of walls to the left according to speed.
        for (int i = 0; i < mapscript->leftWallsAmount; i++) {
            mapscript->leftWalls[i].m_y = mapscript->leftWalls[i].m_y + speed;
        }// for -- update the amount left.

        // Updates the amount of walls to the right according to speed.
        for (int j = 0; j < mapscript->rightWallsAmount; j++) {
            mapscript->rightWalls[j].m_y = mapscript->rightWalls[j].m_y + speed;
        }// for -- update the amount right.

        // Updates the amount of walls to the up according to speed.
        for (int k = 0; k < mapscript->upWallsAmount; k++) {
            mapscript->upWalls[k].m_y = mapscript->upWalls[k].m_y + speed;
        }// for -- update the amount up.

        // Updates the amount of walls to the down according to speed.
        for (int l = 0; l < mapscript->downWallsAmount; l++) {
            mapscript->downWalls[l].m_y = mapscript->downWalls[l].m_y + speed;
        }// for -- update the amount down.
    }// if -- checks mapscript instantiated.

    // Set a new position.
    worldCameraY = worldCameraY - speed;

}

/*
    @brief Guides the camera to accompany the character when moving down.
    @param[in] speed Stores the character's current speed.
    @param[in] scene Pointer that points to the current scene.
*/
void CameraSystem::MoveDown(int speed, Scene *scene) {

    // Check if is diferent of scene and return.
    if (!scene) {
        return;
    }

    // Get the scene game objects.
    m_gameObjects = scene->GetAllGameObjects();

    if (m_gameObjects.empty()) {
        return;
    }

    // Move all scene objects.
    for (auto it = m_gameObjects.begin();it!=m_gameObjects.end();it++) {
        (*it)->SetPosition(Vector((*it)->GetPosition()->m_x ,(*it)->GetPosition()->m_y - speed));
    }

    auto mapscript = (MapScript*)SceneManager::GetInstance()
           ->GetScene("Gameplay")
           ->GetGameObject("Map")
           ->GetComponent("MapScript");
    // Checks if the mapscript variable was instantiated.
    if (mapscript) {

        // Updates the amount of walls to the left according to speed.
        for (int i = 0; i < mapscript->leftWallsAmount; i++) {
            mapscript->leftWalls[i].m_y = mapscript->leftWalls[i].m_y - speed;
        }// for -- update the amount left.

        // Updates the amount of walls to the right according to speed.
        for (int j = 0; j < mapscript->rightWallsAmount; j++) {
            mapscript->rightWalls[j].m_y = mapscript->rightWalls[j].m_y - speed;
        }// for -- update the amount right.

        // Updates the amount of walls to the up according to speed.
        for (int k = 0; k < mapscript->upWallsAmount; k++) {
            mapscript->upWalls[k].m_y = mapscript->upWalls[k].m_y - speed;
        }// for -- update the amount up.

        // Updates the amount of walls to the down according to speed.
        for (int l = 0; l < mapscript->downWallsAmount; l++) {
            mapscript->downWalls[l].m_y = mapscript->downWalls[l].m_y - speed;
        }// for -- update the amount down.
    }// if -- checks mapscript instantiated.


    // Move the camera.
    worldCameraY = worldCameraY + speed;

}

/*
    @brief Guides the camera to accompany the character when moving left.
    @param[in] speed Stores the character's current speed.
    @param[in] scene Pointer that points to the current scene.
*/
void CameraSystem::MoveLeft(int speed,Scene *scene) {

    // Check if is diferent of scene and return.
    if (!scene) {
        return;
    }

    // Get the scene game objects.
    m_gameObjects = scene->GetAllGameObjects();

    if (m_gameObjects.empty()) {
        return;
    }

    // Move all scene objects.
    for (auto it = m_gameObjects.begin();it != m_gameObjects.end(); it++) {
        (*it)->SetPosition(Vector((*it)->GetPosition()->m_x + speed ,(*it)->GetPosition()->m_y ));
    }

    auto mapscript = (MapScript*)SceneManager::GetInstance()
               ->GetScene("Gameplay")
               ->GetGameObject("Map")
               ->GetComponent("MapScript");
     // mapscript->target.x += speed;

    // Checks if the mapscript variable was instantiated.
    if (mapscript) {

        // Updates the amount of walls to the left according to speed.
        for (int i = 0; i < mapscript->leftWallsAmount; i++) {
            mapscript->leftWalls[i].m_x = mapscript->leftWalls[i].m_x + speed;
        }// for -- update the amount left.

        // Updates the amount of walls to the right according to speed.
        for (int j = 0; j < mapscript->rightWallsAmount; j++) {
            mapscript->rightWalls[j].m_x = mapscript->rightWalls[j].m_x + speed;
        }// for -- update the amount right.

        // Updates the amount of walls to the up according to speed.
        for (int k = 0; k < mapscript->upWallsAmount; k++) {
            mapscript->upWalls[k].m_x = mapscript->upWalls[k].m_x + speed;
        }// for -- update the amount up.

        // Updates the amount of walls to the down according to speed.
        for (int l = 0; l < mapscript->downWallsAmount; l++) {
            mapscript->downWalls[l].m_x = mapscript->downWalls[l].m_x + speed;
        }// for -- update the amount down.
    }// if -- checks mapscript instantiated.

    // Set new position camera.
    worldCameraX = worldCameraX - speed;

}

/*
    @brief Guides the camera to accompany the character when moving right.
    @param[in] speed Stores the character's current speed.
    @param[in] scene Pointer that points to the current scene.
*/
void CameraSystem::MoveRight(int speed, Scene *scene) {

    // Check if is diferent of scene and return.
    if(!scene) {
        return;
    }

    // Get the scene game objects.
    m_gameObjects = scene->GetAllGameObjects();

    if (m_gameObjects.empty()) {
        return;
    }

    // Move all scene objects.
    for (auto it = m_gameObjects.begin(); it!=m_gameObjects.end(); it++) {
        (*it)->SetPosition(Vector((*it)->GetPosition()->m_x - speed ,(*it)->GetPosition()->m_y));
    }

    auto mapscript = (MapScript*)SceneManager::GetInstance()
                                ->GetScene("Gameplay")
                                ->GetGameObject("Map")
                                ->GetComponent("MapScript");

    // Checks if the mapscript variable was instantiated.
    if (mapscript) {

        // Updates the amount of walls to the left according to speed.
        for (int i = 0; i < mapscript->leftWallsAmount; i++) {
            mapscript->leftWalls[i].m_x = mapscript->leftWalls[i].m_x - speed;
        }// for -- update the amount left.

        // Updates the amount of walls to the right according to speed.
        for (int j = 0; j < mapscript->rightWallsAmount; j++) {
            mapscript->rightWalls[j].m_x = mapscript->rightWalls[j].m_x - speed;
        }// for -- update the amount right.

        // Updates the amount of walls to the up according to speed.
        for (int k = 0; k < mapscript->upWallsAmount; k++) {
            mapscript->upWalls[k].m_x = mapscript->upWalls[k].m_x - speed;
        }// for -- update the amount up.

        // Updates the amount of walls to the down according to speed.
        for (int l = 0; l < mapscript->downWallsAmount; l++) {
            mapscript->downWalls[l].m_x -= speed;
        }// for -- update the amount down.
    }// if -- checks mapscript instantiated.

    // Moves the camera.
    worldCameraX = worldCameraX + speed;

}

/*
    @brief Sets a camera shake to find the boss.
    @param[in] intensity Stores the intensity of camera shake.
    @param[in] duration Vibration duration in minutes.
    @param[in] scene Pointer that points to the current scene.
*/
void CameraSystem::CameraShake(int intensity, float duration, Scene *scene) {

    // Check if is diferent of scene and return.
    if (!scene) {
        return;
    }


    static int lastShake = 0;
    m_timer.Update(EngineGlobals::fixed_update_interval);
    isShaking = true;

    // Sets the end of the shake.
    if (m_timer.GetTime() >= duration * 1000) {
        isShaking = false;
        m_timer.Restart();
        return;
    }

    // Start or stop the shake.
    if (lastShake == 0) {
        MoveRight(intensity, scene);
        MoveUp(intensity, scene);
        lastShake = 1;
    } else if(lastShake == 1) {
        MoveLeft(intensity, scene);
        MoveDown(intensity, scene);
        lastShake = 0;
    }
}

/*
    @brief Get a starting position in axis x on image.
    @return worldCameraX Position initial in axis x.
*/
float CameraSystem::GetPositionX() {
    return worldCameraX;
}

/*
    @brief Get a starting position in axis y on image.
    @return worldCameraY Position initial in axis y.
*/
float CameraSystem::GetPositionY() {
    return worldCameraY;
}

/*
    @brief Get a speed initial.
    @return m_cameraSpeed Speed initial.
*/
int CameraSystem::GetCameraSpeed() {
    return m_cameraSpeed;
}

/*
    @brief Set a speed initial.
    @param[in] speed Stores the character's current speed.
    @return m_cameraSpeed Speed initial.
*/
void CameraSystem::SetCameraSpeed(int speed) {
    m_cameraSpeed = speed;
}

/*
    @brief Set a starting position in axis x on image.
    @param[in] x Axis X of image.
*/
void CameraSystem::SetAndMovePos_x(float axisX) {
    worldCameraX = axisX;
}

/*
    @brief Set a starting position in axis x on image.
    @param[in] y Axis Y of image.
*/
void CameraSystem::SetAndMovePos_y(float axisY) {
    worldCameraY = axisY;
}

/*
    @brief Reset a starting positions.
*/
void CameraSystem::Reset() {
    worldCameraX = 0;
    worldCameraY = 0;
}

/*
    @brief Zooms to the screen.
    @param[in] zoomSpeed Helps keep up with camera speed.
    @param[in] objectToFollow Character of the game.
    @param[in] scene Pointer that points to the current scene.
*/
void CameraSystem::ZoomIn(int zoomSpeed, GameObject *objectToFollow, Scene *scene) {

    auto map = SceneManager::GetInstance()->GetScene("Gameplay")->
                                            GetGameObject("Map");

    if (!map) {
        return;
    }

    m_beforePositionX = objectToFollow->GetPosition()->m_x;
    m_beforePositionY = objectToFollow->GetPosition()->m_y;
    this->m_cameraSpeed = zoomSpeed;

    auto m_gameObjects = SceneManager::GetInstance()->GetCurrentScene()->
                                                      GetAllGameObjects();
    // Runs from start to finish of the game.
    for (auto it = m_gameObjects.begin(); it!=m_gameObjects.end(); it++) {

        // Checks and updates the zoom ratio.
        if ((*it)->GetName()!="Map") {
            m_proportionX = 100*(((*it)->GetPosition()->m_x + worldCameraX) /
                                                            (map->GetWidth()));
            m_proportionY = 100*(((*it)->GetPosition()->m_y + worldCameraY) /
                                                            (map->GetHeight()));
            // Updates the zoom ratio in the x (width) and y (height) axes.
            if ((*it)->GetZoomProportion()->m_x != 0, (*it)->GetZoomProportion()->m_y != 0) {
                (*it)->SetSize(map->GetWidth() / (*it)->GetZoomProportion()->m_x,
                                                  map->GetHeight()
                                                  / (*it)->GetZoomProportion()->m_y);
                (*it)->GetPosition()->m_x = ((m_proportionX/100) * (map->GetWidth() + zoomSpeed)) - worldCameraX;
                (*it)->GetPosition()->m_y = ((m_proportionY/100) * (map->GetHeight() + zoomSpeed)) - worldCameraY;
            }
        }
    } // for

    auto mapscript = (MapScript*)SceneManager::GetInstance()
                    ->GetScene("Gameplay")
                    ->GetGameObject("Map")
                    ->GetComponent("MapScript");
                    // mapscript->target.x-= speed;

    // Checks if the mapscript variable was instantiated.
    if (mapscript) {
        for (int i = 0; i < mapscript->leftWallsAmount; i++) {
            m_proportionX = 100 * ((mapscript->leftWalls[i].m_x + worldCameraX) / (map->GetWidth()));
            m_proportionY = 100 * ((mapscript->leftWalls[i].m_y + worldCameraY) / (map->GetHeight()));
        }
        // Updates and creates the map information and the proportions of the walls on the left.
        for (int i = 0; i < mapscript->leftWallsAmount; i++) {
            m_proportionX = 100 * ((mapscript->leftWalls[i].m_x + worldCameraX)
                            / (map->GetWidth()));
            m_proportionY = 100 * ((mapscript->leftWalls[i].m_y + worldCameraY)
                            / (map->GetHeight()));

            mapscript->leftWalls[i].m_w = map->GetWidth() / ((map->originalWidth
                                                              / mapscript->leftWallsOriginal[i].m_w));//SHould be original
            mapscript->leftWalls[i].m_h = map->GetHeight() / ((map->originalHeight
                                                              / mapscript->leftWallsOriginal[i].m_h));

            mapscript->leftWalls[i].m_x = ((m_proportionX/100)
                                            * (map->GetWidth() + zoomSpeed))
                                            - worldCameraX;
            mapscript->leftWalls[i].m_y = ((m_proportionY/100)
                                            * (map->GetHeight() + zoomSpeed))
                                            - worldCameraY;
        }

        // Updates and creates the map information and the proportions of the walls on the right.
        for (int j = 0; j < mapscript->rightWallsAmount; j++) {
            m_proportionX = 100 * ((mapscript->rightWalls[j].m_x + worldCameraX) / (map->GetWidth()));
            m_proportionY = 100 * ((mapscript->rightWalls[j].m_y + worldCameraY) / (map->GetHeight()));

            mapscript->rightWalls[j].m_w = map->GetWidth() / ((map->originalWidth
                                                              / mapscript->rightWallsOriginal[j].m_w));//SHould be original
            mapscript->rightWalls[j].m_h = map->GetHeight() / ((map->originalHeight
                                                                / mapscript->rightWallsOriginal[j].m_h));

            mapscript->rightWalls[j].m_x = ((m_proportionX / 100)
                                            * (map->GetWidth() + zoomSpeed))
                                            - worldCameraX;
            mapscript->rightWalls[j].m_y = ((m_proportionY / 100)
                                            * (map->GetHeight() + zoomSpeed))
                                            - worldCameraY;
        }

        // Updates and creates the map information and the proportions of the walls on the up.
        for (int k = 0; k < mapscript->upWallsAmount; k++) {
            m_proportionX = 100 * ((mapscript->upWalls[k].m_x + worldCameraX)
                            / (map->GetWidth()));
            m_proportionY = 100 * ((mapscript->upWalls[k].m_y + worldCameraY)
                            / (map->GetHeight()));

            mapscript->upWalls[k].m_w = map->GetWidth() / ((map->originalWidth
                                                            / mapscript->upWallsOriginal[k].m_w));//SHould be original
            mapscript->upWalls[k].m_h = map->GetHeight() / ((map->originalHeight
                                                            / mapscript->upWallsOriginal[k].m_h));

            mapscript->upWalls[k].m_x = ((m_proportionX/100)
                                        * (map->GetWidth() + zoomSpeed))
                                        - worldCameraX;
            mapscript->upWalls[k].m_y = ((m_proportionY/100)
                                        * (map->GetHeight() + zoomSpeed))
                                        - worldCameraY;
        }

        // Updates and creates the map information and the proportions of the walls on the down.
        for (int l = 0; l < mapscript->downWallsAmount; l++) {
            m_proportionX = 100 * ((mapscript->downWalls[l].m_x + worldCameraX) / (map->GetWidth()));
            m_proportionY = 100 * ((mapscript->downWalls[l].m_y + worldCameraY) / (map->GetHeight()));

            mapscript->downWalls[l].m_w = map->GetWidth() / ((map->originalWidth/mapscript->downWallsOriginal[l].m_w));//SHould be original
            mapscript->downWalls[l].m_h = map->GetHeight() / ((map->originalHeight/mapscript->downWallsOriginal[l].m_h));

            mapscript->downWalls[l].m_x = ((m_proportionX/100) * (map->GetWidth() + zoomSpeed)) - worldCameraX;
            mapscript->downWalls[l].m_y = ((m_proportionY/100) * (map->GetHeight() + zoomSpeed)) - worldCameraY;
        }

    }// if -- checks mapscript instantiated.

    map->SetSize(map->GetWidth() + zoomSpeed, map->GetHeight() + zoomSpeed);

    // Refreshes the position on the x (width) axis.
    if (m_beforePositionX < objectToFollow->GetPosition()->m_x) {
        MoveRight(objectToFollow->GetPosition()->m_x - m_beforePositionX,scene);
    } else if (m_beforePositionX > objectToFollow->GetPosition()->m_x) {
        MoveLeft(m_beforePositionX - objectToFollow->GetPosition()->m_x,scene);
    }

    // Refreshes the position on the y (height) axis.
    if (m_beforePositionY < objectToFollow->GetPosition()->m_y) {
        MoveDown(objectToFollow->GetPosition()->m_y - m_beforePositionY,scene);
    } else if (m_beforePositionY > objectToFollow->GetPosition()->m_y) {
        MoveDown(m_beforePositionY - objectToFollow->GetPosition()->m_y,scene);
    }

}

/*
    @brief Zooms out of the screen.
    @param[in] zoomSpeed Helps keep up with camera speed.
    @param[in] objectToFollow Character of the game.
    @param[in] scene Pointer that points to the current scene.
*/
void CameraSystem::ZoomOut(int zoomSpeed, GameObject *objectToFollow, Scene *scene){

    auto map = SceneManager::GetInstance()->GetScene("Gameplay")->
                                            GetGameObject("Map");
    if (!map) {
        return;
    }

    m_beforePositionX = objectToFollow->GetPosition()->m_x;
    m_beforePositionY = objectToFollow->GetPosition()->m_y;

    this->m_cameraSpeed = zoomSpeed;

    auto m_gameObjects = SceneManager::GetInstance()->GetCurrentScene()->GetAllGameObjects();

    // Runs from start to finish of the game.
    for (auto it = m_gameObjects.begin(); it!=m_gameObjects.end(); it++) {

        // Checks and updates the zoom ratio.
        if ((*it)->GetName()!="Map") {
            m_proportionX = 100*(((*it)->GetPosition()->m_x + worldCameraX)
                                  / (map->GetWidth()));
            m_proportionY = 100*(((*it)->GetPosition()->m_y + worldCameraY)
                                  / (map->GetHeight()));

            // Updates the zoom ratio in the x (width) and y (height) axes.
            if ((*it)->GetZoomProportion()->m_x!=0 && (*it)->GetZoomProportion()->m_y != 0) {
                (*it)->SetSize(map->GetWidth() / (*it)->GetZoomProportion()->m_x,
                map->GetHeight()/(*it)->GetZoomProportion()->m_y);

                (*it)->GetPosition()->m_x = ((m_proportionX / 100)
                                              * (map->GetWidth() - zoomSpeed))
                                            - worldCameraX;
                (*it)->GetPosition()->m_y = ((m_proportionY / 100)
                                              * (map->GetHeight() - zoomSpeed))
                                            - worldCameraY;
            }
        }
    }

    auto mapscript = (MapScript*)SceneManager::GetInstance()
                                               ->GetScene("Gameplay")
                                               ->GetGameObject("Map")
                                               ->GetComponent("MapScript");

    // Checks if the mapscript variable was instantiated.
    if (mapscript) {

        // Updates and creates the map information and the proportions of the walls on the left.
        for (int i = 0; i<mapscript->leftWallsAmount; i++) {
            m_proportionX = 100 * ((mapscript->leftWalls[i].m_x + worldCameraX) / (map->GetWidth()));
            m_proportionY = 100 * ((mapscript->leftWalls[i].m_y + worldCameraY) / (map->GetHeight()));

            mapscript->leftWalls[i].m_w = map->GetWidth()/((map->originalWidth/mapscript->leftWallsOriginal[i].m_w));//SHould be original
            mapscript->leftWalls[i].m_h = map->GetHeight()/((map->originalHeight/mapscript->leftWallsOriginal[i].m_h));

            mapscript->leftWalls[i].m_x = ((m_proportionX/100) * (map->GetWidth() - zoomSpeed)) - worldCameraX;
            mapscript->leftWalls[i].m_y = ((m_proportionY/100) * (map->GetHeight() - zoomSpeed)) - worldCameraY;
        }

        // Updates and creates the map information and the proportions of the walls on the right.
        for (int j = 0; j < mapscript->rightWallsAmount; j++) {
            m_proportionX = 100 * ((mapscript->rightWalls[j].m_x + worldCameraX) / (map->GetWidth()));
            m_proportionY = 100 * ((mapscript->rightWalls[j].m_y + worldCameraY) / (map->GetHeight()));

            mapscript->rightWalls[j].m_w = map->GetWidth()/((map->originalWidth/mapscript->rightWallsOriginal[j].m_w));//SHould be original
            mapscript->rightWalls[j].m_h = map->GetHeight()/((map->originalHeight/mapscript->rightWallsOriginal[j].m_h));

            mapscript->rightWalls[j].m_x = ((m_proportionX/100) * (map->GetWidth() - zoomSpeed)) - worldCameraX;
            mapscript->rightWalls[j].m_y = ((m_proportionY/100) * (map->GetHeight() - zoomSpeed)) - worldCameraY;
        }

        // Updates and creates the map information and the proportions of the walls on the up.
        for (int k = 0; k < mapscript->upWallsAmount; k++) {
            m_proportionX = 100 * ((mapscript->upWalls[k].m_x + worldCameraX) / (map->GetWidth()));
            m_proportionY = 100 * ((mapscript->upWalls[k].m_y + worldCameraY) / (map->GetHeight()));

            mapscript->upWalls[k].m_w = map->GetWidth()/((map->originalWidth/mapscript->upWallsOriginal[k].m_w));//SHould be original
            mapscript->upWalls[k].m_h = map->GetHeight()/((map->originalHeight/mapscript->upWallsOriginal[k].m_h));

            mapscript->upWalls[k].m_x = ((m_proportionX/100) * (map->GetWidth() - zoomSpeed)) - worldCameraX;
            mapscript->upWalls[k].m_y = ((m_proportionY/100) * (map->GetHeight() - zoomSpeed)) - worldCameraY;
        }

        // Updates and creates the map information and the proportions of the walls on the down.
        for (int l = 0; l < mapscript->downWallsAmount; l++) {
            m_proportionX = 100 * ((mapscript->downWalls[l].m_x + worldCameraX) / (map->GetWidth()));
            m_proportionY = 100 * ((mapscript->downWalls[l].m_y + worldCameraY) / (map->GetHeight()));

            mapscript->downWalls[l].m_w = map->GetWidth()/((map->originalWidth/mapscript->downWallsOriginal[l].m_w));//SHould be original
            mapscript->downWalls[l].m_h = map->GetHeight()/((map->originalHeight/mapscript->downWallsOriginal[l].m_h));

            mapscript->downWalls[l].m_x = ((m_proportionX/100) * (map->GetWidth() - zoomSpeed)) - worldCameraX;
            mapscript->downWalls[l].m_y = ((m_proportionY/100) * (map->GetHeight() - zoomSpeed)) - worldCameraY;
        }
    }

    map->SetSize(map->GetWidth() - zoomSpeed ,map->GetHeight() - zoomSpeed);

    // Refreshes the position on the x (width) axis.
    if (m_beforePositionX < objectToFollow->GetPosition()->m_x) {
        MoveRight(objectToFollow->GetPosition()->m_x - m_beforePositionX,scene);
    } else if (m_beforePositionX > objectToFollow->GetPosition()->m_x) {
        MoveLeft(m_beforePositionX - objectToFollow->GetPosition()->m_x,scene);
    }

    // Refreshes the position on the y (height) axis.
    if (m_beforePositionY < objectToFollow->GetPosition()->m_y) {
        MoveUp(objectToFollow->GetPosition()->m_y - m_beforePositionY,scene);
    } else if (m_beforePositionY > objectToFollow->GetPosition()->m_y) {
        MoveUp(m_beforePositionY - objectToFollow->GetPosition()->m_y,scene);
    }
}

/*
    @brief instance of the new class CameraSystem() if not exist.
    @return m_instance New class.
*/
CameraSystem *CameraSystem::GetInstance() {
    if (!m_instance) {
        m_instance = new CameraSystem();
    }
    return m_instance;
}
