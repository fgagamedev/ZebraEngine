#ifndef __GAME_CONTROLLER__
#define __GAME_CONTROLLER__

#include <vector>

#include "Engine/sdl2include.h"
#include "Globals/GCInputs.h"

class GameController {
public:
  GameController(SDL_GameController *gc);
  ~GameController();
  void Update();
  bool GetButtonDown(GameControllerButton button);
  bool GetButtonUp(GameControllerButton button);
  bool GetButtonPressed(GameControllerButton button);
  int GetAxis(GameControllerAxis axis);
  int GetButtonsQuantity() { return m_buttonsQnt; };

private:
  SDL_GameController *m_gameController = nullptr;

  int m_buttonsQnt = 0;
  int m_axesQnt = 0;

  std::vector<int> m_oldButtonsStates;
  std::vector<int> m_currentButtonsStates;
};

#endif // __GAME_CONTROLLER__