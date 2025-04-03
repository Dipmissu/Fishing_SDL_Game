// hook.h
#ifndef HOOK_H
#define HOOK_H

#include <SDL.h>
#include <string>

using namespace std;

class Hook {
private:
    SDL_Rect g_base;
    SDL_Point g_tip;
    double g_angle;
    bool g_extending;
    double g_length;
    double g_speed;
    bool g_attachedBox;
    bool g_attachedMussel;
    bool g_attachedCreature;
    bool g_movingLeft;
    int g_attachedObjectIndex;
    bool g_returned;

public:
    Hook(int x, int y);
    ~Hook();

    void update();
    void render(SDL_Renderer* renderer);

    void startExtend();
    void startRetract();
    void attachObject(int index, int ObjectSize, string id);
    void detachObject(string id);

    bool isExtending() const { return g_extending; }
    bool isAttachedBox() const {return g_attachedBox; }
    bool isAttachedMussel() const { return g_attachedMussel; }
    bool isAttachedCreature() const { return g_attachedCreature; }
    bool hasReturned() const { return g_returned; }
    int getAttachedObjectIndex() const { return g_attachedObjectIndex; }
    double getAngle() const {return g_angle;}
    SDL_Point getTipPosition() const { return g_tip; }
};

#endif // HOOK_H

