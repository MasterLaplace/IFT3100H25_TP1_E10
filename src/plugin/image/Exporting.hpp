/*
** ULAVAL PROJECT, 2025
** IFT3100H25_TP1_E10 [WSL : Ubuntu]
** File description:
** En cours d’exécution, il est possible d’exporter de manière interactive des
** séquences de fichiers images qui correspondent au rendu d’une scène pendant
** un intervalle de temps.
*/

#ifndef EXPORTING_HPP_
#define EXPORTING_HPP_

#include "ofMain.h"

namespace plugin::image {

class Exporting {
public:
    Exporting() = default;
    ~Exporting() = default;

    void setPixels();
    void exportImage();

private:
    ofPixels pixels;
};

} // namespace plugin::image

#endif /* !EXPORTING_HPP_ */
