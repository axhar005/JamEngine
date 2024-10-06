#ifndef MOUSE_H
# define MOUSE_H

#include "engineSetup.h"

#define MAXOPA 160

typedef struct EngineMouse {
    private:
        std::string text;
    public:
        Rectangle     box;
        Rectangle     window;
        Color         color = {255, 255, 255, 0};
        Color         back  = {0, 0, 0, 0};
        int           t = 0;
        bool          draw = true;
        void update(void) {
            const Vector2 p = GetMouseDelta();
            this->box.x += p.x;
            this->box.y += p.y;
            this->window.x = this->box.x;
            this->window.y = this->box.y - this->window.height;
            if (draw && t < MAXOPA) {
                t +=  4;
                if (t > 255) {
                    t = 255;
                    }
            }
            if (!draw && t > 0) {
                t += -6;
                if (t < 0) {
                    t = 0;
                    }
            }
            color = {255, 255, 255, (unsigned char)t};
            back = {0, 0, 0, (unsigned char)t};
        };
        void setWindowSize(Vector2 size) {
            window.width  = size.x;
            window.height = size.y;
        };
        void drawWindow(void) {
            const int ofset = 4;
            const Rectangle outline = {
                this->window.x -ofset,
                this->window.y -ofset,
                this->window.width +  (ofset * 2),
                this->window.height + (ofset * 2)};
            DrawRectangleRec(outline, back);
            DrawRectangleRec(window, color);
            DrawText(this->text.c_str(), this->window.x + 2, this->window.y, 20, back);
        }
        void setText(const std::string& s) {
            this->text = s;
            Vector2 newVec;
            newVec.x = 10;
            newVec.y = 0;
            float localW = 0;
            for (size_t i = 0; i < s.size(); i++) {
                if (s[i] == ' ')
                    localW += 6;
                else
                    localW += 12;
                if (s[i] == '\n') {
                    if (localW > newVec.y)
                        newVec.x = localW;
                    localW = 0;
                    newVec.y += 22;
                }
            }
            if (localW && newVec.x == 0)
                newVec.x = localW;
            this->setWindowSize(newVec);
        }
} EngineMouse;


#endif