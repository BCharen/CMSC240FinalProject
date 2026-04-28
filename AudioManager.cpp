#include "AudioManager.h"

/**
 * @brief Constructor for an AudioManager with all of the level songs
 */
AudioManager::AudioManager(){
    InitAudioDevice();
    SetMasterVolume(0.3);
    level1Song = LoadSound("audio/stage1.wav");
    level2Song = LoadSound("audio/stage2.wav");
    level3Song = LoadSound("audio/stage3.wav");
    curSong = 0;
}

/**
 * @brief Getter for the current song
 * @return returns a pointer to the current song
 */
Sound* AudioManager::getCurSong(){
    switch (curSong)
    {
        case 0:
            return &level1Song;
    
        case 1:
            return &level2Song;
    
        case 2:
            return &level3Song;

        default:
        return &level1Song;
        break;
    }
}

/**
 * @brief switches the song to the next song
 */
void AudioManager::nextSong(){
    
    curSong = (curSong + 1) % 3; 
}

/**
 * @brief unloads all audio
 */
void AudioManager::unloadAll(){
    cout << "unloading songs" << endl;
    UnloadSound(level1Song);
    UnloadSound(level2Song);
    UnloadSound(level3Song);
    CloseAudioDevice();
}
