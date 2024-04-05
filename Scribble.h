#ifndef SCRIBBLE_H
#define SCRIBBLE_H

#include "Point.h"
#include <GL/gl.h>
#include "Shape.h"

class Scribble : public Shape{
    Point points[5000];
    int pCounter;

    float left;
    float right;
    float top;
    float bottom;


public:
    Scribble(){
        pCounter = 0;
        selected = false;

        left = 0;
        right = 0;
        top = 0;
        bottom = 0;
    }

    void setX(float x){
        this->x = x;
    }

    void setY(float y){
        this->y = y;
    }

    void addPoint(float x, float y, Color color){
        if (pCounter == 0){
            this->x = x;
            this->y = y;
        }

        if (this->x - x > left){
            left = this->x - x;
        }
        if (x - this->x > right){
            right = x - this->x;
        }
        if (y - this->y > top){
            top = y - this->y;
        }
        if (this->y - y > bottom){
            bottom = this->y - y;
        }

        points[pCounter] = Point(x - this->x, y - this->y, color);
        pCounter++;
    }

    void draw(){
        if (selected){
            //Draw bounding box
            glLineWidth(2);
            glColor3f(0.6,0.6,0.6);

            glBegin(GL_LINES);

            glVertex2f(x -left - 0.02, y + top + 0.02);
            glVertex2f(x + right + 0.02, y + top + 0.02);

            glVertex2f(x + right + 0.02, y + top + 0.02);
            glVertex2f(x + right + 0.02, y - bottom - 0.02);

            glVertex2f(x + right + 0.02, y - bottom - 0.02);
            glVertex2f(x - left - 0.02, y - bottom - 0.02);

            glVertex2f(x - left - 0.02, y - bottom - 0.02);
            glVertex2f(x - left - 0.02, y + top + 0.02);

            glEnd();
        }

        for (int i = 0; i < pCounter; i++){
            float currX = x + points[i].getX();
            float currY = y + points[i].getY();
            Color currColor = color;
            Point temp(currX, currY, currColor);
            temp.draw();
        }
    }

    bool contains(float x, float y){
        return x >= this->x - left && x <= this->x + right && y <= this->y + top && y >= this->y - bottom;
    }

};

#endif