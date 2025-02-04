/*
** EPITECH PROJECT, 2025
** IFT3100H25_TP1_E10
** File description:
** Renderer
*/

#include "Renderer.hpp"

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

void Renderer::setup()
{
  // fréquence de rafraîchissement du rendu de la fenêtre d'affichage par seconde
  ofSetFrameRate(60);

  // résolution de la fenêtre d'affichage en fonction de l'image
  ofSetWindowShape(512, 512);

  // configurer le niveau de précision des ellipse
  ofSetCircleResolution(64);

  // chargement du code source des shaders
  _shader.load(
    "flat_tint_330_vs.glsl",
    "flat_tint_330_fs.glsl");

  // sélectionner une nouvelle couleur au hasard
  //select_random_colors();
}

void Renderer::draw()
{
  // effacer la fenêtre d'affichage et remplir avec la couleur d'arrière-plan
  ofClear(_color_background.r, _color_background.g, _color_background.b);

  // activer le shader
  _shader.begin();

  // passer la couleur de la teinte RGBA au shader sous forme d'un attribut uniforme (avec composantes normalisées)
  _shader.setUniform4f("tint", _color_tint.r / 255.0f, _color_tint.g / 255.0f, _color_tint.b / 255.0f, 1.0f);

  // dessiner 2 lignes à partir des coins de la fenêtre d'affichage
  ofDrawLine(0.0f, 0.0f, ofGetWidth(), ofGetHeight());
  ofDrawLine(0.0f, ofGetHeight(), ofGetWidth(), 0.0f);

  // activer la zone de remplissage
  ofFill();

  // dessiner une ellipse
  ofDrawEllipse(ofGetWidth() / 2.0f, ofGetHeight() / 2.0f, ofGetWidth() / 8.0f, ofGetHeight() / 8.0f);

  // désactiver la zone de remplissage
  ofNoFill();

  // dessiner un rectangle
  ofDrawRectangle(ofGetWidth() / 4.0f, ofGetHeight() / 4.0f, ofGetWidth() / 2.0f, ofGetHeight() / 2.0f);

  // désactiver le shader
  _shader.end();
}
