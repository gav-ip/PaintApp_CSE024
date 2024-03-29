#ifndef POINT_H
#define POINT_H

#include <GL/freeglut.h>
#include <GL/gl.h>
#include "Color.h"

class Point {
    float x;
    float y;
    Color color;
    int thickness;

public:
    Point() {
        x = 0.0f;
        y = 0.0f;
        thickness = 10;
    }

    Point(float x, float y, Color color) {
        this->x = x;
        this->y = y;
        this->color = color;
        thickness = 10;
    }

    Point(float x, float y, Color color, int thickness) {
        this->x = x;
        this->y = y;
        this->color = color;
        this->thickness = thickness;
    }

    void draw() {
        glColor3f(color.getR(), color.getG(), color.getB());
        glPointSize(thickness);
        glBegin(GL_POINTS);
            glVertex2f(x, y);
        glEnd();
    }

    // Getter functions
    float getX(){
        return x;
    }
    float getY(){
        return y;
    }

    Color getColor(){
        return color;
    }

    int getThickness(){
        return thickness;
    }

    // Setters
    void setX(float x){
        this->x = x;
    }

    void setY(float y){
        this->y = y;
    }

    void setColor(Color color){
        this->color = color;
    }

    void setThickness(int thickness){
        this->thickness = thickness;
    }
};


#endif