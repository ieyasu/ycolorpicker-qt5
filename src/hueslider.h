#ifndef HUESLIDER_H
#define HUESLIDER_H

#include <QWidget>

class Color;

class HueSlider : public QWidget {
    Q_OBJECT
public:
    explicit HueSlider(QWidget *parent, Color &c);

public Q_SLOTS:
    void updateColor();

protected:
    virtual void paintEvent(QPaintEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;

private:
    Color &color;
    float hue;
};

#endif // HUESLIDER_H
