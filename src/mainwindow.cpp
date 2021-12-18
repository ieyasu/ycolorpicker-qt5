#include "colorpicker.h"
#include "color.h"
#include "hueslider.h"
#include "mainwindow.h"
#include "palette.h"
#include "rgbsliders.h"
#include "rgbspinners.h"
#include "satval.h"

#include <QtWidgets>

static QHBoxLayout *mkRgbBox(MainWindow *win, RgbSlider *slider, RgbSpinner *spinner, const QString &text) {
    auto box = new QHBoxLayout();
    box->setSpacing(3);
    box->addStretch();
    box->addWidget(slider);
    box->addWidget(new RgbLabel(win, text));
    box->addWidget(spinner);
    box->addSpacing(indicatorSize);
    return box;
}

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

    auto redSpinner = new RedSpinner(this, color);
    auto redBox = mkRgbBox(this, redslider, redSpinner, QStringLiteral("R:"));

    auto greenSpinner = new GreenSpinner(this, color);
    auto greenBox = mkRgbBox(this, greenslider, greenSpinner, QStringLiteral("G:"));

    auto blueSpinner = new BlueSpinner(this, color);
    auto blueBox = mkRgbBox(this, blueslider, blueSpinner, QStringLiteral("B:"));

    auto stdPalette  = new Palette(this, QStringLiteral("Standard Palette"), color, stdPalColors, stdPalCount);
    auto userPalette = new Palette(this, QStringLiteral("User Palette"), color);

    auto vbox = new QVBoxLayout();
    vbox->setSpacing(spacing);
    vbox->addWidget(stdPalette);
    vbox->addWidget(userPalette);
    vbox->addStretch();

    auto grid = new QGridLayout(this);
    constexpr int m = margin - indicatorSize;
    grid->setContentsMargins(m, m, m, m);
    grid->setHorizontalSpacing(spacing);
    grid->setVerticalSpacing(spacing);
    grid->addWidget(satval, 0, 0);
    grid->addWidget(hueslider, 0, 1);
    grid->addLayout(redBox, 1, 0);
    grid->addLayout(greenBox, 2, 0);
    grid->addLayout(blueBox, 3, 0);
    grid->addLayout(vbox, 0, 2);
    setLayout(grid);

    connect(&color, &Color::changed, satval, &SaturationValue::colorChanged);
    connect(&color, &Color::changed, hueslider, &HueSlider::colorChanged);
    connect(&color, &Color::changed, redslider, &RedSlider::colorChanged);
    connect(&color, &Color::changed, redSpinner, &RedSpinner::colorChanged);
    connect(&color, &Color::changed, greenslider, &GreenSlider::colorChanged);
    connect(&color, &Color::changed, greenSpinner, &GreenSpinner::colorChanged);
    connect(&color, &Color::changed, blueslider, &BlueSlider::colorChanged);
    connect(&color, &Color::changed, blueSpinner, &BlueSpinner::colorChanged);
    color.setHue(240.0f);

    satval->setFocus();
}


RgbLabel::RgbLabel(QWidget *parent, const QString &text)
    : QLabel(parent)
{
    setText(text);
    setAlignment(Qt::AlignRight);
    setMinimumWidth(rgbLabelWidth);
    setMaximumWidth(rgbLabelWidth);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);


}
