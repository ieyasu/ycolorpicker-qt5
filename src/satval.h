/* satval.h - saturation/value selector widget for YColorPicker
 * Copyright 2022 Matthew S. Bishop
 *
 * This program is licensed under the terms of the GNU GPL version 3. See the
 * file LICENSE.txt or <https://www.gnu.org/licenses/> for details.
 */
#ifndef SATVAL_H
#define SATVAL_H

#include <QPixmap>
#include <QPoint>
#include <QWidget>

class Color;

class SaturationValue : public QWidget {
    Q_OBJECT
public:
    explicit SaturationValue(QWidget *parent, Color &c);

public Q_SLOTS:
    void colorChanged();

protected:
    virtual void paintEvent(QPaintEvent *event) override;
    virtual void keyPressEvent(QKeyEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;

private:
    QPixmap square;
    Color &color;
    double hue;

    void paintSquare();
    void setSatVal(const QPoint &pos);
};

#endif // SATVAL_H
