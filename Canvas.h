#ifndef CANVAS_H
#define CANVAS_H

#include "Rectangle.h"
#include "Toolbar.h"
#include "Point.h"
#include "Scribble.h"
#include <iostream>

struct Canvas{
    Rectangle area;

    float offsetX;
    float offsetY;

    Shape* shapes[1000];
    int shapeCounter;
    int selectedShape;

    Canvas(){
        area = Rectangle(-0.8, 1, 1.8, 1.7, Color(1,1,1));
        shapeCounter = 0;
        selectedShape = -1;
        offsetX = 0;
        offsetY = 0;
    }

    void draw(){
        area.draw();

        for (int i = 0; i < shapeCounter; i++){
            shapes[i]->draw();
        }
    }

    void popShape(Shape* arr[], int shapeCounter, int selectedShape){
        if (selectedShape < 0 || selectedShape >= shapeCounter){
            std::cout << "Invalid Index" << std::endl;
            return;
        }
        
        for (int i = selectedShape; i < shapeCounter - 1; i++){
            arr[i] = arr[i + 1];
        }

        shapeCounter--;

    }
    void handleMouseClick(float x, float y, Tool selectedTool, Color color){
        if (selectedTool == PENCIL){
            shapes[shapeCounter] = new Scribble();
            shapeCounter++;
            ((Scribble*)shapes[shapeCounter-1])->addPoint(x, y, color);
        }
        /*ERASER TOOL:
            if a shape contains mouse when left clicked remove that shape
            or scribble*/
        else if (selectedTool == ERASER){
            if (shapes[selectedShape]->isSelected() && shapes[selectedShape]->contains(x,y)){
                popShape(shapes, shapeCounter, selectedShape);
            }
        }
        else if (selectedTool == SQUARE){
            shapes[shapeCounter] = new Rectangle(x, y, 0.3, 0.3, color);
            shapeCounter++;
        }
        else if (selectedTool == MOUSE){
            for (int i = 0; i < shapeCounter; i++){
                shapes[i]->deselect();
            }
            selectedShape = -1;

            for (int i = shapeCounter - 1; i >= 0; i--){
                if (shapes[i]->contains(x,y)){
                    shapes[i]->select();
                    selectedShape = i;
                    offsetX = x - shapes[i]->getX();
                    offsetY = shapes[i]->getY() - y;
                    break;
                }
            }
        }
    }

    void handleMouseDrag(float x, float y, Tool selectedTool, Color color){
        if (selectedTool == PENCIL){
            ((Scribble*)shapes[shapeCounter-1])->addPoint(x, y, color);
        }
        else if (selectedTool == ERASER){
                
        }
        else if (selectedTool == MOUSE){
            if (selectedShape != -1){
                shapes[selectedShape]->setX(x - offsetX);
                shapes[selectedShape]->setY(y + offsetY);
            }
        }
    }

    

    bool contains(float x, float y){
        return area.contains(x, y);
    }
};

#endif