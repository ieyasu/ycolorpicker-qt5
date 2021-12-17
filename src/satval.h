// satval.h - Saturation/Value Selector Widget
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
    float hue;

    void paintSquare();
    void setSatVal(const QPoint &pos);
};

#endif // SATVAL_H
