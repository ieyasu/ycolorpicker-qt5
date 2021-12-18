#include "palette.h"

#include <QtGui>
#include <QtWidgets>

const RgbTriple stdPalColors[stdPalCount] = {
    // row 1
    {  0,  0,  0},
    {127,127,127},
    {136,  0, 21},
    {237, 28, 36},
    {255,127, 39},
    {255,242,  0},
    { 34,177, 76},
    {  0,162,232},
    { 63, 72,204},
    {163, 73,164},
    // row 2
    {255,255,255},
    {194,194,194},
    {185,122, 87},
    {255,174,201},
    {255,201, 14},
    {239,228,176},
    {181,230, 29},
    {153,217,234},
    {112,146,190},
    {200,191,231},
};

Palette::Palette(
    QWidget *parent,
    const QString &text,
    Color &appColor,
    const RgbTriple *initColors, int initCount
)
    : QWidget(parent)
{
    auto grid = new QGridLayout(this);
    grid->setHorizontalSpacing(spacing);
    grid->setVerticalSpacing(spacing);
    auto lbl = new QLabel(this);
    lbl->setText(text);
    grid->addWidget(lbl, 0, 0, 1, -1);

    colors.reserve(20);
    for (int i = 0; i < colors.capacity(); i++) {
        auto cb = new ColorBox(this, appColor);
        if (i < initCount) cb->setRGB(initColors[i]);
        grid->addWidget(cb, 1 + i / 10, i % 10);
        colors.push_back(cb);
    }
}

// *********************************************************************

ColorBox::ColorBox(QWidget *parent, Color &ac)
    : QWidget(parent), appColor(ac), color(255, 255, 255),
      leftDown(false)
{
    setMinimumSize(cbSize, cbSize);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
}

void ColorBox::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setPen(Qt::white);
    painter.setBrush(color.toQColor());
    painter.drawRect(0, 0, cbSize1, cbSize1);
}

void ColorBox::mousePressEvent(QMouseEvent *event) {
    if (event->buttons() & Qt::LeftButton) {
        leftDown = true;
    }
}

void ColorBox::mouseReleaseEvent(QMouseEvent *event) {
    if (leftDown && (event->buttons() & Qt::LeftButton) == 0) {
        leftDown = false;
        if (rect().contains(event->pos())) appColor = color; // set current color
    }
}
