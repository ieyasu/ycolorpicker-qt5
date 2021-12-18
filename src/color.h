// color.h - Color class for color space conversions and color change signalling.
#ifndef COLOR_H
#define COLOR_H

#include "colorpicker.h"

#include <QColor>
#include <QObject>

class Color : public QObject {
    Q_OBJECT
public:
    Color(QObject *parent = nullptr);
    Color(int red, int green, int blue, QObject *parent = nullptr);
    Color(double hue, double sat, double val, QObject *parent = nullptr);

    Color &operator=(const Color &c);

    int getR() const { return r; }
    int getG() const { return g; }
    int getB() const { return b; }
    double getHue() const { return h; }
    double getSat() const { return s; }
    double getVal() const { return v; }
    QColor toQColor() const { return qRgb(r, g, b); }

    void setRGB(const RgbTriple &triple);
    void setSatVal(double sat, double val);

public slots:
    void setR(int red);
    void setG(int grn);
    void setB(int blu);
    void setHue(double hue);
    void setSat(double sat);
    void setVal(double val);

signals:
    void changed();

private:
    int r, g, b;
    double h;     // 0-359
    double s, v;  // 0-1

    void hsv2rgb();
    void rgb2hsv();
};

#endif // COLOR_H
