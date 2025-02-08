// Classe principale de l'application.

#pragma once

#include "../Controller.hpp"
#include "../Controller2D.hpp"
#include "image.hpp"
#include "ofMain.h"

using namespace plugin;

class Application : public ofBaseApp {
public:
    /**
     * @brief fonction d'initialisation de l'application
     *
     */
    void setup();

    /**
     * @brief fonction de mise à jour de la logique de l'application
     *
     */
    void update();

    /**
     * @brief fonction de mise à jour du rendu de la fenêtre d'affichage de l'application
     *
     */
    void draw();

    /**
     * @brief fonction appelée juste avant de quitter l'application
     *
     */
    void exit();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);

private:
    Controller2D controller2D;
    //Controller3D controller3D;
    Controller *currentController;

    /*
    Vestige de l'histogramme.
    Une fois l'histogramme bien implémenté je vais retirer ça.

    ofImage _image;
    image::Histogram _histogram;
    bool _is_histogram_drawn = false;
    char _histogram_color = 'r';
    */
};
