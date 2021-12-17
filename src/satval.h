// satval.h - Saturation/Value Selector Widget
#ifndef SATVAL_H
#define SATVAL_H

#include <QPoint>
#include <QWidget>

class Color;

class SaturationValue : public QWidget {
    Q_OBJECT
public:
    explicit SaturationValue(QWidget *parent, Color &c);

    virtual QSize sizeHint() const override;

public Q_SLOTS:
    void updateColor();

protected:
    virtual void paintEvent(QPaintEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;

private:
    Color &color;
    QPoint pt;
    float hue;
};

#endif // SATVAL_H
