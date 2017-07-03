#ifndef __CAMERA_H_SYSTEM__
#define __CAMERA_H_SYSTEM__
#include "Engine/GameObject.h"
#include "Engine/SceneManager.h"
#include "Engine/Scene.h"
#include "Engine/Timer.h"
#include "Globals/EngineGlobals.h"

#include <math.h>
#include <vector>
class CameraSystem{

public:

  static CameraSystem *GetInstance();

  //Camera Movement
  void MoveRight(int speed,Scene * scene);
  void MoveLeft(int speed,Scene * scene);
  void MoveUp(int speed,Scene * scene);
  void MoveDown(int speed,Scene * scene);

  void Reset();
  float GetPos_x();
  float GetPos_y();
  int GetCameraSpeed();

  bool IsLocked(){return isLocked;}
  void Lock(){isLocked=true;}
  void Unlock(){isLocked=false;}

  bool IsLerping(){return isLerping;}

  void SetCameraSpeed(int speed);
  void SetAndMovePos_x(float x);
  void SetAndMovePos_y(float y);

  //Camera shake
  bool IsShaking(){return isShaking;}
  void CameraShake(int intensity,float duration,Scene * scene);

  //Zoom
  void ZoomIn(int zoomSpeed,GameObject * objectToFollow,Scene * scene);
  void ZoomOut(int zoomSpeed,GameObject * objectToFollow,Scene * scene);



  float currentZoom=0;

  float  worldCamera_x;
  float  worldCamera_y;
  private:
  CameraSystem();
  ~CameraSystem();
 
  float proportion_x;
  float proportion_y;
  float x_pos_before;
  float y_pos_before;
  int cameraSpeed;
  bool isShaking;
  bool isLocked = true;
  bool isLerping = true;
  Timer timer;
  int current_x;
  int current_y;
  std::vector<GameObject *> m_gameObjects;
  static CameraSystem * m_instance;
};


#endif