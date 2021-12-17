// color.h - Color class for color space conversions and color change signalling.
#ifndef COLOR_H
#define COLOR_H

#include <QColor>
#include <QObject>

class Color : public QObject {
    Q_OBJECT
public:
    Color(QObject *parent = nullptr);
    Color(int red, int green, int blue, QObject *parent = nullptr);
    Color(float hue, float sat, float val, QObject *parent = nullptr);

    float getR() const { return r; }
    float getG() const { return g; }
    float getB() const { return b; }
    float getHue() const { return h; }
    float getSat() const { return s; }
    float getVal() const { return v; }
    QColor toQColor() const { return qRgb(r, g, b); }

    void setSatVal(float sat, float val);

public slots:
    void setR(int red) { r = red; rgb2hsv(); }
    void setG(int grn) { g = grn; rgb2hsv(); }
    void setB(int blu) { b = blu; rgb2hsv(); }
    void setHue(float hue) { h = hue; hsv2rgb(); }
    void setSat(float sat) { s = sat; hsv2rgb(); }
    void setVal(float val) { v = val; hsv2rgb(); }
    void setHue(double hue) { h = static_cast<float>(hue); hsv2rgb(); }
    void setSat(double sat) { s = static_cast<float>(sat); hsv2rgb(); }
    void setVal(double val) { v = static_cast<float>(val); hsv2rgb(); }

    //signals:
    //void changed(const Color &color);

private:
    int r, g, b;
    float h;     // 0-360
    float s, v;  // 0-1

    void hsv2rgb();
    void rgb2hsv();
};

#endif // COLOR_H
