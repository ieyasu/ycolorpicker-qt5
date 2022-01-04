/* hueslider.h - widget to select the hue in YColorPicker
 * Copyright 2022 Matthew S. Bishop
 *
 * This program is licensed under the terms of the GNU GPL version 3. See the
 * file LICENSE.txt or <https://www.gnu.org/licenses/> for details.
 */
#ifndef HUESLIDER_H
#define HUESLIDER_H

#include <QWidget>

class Color;

class HueSlider : public QWidget {
    Q_OBJECT
public:
    explicit HueSlider(QWidget *parent, Color &c);

public Q_SLOTS:
    void colorChanged();

protected:
    virtual void paintEvent(QPaintEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void wheelEvent(QWheelEvent *event) override;

private:
    Color &color;
    double hue;
};

#endif // HUESLIDER_H
