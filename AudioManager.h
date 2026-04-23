#ifndef audioMan_h
#define audioMan_h
#include <vector>
#include <iostream>
#include <raylib.h>
using namespace std;
class AudioManager{
    private:
    vector<Music> soundtrack;
    int curSong;
    bool validSongs;
    public:
    void loadSong(const char *fileName);
    Music getCurSong();
    bool getValidSongs();
};

#endif