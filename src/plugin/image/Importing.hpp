/*
** ULAVAL PROJECT, 2025
** IFT3100H25_TP1_E10 [WSL : Ubuntu]
** File description:
** Après le lancement de l’application, il est possible d’importer de manière
** interactive des fichiers images et de les afficher dans une scène sous une
** forme ou une autre.
*/

#ifndef IMPORTING_HPP_
#define IMPORTING_HPP_

#include "ofMain.h"
#include <optional>

namespace plugin::image::Importing {

std::optional<ofImage> importImage();

} // namespace plugin::image::Importing

#endif /* !IMPORTING_HPP_ */
