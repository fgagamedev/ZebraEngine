#include "Customs/FirstBossController.h"
#include <Components/UIText.h>
#include <Engine/SceneManager.h>
#include <Engine/Timer.h>
#include <Customs/PlayerScript.h>

FirstBossController *FirstBossController::m_instance = nullptr;

FirstBossController *FirstBossController::GetInstance() { //Singleton class
  if (!m_instance)
    m_instance = new FirstBossController();

  return m_instance;
}

FirstBossController::FirstBossController() {} //Constructor void

void FirstBossController::StartBossFight() {
  
  //PositBoss();
  //->boss resurge animation
  //wait time
  //set player movement free

}
void FirstBossController::EndBossFight() {
    DeactivatePlayer();
    DeactivateTentacles();
    DeactivateBoss();  
}

/*Add*/
void FirstBossController::AddPlayer(GameObject *player) { m_player = player; }

void FirstBossController::AddBoss(GameObject *boss) { m_boss = boss; }

void FirstBossController::AddTentacle(GameObject *tentacle){ m_tentacles.push_back(tentacle); }

/*Posit*/
void FirstBossController::PositPlayer() { m_player->SetPosition(Vector(m_wPos, m_hPos)); }

void FirstBossController::PositBoss() { m_boss->SetPosition(Vector(m_wPos, m_hPos)); }

void FirstBossController::PositTentacle() { 
  for (auto tentacle : m_tentacles) {

      tentacle->SetPosition(Vector(m_wPos, m_hPos));
  }
} //use rand to posit

/*Active*/
void FirstBossController::ActivatePlayer() {
    m_player->ClearCollisions();
    m_player->active = true;
 
}

void FirstBossController::ActivateBoss() {
    m_player->ClearCollisions();
    m_player->active = true;
 
}

void FirstBossController::ActivateTentacles() { 
   for (auto tentacle : m_tentacles) {
      tentacle->ClearCollisions();
      tentacle->active = true;

   }
}

/*Deactive*/
void FirstBossController::DeactivatePlayer() { m_player->active = false; }

void FirstBossController::DeactivateBoss() { m_boss->active = false; }

void FirstBossController::DeactivateTentacles() {
  for (auto tentacle : m_tentacles)
    tentacle->active = false;
}

void FirstBossController::DeactivateTentacle(int tentacleIndex) {
    m_tentacles[tentacleIndex]->active = false;
}

std::pair <int, int> FirstBossController::GetRandomPosition() {
  srand(time(NULL));
  
  randomPosition.first = rand();
  randomPosition.second = rand();

  return randomPosition;
}

/*

GameObject *FirstBossController::GetRandomTentacle() {
  srand(time(NULL));
  int tentacleIndex = rand() % 3;
  return m_tentacles[tentacleIndex];
}

*/