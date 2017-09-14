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
		void Activate(){active = true;}

	protected:
		void ComponentUpdate() override;

	private:
		bool active = false;
		Timer time;

		void CreateAnimations();

		InputSystem *input = nullptr;
		 GameController* gamecontroller = nullptr;
		Animator *animator = nullptr;
		Vector *position = nullptr;
		int play = 0;

};
#endif
