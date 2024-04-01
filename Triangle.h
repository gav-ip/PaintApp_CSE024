#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <GL/freeglut.h>
#include "Color.h"
#include "Shape.h"


class Triangle : public Shape{

    float w;
    float h;
    Color color;

public:
    Triangle() {
        x = 0.0f;
        y = 0.0f;
        w = 0.4f;
        h = 0.2f;
        selected = false;
    }

    Triangle(float x, float y, float w, float h, Color color) {
        this->x = x;
        this->y = y;
        this->w = w;
        this->h = h;
        this->color = color;
        selected = false;
    }

    void draw() {
        glColor3f(color.getR(), color.getG(), color.getB());
        glBegin(GL_POLYGON);
            glVertex2f(x, y);
            glVertex2f(x - w, y - h);
            glVertex2f(x + w, y - h);
            // glVertex2f(x, y - h);
        glEnd();

        if (selected) {
            Triangle outer(x, y , w , h, Color(0.5f, 0.5f, 0.5f));
            Triangle inner(x, y- 0.025, w- 0.04, h- 0.04, color);
            outer.draw();
            inner.draw();
        }
    }


    bool contains(float mx, float my) {
        if (mx >= x - w && mx <= x + w && my <= y && my >= y - h) {
            return true;
        } else {
            return false;
        }
    }

    void setColor(Color color){
        this->color = color;
    }

    void setW(float w){
        this->w = w;
    }

    void setH(float h){
        this->h = h; 
    }

    float getW(){
        return w;
    }

    float getH(){
        return h;
    }
    
};

#endif