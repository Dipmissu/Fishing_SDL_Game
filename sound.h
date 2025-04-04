// sound.h
#ifndef SOUND_H
#define SOUND_H

#include <SDL.h>
#include <SDL_mixer.h>
#include "texturemanager.h"

class Sound {
private:
    bool sound;
    int soundVolume;
    int musicVolume;
    Mix_Chunk* boxSound;
    Mix_Chunk* grabSound;
    Mix_Chunk* clickSound;
    Mix_Chunk* explosionSound;
    Mix_Music* backgroundSound;

public:
    Sound();
    ~Sound();
    void settingSound(int value);
    void settingMusic(int value);
    void render(SDL_Renderer* renderer);
    void playGrab(bool sound);
    void playExplosion(bool sound);
    void playBox(bool sound);
    void playClick(bool sound);
    void playBackgroundMusic(bool sound);
    //void stopBackgroundMusic();

};

#endif // SOUND_H

