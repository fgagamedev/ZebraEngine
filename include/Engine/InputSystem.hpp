#ifndef __INPUT_SYSTEM__
#define __INPUT_SYSTEM__

#include "Engine/GameController.hpp"
#include "Engine/sdl2include.hpp"

#include "Globals/InputGlobals.hpp"

#include <utility>
#include <vector>

/**
    @file InputSystem.hpp
    @brief This class defines the actions of the buttons needed for playing the game.
    @copyright LGPL. MIT License.
*/

class InputSystem {
public:

    // Singleton getter
    static InputSystem *GetInstance();

    // Update m_states and m_oldStates every frame
    void UpdateStates();

    // Event handling
    bool GetKeyDown(KeyboardInputGlobal key);
    bool GetKeyUp(KeyboardInputGlobal key);
    bool GetKeyPressed(KeyboardInputGlobal key);
    bool GetMouseButtonDown(MouseInputGlobal button);
    bool GetMouseButtonUp(MouseInputGlobal button);
    bool GetMouseButtonPressed(MouseInputGlobal button);
    std::pair<int, int> GetMousePosition();
    GameController *GetGameController(int index);

private:

    // Constructor and destructor
    InputSystem();
    ~InputSystem();

    // Joystick handling
    void LoadGameControllers();
    void UpdateGameControllers();
    void CheckGameControllersConnections();

    // Private attributes
    static InputSystem *m_instance;

    // Keyboard states
    const Uint8 *m_states;
    Uint8 *m_oldStates;
    int m_statesSize;

    // Mouse states
    Uint32 m_mouseStates = 0;
    Uint32 m_oldMouseStates = 0;
    int m_mouseHorizontal, m_mouseVertical;

    // Game controllers
    std::vector<GameController *> m_gameControllers;
};

#endif // __INPUT_SYSTEM__
