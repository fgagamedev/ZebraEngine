/**
    @file CentralLightScript4.hpp
    @brief This class contains all attributes and methods that manages the central light in the game.
    @copyright LGPL. MIT License.
*/
#ifndef __CENTRAL_LIGHT_SCRIPT4__
#define __CENTRAL_LIGHT_SCRIPT4__

#include "Engine/Timer.hpp"
#include "Engine/GameController.hpp"
#include "Engine/InputSystem.hpp"
#include "Engine/GameObject.hpp"
#include "Engine/SceneManager.hpp"

#include "Components/Script.hpp"
#include "Components/Animator.hpp"

#include "Math/Vector.hpp"

#include <string>

class CentralLightScript4 : public Script {

	public:
		CentralLightScript4(GameObject *owner);
		std::string GetComponentName() override {
			return "CentralLightScript4";
		};

		void FixedComponentUpdate() override;
		void Start() override;

        // Represents if this is script is activeted or not.
		void Activate(){active = true;}

	protected:
		void ComponentUpdate() override;

	private:

        // Represents if this is script is activeted or not.
		bool active = false;

        // Instantiating time system.
		Timer time;

		void CreateAnimations();

        // Instantiating input system of the keyboard.
		InputSystem *input = nullptr;

        // Instantiating joystick.
		GameController* gamecontroller = nullptr;

        // Instantiating animations.
		Animator *animator = nullptr;

        // Instantiating vector.
		Vector *position = nullptr;

        // State of the script.
		int play = 0;

};
#endif
