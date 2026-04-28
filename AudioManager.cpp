#include "AudioManager.h"

AudioManager::AudioManager(){
    InitAudioDevice();
    SetMasterVolume(0.3);
    level1Song = LoadSound("stage1.wav");
    curSong = 0;
}

void AudioManager::loadSong(const char *fileName){
    soundtrack = internalLoadSong(fileName);
}  

vector<const char*> AudioManager::internalLoadSong(const char*fileName){
    soundtrack.push_back(fileName);
    return soundtrack;
}

Sound* AudioManager::getCurSong(){
    //cout << soundtrack.empty() << endl;
    return &level1Song;
}
    
bool AudioManager::getValidSongs(){
    return !soundtrack.empty();
}

void AudioManager::unloadAll(){
    cout << "unloading songs" << endl;
    CloseAudioDevice();
}
