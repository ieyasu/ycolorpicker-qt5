#include "colorpicker.h"
#include "color.h"
#include "rgbspinners.h"

RgbSpinner::RgbSpinner(QWidget *parent, Color &c)
    : QSpinBox(parent), color(c)
{
    setMinimum(0);
    setMaximum(rgbSize1);
}

// ********************************************************************

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

// ********************************************************************

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

// ********************************************************************

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
