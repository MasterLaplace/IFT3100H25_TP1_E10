#include "ColourSpaces.hpp"

namespace plugin::image::ColourSpaces {

std::string type_to_string(Type type)
{
    switch (type)
    {
    case Type::RGB: return "RGB";
    case Type::RGBA: return "RGBA";
    case Type::YUV: return "YUV";
    case Type::YCoCg: return "YCoCg";
    case Type::CoCg_Y: return "CoCg_Y";
    case Type::Grayscale: return "Grayscale";
    case Type::HSB: return "HSB";
    case Type::HLS: return "HLS";
    default: return "Unknown";
    }
}

void convert_rgb_to_rgba(ofImage &dst, const ofImage &src, int width, int height)
{
    dst.allocate(width, height, OF_IMAGE_COLOR_ALPHA);
    const ofPixels &srcPixels = src.getPixels();
    ofPixels &dstPixels = dst.getPixels();

    for (int i = 0; i < width * height; i++)
    {
        ofColor color = srcPixels.getColor(i % width, i / width);
        dstPixels.setColor(i % width, i / width, ofColor(color.r, color.g, color.b, 255));
    }
    dst.update();
}

void convert_rgba_to_rgb(ofImage &dst, const ofImage &src, int width, int height)
{
    dst.allocate(width, height, OF_IMAGE_COLOR);
    const ofPixels &srcPixels = src.getPixels();
    ofPixels &dstPixels = dst.getPixels();

    for (int i = 0; i < width * height; i++)
    {
        ofColor color = srcPixels.getColor(i % width, i / width);
        dstPixels.setColor(i % width, i / width, ofColor(color.r, color.g, color.b));
    }
    dst.update();
}

void convert_rgb_to_yuv(ofImage &dst, const ofImage &src, int width, int height)
{
    dst.allocate(width, height, OF_IMAGE_UNDEFINED);
    const ofPixels &srcPixels = src.getPixels();
    ofPixels &dstPixels = dst.getPixels();

    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            ofColor color = srcPixels.getColor(x, y);
            float r = color.r / 255.0f;
            float g = color.g / 255.0f;
            float b = color.b / 255.0f;

            float y = 0.299f * r + 0.587f * g + 0.114f * b;
            float u = -0.14713f * r - 0.28886f * g + 0.436f * b;
            float v = 0.615f * r - 0.51499f * g - 0.10001f * b;

            dstPixels.setColor(x, y, ofColor(y * 255, u * 255, v * 255));
        }
    }
    dst.update();
}

void convert_yuv_to_rgb(ofImage &dst, const ofImage &src, int width, int height)
{
    dst.allocate(width, height, OF_IMAGE_COLOR);
    const ofPixels &srcPixels = src.getPixels();
    ofPixels &dstPixels = dst.getPixels();

    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            ofColor color = srcPixels.getColor(x, y);
            float y = color.r / 255.0f;
            float u = color.g / 255.0f;
            float v = color.b / 255.0f;

            float r = y + 1.13983f * v;
            float g = y - 0.39465f * u - 0.58060f * v;
            float b = y + 2.03211f * u;

            dstPixels.setColor(x, y, ofColor(r * 255, g * 255, b * 255));
        }
    }
    dst.update();
}

void convert_rgb_to_YCoCg(ofImage &dst, const ofImage &src, int width, int height)
{
    dst.allocate(width, height, OF_IMAGE_UNDEFINED);
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
    dst.update();
}

void convert_YCoCg_to_rgb(ofImage &dst, const ofImage &src, int width, int height)
{
    dst.allocate(width, height, OF_IMAGE_COLOR);
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
    dst.update();
}

void convert_rgb_to_CoCg_Y(ofImage &dst, const ofImage &src, int width, int height)
{
    dst.allocate(width, height, OF_IMAGE_UNDEFINED);
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
    dst.update();
}

void convert_CoCg_Y_to_rgb(ofImage &dst, const ofImage &src, int width, int height)
{
    dst.allocate(width, height, OF_IMAGE_COLOR);
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
    dst.update();
}

void convert_rgb_to_hsb(ofImage &dst, const ofImage &src, int width, int height)
{
    dst.allocate(width, height, OF_IMAGE_UNDEFINED);
    const ofPixels &srcPixels = src.getPixels();
    ofPixels &dstPixels = dst.getPixels();

    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            ofColor color = srcPixels.getColor(x, y);
            float r = color.r / 255.0f;
            float g = color.g / 255.0f;
            float b = color.b / 255.0f;

            float max = std::max({r, g, b});
            float min = std::min({r, g, b});
            float delta = max - min;

            float h = 0.0f;
            float s = (max == 0.0f) ? 0.0f : delta / max;
            float v = max;

            if (delta != 0.0f)
            {
                if (max == r)
                {
                    h = (g - b) / delta + (g < b ? 6.0f : 0.0f);
                }
                else if (max == g)
                {
                    h = (b - r) / delta + 2.0f;
                }
                else if (max == b)
                {
                    h = (r - g) / delta + 4.0f;
                }
                h /= 6.0f;
            }

            dstPixels.setColor(x, y, ofColor(h * 255, s * 255, v * 255));
        }
    }
    dst.update();
}

