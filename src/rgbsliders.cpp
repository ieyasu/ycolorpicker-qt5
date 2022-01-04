/* rgbsliders.cpp - widgets for select R/G/B color components in YColorPicker
 * Copyright 2022 Matthew S. Bishop
 *
 * This program is licensed under the terms of the GNU GPL version 3. See the
 * file LICENSE.txt or <https://www.gnu.org/licenses/> for details.
 */
#include "colorpicker.h"
#include "color.h"
#include "rgbsliders.h"

#include <QtGui>

#include <algorithm>

RgbSlider::RgbSlider(QWidget *parent, Color &c)
    : QWidget(parent), color(c), value(-1)
{
    setMinimumSize(QSize(rgbWidth, rgbHeight));
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
}

void RgbSlider::repaint() {
    update(rect());
}

void RgbSlider::paint(QPainter &painter) {
    // indicators
    painter.setPen(Qt::white);
    painter.setBrush(Qt::white);
    constexpr int sz = indicatorSize - 1; // 1px gap
    int x = indicatorSize + value;
    QPoint tind[] = {{x-sz, -1}, {x+sz, -1}, {x, sz-1}, {x-sz, -1}};
    painter.drawPolygon(tind, 4);
    constexpr int y = rgbHeight;
    QPoint bind[] = {{x, y-sz}, {x+sz, y}, {x-sz, y}, {x, y-sz}};
    painter.drawPolygon(bind, 4);
}

void RgbSlider::setValue(int x) {
    x = std::clamp(x, 0, rgbSize1);
    if (x != value) { value = x; updateColor(); }
}

void RgbSlider::mouseMoveEvent(QMouseEvent *event) {
    mousePressEvent(event);
}

void RgbSlider::mousePressEvent(QMouseEvent *event) {
    setValue(event->pos().x() - indicatorSize);
}

void RgbSlider::wheelEvent(QWheelEvent *event) {
    if (event->source() == Qt::MouseEventSynthesizedBySystem) {
        QPoint delta = event->pixelDelta();
        if (delta.x() != 0) setValue(value + delta.x());
        else if (delta.y() != 0) setValue(value + delta.y());
    } else {
        QPoint delta = event->angleDelta();
        if (delta.x() < 0 || delta.y() < 0) setValue(value - 1);
        else if (delta.x() > 0 || delta.y() > 0) setValue(value + 1);
    }
}

// ********************************************************************

RedSlider::RedSlider(QWidget *parent, Color &c)
    : RgbSlider(parent, c) {}

void RedSlider::paintEvent(QPaintEvent *event) {
    (void)event;
    QPainter painter(this);
    paint(painter);

    constexpr int y1 = indicatorSize, y2 = indicatorSize + barHeight - 1;
    const int g = color.getG(), b = color.getB();
    for (int r = 0; r < rgbSize; r++) {
        painter.setPen(qRgb(r, g, b));
        int x = indicatorSize + r;
        painter.drawLine(x, y1, x, y2);
    }
}

void RedSlider::updateColor() {
    color.setR(value);
}

void RedSlider::colorChanged() {
    value = color.getR();
    repaint();
}

// ********************************************************************

GreenSlider::GreenSlider(QWidget *parent, Color &c)
    : RgbSlider(parent, c) {}

void GreenSlider::paintEvent(QPaintEvent *event) {
    (void)event;
    QPainter painter(this);
    paint(painter);

    constexpr int y1 = indicatorSize, y2 = indicatorSize + barHeight - 1;
    const int r = color.getR(), b = color.getB();
    for (int g = 0; g < rgbSize; g++) {
        painter.setPen(qRgb(r, g, b));
        int x = indicatorSize + g;
        painter.drawLine(x, y1, x, y2);
    }
}

void GreenSlider::updateColor() {
    color.setG(value);
}

void GreenSlider::colorChanged() {
    value = color.getG();
    repaint();
}

// ********************************************************************

BlueSlider::BlueSlider(QWidget *parent, Color &c)
    : RgbSlider(parent, c) {}

void BlueSlider::paintEvent(QPaintEvent *event) {
    (void)event;
    QPainter painter(this);
    paint(painter);

    constexpr int y1 = indicatorSize, y2 = indicatorSize + barHeight - 1;
    const int r = color.getR(), g = color.getG();
    for (int b = 0; b < rgbSize; b++) {
        painter.setPen(qRgb(r, g, b));
        int x = indicatorSize + b;
        painter.drawLine(x, y1, x, y2);
    }
}

void BlueSlider::updateColor() {
    color.setB(value);
}

void BlueSlider::colorChanged() {
    value = color.getB();
    repaint();
}
