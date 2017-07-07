#ifndef __MAP_SCRIPT__
#define __MAP_SCRIPT__

#include "Components/Script.h"
#include "Customs/NakedManScript.h"
#include "Engine/SceneManager.h"
#include "Globals/EngineGlobals.h"
#include "Engine/CameraSystem.h"
#include "Customs/ForestActivatorScript.h"
#include "Customs/ForestActivatorScript2.h"
#include "Customs/ForestActivatorScript3.h"
#include "Customs/SnowActivatorScript.h"


class MapScript : public Script {
//Right[45]=button lowerleft,Right[46]=button central,Right[47]=button centralupleft,right[48]=blueboss ->> reserved for buttons
//right[49] = wall left down[48] = blue boss wall
public:
  MapScript(GameObject *owner);
  std::string GetComponentName() override { return "MapScript"; };
  void FixedComponentUpdate() override;
  void Start() override;
  int DetectWallCollision(GameObject* object);

  Vector leftWalls[100];
  Vector leftWallsOriginal[100];
  int leftWallsAmmount=0;

  Vector rightWalls[100];
  int rightWallsAmmount=0;
  Vector rightWallsOriginal[100];

  Vector upWalls[100];
  int upWallsAmmount=0;
  Vector upWallsOriginal[100];

  Vector downWalls[100];
  Vector downWallsOriginal[100];
  int downWallsAmmount=0;
    bool activated=true;

protected:
  void ComponentUpdate() override;

private:
  void RenderWallsRects();
  GameObject *nakedMan = nullptr;
  GameObject *map = nullptr;
  Vector *nakedManPosition = nullptr;
  Vector *mapPosition = nullptr;
  NakedManScript *script = nullptr;
  InputSystem *input = nullptr;
  char nakedManMovements;
  int mapSize_x;
  int mapSize_y;
  int mapSpeed;
  float proportion_x;
  float proportion_y;
  bool shake=false;
  void CreateWalls();

};

#endif