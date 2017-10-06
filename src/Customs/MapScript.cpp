#include "Customs/MapScript.hpp"

#include <stdio.h>
MapScript::MapScript(GameObject *owner) : Script(owner) {}

void MapScript::Start() {

    map = SceneManager::GetInstance()->GetScene("Gameplay")->GetGameObject("Map");

    mapPosition = map->GetPosition();
    this->mapSizeHorizontal = map->GetWidth();
    this->mapSizeVertical = map->GetHeight();
    this->proportionHorizontal=0;
    this->proportionVertical=0;

    // Do not remove the following lines or the zoom will bug
    CameraSystem::GetInstance()->SetAndMovePos_x(mapPosition->m_x*-1);
    CameraSystem::GetInstance()->SetAndMovePos_y(mapPosition->m_y*-1);
    this->mapSpeed=CameraSystem::GetInstance()->GetCameraSpeed();
    nakedMan = SceneManager::GetInstance()->GetScene("Gameplay")->GetGameObject("NakedMan");
    script = (NakedManScript *)nakedMan->GetComponent("NakedManScript");
    nakedManPosition = nakedMan->GetPosition();
    input = InputSystem::GetInstance();
    CreateWalls();

}

void MapScript::ComponentUpdate() {
    // If the player presses "P", the camera shakes.
    if (input->GetKeyPressed(INPUT_P)) {
        cameraShake = true;
    }

    // If the player presses "Z", the camera is locked.
    if (input->GetKeyPressed(INPUT_Z)) {
        CameraSystem::GetInstance()->Lock();
    }

    // Zooms the camera out when the corresponding keys are pressed.
    if (InputSystem::GetInstance()->GetKeyUp(INPUT_DOWN) && CameraSystem::GetInstance()->currentZoom > -50) {
        CameraSystem::GetInstance()->ZoomOut(GetOwner()->originalWidth/4 + 1,nakedMan,SceneManager::GetInstance()
                                                                                                ->GetCurrentScene());
        CameraSystem::GetInstance()->ZoomIn(1,nakedMan,SceneManager::GetInstance()->GetCurrentScene());
        CameraSystem::GetInstance()->currentZoom -=25;
    }

    // Zooms the camera in when the corresponding keys are pressed.
    if (InputSystem::GetInstance()->GetKeyUp(INPUT_UP) && CameraSystem::GetInstance()->currentZoom < 0) {
        CameraSystem::GetInstance()->ZoomIn(GetOwner()->originalWidth/4 +1,nakedMan,SceneManager::GetInstance()
                                                                                            ->GetCurrentScene());
        CameraSystem::GetInstance()->ZoomOut(1,nakedMan,SceneManager::GetInstance()->GetCurrentScene());
        CameraSystem::GetInstance()->currentZoom +=25;
    }
}

void MapScript::FixedComponentUpdate() {

    auto script = (NakedManScript*) SceneManager::GetInstance()
                                                ->GetCurrentScene()
                                                ->GetGameObject("NakedMan")
                                                ->GetComponent("NakedManScript");

    /*
    If the character's life is lower or equal to 0, the game ends with
    EndScene1.
    */
    if (script->life <= 0) {
        SceneManager::GetInstance()->SetCurrentScene("EndScene1");
    }

    auto scriptBossLife = (FirstBossLifeScript*) SceneManager::GetInstance()
                                                            ->GetCurrentScene()
                                                            ->GetGameObject("FirstBossLife")
                                                            ->GetComponent("FirstBossLifeScript");

    auto firstBossLifeRenderer = (RectangleRenderer*)SceneManager::GetInstance()
                                                                ->GetCurrentScene()
                                                                ->GetGameObject("FirstBossLife")
                                                                ->GetComponent("RectangleRenderer");

    int actualLife = firstBossLifeRenderer->GetWidth();
    // If boss's actual life is lower or equal to 0, ends game with EndScene2.
    if (actualLife<=0) {
        SceneManager::GetInstance()->SetCurrentScene("EndScene2");
    }

    /*
    If the camera is shaking, sets the shaking options and then stops
    camera's shaking.
    */
    if (cameraShake) {
        // CameraShake (intensity, duration in seconds)
        CameraSystem::GetInstance()->CameraShake(8,1,SceneManager::GetInstance()
                                                                ->GetCurrentScene());
        if (!CameraSystem::GetInstance()->IsShaking()) {
            cameraShake = false;
        }
    }

}

void MapScript::RenderWallsRects() {

    for (int i = 0; i < leftWallsAmount; i++) {
        SDL_Rect x = {
            leftWalls[i].m_x,
            leftWalls[i].m_y,
            leftWalls[i].m_w,
            leftWalls[i].m_h
        };
        GraphicsSystem::GetInstance()->DrawFillRectangle(&x, x.w,x.h, 255,0,0,100);
    }

    for (int j = 0; j < rightWallsAmount; j++) {
        SDL_Rect x = {
            rightWalls[j].m_x,
            rightWalls[j].m_y,
            rightWalls[j].m_w,
            rightWalls[j].m_h
        };
        GraphicsSystem::GetInstance()->DrawFillRectangle(&x, x.w,x.h, 255,0,0,100);
    }

    for (int k = 0; k < upWallsAmount; k++) {
        SDL_Rect x = {
            upWalls[k].m_x,
            upWalls[k].m_y,
            upWalls[k].m_w,
            upWalls[k].m_h
        };
        GraphicsSystem::GetInstance()->DrawFillRectangle(&x, x.w,x.h, 255,0,0,100);
    }

    for(int l = 0; l < downWallsAmount; l++) {
        SDL_Rect x = {
            downWalls[l].m_x,
            downWalls[l].m_y,
            downWalls[l].m_w,
            downWalls[l].m_h
        };
        GraphicsSystem::GetInstance()->DrawFillRectangle(&x, x.w,x.h, 255,0,0,100);
    }

}

