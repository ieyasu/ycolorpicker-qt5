// satval.cpp - Saturation/Value Selector Widget
#include "colorpicker.h"
#include "color.h"
#include "satval.h"

#include <QtCore>
#include <QtGui>

#include <algorithm>

static constexpr double svSizeD1 = svSize1;

SaturationValue::SaturationValue(QWidget *parent, Color &c)
    : QWidget(parent), square(svSize, svSize), color(c), hue(-1)
{
    constexpr int size = svSize + 2 * indicatorSize;
    setMinimumSize(size, size);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    setFocusPolicy(Qt::StrongFocus);
    setCursor(Qt::CrossCursor);
}

void SaturationValue::paintEvent(QPaintEvent *event) {
    (void)event;
    QPainter painter(this);
    painter.drawPixmap(QPoint(indicatorSize, indicatorSize), square);

    // circle indicator
    painter.setRenderHint(QPainter::Antialiasing);
    auto pen = (color.getSat() < 0.45f && color.getVal() > 0.55f) ? Qt::black : Qt::white;
    painter.setPen(pen);
    int x = static_cast<int>(color.getSat() * svSizeD1);
    int y = static_cast<int>((1 - color.getVal()) * svSizeD1);
    int sz = 2 * indicatorSize + 1;
    painter.drawArc(x, y, sz, sz, 0, 5760);
}

void SaturationValue::paintSquare() {
    QPainter painter(&square);

    for (int y = 0; y < svSize; y++) {
        double v = (svSize - y) / svSizeD1;
        for (int x = 0; x < svSize; x++) {
            double s = x / svSizeD1;
            painter.setPen(Color(hue, s, v).toQColor());
            painter.drawPoint(x, y);
        }
    }
}

void SaturationValue::keyPressEvent(QKeyEvent *event) {
    constexpr double frac = 1 / svSizeD1;
    switch (event->key()) {
    case Qt::Key_Left:
        color.setSat(color.getSat() - frac);
        break;
    case Qt::Key_Right:
        color.setSat(color.getSat() + frac);
        break;
    case Qt::Key_Up:
        color.setVal(color.getVal() + frac);
        break;
    case Qt::Key_Down:
        color.setVal(color.getVal() - frac);
        break;
    }
}

void SaturationValue::mouseMoveEvent(QMouseEvent *event) {
    setSatVal(event->pos());
}

void SaturationValue::mousePressEvent(QMouseEvent *event) {
    setSatVal(event->pos());
    setCursor(Qt::BlankCursor);
}

void SaturationValue::setSatVal(const QPoint &pos) {
    int s = std::clamp(pos.x() - indicatorSize, 0, svSize1);
    int v = std::clamp(svSize1 - (pos.y() - indicatorSize), 0, svSize1);
    color.setSatVal(s / svSizeD1, v / svSizeD1);
}

void SaturationValue::mouseReleaseEvent(QMouseEvent *event) {
    setCursor(Qt::CrossCursor);
}

void SaturationValue::colorChanged() {
    if (hue != color.getHue()) {
        hue = color.getHue();
        paintSquare();
    }
    update(rect()); // repaint
}
