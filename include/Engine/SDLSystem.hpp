/**
    @file SDLSystem.hpp
    @brief Manages the SDL functions.
    @copyright LGPL. MIT License.
*/

#ifndef __SDLSYSTEM_H__
#define __SDLSYSTEM_H__

#include "Engine/CollisionSystem.hpp"
#include "Engine/InputSystem.hpp"
#include "Engine/SceneManager.hpp"
#include "Engine/sdl2include.hpp"

#include "Globals/EngineGlobals.hpp"
#include "Globals/InputGlobals.hpp"
#include "Log/log.hpp"
#include "Log/sdl_log.hpp"

using namespace std;
using namespace EngineGlobals;

class SDLSystem {
public:
    // Initialize all systems
    void Init();

    // Run system
    void Run();

    // Systems shutdown
    void Shutdown();

    // Get singleton instance
    static SDLSystem *GetInstance();

    // Getters and setters
    SDL_Window *GetWindow() const {
        return m_window;
    };
    SDL_Renderer *GetRenderer() const {
        return m_renderer;
    };

    // Change loop variable
    inline void SetRunning(bool condition) {
        m_isRunning = condition;
    };

private:
    // SDL window and renderer attributes
    SDL_Window *m_window = nullptr;
    SDL_Renderer *m_renderer = nullptr;

    // Singleton SDL instance
    static SDLSystem *m_instance;

    // Game attributes
    bool m_isRunning;
    int m_frameRate;
    int m_frameCounter;

    // Integer types with a width of exactly 32 bits
    Uint32 m_currentTicks;
    Uint32 m_lastFrameTicks;
    Uint32 m_gameEndTicks;
    Uint32 m_lastFixedUpdate;
    Uint32 m_currentFix;
    Uint32 m_lastFix;

    // Constructor and destructor
    SDLSystem();
    ~SDLSystem();

    // Systems init
    bool InitSDL();
    bool InitIMG();
    bool InitMixer();
    bool InitTTF();

    // Commons init
    void LoadCommons();

    // Graphics methods
    bool CreateWindow();
    bool CreateRenderer();

    // System framerate counter
    void CalculateFramerate();
    bool FixFramerate();
};

#endif //__SDLSYSTEM_H__
