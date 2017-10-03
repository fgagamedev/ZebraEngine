/**
    @file UISound.cpp
    @brief Creates and plays sounds during the game.
    @copyright MIT License.
*/

#include "Components/UISound.hpp"

UISound::UISound(GameObject *owner, string message, string audio_path,
                 bool is_music, bool play_on_start)
                 : Component (owner, C_COMMON) {
    m_message = message;
    m_audio_path = audio_path;
    m_is_music = is_music;
    m_play_on_start = play_on_start;
    OnPropertyChange();
}


void UISound::Start() {}

/**
    @brief Avoids the sound to play on start while updating a component.
*/
void UISound::ComponentUpdate() {
    if (m_play_on_start) {
        Play(-1, -1);
        m_play_on_start = false;
    }
}

void UISound::FixedComponentUpdate() {}

/**
    @brief Handles what happens whenever a property changes.
    @details If the audio file is found, it plays, else, an error message is shown.
*/
void UISound::OnPropertyChange() {
    // Check if the audio file is a music or a sound.
    switch (m_is_music) {
    // Loads the music file.
    case true:
        m_music = Mix_LoadMUS(m_audio_path.c_str());
        // Verification.
        if( m_music == NULL ) {
            printf("Failed to load music! SDL_mixer Error: %s\n",
                   Mix_GetError());
        }
        break;

    // Loads the sound effect file.
    case false:
        m_sound = Mix_LoadWAV(m_audio_path.c_str());
        // Verification.
        if (m_sound == NULL) {
            printf("Failed to load sound effect! SDL_mixer Error: %s\n",
                   Mix_GetError());
        }
        break;
    }
}

/**
    @brief Play a audio file, with or without loop.
    @param loops.
    @param channel.
*/
void UISound::Play(int loops, int channel) {
    // Plays the music.
    if (m_is_music) {
        Mix_PlayMusic(m_music, loops);

    // Plays the sound effect.
    } else {
        Mix_PlayChannel(channel, m_sound, loops);
    }
}

/**
    @brief Stops the sound either if it's a music or not.
    @param channel.
*/
void UISound::Stop(int channel) {
    // Stops the music.
    if (m_is_music) {
        Mix_HaltMusic();
    // Stops the sound effect.
    } else {
        Mix_HaltChannel(channel);
    }
}

/**
    @brief Pauses the sound either if it's a music or not.
    @param channel.
*/
void UISound::Pause(int channel) {
    // Pauses the music.
    if (m_is_music) {
        Mix_PauseMusic();
    // Pauses the sound effect.
    } else {
        Mix_Pause(channel);
    }
}
