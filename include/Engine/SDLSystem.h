#ifndef __SDLSYSTEM_H__
#define __SDLSYSTEM_H__

#include "Engine/CollisionSystem.h"
#include "Engine/InputSystem.h"
#include "Engine/SceneManager.h"
#include "Engine/sdl2include.h"
#include "Globals/EngineGlobals.h"
#include "Globals/InputGlobals.h"
#include "Log/log.h"
#include "Log/sdl_log.h"

using namespace std;
using namespace EngineGlobals;

class SDLSystem {
public:
  // initialize all systems
  void Init();
  // run system
  void Run();
  // systems shutdown
  void Shutdown();
  // get singleton instance
  static SDLSystem *GetInstance();
  // getters and setters
  SDL_Window *GetWindow() const { return m_window; };
  SDL_Renderer *GetRenderer() const { return m_renderer; };
  // change loop variable
  inline void SetRunning(bool condition) { m_isRunning = condition; };

private:
  // SDL attributes
  SDL_Window *m_window = nullptr;
  SDL_Renderer *m_renderer = nullptr;
  // singleton instance
  static SDLSystem *m_instance;
  // game attributes
  bool m_isRunning;
  int m_framerate;
  int m_frameCounter;
  Uint32 m_currentTicks;
  Uint32 m_lastFrameTicks;
  Uint32 m_gameEndTicks;
  Uint32 m_lastFixedUpdate;
  Uint32 m_currentFix;
  Uint32 m_lastFix;

  // constructor and destructor
  SDLSystem();
  ~SDLSystem();
  // systems init
  bool InitSDL();
  bool InitIMG();
  bool InitMixer();
  bool InitTTF();
  // commons init
  void LoadCommons();
  // graphics methods
  bool CreateWindow();
  bool CreateRenderer();
  // system framerate counter
  void CalculateFramerate();
  bool FixFramerate();
};

#endif //__SDLSYSTEM_H__
