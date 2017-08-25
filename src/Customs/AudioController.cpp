#include "Customs/AudioController.hpp"


AudioController *AudioController::m_instance = nullptr;

AudioController *AudioController::GetInstance() { //Singleton class
  if (!m_instance)
    m_instance = new AudioController();

  return m_instance;
}

AudioController::AudioController() {} //Constructor void


/** Add **/
void AudioController::AddAudio(UISound *sound) { m_sounds.push_back(sound); }




/** Play **/
void AudioController::PlayAudio(string name, int loops){
  for (auto sound : m_sounds) {
      if(sound->GetMessage() == name){
        sound->Play(loops, -1);
      }

   }

}

/** Stop **/
void AudioController::StopAudio(string name){
  for (auto sound : m_sounds) {
      if(sound->GetMessage() == name){
        sound->Stop(-1);
      }

   }

}

/** Pause **/
void AudioController::PauseAudio(string name){
  for (auto sound : m_sounds) {
      if(sound->GetMessage() == name){
        sound->Stop(-1);
      }

   }

}





//void FirstBossController::AddInsideBossFx(GameObject *bossInsideFx) {m_bossInsideFx = bossInsideFx; }




