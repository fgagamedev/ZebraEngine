#ifndef __MAP_SCRIPT__
#define __MAP_SCRIPT__

#include "Components/Script.h"
#include "Customs/NakedManScript.h"
#include "Engine/SceneManager.h"
#include "Globals/EngineGlobals.h"
#include "Engine/CameraSystem.h"

class MapScript : public Script {
public:
  MapScript(GameObject *owner);
  std::string GetComponentName() override { return "MapScript"; };
  void FixedComponentUpdate() override;
  void Start() override;

protected:
  void ComponentUpdate() override;

private:
  GameObject *nakedMan = nullptr;
  GameObject *map = nullptr;
  Vector *nakedManPosition = nullptr;
  Vector *mapPosition = nullptr;
  NakedManScript *script = nullptr;
  char nakedManMovements;
  int mapSize_x;
  int mapSize_y;
  int mapSpeed;
  float proportion_x;
  float proportion_y;

};

#endif