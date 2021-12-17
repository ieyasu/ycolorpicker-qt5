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
    float hue;
};

#endif // HUESLIDER_H
