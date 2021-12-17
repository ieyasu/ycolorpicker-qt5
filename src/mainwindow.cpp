#include "colorpicker.h"
#include "color.h"
#include "hueslider.h"
#include "mainwindow.h"
#include "satval.h"

#include <QtWidgets>

MainWindow::MainWindow()
    : QWidget(nullptr),
      color(240, 0.8, 0.8, this),
      satval(new SaturationValue(this, color)),
      hueslider(new HueSlider(this, color))
{
    setWindowTitle("Color Picker");
    setAutoFillBackground(true);

    auto grid = new QGridLayout(this);
    constexpr int m = margin - indicatorSize;
    grid->setContentsMargins(m, m, m, m);
    grid->setHorizontalSpacing(spacing);
    grid->setVerticalSpacing(spacing);
    grid->addWidget(satval, 0, 0);
    grid->addWidget(hueslider, 0, 1);
    setLayout(grid);

    connect(&color, &Color::changed, satval, &SaturationValue::colorChanged);
    connect(&color, &Color::changed, hueslider, &HueSlider::colorChanged);
    color.setHue(240.0f);
}
