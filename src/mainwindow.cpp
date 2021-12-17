#include "colorpicker.h"
#include "color.h"
#include "hueslider.h"
#include "mainwindow.h"
#include "rgbsliders.h"
#include "satval.h"

#include <QtWidgets>

MainWindow::MainWindow()
    : QWidget(nullptr),
      color(0.0f, 0.8f, 0.8f),
      satval(new SaturationValue(this, color)),
      hueslider(new HueSlider(this, color)),
      redslider(new RedSlider(this, color)),
      greenslider(new GreenSlider(this, color)),
      blueslider(new BlueSlider(this, color))
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
    grid->addWidget(redslider, 1, 0);
    grid->addWidget(greenslider, 2, 0);
    grid->addWidget(blueslider, 3, 0);
    setLayout(grid);

    connect(&color, &Color::changed, satval, &SaturationValue::colorChanged);
    connect(&color, &Color::changed, hueslider, &HueSlider::colorChanged);
    connect(&color, &Color::changed, redslider, &RedSlider::colorChanged);
    connect(&color, &Color::changed, greenslider, &GreenSlider::colorChanged);
    connect(&color, &Color::changed, blueslider, &BlueSlider::colorChanged);
    color.setHue(240.0f);
}
