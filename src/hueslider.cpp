#include "colorpicker.h"
#include "color.h"
#include "hueslider.h"

#include <QtGui>
#include <QtWidgets>

#include <algorithm>

HueSlider::HueSlider(QWidget *parent, Color &c)
    : QWidget(parent), color(c), hue(-1)
{
    setMinimumSize(hsWidth, hsHeight);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
}

void HueSlider::paintEvent(QPaintEvent *event) {
    (void)event;

    QPainter painter(this);

    // gutters - necessary?
    painter.eraseRect(0, 0, indicatorSize, hsHeight);
    painter.eraseRect(indicatorSize + barWidth, 0, indicatorSize, hsHeight);

    // hues
    for (int y = 0; y < svSize; y++) {
        constexpr int l = indicatorSize, r = indicatorSize + barWidth - 1;
        float h = svSize1 - y;
        painter.setPen(Color(h, 1.0f, 0.95f).toQColor());
        int y_ = indicatorSize + y;
        painter.drawLine(l, y_, r, y_);
    }

    // indicators
    painter.setPen(Qt::white);
    painter.setBrush(Qt::white);
    int h = std::clamp(static_cast<int>(hue), 0, svSize1);
    int y = indicatorSize + svSize1 - h;
    constexpr int sz = indicatorSize - 1; // 1px gap
    QPoint lind[] = {{-1, y-sz}, {sz-1, y}, {-1, y+sz}, {-1, y-sz}};
    painter.drawPolygon(lind, 4);
    constexpr int hsw = hsWidth;
    QPoint rind[] = {{hsw, y-sz}, {hsw-sz, y}, {hsw, y+sz}, {hsw, y-sz}};
    painter.drawPolygon(rind, 4);

    painter.end();
}

void HueSlider::mouseMoveEvent(QMouseEvent *event) {
    mousePressEvent(event);
}

void HueSlider::mousePressEvent(QMouseEvent *event) {
    int h = std::clamp(svSize1 - (event->pos().y() - indicatorSize), 0, svSize1);
    if (h != hue) color.setHue(static_cast<float>(h));
}

void HueSlider::wheelEvent(QWheelEvent *event) {
    if (event->source() == Qt::MouseEventSynthesizedBySystem) {
        QPoint delta = event->pixelDelta();
        if (delta.y() != 0) color.setHue(hue + delta.y());
    } else {
        QPoint delta = event->angleDelta();
        if (delta.y() < 0) color.setHue(hue - 1);
        else if (delta.y() > 0) color.setHue(hue + 1);
    }
}

void HueSlider::colorChanged() {
    if (hue != color.getHue()) {
        hue = color.getHue();
        update(rect()); // repaint
    }
}
