/* currcolordisplay.h - display the current color in YColorPicker
 * Copyright 2022 Matthew S. Bishop
 *
 * This program is licensed under the terms of the GNU GPL version 3. See the
 * file LICENSE.txt or <https://www.gnu.org/licenses/> for details.
 */
#ifndef CURRCOLORDISPLAY_H
#define CURRCOLORDISPLAY_H

#include "color.h"

#include <QPoint>
#include <QRect>
#include <QWidget>

enum CcdOver {
    OVER_NONE,
    OVER_FG,
    OVER_BG,
    OVER_CURR,
};

class CurrentColorDisplay : public QWidget {
    Q_OBJECT
public:
    CurrentColorDisplay(QWidget *parent, Color &c);

public Q_SLOTS:
    void colorChanged();

protected:
    virtual bool event(QEvent *event) override;
    virtual void dragEnterEvent(QDragEnterEvent *event) override;
    virtual void dragMoveEvent(QDragMoveEvent *event) override;
    virtual void dropEvent(QDropEvent *event) override;
    virtual void paintEvent(QPaintEvent *event) override;
    virtual void leaveEvent(QEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;

private:
    Color &color;
    Color fgColor, bgColor;
    QRect fgRect, bgRect;
    QRect swapFgBgRect;
    QRect bwRect;
    QRect currClrRect;
    QPoint pt;
    CcdOver downOver;
    CcdOver over;

    void startDrag();
};

#endif // CURRCOLORDISPLAY_H
