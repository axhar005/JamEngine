#ifndef MOUSE_H
# define MOUSE_H

#include "engineSetup.h"

#define MAXOPA 130

typedef struct EngineMouse {
    Rectangle     box;
    Rectangle     window;
    Color         color = {255, 255, 255, 0};
    Color         back  = {0, 0, 0, 0};
    unsigned char t = 0;
    bool          draw = false;
    void update(void) {
        const Vector2 p = GetMouseDelta();
        this->box.x += p.x;
        this->box.y += p.y;
        this->box.width  = 3;
        this->box.height = 3;
        this->window.x = this->box.x;
        this->window.y = this->box.y - this->window.height;
        if (draw && t < MAXOPA) { t +=  1; }
        if (!draw && t > 0)     { t += -1; }
        color = {255, 255, 255, t};
        back = {0, 0, 0, t};
    };
    void setWindowSize(Vector2 size) {
        window.width  = size.x;
        window.height = size.y;
    };
    void drawWindow(void) {
        if (t) {
            const int ofset = 4;
            const Rectangle outline = {
                this->window.x -ofset,
                this->window.y -ofset,
                this->window.width +  (ofset * 2),
                this->window.height + (ofset * 2)};
            DrawRectangleRec(outline, back);
            DrawRectangleRec(window, color);
        }
    }
} EngineMouse;


#endif