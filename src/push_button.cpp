/* push_button.cpp - Custom-look push button for YColorPicker
 * Copyright 2022 Matthew S. Bishop
 *
 * This program is licensed under the terms of the GNU GPL version 3. See the
 * file LICENSE.txt or <https://www.gnu.org/licenses/> for details.
 */
#include "colorpicker.h"
#include "push_button.h"

#include <QtGui>
#include <QtWidgets>

PushButton::PushButton(QWidget *parent)
    : QWidget(parent), leftDown(false) {}

void PushButton::enterEvent(QEvent *event) {
    hover = true;
    update(rect());
}

void PushButton::leaveEvent(QEvent *event) {
    hover = false;
    update(rect());
}

void PushButton::mousePressEvent(QMouseEvent *event) {
    if (event->buttons() & Qt::LeftButton) {
        leftDown = true;
        update(rect());
    }
}

void PushButton::mouseReleaseEvent(QMouseEvent *event) {
    if (leftDown && (event->buttons() & Qt::LeftButton) == 0) {
        leftDown = false;
        update(rect());
        if (rect().contains(event->pos())) emit clicked();
    }
}



ImageButton::ImageButton(QWidget *parent, const QString &filename)
    : PushButton(parent), pixmap(filename)
{
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
}

QSize ImageButton::sizeHint() const {
    return pixmap.size() + QSize(2, 2);
}

void ImageButton::paintEvent(QPaintEvent *event) {
    (void)event;
    QPainter painter(this);

    auto bg = hover ? btnHover : btnBackground;
    painter.fillRect(0, 0, width(), height(), bg);

    painter.setPen(mainBackground);
    int x2 = width()-1, y2 = height()-1;
    QPoint corners[] = {{0,0}, {x2,0}, {0,y2}, {x2,y2}};
    painter.drawPoints(corners, 4);

    if (leftDown) {
        painter.setPen(outline);
        QLine lines[] = {
            { 1, 0,x2-1,   0}, // top
            { 0, 1,   0,y2-1}, // left
            {x2, 1,  x2,y2-1}, // right
            { 1,y2,x2-1,  y2}, // bottom
        };
        painter.drawLines(lines, 4);
    }

    int x = (width() - pixmap.width()) / 2;
    int y = (height() - pixmap.height()) / 2;
    painter.drawPixmap(x, y, pixmap);
}



TextButton::TextButton(QWidget *parent, const QString &label)
    : PushButton(parent), text(label)
{
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
}

QSize TextButton::sizeHint() const {
    QRect bounds = fontMetrics().boundingRect(text);
    return QSize(bounds.width() + spacing * 2, inputHeight);
}

void TextButton::paintEvent(QPaintEvent *event) {
    (void)event;
    QPainter painter(this);

    auto bg = hover ? btnHover : btnBackground;
    painter.fillRect(0, 0, width(), height(), bg);

    painter.setPen(mainBackground);
    int x2 = width()-1, y2 = height()-1;
    QPoint corners[] = {{0,0}, {x2,0}, {0,y2}, {x2,y2}};
    painter.drawPoints(corners, 4);

    if (leftDown) {
        painter.setPen(outline);
        QLine lines[] = {
            { 1, 0,x2-1,   0}, // top
            { 0, 1,   0,y2-1}, // left
            {x2, 1,  x2,y2-1}, // right
            { 1,y2,x2-1,  y2}, // bottom
        };
        painter.drawLines(lines, 4);
    }

    painter.setPen(Qt::white);
    painter.drawText(rect(), Qt::AlignCenter, text);
}
