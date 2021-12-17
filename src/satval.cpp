// satval.cpp - Saturation/Value Selector Widget
#include "colorpicker.h"
#include "color.h"
#include "satval.h"

#include <QtGui>

static constexpr float svSizeF1 = svSize1;

SaturationValue::SaturationValue(QWidget *parent, Color &c)
    : QWidget(parent), color(c), hue(-1)
{
    constexpr int size = svSize + 2 * indicatorSize;
    setMinimumSize(size, size);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
}

void SaturationValue::paintEvent(QPaintEvent *event) {
    (void)event;

    QPainter painter(this);

    for (int y = 0; y < svSize; y++) {
        float v = (svSize - y) / svSizeF1;
        for (int x = 0; x < svSize; x++) {
            float s = x / svSizeF1;
            painter.setPen(Color(hue, s, v).toQColor());
            painter.drawPoint(x + indicatorSize, y + indicatorSize);
        }
    }

    painter.end();
}

void SaturationValue::mouseMoveEvent(QMouseEvent *event) {
    auto pos = event->pos();
    pt = QPoint(pos.x() - indicatorSize, pos.y() - indicatorSize);
    color.setSatVal(pt.x() / svSizeF1, (svSize1 - pt.y()) / svSizeF1);
}

void SaturationValue::colorChanged() {
    if (hue != color.getHue()) {
        hue = color.getHue();
        update(rect()); // repaint
    }
}
