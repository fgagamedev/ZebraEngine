/*
    @file CameraSystem.hpp
    @brief Class that manages the game image,
    including the scenes the zoom and speed that the screen moves.
    @copyright LGPL. MIT License.
*/
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

        // Camera Movement.
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
            // Represents the state of the camera.
            isLocked = true;
        }
        void Unlock() {
            // Represents the state of the camera.
            isLocked = false;
        }
        bool IsLerping() {
            return isLerping;
        }

        void SetCameraSpeed(int speed);
        void SetAndMovePos_x(float axisX);
        void SetAndMovePos_y(float axisY);

        // Camera shake.
        bool IsShaking() {
            return isShaking;
        }

        void CameraShake(int intensity, float duration, Scene *scene);

        // Zoom.
        void ZoomIn(int zoomSpeed, GameObject *objectToFollow, Scene *scene);
        void ZoomOut(int zoomSpeed, GameObject *objectToFollow, Scene *scene);

        // Represents the current zoom of the camera.
        float currentZoom = 0;

        float  worldCameraX;
        float  worldCameraY;

    private:

        CameraSystem();
        ~CameraSystem();

        float m_proportionX;
        float m_proportionY;
        float m_beforePositionX;
        float m_beforePositionY;

        int m_cameraSpeed;

        bool isShaking;

        // Represents the state of the camera.
        bool isLocked = true;

        // Represents the state of movement of the camera.
        bool isLerping = true;

        Timer m_timer;

        std::vector<GameObject*> m_gameObjects;

        static CameraSystem *m_instance;
};

#endif
