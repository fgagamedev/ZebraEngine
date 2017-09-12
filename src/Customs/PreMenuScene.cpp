#include "Customs/PreMenuScene.hpp"
#include "Customs/SdlLogoScript.hpp"
#include "Customs/UnbLogoScript.hpp"
#include "Customs/ZebraLogoScript.hpp"
#include "Customs/ControleLogoScript.hpp"
/**
	@file PreMenuScene.cpp
	@brief Reunites the animations that are shown before the main menu appears.
	@copyright MIT License.
*/

/**
    @brief Tells what happens when the PreMenuScene is activated.
*/
void PreMenuScene::OnActivation() {
    CreateLogoSdl();
    CreateLogoUnb();
    CreateLogoControle();
    CreateLogoZebra();
}

void  PreMenuScene::OnDeactivation() {}

void  PreMenuScene::OnShown() {}

void  PreMenuScene::OnHidden() {}

/**
    @brief Shows the Sdl Logo.
*/
void PreMenuScene::CreateLogoSdl(){

    auto sdl_Logo = new GameObject("SDL LOGO", new Vector(0,0),1024,800,1);
    // Renderer
    auto sdl_logoscript = new SdlLogoScript(sdl_Logo);

    AddGameObject(sdl_Logo);
}

/**
    @brief Shows the UnB Logo.
*/
void PreMenuScene::CreateLogoUnb(){

    auto unb_Logo = new GameObject("UNB LOGO", new Vector(0,0),1024,800,1);
    // Renderer
    auto unb_logoscript = new UnbLogoScript(unb_Logo);

    AddGameObject(unb_Logo);
}

/**
    @brief Shows the video game controller animation.
*/
void PreMenuScene::CreateLogoControle(){

    auto controle_Logo = new GameObject("CONTROLE     LOGO", new Vector(0,0),1024,800,1);
    // Renderer
    auto controle_logoscript = new ControleLogoScript(controle_Logo);

    AddGameObject(controle_Logo);
}

/**
    @brief Shows the Zebra Logo.
*/
void PreMenuScene::CreateLogoZebra(){

    auto zebra_Logo = new GameObject("ZEBRA LOGO", new Vector(0,0),1024,800,1);
    // Renderer
    auto zebra_logoscript = new ZebraLogoScript(zebra_Logo);

    AddGameObject(zebra_Logo);
}
