#include <algorithm>

#include "Engine/InputSystem.hpp"
#include "Log/log.hpp"

// static variables initialization
InputSystem *InputSystem::m_instance = 0;

InputSystem::InputSystem() {
  SDL_PumpEvents();
  SDL_GameControllerEventState(SDL_IGNORE);

  LoadGameControllers();

  m_states = SDL_GetKeyboardState(&m_statesSize);
  m_oldStates = new Uint8[m_statesSize];
  m_mouseStates = SDL_GetMouseState(&m_mouseX, &m_mouseY);
}

InputSystem::~InputSystem() {
  m_states = nullptr;
  delete[] m_oldStates;
  m_oldStates = nullptr;
}

InputSystem *InputSystem::GetInstance() {
  if (!m_instance)
    m_instance = new InputSystem();
  return m_instance;
}

void InputSystem::UpdateStates() {
  // update old states to be equal to actual
  for (int i = 0; i < m_statesSize; i++)
    m_oldStates[i] = m_states[i];
  m_oldMouseStates = m_mouseStates;

  SDL_PumpEvents();
  SDL_GameControllerUpdate();

  UpdateGameControllers();

  m_mouseStates = SDL_GetMouseState(&m_mouseX, &m_mouseY);
}

bool InputSystem::GetKeyDown(KeyboardInputGlobal key) {
  if (m_states[key] && !m_oldStates[key]) {
    // char message[] = "Key down: ";
    // strcat(message, SDL_GetScancodeName((SDL_Scancode)key));
    // INFO(message);
    return true;
  }
  return false;
}

bool InputSystem::GetKeyUp(KeyboardInputGlobal key) {
  if (!m_states[key] && m_oldStates[key]) {
    // char message[] = "Key up: ";
    // strcat(message, SDL_GetScancodeName((SDL_Scancode)key));
    // INFO(message);
    return true;
  }
  return false;
}

bool InputSystem::GetKeyPressed(KeyboardInputGlobal key) {
  if (m_states[key]) {
    // char message[] = "Key pressed: ";
    // strcat(message, SDL_GetScancodeName((SDL_Scancode)key));
    // INFO(message);
    return true;
  }
  return false;
}

bool InputSystem::GetMouseButtonDown(MouseInputGlobal button) {
  bool isPressed = m_mouseStates & SDL_BUTTON(button);
  bool wasPressed = m_oldMouseStates & SDL_BUTTON(button);
  if (isPressed && !wasPressed) {
    // INFO("Mouse button down");
    return true;
  }
  return false;
}

bool InputSystem::GetMouseButtonUp(MouseInputGlobal button) {
  bool isPressed = m_mouseStates & SDL_BUTTON(button);
  bool wasPressed = m_oldMouseStates & SDL_BUTTON(button);
  if (!isPressed && wasPressed) {
    // INFO("Mouse button up");
    return true;
  }
  return false;
}

bool InputSystem::GetMouseButtonPressed(MouseInputGlobal button) {
  if (m_mouseStates & SDL_BUTTON(button)) {
    return true;
  }
  return false;
}

std::pair<int, int> InputSystem::GetMousePosition() {
  std::pair<int, int> position;
  position = std::make_pair(m_mouseX, m_mouseY);
  return position;
}

void InputSystem::LoadGameControllers() {
  int quantity = SDL_NumJoysticks();
  INFO("[INPUT] Loading game controllers");

  for (int i = 0; i < quantity; i++) {
    if (SDL_IsGameController(i)) {
      SDL_GameController *sdl_gc = SDL_GameControllerOpen(i);
      GameController *gc = new GameController(sdl_gc);
      if (sdl_gc)
        m_gameControllers.push_back(gc);
    }
  }
}

void InputSystem::UpdateGameControllers() {
  CheckGameControllersConnections();
  for (auto gc : m_gameControllers)
    gc->Update();
}

void InputSystem::CheckGameControllersConnections() {}

GameController *InputSystem::GetGameController(int index) {
  if (m_gameControllers.size() < (unsigned)index + 1)
    return nullptr;
  return m_gameControllers.at(index);
}
