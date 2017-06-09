#ifndef __CAMERA_H_SYSTEM__
#define __CAMERA_H_SYSTEM__
#include "Engine/GameObject.h"
#include "Engine/SceneManager.h"
#include <vector>
class CameraSystem{

public:

 static CameraSystem *GetInstance();
 //Camera Movement
 void MoveRight(int speed);
 void MoveLeft(int speed);
 void MoveUp(int speed);
 void MoveDown(int speed);
 void Reset();
 float GetPos_x();
 float GetPos_y();
 int GetCameraSpeed();
 void SetCameraSpeed(int speed);
 void SetPos_x(float x);
 void SetPos_y(float y);

 //Zoom
 void ZoomIn(int zoomSpeed,GameObject * objectToFollow);
 void ZoomOut(int zoomSpeed,GameObject * objectToFollow);

 private:
 CameraSystem();
 ~CameraSystem();
 float  worldCamera_x;
 float  worldCamera_y;
 float proportion_x;
 float proportion_y;
 float x_pos_before;
 float y_pos_before;
 int cameraSpeed;

 static CameraSystem * m_instance;
 std::vector<GameObject *> m_gameObjects;
};


#endif