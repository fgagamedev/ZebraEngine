#ifndef __NAKED_MAN_SCRIPT__
#define __NAKED_MAN_SCRIPT__

#include "Components/Animator.h"
#include "Components/Script.h"
#include "Components/UIText.h"
#include "Customs/PlayerAttackScript.h"
#include "Customs/HitScript.h"
#include "Engine/InputSystem.h"
#include "Engine/SceneManager.h"
#include "Engine/CameraSystem.h"
#include "Components/RectangleCollider.h"
#include "Engine/GameController.h"

class NakedManScript : public Script {
public:
  NakedManScript(GameObject *owner);
  std::string GetComponentName() override { return "NakedManScript"; };
  void FixedComponentUpdate() override;
  void Start() override;
  char GetMovement() { return movements; };

  
  int bulletNumber = 10;
protected:
  void ComponentUpdate() override;

private:
  void SetDirection();
  void CreateAnimations();

  void WallCollisionResolution();

  void GameCollisionCheck(); 
  void StartFirstBoss();

  //Player Movements
  void Movements(); 

  bool zoom = true;


  InputSystem *input = nullptr;
  GameController* gamecontroller = nullptr;
  Animator *animator = nullptr;
  Vector *position = nullptr;
  float walkSpeed = 15;
  float fixedWalkSpeed = 15;
  int movements=0; //1=UP,2=DOWN,3=LEFT,4=RIGHT,5=UP LEFT.6=UP RIGHT,7=DOWN LEFT,8=DOWN RIGHT
  int deadzone_x = EngineGlobals::screen_width / 2;
  int deadzone_y = EngineGlobals::screen_height / 2;
  int lastDirection=1;
  int playerprevious=0;
  Vector playerprevious_vec;
  RectangleCollider* nakedManCollider = nullptr;

  int m_hitFrames = 0;
  bool m_hitFrameController = false;

  bool cameraLock=true;
  bool isMovingLooking=true;
  static bool isZooming;
  std::pair<int, int> mousePosition;




};

#endif
