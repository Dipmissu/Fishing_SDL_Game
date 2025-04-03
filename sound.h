// sound.h
#ifndef SOUND_H
#define SOUND_H

#include <SDL_mixer.h>

class Sound {
private:
    bool sound;
    Mix_Chunk* explosionSound;
    Mix_Chunk* grabSound;
    Mix_Chunk* boxSound;
    Mix_Chunk* clickSound;
    Mix_Music* backgroundSound;

public:
    Sound();
    ~Sound();

    void playGrab(bool sound);
    void playExplosion(bool sound);
    void playBox(bool sound);
    void playClick(bool sound);
    void playBackgroundMusic(bool sound);
    //void stopBackgroundMusic();

};

#endif // SOUND_H

