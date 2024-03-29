#ifndef COLOR_SELECTOR_H
#define COLOR_SELECTOR_H

#include "Rectangle.h"
#include "Circle.h"
#include "Color.h"
#include <iostream>
#include <string.h>

struct ColorSelector {
private:
    Rectangle area;
    Rectangle resultColor;
    Rectangle redAxis;
    Rectangle greenAxis;
    Rectangle blueAxis;
    
    Circle redButton;
    Circle greenButton;
    Circle blueButton;

    float redValue;
    float blueValue;
    float greenValue;

    Color currentColor;

public:
    ColorSelector(){
        area = Rectangle(-0.8f, -0.70f, 1.8f, 0.3f, Color(0.3f, 0.3f, 0.3f));
        resultColor = Rectangle(-0.2f, -0.73f, 0.1f, 0.25f, currentColor);
        redButton = Circle(-0.75f, -0.75f, 0.03f, Color (1.0f, 0.0f, 0.0f));
        greenButton = Circle(-0.75f, -0.85f, 0.03f, Color (0.0f, 1.0f, 0.0f));
        blueButton = Circle(-0.75f, -0.95f, 0.03f, Color (0.0f, 0.0f, 1.0f));
        redAxis = Rectangle(-0.75f, -0.74f, 0.5f, 0.03f, Color(0.7f, 0.7f, 0.7f));
        greenAxis = Rectangle(-0.75f, -0.84f, 0.5f, 0.03f, Color(0.7f, 0.7f, 0.7f));
        blueAxis = Rectangle(-0.75f, -0.94f, 0.5f, 0.03f, Color(0.7f, 0.7f, 0.7f));
    }

    Color getCurrentColor(){
        return currentColor;
    }
    void setCurrentColor(float r, float g, float b){
        currentColor = Color(r, g, b);
    }

    void handleMouseClick(float x, float y){
        // use the x position to determine an rgb value 0.0 - 1.0
        // total length of axis = 1.4
        // y represents the value multiplied to get the rgb value
        // 0.5y = 1.0 
        // y = 2
        float length = 1.0 / (redAxis.getW());

        //get max x value
        float xMax = (redAxis.getX()) + (redAxis.getW());

        // (max x-value)[-0.25] * 2  = -0.5 ... this is the value we need to equal 1.0
        // rgb value = [-0.5 + length] (gets the rgb value roughly to 1.0)
        float rgbAdd = (xMax * length) + length;

        
        if (redButton.contains(x,y) && redAxis.contains(x,y)){
            redButton.setX(x);
            redValue = (x * length) + rgbAdd;
            setCurrentColor(redValue,greenValue,blueValue);
            resultColor.setColor(currentColor);
            // calculate the rgb value (0-255):
            // redDisplay = floatredValue * 255
        }

        if (greenButton.contains(x,y) && greenAxis.contains(x,y)){
            greenButton.setX(x);
            greenValue = (x * length) + rgbAdd;
            setCurrentColor(redValue,greenValue,blueValue);
            resultColor.setColor(currentColor);
        }

        if (blueButton.contains(x,y) && blueAxis.contains(x,y)){
            blueButton.setX(x);
            blueValue = (x * length) + rgbAdd;
            setCurrentColor(redValue,greenValue,blueValue);
            resultColor.setColor(currentColor);
        }
    }

    void draw(){
        area.draw();
        resultColor.draw();
        redAxis.draw();
        greenAxis.draw();
        blueAxis.draw();
        redButton.draw();
        greenButton.draw();
        blueButton.draw();
    }

    bool contains(float x, float y){
        return area.contains(x, y);
    }
};
#endif