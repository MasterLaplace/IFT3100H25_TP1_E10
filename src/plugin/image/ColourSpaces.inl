#include "ColourSpaces.hpp"
#include "ofPixels.h"

inline void convert_rgb_to_YCoCg(ofImage &dst, const ofImage &src, int width, int height)
{
    for (int i = 0; i < width * height; i++)
    {
        ofColor color = src.getColor(i % width, i / width);
        int r = color.r;
        int g = color.g;
        int b = color.b;
        int a = color.a;
        dst.setColor(i % width, i / width,
                     ofColor(CLAMP_BYTE(RGB_TO_YCOCG_Y(r, g, b)), CLAMP_BYTE(RGB_TO_YCOCG_CO(r, g, b) + 128),
                             CLAMP_BYTE(RGB_TO_YCOCG_CG(r, g, b) + 128), a));
    }
}

inline void convert_YCoCg_to_rgb(ofImage &dst, const ofImage &src, int width, int height)
{
    for (int i = 0; i < width * height; i++)
    {
        ofColor color = src.getColor(i % width, i / width);
        int y = color.r;
        int co = color.g - 128;
        int cg = color.b - 128;
        int a = color.a;
        dst.setColor(i % width, i / width,
                     ofColor(CLAMP_BYTE(y + COCG_TO_R(co, cg)), CLAMP_BYTE(y + COCG_TO_G(co, cg)),
                             CLAMP_BYTE(y + COCG_TO_B(co, cg)), a));
    }
}

inline void convert_rgb_to_CoCg_Y(ofImage &dst, const ofImage &src, int width, int height)
{
    for (int i = 0; i < width * height; i++)
    {
        ofColor color = src.getColor(i % width, i / width);
        int r = color.r;
        int g = color.g;
        int b = color.b;
        dst.setColor(i % width, i / width,
                     ofColor(CLAMP_BYTE(RGB_TO_YCOCG_CO(r, g, b) + 128), CLAMP_BYTE(RGB_TO_YCOCG_CG(r, g, b) + 128), 0,
                             CLAMP_BYTE(RGB_TO_YCOCG_Y(r, g, b))));
    }
}

inline void convert_CoCg_Y_to_rgb(ofImage &dst, const ofImage &src, int width, int height)
{
    for (int i = 0; i < width * height; i++)
    {
        ofColor color = src.getColor(i % width, i / width);
        int co = color.r - 128;
        int cg = color.g - 128;
        int a = color.b;
        int y = color.a;
        dst.setColor(i % width, i / width,
                     ofColor(CLAMP_BYTE(y + COCG_TO_R(co, cg)), CLAMP_BYTE(y + COCG_TO_G(co, cg)),
                             CLAMP_BYTE(y + COCG_TO_B(co, cg)), a));
    }
}
