#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/freeglut.h>
#include <GL/gl.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <iostream>

struct Texture {
    std::string imagePath;
    float x;
    float y;
    float w;
    float h;
    bool selected;
    
    unsigned char* imageData;
    int imageWidth;
    int imageHeight;
    int bitdepth;
    GLuint texture;

    Texture() {
        //
    }

    Texture(std::string imagePath, float x, float y, float w, float h) {
        this->imagePath = imagePath;
        this->x = x;
        this->y = y;
        this->w = w;
        this->h = h;
        selected = false;
        loadTexture();
    }

    void loadTexture() {
        stbi_set_flip_vertically_on_load(true);
        imageData = stbi_load(imagePath.c_str(), &imageWidth, &imageHeight, &bitdepth, STBI_rgb_alpha);
        if (imageData == NULL) {
            std::cerr << "Failed to load texture file" << std::endl;
        } else {
            std::cout << "Texture file loaded successfully" << std::endl;
        }

        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
    }

    void draw() {
        if (selected) {
            glColor3f(1.0f, 1.0f, 1.0f);
        } else {
            glColor3f(0.8f, 0.8f, 0.8f);
        }
        
        glBegin(GL_POLYGON);
            glVertex2f(x, y - h);
            glVertex2f(x, y);
            glVertex2f(x + w, y);
            glVertex2f(x + w, y - h);
        glEnd();

        glLineWidth(1);
        glColor3f(0.0f, 0.0f, 0.0f);
        glBegin(GL_LINES);
            glVertex2f(x, y - h);
            glVertex2f(x, y);

            glVertex2f(x, y);
            glVertex2f(x + w, y);

            glVertex2f(x + w, y);
            glVertex2f(x + w, y - h);

            glVertex2f(x + w, y - h);
            glVertex2f(x, y - h);
        glEnd();

        // Display texture
        glColor3f(1.0f, 1.0f, 1.0f);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture);

        // Map texture to polygon
        glBegin(GL_POLYGON);
            // bottom left corner
            glTexCoord2f(0.0f, 0.0f); 
            glVertex2f(x, y - h);

            // top left corner
            glTexCoord2f(0.0f, 1.0f); 
            glVertex2f(x, y);

            // top right corner
            glTexCoord2f(1.0f, 1.0f); 
            glVertex2f(x + w, y);

            // bottom right corner
            glTexCoord2f(1.0f, 0.0f); 
            glVertex2f(x + w, y - h);
        glEnd();
        glDisable(GL_TEXTURE_2D);
    }

    bool contains(float mx, float my) {
        if (mx >= x && mx <= x + w && my <= y && my >= y - h) {
            return true;
        } else {
            return false;
        }
    }
};

#endif