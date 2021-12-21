#ifndef PALETTE_H
#define PALETTE_H

#include "colorpicker.h"
#include "color.h"

#include <QPoint>
#include <QWidget>
#include <vector>

class QString;

constexpr int stdPalCount = 20;
extern const RgbTriple stdPalColors[stdPalCount];

class ColorBox : public QWidget {
    Q_OBJECT
public:
    ColorBox(QWidget *parent, Color &appColor);

    void setRGB(const RgbTriple &triple) { color.setRGB(triple); update(rect()); }

protected:
    virtual void dragEnterEvent(QDragEnterEvent *event) override;
    virtual void dropEvent(QDropEvent *event) override;
    virtual void paintEvent(QPaintEvent *event) override;
    virtual void leaveEvent(QEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;

private:
    Color &appColor;
    Color color;
    QPoint pt;
    bool leftDown;

    void startDrag();
};

class Palette : public QWidget {
    Q_OBJECT
public:
    Palette(QWidget *parent, const QString &text, Color &appColor,
            const RgbTriple *initColors = nullptr, int initCount = 0);

    ColorBox *operator[](int i) { return colors[i]; }

    void setDroppable();
private:
    std::vector<ColorBox *> colors;
};

#endif // PALETTE_H
