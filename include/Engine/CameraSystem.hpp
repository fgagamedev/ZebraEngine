#ifndef __CAMERA_H_SYSTEM__
#define __CAMERA_H_SYSTEM__

#include "Engine/GameObject.hpp"
#include "Engine/SceneManager.hpp"
#include "Engine/Scene.hpp"
#include "Engine/Timer.hpp"

#include "Globals/EngineGlobals.hpp"

#include <math.h>
#include <vector>

class CameraSystem{

    public:
        static CameraSystem *GetInstance();

        // Camera Movement
        void MoveRight(int speed, Scene *scene);
        void MoveLeft(int speed, Scene *scene);
        void MoveUp(int speed, Scene *scene);
        void MoveDown(int speed, Scene *scene);

        void Reset();
        float GetPositionX();
        float GetPositionY();
        int GetCameraSpeed();

        bool IsLocked() {
            return isLocked;
        }
        void Lock() {
            isLocked = true;
        }
        void Unlock() {
            isLocked = false;
        }
        bool IsLerping() {
            return isLerping;
        }

        void SetCameraSpeed(int speed);
        void SetAndMovePos_x(float x);
        void SetAndMovePos_y(float y);

        // Camera shake
        bool IsShaking() {
            return isShaking;
        }
        
        void CameraShake(int intensity, float duration, Scene *scene);

        // Zoom
        void ZoomIn(int zoomSpeed, GameObject *objectToFollow, Scene *scene);
        void ZoomOut(int zoomSpeed, GameObject *objectToFollow, Scene *scene);

        float currentZoom = 0;

        float  worldCameraX;
        float  worldCameraY;

    private:

        CameraSystem();
        ~CameraSystem();

        float proportionX;
        float proportionY;
        float beforePositionX;
        float beforePositionY;

        int cameraSpeed;

        bool isShaking;
        bool isLocked = true;
        bool isLerping = true;

        Timer timer;

        std::vector<GameObject*> m_gameObjects;

        static CameraSystem *m_instance;
};

#endif