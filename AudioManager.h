#ifndef audioMan_h
#define audioMan_h
#include <vector>
#include <iostream>
#include <raylib.h>
using namespace std;
class AudioManager{
    private:
    vector<const char*> soundtrack;
    Sound level1Song; 
    int curSong;
    public:
    AudioManager();
    void loadSong(const char *fileName);
    vector<const char*> internalLoadSong(const char* fileName);
    Sound* getCurSong();
    bool getValidSongs();
    void unloadAll();
};

#endif