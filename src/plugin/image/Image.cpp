#include "Image.hpp"

namespace plugin::image {

void Image::convert(ColourSpaces::Type nType)
{
    ofImage dst;
    int width = getWidth();
    int height = getHeight();

    switch (_type)
    {
    case ColourSpaces::Type::RGB: break;
    case ColourSpaces::Type::RGBA: ColourSpaces::convert_rgba_to_rgb(dst, *this, width, height); break;
    case ColourSpaces::Type::YUV: ColourSpaces::convert_yuv_to_rgb(dst, *this, width, height); break;
    case ColourSpaces::Type::YCoCg: ColourSpaces::convert_YCoCg_to_rgb(dst, *this, width, height); break;
    case ColourSpaces::Type::CoCg_Y: ColourSpaces::convert_CoCg_Y_to_rgb(dst, *this, width, height); break;
    case ColourSpaces::Type::Grayscale: _type = ColourSpaces::Type::RGB; return;
    case ColourSpaces::Type::HSB: ColourSpaces::convert_hsb_to_rgb(dst, *this, width, height); break;
    default: break;
    }

    switch (nType)
    {
    case ColourSpaces::Type::RGB: break;
    case ColourSpaces::Type::RGBA: ColourSpaces::convert_rgb_to_rgba(dst, *this, width, height); break;
    case ColourSpaces::Type::YUV: ColourSpaces::convert_rgb_to_yuv(*this, dst, width, height); break;
    case ColourSpaces::Type::YCoCg: ColourSpaces::convert_rgb_to_YCoCg(*this, dst, width, height); break;
    case ColourSpaces::Type::CoCg_Y: ColourSpaces::convert_rgb_to_CoCg_Y(*this, dst, width, height); break;
    case ColourSpaces::Type::Grayscale: ColourSpaces::convert_rgb_to_grayscale(*this, dst, width, height); break;
    case ColourSpaces::Type::HSB: ColourSpaces::convert_rgb_to_hsb(*this, dst, width, height); break;
    default: break;
    }
}

} // namespace plugin::image
