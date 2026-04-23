#include "AudioManager.h"

void AudioManager::loadSong(const char *fileName){
    Music newSong = LoadMusicStream(fileName);
    if(IsMusicValid(newSong)){
        cerr << "valid" << endl;
        soundtrack.push_back(newSong);
        validSongs=true;
    }
    else {
        cerr << fileName << endl;
        UnloadMusicStream(newSong);
    }

}  

Music AudioManager::getCurSong(){
    return soundtrack.at(curSong);
}
    
bool AudioManager::getValidSongs(){
    return validSongs;
}
