/**
    @file MainScene.hpp
    @brief Class that represents the Main Scene of the game.
    @copyright LGPL. MIT License.
*/

#ifndef __MAIN_SCENE__
#define __MAIN_SCENE__

#include "Engine/Image.hpp"
#include "Engine/Scene.hpp"

#include "Components/RectangleRenderer.hpp"
#include "Components/Renderer.hpp"
#include "Components/UIButton.hpp"
#include "Components/UIText.hpp"
#include "Components/UISound.hpp"
#include "Customs/CatchAllButtonScript.hpp"
#include "Customs/MissileButtonScript.hpp"
#include "Customs/PlayButtonScript.hpp"
#include "Customs/QuitButtonScript.hpp"
#include "Globals/EngineGlobals.hpp"


class MainScene : public Scene {
    public:
        MainScene();
        virtual void OnActivation() override;
        virtual void OnDeactivation() override;
        virtual void OnShown() override;
        virtual void OnHidden() override;

    private:
        void CreateAnimation();
        void CreateLogo();
        void CreatePlayButton();
        void CreateQuitButton();
        void CreateMusic();
        

        //Middle position of width.
        int m_widthMiddle = 0;

        //Middle position of height.
        int m_heightMiddle = 0;
};

#endif
