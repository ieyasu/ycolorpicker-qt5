#ifndef CURRCOLORDISPLAY_H
#define CURRCOLORDISPLAY_H

#include <QRect>
#include <QWidget>

class CurrentColorDisplay : public QWidget {
    Q_OBJECT
public:
    CurrentColorDisplay(QWidget *parent, Color &c);

public Q_SLOTS:
    void colorChanged();

protected:
    virtual void paintEvent(QPaintEvent *event) override;

private:
    Color &color;
    Color fgColor, bgColor;
    QRect fgRect, bgRect;
    QRect swapFgBgRect;
    QRect bwRect;
};

#endif // CURRCOLORDISPLAY_H
