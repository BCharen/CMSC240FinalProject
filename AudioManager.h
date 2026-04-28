#ifndef audioMan_h
#define audioMan_h
#include <vector>
#include <iostream>
#include <raylib.h>
using namespace std;
class AudioManager{
    private:
    Sound level1Song; 
    Sound level2Song;
    Sound level3Song;
    int curSong;
    bool fading;
    float curVolume;
    float fadeSpeed = 0.001;
    public:
    AudioManager();
    void setFading(bool state);
    void Fade();
    Sound* getCurSong();
    void nextSong();
    void unloadAll();
};

#endif