void MapScript::CreateWalls() {
    // defines the walls' positions on the map (three lines defining each wall)
    downWalls[downWallsAmount] = {-3507,-2538,4364,75};
    downWallsOriginal[downWallsAmount] = {-3507,-2538,4364,75};
    downWallsAmount++;

    rightWalls[rightWallsAmount] = {826,-3798,67,945};
    rightWallsOriginal[rightWallsAmount] = {826,-3798,67,945};
    rightWallsAmount++;

    downWalls[downWallsAmount] = {857,-3831,1935,30};
    downWallsOriginal[downWallsAmount] = {857,-3831,1935,30};
    downWallsAmount++;


    leftWalls[leftWallsAmount] = {2801,-3800,30,945};
    leftWallsOriginal[leftWallsAmount] = {2801,-3800,30,945};
    leftWallsAmount++;

    upWalls[upWallsAmount] = {2465,-2855,360,30};
    upWallsOriginal[upWallsAmount] = {2465,-2855,360,30};
    upWallsAmount++;

    leftWalls[leftWallsAmount] = {2436,-2811,30,690};
    leftWallsOriginal[leftWallsAmount] = {2436,-2811,30,690};
    leftWallsAmount++;

    downWalls[downWallsAmount] = {2468,-2118,360,30};
    downWallsOriginal[downWallsAmount] = {2468,-2118,360,30};
    downWallsAmount++;

    leftWalls[leftWallsAmount] = {2791,-2086,30,285};
    leftWallsOriginal[leftWallsAmount] = {2791,-2086,30,285};
    leftWallsAmount++;

    upWalls[upWallsAmount] = {2656,-1801,135,30};
    upWallsOriginal[upWallsAmount] = {2656,-1801,135,30};
    upWallsAmount++;

    leftWalls[leftWallsAmount] = {2626,-1770,30,449};
    leftWallsOriginal[leftWallsAmount] = {2626,-1770,30,449};
    leftWallsAmount++;

    upWalls[upWallsAmount] = {2344,-1313,285,30};
    upWallsOriginal[upWallsAmount] = {2344,-1313,285,30};
    upWallsAmount++;

    rightWalls[rightWallsAmount] = {2314,-1572,30,259};
    rightWallsOriginal[rightWallsAmount] = {2314,-1572,30,259};
    rightWallsAmount++;

    upWalls[upWallsAmount] = {934,-1608, 1366,30};
    upWallsOriginal[upWallsAmount] = {934,-1608, 1366,30};
    upWallsAmount++;

    leftWalls[leftWallsAmount] = {897,-1574,30,224};
    leftWallsOriginal[leftWallsAmount] = {897,-1574,30,224};
    leftWallsAmount++;

    downWalls[downWallsAmount] = {933,-1349,1125,30};
    downWallsOriginal[downWallsAmount] = {933,-1349,1125,30};
    downWallsAmount++;

    leftWalls[leftWallsAmount] = {2058,-1318,30,375};
    leftWallsOriginal[leftWallsAmount] = {2058,-1318,30,375  };
    leftWallsAmount++;

    upWalls[upWallsAmount] = {933,-933,1125,30};
    upWallsOriginal[upWallsAmount] = {933,-933,1125,30};
    upWallsAmount++;

    leftWalls[leftWallsAmount] = {900,-903,30,540};
    leftWallsOriginal[leftWallsAmount] = {900,-903,30,540};
    leftWallsAmount++;

    upWalls[upWallsAmount] = {542,-360,360,30};
    upWallsOriginal[upWallsAmount] = {542,-360,360,30};
    upWallsAmount++;

    leftWalls[leftWallsAmount] = {514,-329,30,500};
    leftWallsOriginal[leftWallsAmount] = {514,-329,30,500 };
    leftWallsAmount++;


    rightWalls[rightWallsAmount] = {297,-519,30,644};
    rightWallsOriginal[rightWallsAmount] = {297,-519,30,644};
    rightWallsAmount++;

    upWalls[upWallsAmount] = {-63,-548,360,30};
    upWallsOriginal[upWallsAmount] = {-63,-548,360,30};
    upWallsAmount++;

    rightWalls[rightWallsAmount] = {-85,-715,30,165};
    rightWallsOriginal[rightWallsAmount] = {-85,-715,30,165};
    rightWallsAmount++;

    upWalls[upWallsAmount] = {-710,-738,624,30};
    upWallsOriginal[upWallsAmount] = {-710,-738,624,30};
    upWallsAmount++;

    rightWalls[rightWallsAmount] = {-752,-1480,30,733};
    rightWallsOriginal[rightWallsAmount] = {-752,-1480,30,733};
    rightWallsAmount++;

    upWalls[upWallsAmount] = {-1214,-1513,476,30};
    upWallsOriginal[upWallsAmount] = {-1214,-1513,476,30};
    upWallsAmount++;

    rightWalls[rightWallsAmount] = {-1239,-2244,30,735};
    rightWallsOriginal[rightWallsAmount] = {-1239,-2244,30,735};
    rightWallsAmount++;

    upWalls[upWallsAmount] = {-1557,-2278, 317,30};
    upWallsOriginal[upWallsAmount] = {-1557,-2278, 317,30};
    upWallsAmount++;

    leftWalls[leftWallsAmount] = {-1590,-2247,30,986};
    leftWallsOriginal[leftWallsAmount] = {-1590,-2247,30,986};
    leftWallsAmount++;

    upWalls[upWallsAmount] = {-2173,-1257,591 ,30};
    upWallsOriginal[upWallsAmount] = {-2173,-1257,591 ,30};
    upWallsAmount++;

    rightWalls[rightWallsAmount] = {-2205,-2461,33,735};
    rightWallsOriginal[rightWallsAmount] = {-1239,-2244,30,1200};
    rightWallsAmount++;

    leftWalls[leftWallsAmount] = {-445,-2250,30,326};
    leftWallsOriginal[leftWallsAmount] = {-445,-2250,30,326};
    leftWallsAmount++;

    upWalls[upWallsAmount] = {-416,-2280,706,30};
    upWallsOriginal[upWallsAmount] = {-416,-2280,706,30};
    upWallsAmount++;

    rightWalls[rightWallsAmount] = {290,-2250,30,326};
    rightWallsOriginal[rightWallsAmount] = {290,-2250,30,326};
    rightWallsAmount++;

    downWalls[downWallsAmount] = {-416,-1927,706,30};
    downWallsOriginal[downWallsAmount] = {-416,-1927,706,30};
    downWallsAmount++;

    upWalls[upWallsAmount] = {543,-2278,135 ,30};
    upWallsOriginal[upWallsAmount] = {543,-2278,135 ,30};
    upWallsAmount++;

    downWalls[downWallsAmount] = {543,-2116,135,30};
    downWallsOriginal[downWallsAmount] = {543,-2116,135,30};
    downWallsAmount++;

    leftWalls[leftWallsAmount] = {513,-2250,30,134};
    leftWallsOriginal[leftWallsAmount] = {513,-2250,30,135};
    leftWallsAmount++;

    rightWalls[rightWallsAmount] = {679,-2250,30,134};
    rightWallsOriginal[rightWallsAmount] = {679,-2251,30,135};
    rightWallsAmount++;

    leftWalls[leftWallsAmount] = {-1014,-2058,30,417};
    leftWallsOriginal[leftWallsAmount] = {-1014,-2058,30,417};
    leftWallsAmount++;

    rightWalls[rightWallsAmount] = {-669,-2058,30,417};
    rightWallsOriginal[rightWallsAmount] = {-669,-2058,30,417};
    rightWallsAmount++;

    upWalls[upWallsAmount] = {-983,-2084, 313,29};
    upWallsOriginal[upWallsAmount] = {-983,-2084, 313,29};
    upWallsAmount++;

    downWalls[downWallsAmount] = {-983,-1640,313,29};
    downWallsOriginal[downWallsAmount] = {-983,-1640,313,29};
    downWallsAmount++;

    upWalls[upWallsAmount] = {894,-2852, 556,30};
    upWallsOriginal[upWallsAmount] = {894,-2852, 556,30};
    upWallsAmount++;

    rightWalls[rightWallsAmount] = {1441,-2824,30,705};
    rightWallsOriginal[rightWallsAmount] = {1441,-2824,30,705};
    rightWallsAmount++;

    leftWalls[leftWallsAmount] = {862,-2824,30,705};
    leftWallsOriginal[leftWallsAmount] = {862,-2824,30,705};
    leftWallsAmount++;

    downWalls[downWallsAmount] = {894,-2117,556,30};
    downWallsOriginal[downWallsAmount] = {894,-2117,556,30};
    downWallsAmount++;

    leftWalls[leftWallsAmount] = {1003,-1317,30,255};
    leftWallsOriginal[leftWallsAmount] = {1003,-1317,30,255};
    leftWallsAmount++;

    rightWalls[rightWallsAmount] = {1350,-1317,30,255};
    rightWallsOriginal[rightWallsAmount] = {1350,-1317,30,255};
    rightWallsAmount++;

    downWalls[downWallsAmount] = {1034,-1058,315,29};
    downWallsOriginal[downWallsAmount] = {1034,-1058,315,29};
    downWallsAmount++;

    upWalls[upWallsAmount] = {-631,-1700, 931,30};
    upWallsOriginal[upWallsAmount] = {-631,-1700, 931,30};
    upWallsAmount++;

    leftWalls[leftWallsAmount] = {-631,-1610,30,70};
    leftWallsOriginal[leftWallsAmount] = {-631,-1610,30,70};
    leftWallsAmount++;

    downWalls[downWallsAmount] = {-600,-1540,164,30};
    downWallsOriginal[downWallsAmount] = {1034,-1058,315,29};
    downWallsAmount++;

    upWalls[upWallsAmount] = {-720,-1409, 285,30};
    upWallsOriginal[upWallsAmount] = {-720,-1409, 285,30};
    upWallsAmount++;

    leftWalls[leftWallsAmount] = {-442,-1507, 30,105};
    leftWallsOriginal[leftWallsAmount] = {-442,-1507, 30,105};
    leftWallsAmount++;

    downWalls[downWallsAmount] = {-720,-1251,780,30};
    downWallsOriginal[downWallsAmount] = {-720,-1251,780,30};
    downWallsAmount++;

    leftWalls[leftWallsAmount] = {-60,-1221, 30,255};
    leftWallsOriginal[leftWallsAmount] = {-60,-1221, 30,255};
    leftWallsAmount++;

    downWalls[downWallsAmount] = {-30,-966,330,30};
    downWallsOriginal[downWallsAmount] = {-30,-966,330,30};
    downWallsAmount++;

    rightWalls[rightWallsAmount] = {292,-1673,30,706};
    rightWallsOriginal[rightWallsAmount] = {292,-1673,30,706};
    rightWallsAmount++;

    upWalls[upWallsAmount] = {548,-1894, 705,30};
    upWallsOriginal[upWallsAmount] = {548,-1894, 705,30};
    upWallsAmount++;

    leftWalls[leftWallsAmount] = {518,-1863, 30,323};
    leftWallsOriginal[leftWallsAmount] = {518,-1863, 30,323};
    leftWallsAmount++;


    downWalls[downWallsAmount] = {548,-1539,120,29};
    downWallsOriginal[downWallsAmount] = {548,-1539,120,29};
    downWallsAmount++;

    rightWalls[rightWallsAmount] = {677,-1704,30,163};
    rightWallsOriginal[rightWallsAmount] = {677,-1704,30,163};
    rightWallsAmount++;

    downWalls[downWallsAmount] = {707,-1734,257,30};
    downWallsOriginal[downWallsAmount] = {707,-1734,257,30};
    downWallsAmount++;

    downWalls[downWallsAmount] = {982,-1832,268,30};
    downWallsOriginal[downWallsAmount] = {982,-1832,268,30};
    downWallsAmount++;

    rightWalls[rightWallsAmount] = {1254,-1865,26,34};
    rightWallsOriginal[rightWallsAmount] = {1254,-1865,26,34};
    rightWallsAmount++;

    rightWalls[rightWallsAmount] = {969,-1800,30,70};
    rightWallsOriginal[rightWallsAmount] = {969,-1800,30,70};
    rightWallsAmount++;

    rightWalls[rightWallsAmount] = {-3526,-1260,30,1930};
    rightWallsOriginal[rightWallsAmount] = {-3526,-1260,30,1930};
    rightWallsAmount++;

    upWalls[upWallsAmount] = {-3498,670, 942,30};
    upWallsOriginal[upWallsAmount] = {-3498,670, 942,30};
    upWallsAmount++;

    leftWalls[leftWallsAmount] = {-2556,52, 30,615};
    leftWallsOriginal[leftWallsAmount] = {-2556,52, 30,615};
    leftWallsAmount++;

    downWalls[downWallsAmount] = {-3497,-1287,954,30};
    downWallsOriginal[downWallsAmount] = {-3497,-1287,954,30};
    downWallsAmount++;

    leftWalls[leftWallsAmount] = {-2556,-1250, 30,672};
    leftWallsOriginal[leftWallsAmount] = {-2556,1250, 30,672};
    leftWallsAmount++;

    downWalls[downWallsAmount] = {-2522,-583,135,30};
    downWallsOriginal[downWallsAmount] = {-2522,-583,135,30};
    downWallsAmount++;

    rightWalls[rightWallsAmount] = {-2394,-748,30,162};
    rightWallsOriginal[rightWallsAmount] = {-2394,-748,30,162};
    rightWallsAmount++;

    downWalls[downWallsAmount] = {-2364,-778,203,30};
    downWallsOriginal[downWallsAmount] = {-2364,-778,203,30};
    downWallsAmount++;

    leftWalls[leftWallsAmount] = {-2161,-742, 30,163};
    leftWallsOriginal[leftWallsAmount] = {-2161,-742, 30,163};
    leftWallsAmount++;

    downWalls[downWallsAmount] = {-2139,-578,166,30};
    downWallsOriginal[downWallsAmount] = {-2364,-778,203,30};
    downWallsAmount++;

    leftWalls[leftWallsAmount] = {-1975,-547, 30,734};
    leftWallsOriginal[leftWallsAmount] = {-1975,-547, 30,734};
    leftWallsAmount++;

    upWalls[upWallsAmount] = {-2518,27, 122,30};
    upWallsOriginal[upWallsAmount] = {-2518,27, 122,30};
    upWallsAmount++;

    rightWalls[rightWallsAmount] = {-2397,57,30,2758};
    rightWallsOriginal[rightWallsAmount] = {-2397,57,30,2758};
    rightWallsAmount++;

    downWalls[downWallsAmount] = {-1950,186,164,29};
    downWallsOriginal[downWallsAmount] = {-1950,186,164,29};
    downWallsAmount++;

    leftWalls[leftWallsAmount] = {-1786,215, 30,195};
    leftWallsOriginal[leftWallsAmount] = {-1786,215, 30,195};
    leftWallsAmount++;

    upWalls[upWallsAmount] = {-1951,410, 165,30};
    upWallsOriginal[upWallsAmount] = {-1951,410, 165,30};
    upWallsAmount++;

    leftWalls[leftWallsAmount] = {-1981,441, 30,1951};
    leftWallsOriginal[leftWallsAmount] = {-1786,215, 30,1951};
    leftWallsAmount++;

    downWalls[downWallsAmount] = {-1952,2393,42,30};
    downWallsOriginal[downWallsAmount] = {-1952,2393,42,30};
    downWallsAmount++;

    upWalls[upWallsAmount] = {-2365,2813,1860 ,30};
    upWallsOriginal[upWallsAmount] = {-2365,2813,1860 ,30};
    upWallsAmount++;

    leftWalls[leftWallsAmount] = {-1405,2515, 30,300};
    leftWallsOriginal[leftWallsAmount] = {-1405,2515, 30,300};
    leftWallsAmount++;

    downWalls[downWallsAmount] = {-1570,2490,167,30};
    downWallsOriginal[downWallsAmount] = {-1570,2490,167,30};
    downWallsAmount++;

    leftWalls[leftWallsAmount] = {-1593,1975, 30,514};
    leftWallsOriginal[leftWallsAmount] = {-1593,1975, 30,514};
    leftWallsAmount++;

    upWalls[upWallsAmount] = {-1563,1945, 352,30};
    upWallsOriginal[upWallsAmount] = {-1563,1945, 352,30};
    upWallsAmount++;

    rightWalls[rightWallsAmount] = {-1910,2136,30,254};
    rightWallsOriginal[rightWallsAmount] = {-1910,2136,30,254};
    rightWallsAmount++;

    downWalls[downWallsAmount] = {-1890,2106,75,30};
    downWallsOriginal[downWallsAmount] = {-1890,2106,75,30};
    downWallsAmount++;

    rightWalls[rightWallsAmount] = {-1820,1843,30,262};
    rightWallsOriginal[rightWallsAmount] = {-1820,1843,30,262};
    rightWallsAmount++;

    downWalls[downWallsAmount] = {-1792,1815,360,30};
    downWallsOriginal[downWallsAmount] = {-1792,1815,360,30};
    downWallsAmount++;

    upWalls[upWallsAmount] = {-1792,1655,360 ,30};
    upWallsOriginal[upWallsAmount] = {-1792,1655,360 ,30};
    upWallsAmount++;

    rightWalls[rightWallsAmount] = {-1432,1686,30,128};
    rightWallsOriginal[rightWallsAmount] = {-1432,1686,30,128};
    rightWallsAmount++;

    rightWalls[rightWallsAmount] = {-1815,597,30,1005};
    rightWallsOriginal[rightWallsAmount] = {-1815,597,30,1005};
    rightWallsAmount++;

    downWalls[downWallsAmount] = {-1787,567,160,30};
    downWallsOriginal[downWallsAmount] = {-1787,567,160,30};
    downWallsAmount++;

    rightWalls[rightWallsAmount] = {-1627,27,30,539};
    rightWallsOriginal[rightWallsAmount] = {-1627,27,30,539};
    rightWallsAmount++;

    upWalls[upWallsAmount] = {-1791,28,195 ,30};
    upWallsOriginal[upWallsAmount] = {-1791,28,195 ,30};
    upWallsAmount++;

    rightWalls[rightWallsAmount] = {-1816,-752,30,779};
    rightWallsOriginal[rightWallsAmount] = {-1816,-752,30,779};
    rightWallsAmount++;

    downWalls[downWallsAmount] = {-1791,-776,770,30};
    downWallsOriginal[downWallsAmount] = {-1791,-776,770,30};
    downWallsAmount++;

    leftWalls[leftWallsAmount] = {-1018,-746, 30,675};
    leftWallsOriginal[leftWallsAmount] = {-1018,-746, 30,675};
    leftWallsAmount++;

    upWalls[upWallsAmount] = {-1081,-66,60 ,30};
    upWallsOriginal[upWallsAmount] = {-1081,-66,60 ,30};
    upWallsAmount++;

    leftWalls[leftWallsAmount] = {-1111,-35, 30,222};
    leftWallsOriginal[leftWallsAmount] = {-1111,-35, 30,222};
    leftWallsAmount++;

    downWalls[downWallsAmount] = {-1081,188,60,30};
    downWallsOriginal[downWallsAmount] = {-1081,188,60,30};
    downWallsAmount++;

    leftWalls[leftWallsAmount] = {-1021,218, 30,60};
    leftWallsOriginal[leftWallsAmount] = {-1021,218, 30,60};
    leftWallsAmount++;

    downWalls[downWallsAmount] = {-990,278,359,30};
    downWallsOriginal[downWallsAmount] = {-990,278,359,30};
    downWallsAmount++;

    leftWalls[leftWallsAmount] = {-1596,-330, 30,308};
    leftWallsOriginal[leftWallsAmount] = {-1596,-330, 30,308};
    leftWallsAmount++;

    rightWalls[rightWallsAmount] = {-1334,-330,30,322};
    rightWallsOriginal[rightWallsAmount] = {-1334,-330,30,322};
    rightWallsAmount++;

    upWalls[upWallsAmount] = {-1558,-360,225 ,31};
    upWallsOriginal[upWallsAmount] = {-1558,-360,225 ,31};
    upWallsAmount++;

    downWalls[downWallsAmount] = {-1558,-5,225,30};
    downWallsOriginal[downWallsAmount] = {-1558,-5,225,30};
    downWallsAmount++;

    leftWalls[leftWallsAmount] = {-1213,1397, 31 ,548};
    leftWallsOriginal[leftWallsAmount] = {-1213,1397, 31 ,548};
    leftWallsAmount++;

    upWalls[upWallsAmount] = {-1181,1374,710,30};
    upWallsOriginal[upWallsAmount] = {-1181,1374,710,30};
    upWallsAmount++;

    leftWalls[leftWallsAmount] = {-1016,533, 30 ,840};
    leftWallsOriginal[leftWallsAmount] = {-1016,533, 30 ,840};
    leftWallsAmount++;

    upWalls[upWallsAmount] = {-985,503,307,30};
    upWallsOriginal[upWallsAmount] = {-985,503,307,30};
    upWallsAmount++;

    upWalls[upWallsAmount] = {-1473,605,330,30};
    upWallsOriginal[upWallsAmount] = {-1473,605,330,30};
    upWallsAmount++;

    downWalls[downWallsAmount] = {-1474,1145,330,30};
    downWallsOriginal[downWallsAmount] = {-1474,1145,330,30};
    downWallsAmount++;

    leftWalls[leftWallsAmount] = {-1498,636, 30 ,506};
    leftWallsOriginal[leftWallsAmount] = {-1498,636, 30 ,506};
    leftWallsAmount++;

    rightWalls[rightWallsAmount] = {-1143,636,30,508};
    rightWallsOriginal[rightWallsAmount] = {-1143,636,30,508};
    rightWallsAmount++;

    rightWalls[rightWallsAmount] = {-1240,2525,30,283};
    rightWallsOriginal[rightWallsAmount] = {-1240,2525,30,283};
    rightWallsAmount++;

    downWalls[downWallsAmount] = {-1210,2494,165,30};
    downWallsOriginal[downWallsAmount] = {-1210,2494,165,30};
    downWallsAmount++;

    rightWalls[rightWallsAmount] = {-1044,2140,30,345};
    rightWallsOriginal[rightWallsAmount] = {-1044,2140,30,345};
    rightWallsAmount++;

    downWalls[downWallsAmount] = {-1014,2115,345,30};
    downWallsOriginal[downWallsAmount] = {-1014,2115,345,30};
    downWallsAmount++;

    downWalls[downWallsAmount] = {-634,-386,585,30};
    downWallsOriginal[downWallsAmount] = {-634,-386,585,30};
    downWallsAmount++;

    rightWalls[rightWallsAmount] = {-664,-356,30,90};
    rightWallsOriginal[rightWallsAmount] = {-664,-356,30,90};
    rightWallsAmount++;

    rightWalls[rightWallsAmount] = {-664,-164,30,90};
    rightWallsOriginal[rightWallsAmount] = {-664,-356,30,90};
    rightWallsAmount++;

    rightWalls[rightWallsAmount] = {-660,120,30,105};
    rightWallsOriginal[rightWallsAmount] = {-660,120,30,105};
    rightWallsAmount++;

    rightWalls[rightWallsAmount] = {-472,-230,30,30};
    rightWallsOriginal[rightWallsAmount] = {-472,-230,30,30};
    rightWallsAmount++;

    leftWalls[leftWallsAmount] = {-352,-230, 30 ,30};
    leftWallsOriginal[leftWallsAmount] = {-352,-230, 30 ,30};
    leftWallsAmount++;

    rightWalls[rightWallsAmount] = {-573,-39,30,124};
    rightWallsOriginal[rightWallsAmount] = {-573,-39,30,124};
    rightWallsAmount++;

    rightWalls[rightWallsAmount] = {-471,245,30,132};
    rightWallsOriginal[rightWallsAmount] = {-471,245,30,132  };
    rightWallsAmount++;

    rightWalls[rightWallsAmount] = {-665,533,30,68};
    rightWallsOriginal[rightWallsAmount] = {-665,533,30,68 };
    rightWallsAmount++;

    rightWalls[rightWallsAmount] = {-477,630,30,132};
    rightWallsOriginal[rightWallsAmount] = {-477,630,30,132};
    rightWallsAmount++;

    rightWalls[rightWallsAmount] = {-665,788,30,579};
    rightWallsOriginal[rightWallsAmount] = {-665,788,30,579};
    rightWallsAmount++;

    rightWalls[rightWallsAmount] = {-473,1402,29,509};
    rightWallsOriginal[rightWallsAmount] = {-473,1402,29,509};
    rightWallsAmount++;

    rightWalls[rightWallsAmount] = {-666,1938,30,164};
    rightWallsOriginal[rightWallsAmount] = {-666,1938,30,164};
    rightWallsAmount++;

    leftWalls[leftWallsAmount] = {-53,-354, 30 ,539};
    leftWallsOriginal[leftWallsAmount] = {-53,-354, 30 ,539};
    leftWallsAmount++;

    leftWalls[leftWallsAmount] = {-154,-44, 30 ,36};
    leftWallsOriginal[leftWallsAmount] = {-154,-44, 30 ,36};
    leftWallsAmount++;

    leftWalls[leftWallsAmount] = {40,634, 30 ,450};
    leftWallsOriginal[leftWallsAmount] = {40,634, 30 ,450};
    leftWallsAmount++;

    leftWalls[leftWallsAmount] = {-251,1113, 30 ,37};
    leftWallsOriginal[leftWallsAmount] = {-251,1113, 30 ,37};
    leftWallsAmount++;

    leftWalls[leftWallsAmount] = {-158,1178, 30 ,102};
    leftWallsOriginal[leftWallsAmount] = {-  158,1178, 30 ,102};
    leftWallsAmount++;

    leftWalls[leftWallsAmount] = {-343,1307, 30 ,930};
    leftWallsOriginal[leftWallsAmount] = {-343,1307, 30 ,930};
    leftWallsAmount++;

    leftWalls[leftWallsAmount] = {-730,2267, 30 ,549};
    leftWallsOriginal[leftWallsAmount] = {-730,2267, 30 ,549};
    leftWallsAmount++;

    upWalls[upWallsAmount] = {-632,-261,157,30};
    upWallsOriginal[upWallsAmount] = {-632,-261,157,30};
    upWallsAmount++;

    upWalls[upWallsAmount] = {-318,-261,270,30};
    upWallsOriginal[upWallsAmount] = {-318,-258,270,30};
    upWallsAmount++;

    upWalls[upWallsAmount] = {-628,-69,70,31};
    upWallsOriginal[upWallsAmount] = {-628,-69,70,31};
    upWallsAmount++;

    upWalls[upWallsAmount] = {-120,-71,30,30};
    upWallsOriginal[upWallsAmount] = {-120,-71,30,30};
    upWallsAmount++;

    downWalls[downWallsAmount] = {-632,-201,157,30};
    downWallsOriginal[downWallsAmount] = {-632,-201,157,30};
    downWallsAmount++;

    downWalls[downWallsAmount] = {-318,-198,270,30};
    downWallsOriginal[downWallsAmount] = {-318,-198,270,30};
    downWallsAmount++;

    downWalls[downWallsAmount] = {-628,93,59,29};
    downWallsOriginal[downWallsAmount] = {-628,93,59,31};
    downWallsAmount++;

    downWalls[downWallsAmount] = {-130,-5,30,30};
    downWallsOriginal[downWallsAmount] = {-130,-5,30,30};
    downWallsAmount++;

    upWalls[upWallsAmount] = {-629,215,144,30};
    upWallsOriginal[upWallsAmount] = {-629,215,144,30};
    upWallsAmount++;

    downWalls[downWallsAmount] = {-629,376,151,30};
    downWallsOriginal[downWallsAmount] = {-629,376,151,30};
    downWallsAmount++;

    leftWalls[leftWallsAmount] = {-636,309, 30 ,64};
    leftWallsOriginal[leftWallsAmount] = {-636,309, 30 ,64};
    leftWallsAmount++;

    upWalls[upWallsAmount] = {-634,600,150,30};
    upWallsOriginal[upWallsAmount] = {-634,600,150,30};
    upWallsAmount++;

    downWalls[downWallsAmount] = {-634,764,150,30};
    downWallsOriginal[downWallsAmount] = {-634,764,150,30};
    downWallsAmount++;

    upWalls[upWallsAmount] = {-217,1085,250,30};
    upWallsOriginal[upWallsAmount] = {-217,1085,250,30};
    upWallsAmount++;

    downWalls[downWallsAmount] = {-230,1142,45,30};
    downWallsOriginal[downWallsAmount] = {-230,1142,45,30};
    downWallsAmount++;

    upWalls[upWallsAmount] = {-315,1270,155,30};
    upWallsOriginal[upWallsAmount] = {-315,1270,155,30};
    upWallsAmount++;

    downWalls[downWallsAmount] = {-632,1914,150,30};
    downWallsOriginal[downWallsAmount] = {-632,1914,150,30};
    downWallsAmount++;

    upWalls[upWallsAmount] = {-695,2231,345,30};
    upWallsOriginal[upWallsAmount] = {-695,2231,345,30};
    upWallsAmount++;

    upWalls[upWallsAmount] = {-407,886,30,30};
    upWallsOriginal[upWallsAmount] = {-407,886,30,30};
    upWallsAmount++;

    downWalls[downWallsAmount] = {-407,950,30,30};
    downWallsOriginal[downWallsAmount] = {-407,950,30,30};
    downWallsAmount++;

    leftWalls[leftWallsAmount] = {-441,920, 30 ,30};
    leftWallsOriginal[leftWallsAmount] = {-441,920, 30 ,30};
    leftWallsAmount++;

    rightWalls[rightWallsAmount] = {-373,920,30,30};
    rightWallsOriginal[rightWallsAmount] = {-373,920,30,30};
    rightWallsAmount++;

    leftWalls[leftWallsAmount] = {-250,732, 30 ,225};
    leftWallsOriginal[leftWallsAmount] = {-250,732, 30 ,225};
    leftWallsAmount++;

    rightWalls[rightWallsAmount] = {-190,732,30,225};
    rightWallsOriginal[rightWallsAmount] = {-190,732,30,225};
    rightWallsAmount++;

    downWalls[downWallsAmount] = {-220,958,30,30};
    downWallsOriginal[downWallsAmount] = {-220,958,30,30};
    downWallsAmount++;

    upWalls[upWallsAmount] = {-220,702,30,30};
    upWallsOriginal[upWallsAmount] = {-220,702,30,30};
    upWallsAmount++;

    downWalls[downWallsAmount] = {-17,188,254,30};
    downWallsOriginal[downWallsAmount] = {-17,188,254,30};
    downWallsAmount++;

    upWalls[upWallsAmount] = {78,599,600,30};
    upWallsOriginal[upWallsAmount] = {-78,599,600,30};
    upWallsAmount++;

    leftWalls[leftWallsAmount] = {228,249, 30 ,135};
    leftWallsOriginal[leftWallsAmount] = {228,249, 30 ,135};
    leftWallsAmount++;

    rightWalls[rightWallsAmount] = {299,100,30,280};
    rightWallsOriginal[rightWallsAmount] = {299,100,30,280};
    rightWallsAmount++;

    downWalls[downWallsAmount] = {259,379,37 ,29};
    downWallsOriginal[downWallsAmount] = {259,379,37 ,29};
    downWallsAmount++;

    upWalls[upWallsAmount] = {263,502,30,30};
    upWallsOriginal[upWallsAmount] = {263,502,30,30};
    upWallsAmount++;

    leftWalls[leftWallsAmount] = {234,533, 30 ,98};
    leftWallsOriginal[leftWallsAmount] = {234,533, 30 ,98};
    leftWallsAmount++;

    rightWalls[rightWallsAmount] = {292,533,30,98};
    rightWallsOriginal[rightWallsAmount] = {292,533,30,98};
    rightWallsAmount++;

    leftWalls[leftWallsAmount] = {705,215, 30 ,375};
    leftWallsOriginal[leftWallsAmount] = {705,215, 30 ,375};
    leftWallsAmount++;

    downWalls[downWallsAmount] = {545,188,165 ,30};
    downWallsOriginal[downWallsAmount] = {545,188,165 ,30};
    downWallsAmount++;

    upWalls[upWallsAmount] = {-222,310,458,30};
    upWallsOriginal[upWallsAmount] = {-222,310,458,30};
    upWallsAmount++;

    downWalls[downWallsAmount] = {-222,383,458 ,30};
    downWallsOriginal[downWallsAmount] = {-222,383,458 ,30};
    downWallsAmount++;

    leftWalls[leftWallsAmount] = {-250,330, 30 ,48};
    leftWallsOriginal[leftWallsAmount] = {-250,330, 30 ,48};
    leftWallsAmount++;

    upWalls[upWallsAmount] = {330,120,57,30};
    upWallsOriginal[upWallsAmount] = {330,120,57,30  };
    upWallsAmount++;

    downWalls[downWallsAmount] = {330,182,57 ,30};
    downWallsOriginal[downWallsAmount] = {330,182,57 ,30};
    downWallsAmount++;

    rightWalls[rightWallsAmount] = {387,150,30,30};
    rightWallsOriginal[rightWallsAmount] = {387,150,30,30};
    rightWallsAmount++;

    //Buttons
    rightWalls[rightWallsAmount] = {-981,2518,45,40};
    rightWallsOriginal[rightWallsAmount] = {-981,2518,45,40};
    rightWallsAmount++;

    rightWalls[rightWallsAmount] = {774,-509,29,30};
    rightWallsOriginal[rightWallsAmount] = {774,-509,29,30};
    rightWallsAmount++;

    rightWalls[rightWallsAmount] = {-520,-1506,30,30};
    rightWallsOriginal[rightWallsAmount] = {-539,-1506,30,30};
    rightWallsAmount++;

    rightWalls[rightWallsAmount] = {1786,-3384,30,30};
    rightWallsOriginal[rightWallsAmount] = {1786,-3384,30,30};
    rightWallsAmount++;

    // defines stairs' positions & behavior
    rightWalls[rightWallsAmount] = {-2392,-543,30,554};
    rightWallsOriginal[rightWallsAmount] = {-2392,-543,30,554};
    rightWallsAmount++;

    downWalls[downWallsAmount] = {1472,-2711,1000,45};
    downWallsOriginal[downWallsAmount] = {1472,-2711,1000,45};
    downWallsAmount++;
}

