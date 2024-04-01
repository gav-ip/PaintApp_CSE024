#ifndef TOOLBAR_H
#define TOOLBAR_H

#include "Rectangle.h"
#include "Texture.h"

enum Tool {MOUSE, PENCIL, ERASER, FORWARD, BACKWARD, SQUARE, TRIANGLE, CLEAR};

class Toolbar{
    Rectangle area;
    Tool selectedTool;

    Texture mouseButton;
    Texture pencilButton;
    Texture eraserButton;
    Texture forwardButton;
    Texture backwardButton;
    Texture squareButton;
    Texture triangleButton;
    Texture clearButton;

    void delesectAll(){
        mouseButton.selected = false;
        pencilButton.selected = false;
        eraserButton.selected = false;
        forwardButton.selected = false;
        backwardButton.selected = false;
        squareButton.selected = false;
        triangleButton.selected = false;
        clearButton.selected = false;
    }

public:
    Toolbar(){
        area = Rectangle(-1, 1, 0.2, 2, Color(0.8,0.8,0.8));
        mouseButton = Texture("assets/mouse.png", -1, 1, 0.2, 0.2);
        pencilButton = Texture("assets/pencil.png", -1, 0.8, 0.2, 0.2);
        eraserButton = Texture("assets/eraser.png", -1, 0.6, 0.2, 0.2);
        forwardButton = Texture("assets/forwardarrow.png", -1, 0.4, 0.2, 0.2);
        backwardButton = Texture("assets/backarrow.png", -1, 0.2, 0.2, 0.2);
        squareButton = Texture("assets/square.png", -1, 0.0, 0.2, 0.2);
        triangleButton = Texture("assets/triangle.png", -1, -0.2, 0.2, 0.2);
        clearButton = Texture("assets/trash.png", -1, -0.4, 0.2, 0.2);
        selectedTool = PENCIL;
        pencilButton.selected = true;
    }

    void draw(){
        area.draw();
        mouseButton.draw();
        pencilButton.draw();
        eraserButton.draw();
        forwardButton.draw();
        backwardButton.draw();
        squareButton.draw();
        triangleButton.draw();
        clearButton.draw();
    }

    bool contains(float x, float y){
        return area.contains(x, y);
    }

    void handleMouseClick(float x, float y){
        if (mouseButton.contains(x, y)){
            delesectAll();
            mouseButton.selected = true;
            selectedTool = MOUSE;
        }
        else if (pencilButton.contains(x, y)){
            delesectAll();
            pencilButton.selected = true;
            selectedTool = PENCIL;
        }
        else if (eraserButton.contains(x, y)){
            delesectAll();
            eraserButton.selected = true;
            selectedTool = ERASER;
        }
        else if (forwardButton.contains(x, y)){
            delesectAll();
            forwardButton.selected = true;
            selectedTool = FORWARD;
        }
        else if (backwardButton.contains(x, y)){
            delesectAll();
            backwardButton.selected = true;
            selectedTool = BACKWARD;
        }
        else if (squareButton.contains(x, y)){
            delesectAll();
            squareButton.selected = true;
            selectedTool = SQUARE;
        }
        else if (triangleButton.contains(x, y)){
            delesectAll();
            triangleButton.selected = true;
            selectedTool = TRIANGLE;
        }
        else if (clearButton.contains(x, y)){
            delesectAll();
            clearButton.selected = true;
            selectedTool = CLEAR;
        }
    }
    void handleClear(float x, float y){
    }

    Tool getSelectedTool(){
        return selectedTool;
    }

    void selectEraser(){
        delesectAll();
        eraserButton.selected = true;
        selectedTool = ERASER;
    }
};

#endif