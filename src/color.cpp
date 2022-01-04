/* color.cpp - Color class for YColorPicker
 * Copyright 2022 Matthew S. Bishop
 *
 * This program is licensed under the terms of the GNU GPL version 3. See the
 * file LICENSE.txt or <https://www.gnu.org/licenses/> for details.
 */
#include "color.h"

#include <math.h>

#include <algorithm>

Color::Color(int red, int green, int blue)
    : r(red), g(green), b(blue)
{
    rgb2hsv();
}

Color::Color(double hue, double sat, double val)
    : h(hue), s(sat), v(val)
{
    hsv2rgb();
}

Color::Color(const Color &c) : r(c.r), g(c.g), b(c.b), h(c.h), s(c.s), v(c.v) {}

Color::Color(const QColor &c)
    : r(c.red()), g(c.green()), b(c.blue())
{
    rgb2hsv();
}

Color &Color::operator=(const QColor &c)
{
    bool ch = false;
    if (  c.red() != r) { r = c.red();   ch = true; }
    if (c.green() != g) { g = c.green(); ch = true; }
    if ( c.blue() != b) { b = c.blue();  ch = true; }
    rgb2hsv();
    return *this;
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

void Color::setHue(double hue) {
    hue = std::clamp(hue, 0.0, 359.0);
    if (hue != h) { h = hue; hsv2rgb(); }
}
void Color::setSat(double sat) {
    sat = std::clamp(sat, 0.0, 1.0);
    if (sat != s) { s = sat; hsv2rgb(); }
}
void Color::setVal(double val) {
    val = std::clamp(val, 0.0, 1.0);
    if (val != v) { v = val; hsv2rgb(); }
}

void Color::setSatVal(double sat, double val) {
    bool changed = false;
    sat = std::clamp(sat, 0.0, 1.0);
    if (sat != s) { s = sat; changed = true; }
    val = std::clamp(val, 0.0, 1.0);
    if (val != v) { v = val; changed = true; }
    if (changed) hsv2rgb();
}

void Color::setRGB(int red, int grn, int blu) {
    bool ch = false;
    red = std::clamp(red, 0, 255);
    if (red != r) { r = red; ch = true; }
    grn = std::clamp(grn, 0, 255);
    if (grn != g) { g = grn; ch = true; }
    blu = std::clamp(blu, 0, 255);
    if (blu != b) { b = blu; ch = true; }
    if (ch) rgb2hsv();
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

static inline double mod2d(double x) {
    return x - floorf(x / 2) * 2;
}

void Color::hsv2rgb() {
    double c = s * v;
    double h_ = h / 60.0;
    double x = c * (1 - fabsf(mod2d(h_) - 1));

    double rf = 0, gf = 0, bf = 0;
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

    double m = v - c;
    r = static_cast<int>(256 * (rf + m));
    if (r > 255) r = 255;
    g = static_cast<int>(256 * (gf + m));
    if (g > 255) g = 255;
    b = static_cast<int>(256 * (bf + m));
    if (b > 255) b = 255;

    emit changed();
}

static inline double mod6d(double x) {
    return x - floorf(x / 6) * 6;
}

void Color::rgb2hsv() {
    double rf = r / 255.0;
    double gf = g / 255.0;
    double bf = b / 255.0;
    double cmax = r > g ? (r > b ? rf : bf) : (g > b ? gf : bf);
    double cmin = r < g ? (r < b ? rf : bf) : (g < b ? gf : bf);
    double del = cmax - cmin;
    if (del == 0) del = 1e-20;

    if (cmax == rf) {
        h = 60 * mod6d((gf - bf) / del);
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
