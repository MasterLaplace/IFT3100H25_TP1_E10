/*
** ULAVAL PROJECT, 2025
** IFT-INFOGRAPHIE [WSL : Ubuntu]
** File description:
** L’application permet de manière interactive de choisir et de convertir des
** couleurs dans l’espace RGB et HSB pour au moins 2 éléments distincts.
**
** Source:
** https://stackoverflow.com/questions/12524623/what-are-the-practical-differences-when-working-with-colors-in-a-linear-vs-a-no
** https://github.com/DustinHLand/vkDOOM3/blob/master/neo/renderer/Color/ColorSpace.cpp
*/

#ifndef COLOURSPACES_HPP_
#define COLOURSPACES_HPP_

#include "ofImage.h"
#include "ofPixels.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

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

enum class Type {
    RGB,
    RGBA,
    YUV,
    YCoCg,
    CoCg_Y,
    Grayscale,
    HSB,
    HLS
};

/**
 * @brief return the string representation of the type
 *
 * @param type  the type
 * @return std::string  the string representation of the type
 */
std::string type_to_string(Type type);

/**
 * @brief convert rgb to rgba image
 *
 */
void convert_rgb_to_rgba(ofImage &dst, const ofImage &src, int width, int height);

/**
 * @brief convert rgba to rgb image
 *
 */
void convert_rgba_to_rgb(ofImage &dst, const ofImage &src, int width, int height);

/**
 * @brief convert rgb to yuv image
 *
 */
void convert_rgb_to_yuv(ofImage &dst, const ofImage &src, int width, int height);

/**
 * @brief convert yuv to rgb image
 *
 */
void convert_yuv_to_rgb(ofImage &dst, const ofImage &src, int width, int height);

/**
 * @brief convert rgb to YCoCg image
 *
 */
void convert_rgb_to_YCoCg(ofImage &dst, const ofImage &src, int width, int height);

/**
 * @brief convert YCoCg to rgb image
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

/**
 * @brief convert rgb to hsb image
 *
 */
void convert_rgb_to_hsb(ofImage &dst, const ofImage &src, int width, int height);

/**
 * @brief convert hsb to rgb image
 *
 */
void convert_hsb_to_rgb(ofImage &dst, const ofImage &src, int width, int height);

/**
 * @brief convert rgb to grayscale image
 *
 */
void convert_rgb_to_grayscale(ofImage &dst, const ofImage &src, int width, int height);

/**
 * @brief convert rgb to hls image
 *
 */
void convert_rgb_to_hls(ofImage &dst, const ofImage &src, int width, int height);

/**
 * @brief convert hls to rgb image
 *
 */
void convert_hls_to_rgb(ofImage &dst, const ofImage &src, int width, int height);

} // namespace plugin::image::ColourSpaces

#endif /* !COLOURSPACES_HPP_ */