void convert_hsb_to_rgb(ofImage &dst, const ofImage &src, int width, int height)
{
    dst.allocate(width, height, OF_IMAGE_COLOR);
    const ofPixels &srcPixels = src.getPixels();
    ofPixels &dstPixels = dst.getPixels();

    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            ofColor color = srcPixels.getColor(x, y);
            float h = color.r / 255.0f;
            float s = color.g / 255.0f;
            float v = color.b / 255.0f;

            int i = int(h * 6.0f);
            float f = h * 6.0f - i;
            float p = v * (1.0f - s);
            float q = v * (1.0f - f * s);
            float t = v * (1.0f - (1.0f - f) * s);

            float r = 0, g = 0, b = 0;
            switch (i % 6)
            {
            case 0: r = v, g = t, b = p; break;
            case 1: r = q, g = v, b = p; break;
            case 2: r = p, g = v, b = t; break;
            case 3: r = p, g = q, b = v; break;
            case 4: r = t, g = p, b = v; break;
            case 5: r = v, g = p, b = q; break;
            }

            dstPixels.setColor(x, y, ofColor(r * 255, g * 255, b * 255));
        }
    }
    dst.update();
}

void convert_rgb_to_grayscale(ofImage &dst, const ofImage &src, int width, int height)
{
    dst.allocate(width, height, OF_IMAGE_GRAYSCALE);
    const ofPixels &srcPixels = src.getPixels();
    ofPixels &dstPixels = dst.getPixels();

    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            ofColor color = srcPixels.getColor(x, y);
            float gray = 0.299f * color.r + 0.587f * color.g + 0.114f * color.b;
            dstPixels.setColor(x, y, ofColor(gray));
        }
    }
    dst.update();
}

void convert_rgb_to_hls(ofImage &dst, const ofImage &src, int width, int height)
{
    dst.allocate(width, height, OF_IMAGE_UNDEFINED);
    const ofPixels &srcPixels = src.getPixels();
    ofPixels &dstPixels = dst.getPixels();

    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            ofColor color = srcPixels.getColor(x, y);
            float r = color.r / 255.0f;
            float g = color.g / 255.0f;
            float b = color.b / 255.0f;

            float max = std::max({r, g, b});
            float min = std::min({r, g, b});
            float delta = max - min;

            float h = 0.0f;
            float l = (max + min) / 2.0f;
            float s = (max == min) ? 0.0f : (l <= 0.5f ? delta / (max + min) : delta / (2.0f - max - min));

            if (delta != 0.0f)
            {
                if (max == r)
                {
                    h = (g - b) / delta + (g < b ? 6.0f : 0.0f);
                }
                else if (max == g)
                {
                    h = (b - r) / delta + 2.0f;
                }
                else if (max == b)
                {
                    h = (r - g) / delta + 4.0f;
                }
                h /= 6.0f;
            }

            dstPixels.setColor(x, y, ofColor(h * 255, l * 255, s * 255));
        }
    }
    dst.update();
}

void convert_hls_to_rgb(ofImage &dst, const ofImage &src, int width, int height)
{
    dst.allocate(width, height, OF_IMAGE_COLOR);
    const ofPixels &srcPixels = src.getPixels();
    ofPixels &dstPixels = dst.getPixels();

    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            ofColor color = srcPixels.getColor(x, y);
            float h = color.r / 255.0f;
            float l = color.g / 255.0f;
            float s = color.b / 255.0f;

            float r, g, b;

            if (s == 0.0f)
            {
                r = g = b = l; // achromatic
            }
            else
            {
                auto hue2rgb = [](float p, float q, float t) {
                    if (t < 0.0f)
                        t += 1.0f;
                    if (t > 1.0f)
                        t -= 1.0f;
                    if (t < 1.0f / 6.0f)
                        return p + (q - p) * 6.0f * t;
                    if (t < 1.0f / 2.0f)
                        return q;
                    if (t < 2.0f / 3.0f)
                        return p + (q - p) * (2.0f / 3.0f - t) * 6.0f;
                    return p;
                };

                float q = l < 0.5f ? l * (1.0f + s) : l + s - l * s;
                float p = 2.0f * l - q;
                r = hue2rgb(p, q, h + 1.0f / 3.0f);
                g = hue2rgb(p, q, h);
                b = hue2rgb(p, q, h - 1.0f / 3.0f);
            }

            dstPixels.setColor(x, y, ofColor(r * 255, g * 255, b * 255));
        }
    }
    dst.update();
}

} // namespace plugin::image::ColourSpaces
