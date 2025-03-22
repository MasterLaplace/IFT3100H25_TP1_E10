/*
** ULAVAL PROJECT, 2025
** IFT3100H25_TP1_E10 [WSL : Ubuntu]
** File description:
** Image
*/

#ifndef IMAGE_HPP_
#define IMAGE_HPP_

#include "ColourSpaces.hpp"
#include "ToneMapping.hpp"
#include "ofShader.h"

namespace plugin::image {

class Image : public ofImage {
public:
    Image() : ofImage() { type = OF_IMAGE_COLOR_ALPHA; }
    ~Image() = default;

    void convert(ColourSpaces::Type ntype);

    ToneMapping::Type getToneMapping() const { return _toneMapping; }
    void setExposure(float exposure) { _exposure = exposure; }
    void setGamma(float gamma) { _gamma = gamma; }
    void setToneMapping(ToneMapping::Type toneMapping) { _toneMapping = toneMapping; }

    void draw(float x, float y) const override;

private:
    ColourSpaces::Type _type = ColourSpaces::Type::RGBA;
    ToneMapping::Type _toneMapping = ToneMapping::Type::None;

    float _exposure = 1.0f;
    float _gamma = 2.2f;
};

} // namespace plugin::image

#endif /* !IMAGE_HPP_ */
