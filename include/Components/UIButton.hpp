#ifndef __UI_BUTTON__
#define __UI_BUTTON__

#include "Engine/Component.hpp"
#include "Engine/SceneManager.hpp"

#include "Components/Renderer.hpp"

#include <string>

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
