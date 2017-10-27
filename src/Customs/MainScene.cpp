/**
    @file MainScene.cpp
    @brief Methods that manages the main scene of the game.
    @copyright LGPL. MIT License.
*/

#include "Customs/MainScene.hpp"
#include "Customs/MenuAnimationScript.hpp"

const int middlePosition = 2;

MainScene::MainScene() {

}

/**
    @brief that function is for when the state is actived, and create the logo,
    playButton, QuitButton, the music and animation.
*/
void MainScene::OnActivation() {
    // On activation, gets the screen width and height to middle position the basic components of the game.
    m_widthMiddle = EngineGlobals::screen_width / middlePosition;
    m_heightMiddle = EngineGlobals::screen_height / middlePosition;
    CreateLogo();
    CreatePlayButton();
    CreateQuitButton();
    CreateMusic();
    CreateAnimation();

}

/**
    @brief that function is for when the state is deactived and because of that,
    nothing is created.
*/
void MainScene::OnDeactivation() {

}

/**
    @brief that function is for when the state is on show and because of that,
    nothing is created.
*/
void MainScene::OnShown() {

}

/**
    @brief that function is for when the state is on hidden and because of that,
    nothing is created.
*/
void MainScene::OnHidden() {

}


/**
    @brief that function create the logo of the game. Select the place of the logo,
    then create the logo as a game object. After create the logo image and renderer it.
*/
void MainScene::CreateLogo() {
    /*
        Setting and render the game logo image in the middle of the screen,
        in a gameobject.
    */
    unsigned int xMiddle = EngineGlobals::screen_width / middlePosition - 240;

    auto logo = new GameObject("Logo", new Vector(-30,0), 1024, 800,1);

    auto logoImage = new Image("assets/logo2.png", 0, 0, 311, 256);
    new Renderer(logo, logoImage);

    AddGameObject(logo);
}

/**
    @brief that function create the play button for the game starts. Set the place of
    the button, create the "Play" as a GameObject, the text of it, the button and the sound.
*/
void MainScene::CreatePlayButton() {
    /*
        Position the play button and its text, by setting the new gameobject in the
        middle position of the screen, and instantiates the sound of the button.
    */
    int xMiddle = EngineGlobals::screen_width / middlePosition - 100;
    auto play = new GameObject("Play", new Vector(xMiddle, 400), 200, 100,1);
    new UIText(play, "Play", "assets/Fonts/mini-pixel-7/mini-pixel-7.ttf",
                               200, 255, 255, 255, 150, 1);
    new UIButton(play);
    new UISound(play, "playSound", "assets/Audio/Button/MusicButton1.wav", false, false);
    new PlayButtonScript(play);
    AddGameObject(play);
}

/**
    @brief that function create the play button for quit the game. Set the place of
    the button, create the "Quit" as a GameObject, the text of it, the button and the sound.
*/
void MainScene::CreateQuitButton() {
    /*
        Position the quit button and its text, by setting the new gameobject in the    //CreateBackground();
    //CreateGamemodes();
        middle position of the screen, and instantiates the sound of the button.
    */
    int xMiddle = EngineGlobals::screen_width / middlePosition - 100;
    auto quit = new GameObject("Quit", new Vector(xMiddle, 500), 200, 100, 1);
    new UIText(quit, "Quit", "assets/Fonts/mini-pixel-7/mini-pixel-7.ttf",
                               200, 255, 255, 255, 150, 1);
    new UIButton(quit);
    new UISound(quit, "playSound", "assets/Audio/Button/MusicButton1.wav", false, false);
    new QuitButtonScript(quit);
    AddGameObject(quit);
}

/**
    @brief that function create the animation of the main scene of the game. Add
    the backgroundAnimation as a GameObject and the backgroundAnimationScript as a
    MenuAnimationScript.
*/
void MainScene::CreateAnimation() {
    // Create a gameobject for the background animation and its script, and a vector with its positions.
    auto BackgroundAnimation = new GameObject("BackgroundAnimation", new Vector(0 ,0), 1024, 800, 0);
    new MenuAnimationScript(BackgroundAnimation);
    AddGameObject(BackgroundAnimation);
}


/**
    @brief that function create the music theme of the game. Add the music as a
    GameObject and the themeMusic as a UISound.
*/
void MainScene::CreateMusic() {
    // Create a gameobject for the game music, and a vector with its positions.
    auto music = new GameObject("Music", new Vector(200, 200), 200, 100);
    // Instantiate the UI sound, and define its states.
    new UISound(music, "Music", "assets/Audio/Menu/Menu.ogg", false, true);
    // Add the whole music instantiated in a vector of gameobjects.
    AddGameObject(music);
}
