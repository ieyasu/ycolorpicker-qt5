#ifndef CURRCOLORDISPLAY_H
#define CURRCOLORDISPLAY_H

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

    void startDrag();
};

#endif // CURRCOLORDISPLAY_H
