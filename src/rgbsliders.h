/* rgbsliders.h - widgets for selecting R/G/B color components in YColorPicker
 * Copyright 2022 Matthew S. Bishop
 *
 * This program is licensed under the terms of the GNU GPL version 3. See the
 * file LICENSE.txt or <https://www.gnu.org/licenses/> for details.
 */
#ifndef RGBSLIDERS_H
#define RGBSLIDERS_H

#include <QWidget>

class QPainter;
class Color;

class RgbSlider : public QWidget {
    Q_OBJECT
public:
    explicit RgbSlider(QWidget *parent, Color &c);

public Q_SLOTS:
    void repaint();

protected:
    Color &color;
    int value;

    void paint(QPainter &painter);
    void setValue(int x);
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void wheelEvent(QWheelEvent *event) override;
    virtual void updateColor() = 0;
};

class RedSlider : public RgbSlider {
    Q_OBJECT
public:
    explicit RedSlider(QWidget *parent, Color &c);

public Q_SLOTS:
    void colorChanged();

protected:
    virtual void updateColor();
    virtual void paintEvent(QPaintEvent *event) override;
};

class GreenSlider : public RgbSlider {
    Q_OBJECT
public:
    explicit GreenSlider(QWidget *parent, Color &c);

public Q_SLOTS:
    void colorChanged();

protected:
    virtual void updateColor();
    virtual void paintEvent(QPaintEvent *event) override;
};

class BlueSlider : public RgbSlider {
    Q_OBJECT
public:
    explicit BlueSlider(QWidget *parent, Color &c);

public Q_SLOTS:
    void colorChanged();

protected:
    virtual void updateColor();
    virtual void paintEvent(QPaintEvent *event) override;
};

#endif // RGBSLIDERS_H
