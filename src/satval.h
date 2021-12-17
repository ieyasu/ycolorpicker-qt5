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

public Q_SLOTS:
    void colorChanged();

protected:
    virtual void paintEvent(QPaintEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;

private:
    Color &color;
    QPoint pt;
    float hue;
};

#endif // SATVAL_H
