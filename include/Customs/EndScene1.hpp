#ifndef __END_SCENE1__
#define __END_SCENE1__

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

/**
    @file EndScene1.hpp
    @brief This class contains all attributes and methods that manages some of the scenes in the game.
    @copyright LGPL. MIT License.
*/

class EndScene1 : public Scene {
public:
    EndScene1();
    virtual void OnActivation() override;
    virtual void OnDeactivation() override;
    virtual void OnShown() override;
    virtual void OnHidden() override;

private:
    void CreateGameOver();
    void CreateQuitButton();
    int m_widthMiddle = 0;
    int m_heightMiddle = 0;

};

#endif
