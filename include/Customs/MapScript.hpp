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
        char nakedManMovements;
        int mapSize_x;
        int mapSize_y;
        int mapSpeed;
        float proportion_x;
        float proportion_y;
        // camera shaking
        bool shake = false;
        void CreateWalls();
};

#endif
