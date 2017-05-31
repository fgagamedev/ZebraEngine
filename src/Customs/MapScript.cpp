#include "Customs/MapScript.h"

MapScript::MapScript(GameObject *owner) : Script(owner) {}

void MapScript::Start() {
  nakedMan = SceneManager::GetInstance()
                 ->GetScene("Gameplay")
                 ->GetGameObject("NakedMan");
  nakedManPosition = nakedMan->GetPosition();
  script = (NakedManScript *)nakedMan->GetComponent("NakedManScript");
}

void MapScript::ComponentUpdate() {}

void MapScript::FixedComponentUpdate() {
  nakedManMovements = script->GetMovement();
  if (!nakedManMovements)
    return;
  if (nakedManPosition->m_x + 64 >= EngineGlobals::screen_width / 2 + 100 &&
      (nakedManMovements & 0x01))
    GetOwner()->GetPosition()->m_x -= 7;
  if (nakedManPosition->m_x <= EngineGlobals::screen_width / 2 - 100 &&
      (nakedManMovements & 0x02))
    GetOwner()->GetPosition()->m_x += 7;
  if (nakedManPosition->m_y + 64 >= EngineGlobals::screen_height / 2 + 100 &&
      (nakedManMovements & 0x04))
    GetOwner()->GetPosition()->m_y -= 7;
  if (nakedManPosition->m_y <= EngineGlobals::screen_height / 2 - 100 &&
      (nakedManMovements & 0x08))
    GetOwner()->GetPosition()->m_y += 7;
}
