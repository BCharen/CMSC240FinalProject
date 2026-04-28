#include "AudioManager.h"

AudioManager::AudioManager(){
    InitAudioDevice();
    SetMasterVolume(0.3);
    level1Song = LoadSound("stage1.wav");
    level2Song = LoadSound("stage2.wav");
    level3Song = LoadSound("stage3.wav");
    curSong = 0;
}

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

void AudioManager::nextSong(){
    curSong = (curSong + 1) % 3; 
}

void AudioManager::unloadAll(){
    cout << "unloading songs" << endl;
    CloseAudioDevice();
}
