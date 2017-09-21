/**
    @file MenuAnimationScript.hpp
    @brief Class that represents the scrip of the Menu Animation of the game.
    @copyright LGPL. MIT License.
*/

#ifndef __MENU_ANIMATION_SCRIPT__
#define __MENU_ANIMATION_SCRIPT__

#include "Engine/SceneManager.hpp"

#include "Components/Animator.hpp"
#include "Components/Script.hpp"


class MenuAnimationScript : public Script {
public:
    MenuAnimationScript (GameObject *owner);
    std::string GetComponentName() override { return "MenuAnimationScript"; };
    void FixedComponentUpdate() override;
    void Start() override;

protected:
    void ComponentUpdate() override;

private:
    void CreateAnimations();

    // Sets the state of the initial animation.
    bool initialanimation=false;

    // Sets the number of current frames in the script.
    int currentframe=0;
    
    // Sets state of the game.
    bool isPlaying=false;

    // Instantiating animations.
    Animator *animator = nullptr;

    // Instantiating object position, type vector.
    Vector *position = nullptr;
};

#endif
