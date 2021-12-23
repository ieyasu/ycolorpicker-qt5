/* push_button.cpp - Custom-look push button classes.
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
        if (rect().contains(event->pos())) clicked();
    }
}

void PushButton::clicked() {}



ImageButton::ImageButton(QWidget *parent, const QString &filename)
    : PushButton(parent), pixmap(filename) {}

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

    painter.drawPixmap(1, 1, pixmap);
}
