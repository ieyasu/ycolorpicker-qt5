/* satval.cpp - saturation/value selector widget for YColorPicker
 * Copyright 2022 Matthew S. Bishop
 *
 * This program is licensed under the terms of the GNU GPL version 3. See the
 * file LICENSE.txt or <https://www.gnu.org/licenses/> for details.
 */
#include "colorpicker.h"
#include "color.h"
#include "satval.h"

#include <QtCore>
#include <QtGui>

#include <algorithm>
#include <math.h>

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
    double sat = color.getSat(), val = color.getVal();
    double v = 1 - color.getVal();
    double hue = color.getHue();
    int u;
    if (hue < 25 || hue > 219) { // dark hue - use distance from top-left corner
        double dist = sqrt(sat * sat + v * v);
        u = (dist < 0.5) ? 0 : 255;
    } else { // light hue - use line
        u = (v < 0.5 - 0.15 * sat) ? 0 : 255;
    }
    QPen pen(qRgb(u, u, u));
    pen.setWidth(2);
    painter.setPen(pen);
    painter.setRenderHint(QPainter::Antialiasing);
    int x = static_cast<int>(sat * svSizeD1);
    int y = static_cast<int>(v * svSizeD1);
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
