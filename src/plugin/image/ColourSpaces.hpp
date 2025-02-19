/*
** EPITECH PROJECT, 2025
** IFT-INFOGRAPHIE [WSL : Ubuntu]
** File description:
** L’application permet de manière interactive de choisir et de convertir des
** couleurs dans l’espace RGB et HSB pour au moins 2 éléments distincts.
*/

#ifndef COLOURSPACES_HPP_
#define COLOURSPACES_HPP_

#include <fstream>
#include <iostream>
#include <vector>

#include "ofImage.h"
#include "ofPixels.h"

#define RGB_TO_YCOCG_Y(r, g, b)  (((r + (g << 1) + b) + 2) >> 2)
#define RGB_TO_YCOCG_CO(r, g, b) ((((r << 1) - (b << 1)) + 2) >> 2)
#define RGB_TO_YCOCG_CG(r, g, b) (((-r + (g << 1) - b) + 2) >> 2)

#define COCG_TO_R(co, cg) (co - cg)
#define COCG_TO_G(co, cg) (cg)
#define COCG_TO_B(co, cg) (-co - cg)

#if __cplusplus >= 202002L
#    define CLAMP_BYTE(x) (std::clamp((x), 0, 255))
#else
#    define CLAMP_BYTE(x) (std::min(255, std::max(0, (x))))
#endif

namespace plugin::image::ColourSpaces {

/**
 * @brief convert rgb to yuv image
 *
 */
void convert_rgb_to_YCoCg(ofImage &dst, const ofImage &src, int width, int height);

/**
 * @brief convert yuv to rgb image
 *
 */
void convert_YCoCg_to_rgb(ofImage &dst, const ofImage &src, int width, int height);

/**
 * @brief convert rgb to CoCg_Y image
 *
 */
void convert_rgb_to_CoCg_Y(ofImage &dst, const ofImage &src, int width, int height);

/**
 * @brief convert CoCg_Y to rgb image
 *
 */
void convert_CoCg_Y_to_rgb(ofImage &dst, const ofImage &src, int width, int height);

#include "ColourSpaces.inl"

} // namespace plugin::image::ColourSpaces

#endif /* !COLOURSPACES_HPP_ */
