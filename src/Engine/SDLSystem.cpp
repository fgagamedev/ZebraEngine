/**
    @file SDLSystem.cpp
    @brief Manages the SDL functions.
    @copyright LGPL. MIT License.
*/

#include "Engine/SDLSystem.hpp"

#include "Customs/FirstBossScene.hpp"
#include "Customs/MainScene.hpp"
#include "Customs/GamePlayScene.hpp"
#include "Customs/PreMenuScene.hpp"
#include "Customs/EndScene1.hpp"
#include "Customs/EndScene2.hpp"

const int red = 0;
const int green = 0;
const int blue = 0;
const int alpha = 255;
const int frequency = 44100;
const int channels = 2;
const int chunksize = 2048;
const int ticksLimit = 1000;

// Static variables initialization
SDLSystem *SDLSystem::m_instance = nullptr;

/**
    @brief Initialize the frame counter and the frame ticks counter.
*/
SDLSystem::SDLSystem() {
    m_frameCounter = 0;
    m_lastFrameTicks = 0;
}

/**
    @brief Initialize the instance, window and renderer pointers.
*/
SDLSystem::~SDLSystem() {
    m_instance = nullptr;
    m_window = nullptr;
    m_renderer = nullptr;
}

/**
    @brief Initialize all systems.
*/
void SDLSystem::Init() {
    INFO("SDLSystem::Init() initialized");

    // Check initialization fails
    if (!(InitSDL() && InitIMG() && InitMixer() && InitTTF())) {
        // Display error message
        ERROR("SDLSystem::Init() failed.");
            return;
    }

    // Check creation fails
    if (!(CreateWindow() && CreateRenderer())) {
        // Display error message
        ERROR("SDLSystem::Init() failed.");
            return;
    }

    INFO("SDLSystem::Init() completed");
}

/**
    @brief Runs the SDL library.
*/
void SDLSystem::Run() {
    INFO("Starting Run().");

    m_isRunning = true;

    LoadCommons();
    SceneManager::GetInstance()->SetCurrentScene("Pre Menu");

    SceneManager::GetInstance()->Start();

    // Update utilities while SDL System is running
    while (m_isRunning) {
        if (!FixFramerate()) {
            continue;
        }

        // Clear front buffer.
        SDL_SetRenderDrawColor(m_renderer, red, green, blue, alpha);
        SDL_RenderClear(m_renderer);

        // Draw update changing the back buffer.
        SceneManager::GetInstance()->DrawUpdate();

        CalculateFramerate();
        InputSystem::GetInstance()->UpdateStates();

        // All updates but draw are called here.
        SceneManager::GetInstance()->Update();

        /*
            Update scene manager and collision system based on
            fixed interval of ticks.
        */
        if (SDL_GetTicks() - m_lastFixedUpdate >
            EngineGlobals::fixed_update_interval) {
            SceneManager::GetInstance()->FixedUpdate();
            CollisionSystem::GetInstance()->Update();
            m_lastFixedUpdate = SDL_GetTicks();
        }

        // Getting back buffer and sending to front buffer.
        SDL_RenderPresent(m_renderer);
    } // while -- Update utilities while SDL System is nunning

    INFO("Ending Run().");
}

/**
    @brief Shut down SDL library and its subsystems used in the game.
*/
void SDLSystem::Shutdown() {
    INFO("Shutdown() Initialized.")

    /*
        Get number of milliseconds since the SDL library initialization
        when it is being shutdown.
    */
    m_gameEndTicks = SDL_GetTicks();

    IMG_Quit();
    Mix_Quit();
    TTF_Quit();
    SDL_Quit();

    INFO("Shutdown completed.")
}

/**
    @brief Get the singleton instance of the game.
    @return The singleton instance of the game
*/
SDLSystem *SDLSystem::GetInstance() {
    // Create if there is no instance
    if (!m_instance) {
        m_instance = new SDLSystem();
    }

    return m_instance;
}

/**
    @brief Initialize the SDL library and starts its subsystems used in the game.
    @return False if the system initialization fails and true if it's succeed.
*/
bool SDLSystem::InitSDL() {
    INFO("Initializing SDL");

    // Receives 0 if the chosen flags are initialized.
    int initialize = SDL_Init(SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_VIDEO |
               SDL_INIT_JOYSTICK | SDL_INIT_GAMECONTROLLER | SDL_INIT_EVENTS);

    // Check initialization fail
    if (initialize != 0) {
        // Display error message
        SDL_ERROR("SDLSystem::InitSDL() failed.");
        return false;
    }

    INFO("SDL Initialized.")
        return true;
}

