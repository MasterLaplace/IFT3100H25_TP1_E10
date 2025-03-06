/*
** ULAVAL PROJECT, 2025
** IFT3100H25_TP1_E10 [WSL : Ubuntu]
** File description:
** Image
*/

#ifndef IMAGE_HPP_
#define IMAGE_HPP_

#include "ColourSpaces.hpp"

namespace plugin::image {

class Image : public ofImage {
    public:
        Image() : ofImage() {
            type = OF_IMAGE_COLOR_ALPHA;
        }
        ~Image() = default;

        void convert(ColourSpaces::Type ntype);

    private:
        ColourSpaces::Type _type = ColourSpaces::Type::RGBA;
};

} // namespace plugin::image

#endif /* !IMAGE_HPP_ */
