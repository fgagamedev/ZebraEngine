/**
    @file CatchAllButtonScript.hpp
    @brief Manages the Catch All button functions.
    @copyright LGPL. MIT License.
*/

#ifndef __CATCH_ALL_BUTTON_SCRIPT__
#define __CATCH_ALL_BUTTON_SCRIPT__

#include "Components/Script.hpp"
#include "Components/UIButton.hpp"
#include "Customs/MenuController.hpp"
#include "Components/UIText.hpp"
#include "Log/log.hpp"


using namespace std;

class CatchAllButtonScript : public Script {
public:
    CatchAllButtonScript(GameObject *owner);
    virtual void Start() override;
    virtual void ComponentUpdate() override;

    // Replace the component name and return it.
    virtual string GetComponentName() override {
        return "CatchAllButtonScript";
    };


private:
    // Set the CatchAll button as a UIButton
    UIButton *m_uiButton = nullptr;

    // Set a checkbox game object
    GameObject *m_checkbox = nullptr;
};

#endif
