/*
** EPITECH PROJECT, 2025
** IFT3100H25_TP1_E10
** File description:
** Classe responsable du rendu de l'application.
*/

#ifndef RENDERER_HPP_
#define RENDERER_HPP_

#include "ofMain.h"

class Renderer {
public:
    Renderer();
    ~Renderer();

    void setup();
    void draw();

protected:
private:
    ofColor _color_background;
    ofColor _color_tint;
    ofColor _color_random;

    ofShader _shader;
};

#endif /* !RENDERER_HPP_ */
