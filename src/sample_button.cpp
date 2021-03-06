/* sample_button.cpp - widget for reading a pixel from somewhere on the screen in YColorPicker
 * Copyright 2022 Matthew S. Bishop
 *
 * This program is licensed under the terms of the GNU GPL version 3. See the
 * file LICENSE.txt or <https://www.gnu.org/licenses/> for details.
 */
#include "color.h"
#include "sample_button.h"

#include <QtGui>
#include <QtWidgets>

SampleButton::SampleButton(QWidget *parent, Color &c)
    : ImageButton(parent, ":/images/dropper_btn.png"),
      color(c), grabbing(false)
{
    connect(this, SIGNAL(clicked()), this, SLOT(startGrab()));
}

void SampleButton::startGrab() {
    QCursor cursor(QPixmap(":/images/dropper_cur.png"), 8, 19);
    grabMouse(cursor);
    grabbing = true;
}

void SampleButton::mousePressEvent(QMouseEvent *event) {
    QPoint pos = event->pos();
    if (grabbing) {
        releaseMouse();
        grabbing = false;
        readPixel();
    } else {
        ImageButton::mousePressEvent(event);
    }
}

/* Uses QScreen::grabWindow() to access the pixel at the mouse cursor position.
 *
 * On my (MSB) setup with two physical screens in X11, the current screen and
 * cursor position don't match up in the expected way: the QScreen doesn't
 * change when I move the app window between them, and the cursor coordinates
 * can be outside the screen's width/height depending on which screen I click
 * in. The solution is to loop through the screens until the cursor is found to
 * be inside one of them, then the cursor's coordinates need to be adjusted by
 * the screen's x/y offset. Have not tested on Windows or Mac.
 */
void SampleButton::readPixel() {
    QPoint pos = QCursor::pos();
    QScreen *screen = nullptr;
    auto screens = QGuiApplication::screens();
    for (int i = 0; i < screens.size(); i++) {
        auto geom = screens[i]->geometry();
        if (geom.contains(pos)) {
            screen = screens[i];
            pos.setX(pos.x() - geom.x());
            pos.setY(pos.y() - geom.y());
            break;
        }
    }
    if (screen) {
        auto pixmap = screen->grabWindow(0, pos.x(), pos.y(), 1, 1);
        auto image = pixmap.toImage();
        color = image.pixelColor(0, 0);
    } else {
        auto msg = QString("Couldn't find screen at mouse position (%1,%2)")
            .arg(pos.x()).arg(pos.y());
        QMessageBox::critical(this, "Error Sampling Pixel", msg);
    }
}
