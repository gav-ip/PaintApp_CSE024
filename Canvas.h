#ifndef CANVAS_H
#define CANVAS_H

#include "Rectangle.h"
#include "Triangle.h"
#include "Circle.h"
#include "Hexagon.h"
#include "Toolbar.h"
#include "Point.h"
#include "Scribble.h"
#include "Color.h"
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
        //NOTE: unable to remove first or last index because of data leak
        for (int i = selectedShape; i < shapeCounter - 1; i++){
            arr[i] = arr[i + 1];
        }

        shapeCounter--;
    }

    void moveForward(Shape* arr[], int selectedShape){
        //move shape forward, swap index after the selectedShape index
        //DOES NOT ACCOUNT FOR EDGE CASE
        for (int i = selectedShape; i < selectedShape + 1; i++){
            Shape* temp = arr[i];
            arr[i] = arr[i+1];
            arr[i+1] = temp;
        }
    }
    
    void moveBackward(Shape* arr[], int shapeCounter, int selectedShape){
        // move shape backward, swap index after the selectedShape index 
        //DOES NOT ACCOUNT FOR EDGE CASE
        Shape* temp = arr[selectedShape];

        for (int i = selectedShape; i < shapeCounter -1; i++){
            arr[i] = arr[i+1];
        }

        arr[selectedShape - 1] = temp;
    }
    void handleMouseClick(float x, float y, Tool selectedTool, Color color){

        //NOTE: Must click on canvas to initiate each tool
        if (selectedTool == PENCIL){
            shapes[shapeCounter] = new Scribble();
            shapeCounter++;
            ((Scribble*)shapes[shapeCounter-1])->addPoint(x, y, color);
        }

        else if (selectedTool == ERASER){
            /*ERASER TOOL:
            if a shape contains mouse when left clicked remove that shape
            or scribble*/
            if (selectedShape != -1){
                if (selectedShape == 0){std::cout << "Invalid Index, cannot remove first index" << std::endl;}
                else if (selectedShape == shapeCounter){std::cout << "Invalid Index, cannot remove last index" << std::endl;}
                else if(shapes[selectedShape]->isSelected() && shapes[selectedShape]->contains(x,y)){
                    popShape(shapes, shapeCounter, selectedShape);
                }
            }
        }

        else if (selectedTool == FORWARD){
            if (selectedShape != -1){
                if (shapes[selectedShape]->isSelected() && shapes[selectedShape]->contains(x,y)){
                    moveForward(shapes, selectedShape);
                }
            }
        }

        else if (selectedTool == BACKWARD){
            if (selectedShape != -1){
                if (shapes[selectedShape]->isSelected() && shapes[selectedShape]->contains(x,y)){
                    moveForward(shapes, selectedShape);
                }
            }
        }

        else if (selectedTool == SQUARE){
            shapes[shapeCounter] = new Rectangle(x, y, 0.3, 0.3, color);
            shapeCounter++;
        }

        else if (selectedTool == TRIANGLE){
            shapes[shapeCounter] = new Triangle(x, y, 0.3, 0.3, color);
            shapeCounter++;
        }
        else if (selectedTool == CIRCLE){
            shapes[shapeCounter] = new Circle(x, y, 0.3, color);
            shapeCounter++;
        }
        else if (selectedTool == HEXAGON){
            shapes[shapeCounter] = new Hexagon(x, y, 0.3, color);
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

        else if (selectedTool == CLEAR){
            shapeCounter = 0;
        }
        
    }

    void handleMouseDrag(float x, float y, Tool selectedTool, Color color){
        if (selectedTool == PENCIL){
            ((Scribble*)shapes[shapeCounter-1])->addPoint(x, y, color);
        }
        else if (selectedTool == ERASER){
            //((Scribble*)shapes[shapeCounter-1])->addPoint(x, y, color);
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