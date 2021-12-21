#include "colorpicker.h"
#include "color.h"
#include "color_formats.h"
#include "currcolordisplay.h"
#include "hueslider.h"
#include "mainwindow.h"
#include "palette.h"
#include "rgbsliders.h"
#include "component_spinners.h"
#include "satval.h"

#include <QtWidgets>

static QHBoxLayout *mkRgbBox(MainWindow *win, RgbSlider *slider, RgbSpinner *spinner, QChar c) {
    auto box = new QHBoxLayout();
    box->setSpacing(3);
    box->addStretch();
    box->addWidget(slider);
    box->addWidget(new CmpLabel(win, c));
    box->addWidget(spinner);
    box->addSpacing(indicatorSize);
    return box;
}

static QHBoxLayout *mkHsvBox(MainWindow *win, HsvSpinner *spinner, QChar c) {
    auto box = new QHBoxLayout();
    box->setSpacing(0);
    box->addSpacing(indicatorSize);
    box->addWidget(new CmpLabel(win, c));
    box->addSpacing(3);
    box->addWidget(spinner);
    box->addStretch();
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
    auto redBox = mkRgbBox(this, redslider, redSpinner, 'R');

    auto greenSpinner = new GreenSpinner(this, color);
    auto greenBox = mkRgbBox(this, greenslider, greenSpinner, 'G');

    auto blueSpinner = new BlueSpinner(this, color);
    auto blueBox = mkRgbBox(this, blueslider, blueSpinner, 'B');

    auto hueSpinner = new HueSpinner(this, color);
    auto hueBox = mkHsvBox(this, hueSpinner, 'H');

    auto satSpinner = new SatSpinner(this, color);
    auto satBox = mkHsvBox(this, satSpinner, 'S');

    auto valSpinner = new ValSpinner(this, color);
    auto valBox = mkHsvBox(this ,valSpinner, 'V');

    auto stdPalette  = new Palette(this, QStringLiteral("Standard Palette"), color, stdPalColors, stdPalCount);
    auto userPalette = new Palette(this, QStringLiteral("User Palette"), color);
    userPalette->setDroppable();

    auto currColor = new CurrentColorDisplay(this, color);

    auto lbl = new QLabel(this);
    lbl->setText(QStringLiteral("Hex:"));
    hueBox->addWidget(lbl);
    auto hexFmt = new HexFmt(this, color);
    hueBox->addWidget(hexFmt);
    hueBox->addSpacing(indicatorSize);

    lbl = new QLabel(this);
    lbl->setText(QStringLiteral("RGB:"));
    satBox->addWidget(lbl);
    auto rgbFmt = new RgbFmt(this, color);
    satBox->addWidget(rgbFmt);
    satBox->addSpacing(indicatorSize);

    auto vbox = new QVBoxLayout();
    vbox->setSpacing(spacing);
    vbox->addWidget(stdPalette);
    vbox->addWidget(userPalette);
    vbox->addStretch();
    vbox->addWidget(currColor);
    vbox->addSpacing(1);

    auto grid = new QGridLayout(this);
    grid->setSizeConstraint(QLayout::SetFixedSize); // no resize window
    constexpr int m = margin - indicatorSize;
    grid->setContentsMargins(m, m, m, m);
    grid->setHorizontalSpacing(spacing);
    grid->setVerticalSpacing(spacing);
    grid->addWidget(satval, 0, 0, Qt::AlignTop);
    grid->addWidget(hueslider, 0, 1, Qt::AlignTop);
    grid->addLayout(redBox, 1, 0);
    grid->addLayout(greenBox, 2, 0);
    grid->addLayout(blueBox, 3, 0);
    grid->addLayout(hueBox, 1, 1, 1, 2);
    grid->addLayout(satBox, 2, 1, 1, 2);
    grid->addLayout(valBox, 3, 1, 1, 2);
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
    connect(&color, &Color::changed, hueSpinner, &HueSpinner::colorChanged);
    connect(&color, &Color::changed, satSpinner, &SatSpinner::colorChanged);
    connect(&color, &Color::changed, valSpinner, &ValSpinner::colorChanged);
    connect(&color, &Color::changed, currColor, &CurrentColorDisplay::colorChanged);
    connect(&color, &Color::changed, hexFmt, &HexFmt::colorChanged);
    connect(&color, &Color::changed, rgbFmt, &RgbFmt::colorChanged);

    color.setHue(204.0f);

    satval->setFocus();
}


CmpLabel::CmpLabel(QWidget *parent, QChar c)
    : QLabel(parent)
{
    QString text(c);
    text.append(':');
    setText(text);
    setAlignment(Qt::AlignRight);
    setMinimumWidth(rgbLabelWidth);
    setMaximumWidth(rgbLabelWidth);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);


}