/**
    @brief Initialize image support.
    @return False if the initialization fails and true if it's succeed.
*/
bool SDLSystem::InitIMG() {
    INFO("Initializing IMG");

    // Receives 0 if the chosen flags are initialized
    int flags = IMG_INIT_PNG | IMG_INIT_JPG;
    int initialize = IMG_Init(flags);

    // Check image initialization fail
    if ((initialize & flags) != flags) {
        // Display error message
        SDL_IMG_ERROR("SDLSystem::InitIMG() failed.");
        return false;
    }

    INFO("IMG Initialized.");
    return true;
}

/**
    @brief Initialize the SDL's sound mixing library.
    @return False if the initialization fails and true if it's succeed.
*/
bool SDLSystem::InitMixer() {
    INFO("Initializing Mixer");

    // Choose frequency, Uint16 format, channels and chunksize
    int initialize = Mix_OpenAudio(frequency, MIX_DEFAULT_FORMAT, channels, chunksize);

    // Check mixer initialization fail
    if (initialize != 0) {
        // Display error message
        SDL_MIX_ERROR("SDLSystem::InitMixer() failed.");
        return false;
    }

    INFO("Mixer Initialized.");
    return true;
}

/**
    @brief Initialize the SDL's TrueType font rendering library.
    @return False if the initialization fails and true if it's succeed.
*/
bool SDLSystem::InitTTF() {
    INFO("Initializing TTF");

    int initialize = TTF_Init();

    // Check TTF initialization fail
    if (initialize != 0) {
        // Display error message
        SDL_TTF_ERROR("SDLSystem::InitTTF() failed.");
        return false;
    }

    INFO("TTF Initialized.");
    return true;
}

/**
    @brief Creates a window with the specified title, position and dimensions.
    @return False if the window creation fails and true if it's succeed.
*/
bool SDLSystem::CreateWindow() {
    INFO("Creating window.");

    m_window = SDL_CreateWindow(EngineGlobals::window_title.c_str(),
                                SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                EngineGlobals::screen_width,
                                EngineGlobals::screen_height, SDL_WINDOW_SHOWN);

    // Check window creation fail
    if (!m_window) {
        // Display error message
        SDL_ERROR("SDLSystem::CreateWindow() failed.");
        return false;
    }

    INFO("Created window successfully.");
        return true;
}

/**
    @brief Creates a 2D rendering context for the window.
    @return False if the renderer creation fails and true if it's succeed.
*/
bool SDLSystem::CreateRenderer() {
    INFO("Creating renderer.");

    // Use hardware acceleration with first rendering driver that support it.
    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);

    // Check renderer creation fail
    if (!m_renderer) {
        // Display error message
        SDL_ERROR("SDLSystem::CreateRenderer() failed.");
        return false;
    }

    SDL_SetRenderDrawBlendMode(m_renderer,SDL_BLENDMODE_BLEND);
    INFO("Created renderer successfully.");
        return true;
}

/**
    @brief Calculates the frame rate.
*/
void SDLSystem::CalculateFramerate() {
    m_currentTicks = SDL_GetTicks();

    // Adjust frame rate based on limit of ticks
    if (m_currentTicks - m_lastFrameTicks >= ticksLimit) {
        m_frameRate = m_frameCounter;
        m_frameCounter = 0;
        m_lastFrameTicks = m_currentTicks;
    }
    m_frameCounter++;
}

/**
    @brief Loads necessary game scenes.
*/
void SDLSystem::LoadCommons() {
    // Instantiate and add multiple scenes to scene manager.
    auto endScene1 = new EndScene1();
    SceneManager::GetInstance()->AddScene(std::make_pair("EndScene1",
                                                         endScene1));
    auto endScene2 = new EndScene2();
    SceneManager::GetInstance()->AddScene(std::make_pair("EndScene2",
                                                         endScene2));
    auto preMenuScene = new PreMenuScene();
    SceneManager::GetInstance()->AddScene(std::make_pair("Pre Menu",
                                                         preMenuScene));
    auto mainScene = new MainScene();
    SceneManager::GetInstance()->AddScene(std::make_pair("Main",
                                                         mainScene));
    auto gameplayScene = new GamePlayScene();
    SceneManager::GetInstance()->AddScene(std::make_pair("Gameplay",
                                                         gameplayScene));
    auto firstBossScene = new FirstBossScene();
    SceneManager::GetInstance()->AddScene(std::make_pair("FirstBossScene",
                                                         firstBossScene));
}

/**
    @brief Adjusts the Frame rate based in the update rate interval.
    @return False if the calculated interval is less than the update rate
    interval and true if it's not.
*/
bool SDLSystem::FixFramerate() {
    m_currentFix = SDL_GetTicks();
    float fixInterval = m_currentFix - m_lastFix;

    // Compare intervals to check the need to fix frame rate
    if (fixInterval < update_rate_interval){
        return false;
    }

    m_lastFix = SDL_GetTicks();
    return true;
}
