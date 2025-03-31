// sound.h
#pragma once
#include <SDL_mixer.h>

class Sound {
private:
    bool sound;
    Mix_Chunk* explosionSound;
    Mix_Chunk* grabSound;
    //Mix_Chunk* coinSound;
    //Mix_Chunk* timeSound;
    Mix_Music* backgroundSound;

public:
    Sound();
    ~Sound();

    void playGrab(bool sound);
    void playExplosion(bool sound);
    //void playTime(bool sound);
    //void playCoin(bool sound);
    void playBackgroundMusic(bool sound);
    //void stopBackgroundMusic();

};
