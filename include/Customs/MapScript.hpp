    #ifndef __MAP_SCRIPT__
    #define __MAP_SCRIPT__

    #include "Engine/CameraSystem.hpp"
    #include "Engine/SceneManager.hpp"

    #include "Components/Script.hpp"
    #include "Customs/NakedManScript.hpp"
    #include "Customs/ForestActivatorScript.hpp"
    #include "Customs/ForestActivatorScript2.hpp"
    #include "Customs/ForestActivatorScript3.hpp"
    #include "Customs/SnowActivatorScript.hpp"
    #include "Globals/EngineGlobals.hpp"

    class MapScript : public Script {
        public:
            MapScript(GameObject *owner);
            std::string GetComponentName() override {
                return "MapScript";
            };
            void FixedComponentUpdate() override;
            void Start() override;
            int DetectWallCollision(GameObject* object);

            Vector leftWalls[100] = {};
            Vector leftWallsOriginal[100] = {};
            int leftWallsAmount=0;

            Vector rightWalls[100] = {};
            int rightWallsAmount=0;
            Vector rightWallsOriginal[100] = {};

            Vector upWalls[100] = {};
            int upWallsAmount=0;
            Vector upWallsOriginal[100] = {};

            Vector downWalls[100] = {};
            Vector downWallsOriginal[100] = {};
            int downWallsAmount = 0;
            bool activated = true;

        protected:
            void ComponentUpdate() override;

        private:
            void RenderWallsRects();
            GameObject *nakedMan = nullptr;
            GameObject *map = nullptr;
            Vector *nakedManPosition = nullptr;
            Vector *mapPosition = nullptr;
            NakedManScript *script = nullptr;
            // player inputs
            InputSystem *input = nullptr;
            char nakedManMovements = ' ';
            int mapSizeHorizontal = 0;
            int mapSizeVertical = 0;
            int mapSpeed = 0;
            float proportionHorizontal = 0.0;
            float proportionVertical = 0.0;
            // camera shaking
            bool cameraShake = false;
            void CreateWalls();
    };

    #endif
