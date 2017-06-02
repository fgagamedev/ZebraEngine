#ifndef __UI_BUTTON__
#define __UI_BUTTON__

#include <string>

#include "Components/Renderer.h"
#include "Engine/Component.h"
#include "Engine/SceneManager.h"

class UIButton : public Component {
public:
  // constructor and destructor
  UIButton(GameObject *owner);
  ~UIButton();
  // overrides
  std::string GetComponentName() override { return "UIButton"; };
  void Start() override;
  // uibutton methods
  bool IsClicked();
  bool IsOver();

private:
  Vector *m_position = nullptr;
};

#endif // __UI_BUTTON__
