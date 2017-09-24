#include <algorithm>

#include "Engine/InputSystem.hpp"
#include "Log/log.hpp"

/**
    @file InputSystem.cpp
    @brief Methods for the actions of the buttons needed for playing the game.
    @copyright LGPL. MIT License.
*/


// Static variables initialization
InputSystem *InputSystem::m_instance = 0;

/**
    @brief Initializes InputSystem instance.
*/
InputSystem::InputSystem() {
    SDL_PumpEvents();
    SDL_GameControllerEventState(SDL_IGNORE);

    LoadGameControllers();

    m_states = SDL_GetKeyboardState(&m_statesSize);
    m_oldStates = new Uint8[m_statesSize];
    m_mouseStates = SDL_GetMouseState(&m_mouseX, &m_mouseY);
}

// Destructor
InputSystem::~InputSystem() {
    m_states = nullptr;
    delete[] m_oldStates;
    m_oldStates = nullptr;
}

/**
    @brief Get the current instance of input system.
    @return m_instance.
*/
InputSystem *InputSystem::GetInstance() {
    // Checks if singleton exists.
    if (!m_instance) {
        m_instance = new InputSystem();
    }
    return m_instance;
}

/**
    @brief Update the state of the input.
*/
void InputSystem::UpdateStates() {
    // Update old states to be equal to actual.
    for (int i = 0; i < m_statesSize; i++) {
        m_oldStates[i] = m_states[i];
    }
    m_oldMouseStates = m_mouseStates;

    SDL_PumpEvents();
    SDL_GameControllerUpdate();

    UpdateGameControllers();

    m_mouseStates = SDL_GetMouseState(&m_mouseX, &m_mouseY);
}

/**
    @brief Get the current state of a button down on a keyboard.
    @param[in] key - state of a button from the keyboard.
    @return bool.
*/
bool InputSystem::GetKeyDown(KeyboardInputGlobal key) {
    if (m_states[key] && !m_oldStates[key]) {
        /**
        char message[] = "Key down: ";
        strcat(message, SDL_GetScancodeName((SDL_Scancode)key));
        INFO(message);
        */
        return true;
    }
    return false;
}

/**
    @brief Get the current state of a button up on a keyboard.
    @param[in] key - state of a button from the keyboard.
    @return bool.
*/
bool InputSystem::GetKeyUp(KeyboardInputGlobal key) {
    if (!m_states[key] && m_oldStates[key]) {
        return true;
    }
    return false;
}

/**
    @brief Get the current state of a pressed button up on a keyboard.
    @param[in] key - state of a button from the keyboard.
    @return bool.
*/
bool InputSystem::GetKeyPressed(KeyboardInputGlobal key) {
    if (m_states[key]) {
        return true;
    }
    return false;
}

/**
    @brief Get the current state of a mouse pressed button, and returns the current button status
    pressed down.
    @param[in] button - state of a button from the mouse.
    @return bool.
*/
bool InputSystem::GetMouseButtonDown(MouseInputGlobal button) {
    bool isPressed = m_mouseStates & SDL_BUTTON(button);
    bool wasPressed = m_oldMouseStates & SDL_BUTTON(button);
    if (isPressed && !wasPressed) {
        return true;
    }
    return false;
}

/**
    @brief Get the current state of a mouse pressed button, and returns the current button status
    pressed up.
    @param[in] button - state of a button from the mouse.
    @return bool.
*/
bool InputSystem::GetMouseButtonUp(MouseInputGlobal button) {
    bool isPressed = m_mouseStates & SDL_BUTTON(button);
    bool wasPressed = m_oldMouseStates & SDL_BUTTON(button);
    if (!isPressed && wasPressed) {
        return true;
    }
    return false;
}

/**
    @brief Check if a mouse button was pressed.
    @param[in] button - state of a button from the mouse.
    @return bool.
*/
bool InputSystem::GetMouseButtonPressed(MouseInputGlobal button) {
    if (m_mouseStates & SDL_BUTTON(button)) {
        return true;
    }
    return false;
}

/**
    @brief Defines the mouse position.
    @return position.
*/
std::pair<int, int> InputSystem::GetMousePosition() {
    std::pair<int, int> position;
    position = std::make_pair(m_mouseX, m_mouseY);
    return position;
}

/**
    @brief Count connected joysticks, and load them.
*/
void InputSystem::LoadGameControllers() {
    int quantity = SDL_NumJoysticks();
    INFO("[INPUT] Loading game controllers");

    // Count available game controllers.
    for (int i = 0; i < quantity; i++) {
        // Checking if it's a joystick.
        if (SDL_IsGameController(i)) {
            SDL_GameController *sdl_gc = SDL_GameControllerOpen(i);
            GameController *gc = new GameController(sdl_gc);
            if (sdl_gc) {
                m_gameControllers.push_back(gc);
            }
        }
    }
}

/**
    @brief Update status of current joystick.
*/
void InputSystem::UpdateGameControllers() {
    CheckGameControllersConnections();
    for (auto gc : m_gameControllers) {
        gc->Update();
    }
}

/**
    @brief Check connection status of current joystick.
*/
void InputSystem::CheckGameControllersConnections() {}

/**
    @brief Defines the N'th game controller on the system.
    @param[in] index - the controller identifier.
    @return GameController.
*/
GameController *InputSystem::GetGameController(int index) {
    if (m_gameControllers.size() < (unsigned)index + 1) {
        // Return NULL if an error occurred.
        return nullptr;
    }
    // Return a controller identifier.
    return m_gameControllers.at(index);
}
