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
    case ColourSpaces::Type::Grayscale: _type = ColourSpaces::Type::RGB; break;
    case ColourSpaces::Type::HSB: ColourSpaces::convert_hsb_to_rgb(dst, *this, width, height); break;
    case ColourSpaces::Type::HLS: ColourSpaces::convert_hls_to_rgb(dst, *this, width, height); break;
    default: break;
    }

    _type = nType;

    switch (nType)
    {
    case ColourSpaces::Type::RGB: break;
    case ColourSpaces::Type::RGBA: ColourSpaces::convert_rgb_to_rgba(*this, dst, width, height); break;
    case ColourSpaces::Type::YUV: ColourSpaces::convert_rgb_to_yuv(*this, dst, width, height); break;
    case ColourSpaces::Type::YCoCg: ColourSpaces::convert_rgb_to_YCoCg(*this, dst, width, height); break;
    case ColourSpaces::Type::CoCg_Y: ColourSpaces::convert_rgb_to_CoCg_Y(*this, dst, width, height); break;
    case ColourSpaces::Type::Grayscale: ColourSpaces::convert_rgb_to_grayscale(*this, dst, width, height); break;
    case ColourSpaces::Type::HSB: ColourSpaces::convert_rgb_to_hsb(*this, dst, width, height); break;
    case ColourSpaces::Type::HLS: ColourSpaces::convert_rgb_to_hls(*this, dst, width, height); break;
    default: break;
    }
}

/*
C'est la fonction draw qui a ete redefini pour y ajouter le tonemapping.
*/
void Image::draw(float x, float y) const
{
    if (_toneMapping == ToneMapping::Type::None)
    {
        ofShader tonalShader;
        if (tonalShader.load("tone_mapping_330_vs.glsl", "none_330_fs.glsl"))
        {
            tonalShader.begin();

            tonalShader.setUniformTexture("image", getTexture(), 0);
            tonalShader.setUniform1f("exposure", _exposure);
            tonalShader.setUniform1f("gamma", _gamma);

            ofImage::draw(x, y);

            tonalShader.end();
        }
        else
        {
            std::cerr << "Erreur dans le chargement du shader de None." << std::endl;
        }
    }

    else if (_toneMapping == ToneMapping::Type::Reinhard)
    {
        ofShader tonalShader;
        if (tonalShader.load("tone_mapping_330_vs.glsl", "reinhard_330_fs.glsl"))
        {
            tonalShader.begin();

            tonalShader.setUniformTexture("image", getTexture(), 0);
            tonalShader.setUniform1f("exposure", _exposure);
            tonalShader.setUniform1f("gamma", _gamma);

            ofImage::draw(x, y);

            tonalShader.end();
        }
        else
        {
            std::cerr << "Erreur dans le chargement du shader de Reinhard." << std::endl;
        }
    }
    else if (_toneMapping == ToneMapping::Type::Filmic)
    {
        ofShader tonalShader;
        if (tonalShader.load("tone_mapping_330_vs.glsl", "filmic_330_fs.glsl"))
        {
            tonalShader.begin();

            tonalShader.setUniformTexture("image", getTexture(), 0);
            tonalShader.setUniform1f("exposure", _exposure);
            tonalShader.setUniform1f("gamma", _gamma);

            ofImage::draw(x, y);

            tonalShader.end();
        }
        else
        {
            std::cerr << "Erreur dans le chargement du shader Filmic." << std::endl;
        }
    }
}

} // namespace plugin::image
