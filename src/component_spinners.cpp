#include "colorpicker.h"
#include "color.h"
#include "component_spinners.h"

RgbSpinner::RgbSpinner(QWidget *parent, Color &c)
    : QSpinBox(parent), color(c)
{
    setMinimum(0);
    setMaximum(rgbSize1);
    setMinimumHeight(inputHeight);
}

// ---------------------------------------------------------------------

RedSpinner::RedSpinner(QWidget *parent, Color &c)
    : RgbSpinner(parent, c)
{
    connect(this, SIGNAL(valueChanged(int)), &c, SLOT(setR(int)));
}

void RedSpinner::colorChanged() {
    setValue(color.getR());
}

// ---------------------------------------------------------------------

GreenSpinner::GreenSpinner(QWidget *parent, Color &c)
    : RgbSpinner(parent, c)
{
    connect(this, SIGNAL(valueChanged(int)), &c, SLOT(setG(int)));
}

void GreenSpinner::colorChanged() {
    setValue(color.getG());
}

// ---------------------------------------------------------------------

BlueSpinner::BlueSpinner(QWidget *parent, Color &c)
    : RgbSpinner(parent, c)
{
    connect(this, SIGNAL(valueChanged(int)), &c, SLOT(setB(int)));
}

void BlueSpinner::colorChanged() {
    setValue(color.getB());
}


// ********************************************************************


HsvSpinner::HsvSpinner(QWidget *parent, Color &c, double max, double step)
    : QDoubleSpinBox(parent), color(c)
{
    setMaximum(max);
    setSingleStep(step);
    setMinimumWidth(74);
    setMinimumHeight(inputHeight);
}

// ---------------------------------------------------------------------

HueSpinner::HueSpinner(QWidget *parent, Color &c)
    : HsvSpinner(parent, c, 359, 1)
{
    setDecimals(1);
    connect(this, SIGNAL(valueChanged(double)), &c, SLOT(setHue(double)));
}

void HueSpinner::colorChanged() {
    setValue(color.getHue());
}

// ---------------------------------------------------------------------

SatSpinner::SatSpinner(QWidget *parent, Color &c)
    : HsvSpinner(parent, c, 1, 0.0025)
{
    setDecimals(4);
    connect(this, SIGNAL(valueChanged(double)), &c, SLOT(setSat(double)));
}

void SatSpinner::colorChanged() {
    setValue(color.getSat());
}

// ---------------------------------------------------------------------

ValSpinner::ValSpinner(QWidget *parent, Color &c)
    : HsvSpinner(parent, c, 1, 0.0025)
{
    setDecimals(4);
    connect(this, SIGNAL(valueChanged(double)), &c, SLOT(setVal(double)));
}

void ValSpinner::colorChanged() {
    setValue(color.getVal());
}
