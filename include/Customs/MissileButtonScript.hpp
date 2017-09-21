/**
    @file MissileButtonScript.hpp
    @brief This class contains all attributes and methods that manages the
    missile button in the game.
    @copyright LGPL. MIT License.
*/
#ifndef __MISSILE_BUTTON_SCRIPT__
#define __MISSILE_BUTTON_SCRIPT__

#include "Components/Script.hpp"
#include "Components/UIButton.hpp"
#include "Customs/MenuController.hpp"

using namespace std;

class MissileButtonScript : public Script {

    public:
        MissileButtonScript(GameObject *owner);
        virtual void Start() override;
        virtual void ComponentUpdate() override;
        virtual string GetComponentName() override {
            return "MissileButtonScript";
        };
    private:

        // Sets the position of a UiButton
        UIButton *m_uiButton = nullptr;

        // Sets the position of a gameobject of a checkbox
        GameObject *m_checkbox = nullptr;
};

#endif
