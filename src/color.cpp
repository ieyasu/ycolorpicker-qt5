#include "color.h"

#include <math.h>

#include <algorithm>

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

Color &Color::operator=(const Color &c) {
    bool ch = false;
    if (c.r != r) { r = c.r; ch = true; }
    if (c.g != g) { g = c.g; ch = true; }
    if (c.b != b) { b = c.b; ch = true; }
    if (c.h != h) { h = c.h; ch = true; }
    if (c.s != s) { s = c.s; ch = true; }
    if (c.v != v) { v = c.v; ch = true; }
    if (ch) emit changed();
    return *this;
}

void Color::setR(int red) {
    red = std::clamp(red, 0, 255);
    if (red != r) { r = red; rgb2hsv(); }
}
void Color::setG(int grn) {
    grn = std::clamp(grn, 0, 255);
    if (grn != g) { g = grn; rgb2hsv(); }
}
void Color::setB(int blu) {
    blu = std::clamp(blu, 0, 255);
    if (blu != b) { b = blu; rgb2hsv(); }
}

void Color::setHue(float hue) {
    hue = std::clamp(hue, 0.0f, 359.0f);
    if (hue != h) { h = hue; hsv2rgb(); }
}
void Color::setSat(float sat) {
    sat = std::clamp(sat, 0.0f, 1.0f);
    if (sat != s) { s = sat; hsv2rgb(); }
}
void Color::setVal(float val) {
    val = std::clamp(val, 0.0f, 1.0f);
    if (val != v) { v = val; hsv2rgb(); }
}

void Color::setHue(double hue) {
    hue = std::clamp(hue, 0.0, 359.0);
    if (hue != h) { h = static_cast<float>(hue); hsv2rgb(); }
}
void Color::setSat(double sat) {
    sat = std::clamp(sat, 0.0, 1.0);
    if (sat != s) { s = static_cast<float>(sat); hsv2rgb(); }
}
void Color::setVal(double val) {
    val = std::clamp(val, 0.0, 1.0);
    if (val != v) { v = static_cast<float>(val); hsv2rgb(); }
}

void Color::setSatVal(float sat, float val) {
    bool changed = false;
    sat = std::clamp(sat, 0.0f, 1.0f);
    if (sat != s) { s = sat; changed = true; }
    val = std::clamp(val, 0.0f, 1.0f);
    if (val != v) { v = val; changed = true; }
    if (changed) hsv2rgb();
}

void Color::setRGB(const RgbTriple &triple) {
    bool changed = false;
    if (triple.r != r) { r = triple.r; changed = true; }
    if (triple.g != g) { g = triple.g; changed = true; }
    if (triple.b != b) { b = triple.b; changed = true; }
    if (changed) rgb2hsv();
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

    emit changed();
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
    if (del == 0) del = 1e-20;

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

    emit changed();
}
