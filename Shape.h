#ifndef SHAPE_H
#define SHAPE_H

#include "Color.h"

class Shape{
protected:
    float x;
    float y;
    bool selected;
    Color color;

public:
    virtual void draw() = 0;
    virtual bool contains(float, float) = 0;

    void setCurrentColor(Color color){
        this->color = color;
    }

    void select(){
        selected = true;
    }

    void deselect(){
        selected = false;
    }

    bool isSelected(){
        return selected;
    }

    void setX(float x){
        this->x = x;
    }

    void setY(float y){
        this->y = y;
    }

    float getX(){
        return x;
    }

    float getY(){
        return y;
    }

    virtual ~Shape(){}

};

#endif