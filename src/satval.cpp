// satval.cpp - Saturation/Value Selector Widget
#include "color.h"
#include "satval.h"

#include <QtGui>

static constexpr int svSize = 360;
static constexpr int svSize1 = svSize - 1;
static constexpr float svSizeF1 = svSize1;

SaturationValue::SaturationValue(QWidget *parent, Color &c)
    : QWidget(parent), color(c), hue(c.getHue())
{
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
}

QSize SaturationValue::sizeHint() const {
    return QSize(svSize, svSize);
}

void SaturationValue::paintEvent(QPaintEvent *event) {
    (void)event;

    QPainter painter(this);

    hue = 240;

    for (int y = 0; y < svSize; y++) {
        float v = (svSize - y) / svSizeF1;
        for (int x = 0; x < svSize; x++) {
            float s = x / svSizeF1;
            painter.setPen(Color(hue, s, v).toQColor());
            painter.drawPoint(x, y);
        }
    }

    painter.end();
}

void SaturationValue::mouseMoveEvent(QMouseEvent *event) {
    pt = event->pos();
    color.setSatVal(pt.x() / svSizeF1, (svSize1 - pt.y()) / svSizeF1);
}

void SaturationValue::updateColor() {
    if (hue != color.getHue()) {
        hue = color.getHue();
        update(rect()); // repaint
    }
}
