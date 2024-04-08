#ifndef HEXAGON_H
#define HEXAGON_H

#include <GL/freeglut.h>
#include <cmath>
#include "Shape.h"

class Hexagon : public Shape {
    float size;

public:
    Hexagon() {
        x = 0.0f;
        y = 0.0f;
        size = 0.1f;
        selected = false;
    }

    Hexagon(float x, float y, float size, Color color) {
        this->x = x;
        this->y = y;
        this->size = size;
        this->color = color;
        selected = false;
    }

    //getters
    float getS() {
        return size;
    }
    Color getColor() {
        return color;
    }

    //setters
    void setS(float size) {
        this->size = size;
    }
    void setColor(Color color) {
        this->color = color;
    }

    void draw() {
        glColor3f(color.getR(), color.getG(), color.getB());
        glBegin(GL_POLYGON);
        for (int i = 0; i < 6; ++i) {
            glVertex2f(x + size * cos(i * M_PI / 3), y + size * sin(i * M_PI / 3));
        }
        glEnd();

        if (selected) {
            Hexagon outer(x, y, size - 0.04f, Color(1.0f, 1.0f, 1.0f));
            Hexagon inner(x, y, size - 0.08f, color);
            outer.draw();
            inner.draw();
        }
    }


    bool contains(float mx, float my) {
        float dx = mx - x;
        float dy = my - y;
        float dist = sqrt(dx * dx + dy * dy);
        return dist <= size;
    }

};
#endif