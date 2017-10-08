#include "Customs/AudioController.hpp"

/**
    @file AudioController.cpp
    @brief Methods that manages all game's audio.
    @copyright LGPL. MIT License.
*/

AudioController *AudioController::m_instance = nullptr;

/**
    @brief Checking the current game's audio state.
    @return m_instance.
*/
AudioController *AudioController::GetInstance() {
    // Singleton class

    // If the m_instance is not initialized, intializes it.
    if (!m_instance){
        m_instance = new AudioController();
    }
return m_instance;
}

//Constructor void
AudioController::AudioController() {
}

/**
    @brief Initializes a sound object.
    @param[in] sound - the UI sound component.
*/
void AudioController::AddAudio(UISound *sound) {
    // Add
    m_sounds.push_back(sound);
}

/**
    @brief Plays pre existent sounds.
    @param[in] sound - the name of the sound component.
    @param[in] loops - the number of times that the audio will play.
*/
void AudioController::PlayAudio(string name, int loops){
    // Play
    for (auto sound : m_sounds) {
        /*
        If the message is correspondent to the sound component name, plays
        the sound.
        */
        if(sound->GetMessage() == name) {
            sound->Play(loops, -1);
        }
    }
}

/**
    @brief Stops a current playing sound.
    @param[in] sound - the name of the sound component.
*/
void AudioController::StopAudio(string name){
    // Stop
    for (auto sound : m_sounds) {
        /*
        If the message is correspondent to the sound component name, stops
        the sound.
        */
        if(sound->GetMessage() == name) {
            sound->Stop(-1);
        }
    }

}

/**
    @brief Pause a current playing sound.
    @param[in] sound - the name of the sound component.
*/
void AudioController::PauseAudio(string name){
    // Pause
    for (auto sound : m_sounds) {
        /*
        If the message is correspondent to the sound component name, stops
        the sound.
        */
        if(sound->GetMessage() == name){
            sound->Stop(-1);
        }
    }
}
