#include "color.h"

#include <math.h>

Color::Color(QObject *parent)
    : QObject(parent),
      r(0), g(0), b(0),
      h(0), s(0), v(0) {}

Color::Color(int red, int green, int blue, QObject *parent)
    : QObject(parent),
      r(red), g(green), b(blue)
{
    rgb2hsv();
}

Color::Color(float hue, float sat, float val, QObject *parent)
    : QObject(parent),
      h(hue), s(sat), v(val)
{
    hsv2rgb();
}

void Color::setSatVal(float sat, float val) {
    s = sat;
    v = val;
    hsv2rgb();
}

// https://en.wikipedia.org/wiki/HSL_and_HSV#Color_conversion_formulae
// https://www.rapidtables.com/convert/color/hsv-to-rgb.html

static inline float mod2f(float x) {
    return x - floorf(x / 2) * 2;
}

void Color::hsv2rgb() {
    float c = s * v;
    float h_ = h / 60.0f;
    float x = c * (1 - fabsf(mod2f(h_) - 1));

    float rf = 0, gf = 0, bf = 0;
    if (h_ <= 1) {
        rf = c;
        gf = x;
    } else if (h_ <= 2) {
        rf = x;
        gf = c;
    } else if (h_ <= 3) {
        gf = c;
        bf = x;
    } else if (h_ <= 4) {
        gf = x;
        bf = c;
    } else if (h_ <= 5) {
        rf = x;
        bf = c;
    } else if (h_ <= 6) {
        rf = c;
        bf = x;
    }

    float m = v - c;
    r = static_cast<int>(255 * (rf + m));
    g = static_cast<int>(255 * (gf + m));
    b = static_cast<int>(255 * (bf + m));
}

static inline float mod6f(float x) {
    return x - floorf(x / 6) * 6;
}

void Color::rgb2hsv() {
    float rf = r / 255.0f;
    float gf = g / 255.0f;
    float bf = b / 255.0f;
    float cmax = r > g ? (r > b ? rf : bf) : (g > b ? gf : bf);
    float cmin = r < g ? (r < b ? rf : bf) : (g < b ? gf : bf);
    float del = cmax - cmin;

    if (cmax == 0 || del == 0) {
        h = s = v = 0;
        return;
    }

    if (cmax == rf) {
        h = 60 * mod6f((gf - bf) / del);
    } else if (cmax == gf) {
        h = 60 * ((bf - rf) / del + 2);
    } else if (cmax == bf) {
        h = 60 * ((rf - gf) / del + 4);
    } else {
        h = 0;
    }
    s = (cmax == 0) ? 0 : del / cmax;
    v = cmax;
}
