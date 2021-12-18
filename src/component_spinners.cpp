#include "colorpicker.h"
#include "color.h"
#include "component_spinners.h"

RgbSpinner::RgbSpinner(QWidget *parent, Color &c)
    : QSpinBox(parent), color(c)
{
    setMinimum(0);
    setMaximum(rgbSize1);
}

// ---------------------------------------------------------------------

RedSpinner::RedSpinner(QWidget *parent, Color &c)
    : RgbSpinner(parent, c)
{
    connect(this, SIGNAL(valueChanged(int)), this, SLOT(changed(int)));
}

void RedSpinner::changed(int x) {
    color.setR(x);
}

void RedSpinner::colorChanged() {
    setValue(color.getR());
}

// ---------------------------------------------------------------------

GreenSpinner::GreenSpinner(QWidget *parent, Color &c)
    : RgbSpinner(parent, c)
{
    connect(this, SIGNAL(valueChanged(int)), this, SLOT(changed(int)));
}

void GreenSpinner::changed(int x) {
    color.setG(x);
}

void GreenSpinner::colorChanged() {
    setValue(color.getG());
}

// ---------------------------------------------------------------------

BlueSpinner::BlueSpinner(QWidget *parent, Color &c)
    : RgbSpinner(parent, c)
{
    connect(this, SIGNAL(valueChanged(int)), this, SLOT(changed(int)));
}

void BlueSpinner::changed(int x) {
    color.setB(x);
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
}

// ---------------------------------------------------------------------

HueSpinner::HueSpinner(QWidget *parent, Color &c)
    : HsvSpinner(parent, c, 359, 1)
{
    setDecimals(1);
    connect(this, SIGNAL(valueChanged(double)), this, SLOT(changed(double)));
}

void HueSpinner::changed(double x) {
    color.setHue(x);
}

void HueSpinner::colorChanged() {
    setValue(color.getHue());
}

// ---------------------------------------------------------------------

SatSpinner::SatSpinner(QWidget *parent, Color &c)
    : HsvSpinner(parent, c, 1, 0.0025)
{
    setDecimals(3);
    connect(this, SIGNAL(valueChanged(double)), this, SLOT(changed(double)));
}

void SatSpinner::changed(double x) {
    color.setSat(x);
}

void SatSpinner::colorChanged() {
    setValue(color.getSat());
}

// ---------------------------------------------------------------------

ValSpinner::ValSpinner(QWidget *parent, Color &c)
    : HsvSpinner(parent, c, 1, 0.0025)
{
    setDecimals(3);
    connect(this, SIGNAL(valueChanged(double)), this, SLOT(changed(double)));
}

void ValSpinner::changed(double x) {
    color.setVal(x);
}

void ValSpinner::colorChanged() {
    setValue(color.getVal());
}
