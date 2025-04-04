// sound.cpp
#include "sound.h"

Sound::Sound():
    soundVolume(64),
    musicVolume(64){
    boxSound = Mix_LoadWAV("sound/box.wav");
    grabSound = Mix_LoadWAV("sound/grab.wav");
    clickSound = Mix_LoadWAV("sound/click.wav");
    explosionSound = Mix_LoadWAV("sound/explosion.wav");
    backgroundSound = Mix_LoadMUS("sound/background.mp3");
}

Sound::~Sound(){
    Mix_FreeChunk(boxSound);
    Mix_FreeChunk(grabSound);
    Mix_FreeChunk(clickSound);
    Mix_FreeChunk(explosionSound);
    Mix_FreeMusic(backgroundSound);
    Mix_CloseAudio();
}

void Sound::settingSound(int value) {
    soundVolume = value;
    if(soundVolume == 0) {
        Mix_HaltChannel(-1);
    } else {
        Mix_Volume(-1, soundVolume);
    }
}

void Sound::settingMusic(int value) {
    musicVolume = value;
    Mix_VolumeMusic(musicVolume);
}

void Sound::playBox(bool sound){
    if(sound) Mix_PlayChannel(-1, boxSound, 0);
}

void Sound::playClick(bool sound){
    if(sound) Mix_PlayChannel(-1, clickSound, 0);
}

void Sound::playExplosion(bool sound){
    if(sound) Mix_PlayChannel(-1, explosionSound, 0);
}

void Sound::playGrab(bool sound){
    if(sound) Mix_PlayChannel(-1, grabSound, 0);
}

void Sound::playBackgroundMusic(bool sound){
    if(sound) Mix_PlayMusic(backgroundSound, -1);
}

