#include "Customs/EndScene2.hpp"
#include "Customs/MenuAnimationScript.hpp"

/*
    @file EndScene2.cpp
    @brief Methods that manages the end-game animations and a 'quit' button.
    @copyright MIT License.
*/

// Constructor
EndScene2::EndScene2() {}

/*
    @brief On activation of the second scene, creates 'quit' button and animation in the middle of the screen.
    @return void
*/
void EndScene2::OnActivation() {
    m_width_middle = EngineGlobals::screen_width / 2;
    m_height_middle = EngineGlobals::screen_height / 2;

    CreateQuitButton();
    CreateAnimation();
}

/*
    @brief Method for handling deactivation state changing.
    @return void
*/
void EndScene2::OnDeactivation() {}

/*
    @brief Method for handling showing state changing.
    @return void
*/
void EndScene2::OnShown() {}

/*
    @brief Method for handling on hidden state changing.
    @return void
*/
void EndScene2::OnHidden() {}

/*
    @brief Method that creates the game over's end scene and its background animation.
    @return void
*/
void EndScene2::CreateAnimation(){
    auto BackgroundAnimation = new GameObject("ToBeAnimation", new Vector(0 ,0),1024,800,0);
    auto gameOverScript = new GameOverScript(BackgroundAnimation);
    AddGameObject(BackgroundAnimation);
}

/*
    @brief Method that creates 'quit' button on the middle of the screen, and plays a button sound.
    @return void
*/
void EndScene2::CreateQuitButton() {
    int xMiddle = EngineGlobals::screen_width / 2 - 100;
    auto quit = new GameObject("Quit", new Vector(xMiddle, 500), 200, 100,0);
    auto quitText = new UIText(quit, "Quit", "assets/Fonts/mini-pixel-7/mini-pixel-7.ttf",
                             200, 255, 255, 255, 150, 1);
    auto quitButton = new UIButton(quit);
    auto quitSound = new UISound(quit, "playSound", "assets/Audio/Button/MusicButton1.wav", false, false);
    auto script = new QuitButtonScript(quit);

    AddGameObject(quit);
}
