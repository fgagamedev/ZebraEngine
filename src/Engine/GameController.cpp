#include "Engine/GameController.h"
#include "Log/log.h"

GameController::GameController(SDL_GameController *gc) {
  if (gc) {
    INFO("    " << SDL_GameControllerName(gc) << " opened");
    m_gameController = gc;
  } else {
    ERROR("    Could not open game controller " << SDL_GameControllerName(gc));
  }

  m_oldButtonsStates.resize(GC_INPUT_MAX, 0);
  m_currentButtonsStates.resize(GC_INPUT_MAX, 0);
}

GameController::~GameController() { m_gameController = nullptr; }

void GameController::Update() {
  m_oldButtonsStates = m_currentButtonsStates;

  for (int i = 0; i < GC_INPUT_MAX; i++) {
    m_currentButtonsStates[i] = SDL_GameControllerGetButton(
        m_gameController, (SDL_GameControllerButton)i);
  }
}

bool GameController::GetButtonDown(GameControllerButton button) {
  if (m_currentButtonsStates[button] && !m_oldButtonsStates[button])
    return true;
  return false;
}

bool GameController::GetButtonUp(GameControllerButton button) {
  if (!m_currentButtonsStates[button] && m_oldButtonsStates[button])
    return true;
  return false;
}

bool GameController::GetButtonPressed(GameControllerButton button) {
  return SDL_GameControllerGetButton(m_gameController,
                                     (SDL_GameControllerButton)button);
}

int GameController::GetAxis(GameControllerAxis axis) {
  return SDL_GameControllerGetAxis(m_gameController,
                                   (SDL_GameControllerAxis)axis);
}