int MapScript::DetectWallCollision(GameObject* object){
    /*
    determines the player's behavior when facing (or not) a wall, where:
    0 not colliding; 1 = left; 2 = right; 3 = up; 4 = down
    */
    for (int i = 0; i < leftWallsAmount; i++) {
        if (((leftWalls[i].m_x <= (object->GetPosition()->m_x + object->GetWidth())) &&
            ((leftWalls[i].m_x + leftWalls[i].m_w) >= object->GetPosition()->m_x)) &&
            ((leftWalls[i].m_y <=(object->GetPosition()->m_y + object->GetHeight())) &&
            ((leftWalls[i].m_y + leftWalls[i].m_h) >= object->GetPosition()->m_y))) {

            Vector playerprevious_vec;
            playerprevious_vec.m_x = leftWalls[i].m_x - 1 - object->GetWidth();
            playerprevious_vec.m_y = object->GetPosition()->m_y;
            object->SetPosition(playerprevious_vec);
        }
    }

    for(int j = 0; j < rightWallsAmount; j++) {
        if (((rightWalls[j].m_x <= (object->GetPosition()->m_x + object->GetWidth())) &&
            ((rightWalls[j].m_x + rightWalls[j].m_w) >= object->GetPosition()->m_x)) &&
            ((rightWalls[j].m_y <=(object->GetPosition()->m_y + object->GetHeight())) &&
            ((rightWalls[j].m_y + rightWalls[j].m_h) >= object->GetPosition()->m_y))) {

            if (j == 45) {
                auto script = (SnowActivatorScript*)SceneManager::GetInstance()
                                                                ->GetCurrentScene()
                                                                ->GetGameObject("SNOW ACTIVATOR")
                                                                ->GetComponent("SnowActivatorScript");
                script->Activate();
                return 0;
            }

            // central
            if (j == 46) {
                auto script = (ForestActivatorScript2*)SceneManager::GetInstance()
                                                                    ->GetCurrentScene()
                                                                    ->GetGameObject("FOREST ACTIVATOR2")
                                                                    ->GetComponent("ForestActivatorScript2");
                script->Activate();
                return 0;
            }

            // left
            if (j == 47) {
                auto script = (ForestActivatorScript3*)SceneManager::GetInstance()
                                                                    ->GetCurrentScene()
                                                                    ->GetGameObject("FOREST ACTIVATOR3")
                                                                    ->GetComponent("ForestActivatorScript3");
                script->Activate();
                return 0;
            }

            // blue
            if (j == 48) {
                auto script = (ForestActivatorScript*)SceneManager::GetInstance()
                                                                    ->GetCurrentScene()
                                                                    ->GetGameObject("FOREST ACTIVATOR")
                                                                    ->GetComponent("ForestActivatorScript");
                script->Activate();
                return 0;
            }

            Vector playerprevious_vec;
            playerprevious_vec.m_x = rightWalls[j].m_x + rightWalls[j].m_w + 1;
            playerprevious_vec.m_y = object->GetPosition()->m_y;
            object->SetPosition(playerprevious_vec);

        }
    }

    for (int k = 0; k < upWallsAmount; k++) {
        if (((upWalls[k].m_x <= (object->GetPosition()->m_x + object->GetWidth())) &&
            ((upWalls[k].m_x + upWalls[k].m_w) >= object->GetPosition()->m_x)) &&
            ((upWalls[k].m_y <= (object->GetPosition()->m_y + object->GetHeight())) &&
            ((upWalls[k].m_y + upWalls[k].m_h)>=object->GetPosition()->m_y))) {

            Vector playerprevious_vec;
            playerprevious_vec.m_x = object->GetPosition()->m_x;
            playerprevious_vec.m_y = upWalls[k].m_y - 1 - object->GetHeight();
            object->SetPosition(playerprevious_vec);
        }
    }


    for (int l = 0; l < downWallsAmount; l++) {
        if (((downWalls[l].m_x <= (object->GetPosition()->m_x + object->GetWidth())) &&
            ((downWalls[l].m_x + downWalls[l].m_w) >= object->GetPosition()->m_x)) &&
            ((downWalls[l].m_y <= (object->GetPosition()->m_y + object->GetHeight())) &&
            ((downWalls[l].m_y + downWalls[l].m_h) >= object->GetPosition()->m_y))) {

            Vector playerprevious_vec;
            playerprevious_vec.m_x = object->GetPosition()->m_x;
            playerprevious_vec.m_y = downWalls[l].m_y + downWalls[l].m_h + 1;
            object->SetPosition(playerprevious_vec);
        }
    }

    return 0;

}
