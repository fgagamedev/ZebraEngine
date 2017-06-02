#ifndef __MAP_SCRIPT__
#define __MAP_SCRIPT__

#include "Components/Script.h"
#include "Customs/NakedManScript.h"
#include "Engine/SceneManager.h"
#include "Globals/EngineGlobals.h"

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
  Vector *nakedManPosition = nullptr;
  NakedManScript *script = nullptr;
  char nakedManMovements;
};

#endif