// sound.cpp
#include "sound.h"

Sound::Sound(){
    //timeSound = Mix_LoadWAV("sound/time.wav");
    //coinSound = Mix_LoadWAV("sound/coin.wav");
    //grabBackSound = Mix_LoadWAV("sound/grabback.wav");
    grabSound = Mix_LoadWAV("sound/grab.wav");
    explosionSound = Mix_LoadWAV("sound/explosion.wav");
    backgroundSound = Mix_LoadMUS("sound/background.mp3");
}

Sound::~Sound(){
    //Mix_FreeChunk(timeSound);
    //Mix_FreeChunk(coinSound);
    //Mix_FreeChunk(grabBackSound);
    Mix_FreeChunk(grabSound);
    Mix_FreeChunk(explosionSound);
    Mix_FreeMusic(backgroundSound);
    Mix_CloseAudio();
}

/*Sound::playCoin(bool sound){
    if(sound) Mix_PlayChannel(-1, coinSound, 0);
}*/

void Sound::playExplosion(bool sound){
    if(sound) Mix_PlayChannel(-1, explosionSound, 0);
}

void Sound::playGrab(bool sound){
    if(sound) Mix_PlayChannel(-1, grabSound, 0);
}

void Sound::playBackgroundMusic(bool sound){
    if(sound) Mix_PlayMusic(backgroundSound, -1);
}
