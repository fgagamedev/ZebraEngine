#ifndef __CAMERA_H_SYSTEM__
#define __CAMERA_H_SYSTEM__
#include "Engine/GameObject.h"
#include "Engine/SceneManager.h"
#include "Engine/Timer.h"
#include "Globals/EngineGlobals.h"
#include <math.h>
#include <vector>
class CameraSystem{

public:

  static CameraSystem *GetInstance();

  //Camera Movement
  static void MoveRight(int speed);
  static void MoveLeft(int speed);
  static void MoveUp(int speed);
  static void MoveDown(int speed);
  static void CameraShake(int intensity,float duration);

  void Reset();
  float GetPos_x();
  float GetPos_y();
  int GetCameraSpeed();

  void SetCameraSpeed(int speed);
  void SetPos_x(float x);
  void SetPos_y(float y);

  //Camera shake
  static bool IsShaking();

  //Zoom
  void ZoomIn(int zoomSpeed,GameObject * objectToFollow);
  void ZoomOut(int zoomSpeed,GameObject * objectToFollow);

  private:
  CameraSystem();
  ~CameraSystem();
  static float  worldCamera_x;
  static float  worldCamera_y;
  float proportion_x;
  float proportion_y;
  float x_pos_before;
  float y_pos_before;
  int cameraSpeed;
  static bool isShaking;
  static Timer timer;
  static int current_x;
  static int current_y;
  static CameraSystem * m_instance;
  static std::vector<GameObject *> m_gameObjects;
};


#endif