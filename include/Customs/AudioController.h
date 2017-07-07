#ifndef AUDIO_CONTROLLER_H
#define AUDIO_CONTROLLER_H

#include <Engine/GameObject.h>
#include <Globals/EngineGlobals.h>
#include "Customs/FirstBossAttackScript.h"
#include <stdlib.h>
#include <time.h>
#include <Engine/SceneManager.h>
#include <Engine/Timer.h>
#include <Customs/PlayerScript.h>
#include <Components/UISound.h>

class AudioController {
public:
  static AudioController *GetInstance();

  void StartBossFight();
  void EndBossFight();
  
  /*Add*/
  void AddAudio(UISound *sound);
 
  /*Play*/
  void PlayAudio(string name, int loops);
  
  /*Stop*/
  void StopAudio(string name);
  
  /*Pause*/
  void PauseAudio(string name);
  
private:
  AudioController();
  static AudioController *m_instance;
  
  //Objects
  std::vector<UISound *> m_sounds;
  

  
};

#endif
