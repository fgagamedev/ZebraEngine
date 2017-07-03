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
  PositAllTentacles();
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

void FirstBossController::PositAllTentacles() { 
  for (auto tentacle : m_tentacles) {
      Vector *position = m_player->GetPosition();
      tentacle->SetPosition(Vector(position->m_x + 30, position->m_y - 30));
  }
} 

void FirstBossController::PositTentacle(int index) { 

      Vector *position = m_player->GetPosition();
      m_tentacles[index]->SetPosition(Vector(position->m_x , position->m_y - 250));
  
} 

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

void FirstBossController::FirstAttack() {
    cout << "FirstAttack" << endl;
    if(actualTentacle == 4)
      actualTentacle = 1;

    m_tentacles[actualTentacle]->ClearCollisions();
    m_tentacles[actualTentacle]->active = true;
    PositTentacle(actualTentacle);
    auto firstBossAttackScript = (FirstBossAttackScript*)m_tentacles[actualTentacle]->GetComponent("FirstBossAttackScript");
    firstBossAttackScript->attack = true;
/*
      auto script = (ScoreScript*)SceneManager::GetInstance()
                   ->GetScene("Gameplay")
                   ->GetGameObject("Score")
                   ->GetComponent("ScoreScript");
                   script->SetScore(0);

                   */
    actualTentacle++;

     //animator = (Animator *)GetOwner()->GetComponent("Animator");
}

void FirstBossController::SecondAttack() {
    
}

/*

GameObject *FirstBossController::GetRandomTentacle() {
  srand(time(NULL));
  int tentacleIndex = rand() % 3;
  return m_tentacles[tentacleIndex];
}

*/