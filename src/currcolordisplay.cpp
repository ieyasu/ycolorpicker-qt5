#include "colorpicker.h"
#include "color.h"
#include "currcolordisplay.h"

#include <QtGui>

constexpr int swapSize = fgbgSize - fgbgOff - 3;
constexpr int bwSize = swapSize/2;
constexpr int pd = indicatorSize;
constexpr int currClrX1 = pd + (cbSize + spacing) * 2;
constexpr int currClrSize = cbSize * 2 + spacing - 1;

static Color white(255, 255, 255);
static Color black;

CurrentColorDisplay::CurrentColorDisplay(QWidget *parent, Color &c)
    : QWidget(parent), color(c),
      fgColor(black), bgColor(white),
      fgRect(pd, pd, fgbgSize, fgbgSize),
      bgRect(pd + fgbgSize - fgbgOff, pd + fgbgSize - fgbgOff, fgbgSize, fgbgSize),
      swapFgBgRect(pd + fgbgAreaSize - swapSize, pd, swapSize, swapSize),
      bwRect(pd, pd + fgbgAreaSize - swapSize + 1, swapSize, swapSize)
{
    setMinimumSize(currcdWidth, currcdHeight);
}

void CurrentColorDisplay::paintEvent(QPaintEvent *event) {
    (void)event;
    QPainter painter(this);

    // foreground/background colors
    painter.setPen(Qt::white);
    painter.setBrush(bgColor.toQColor());
    painter.drawRect(bgRect);
    painter.setBrush(fgColor.toQColor());
    painter.drawRect(fgRect);

    // swap arrows
    painter.setBrush(Qt::white);
    int sz = 3;
    int x1 = swapFgBgRect.x() + 1, y1 = swapFgBgRect.y() + sz + 1;
    QPoint pts[] = {{x1, y1}, {x1+sz, y1-sz}, {x1+sz, y1+sz}, {x1, y1}, {x1+sz, y1+sz}};
    painter.drawPolygon(pts, 5);
    int x2 = swapFgBgRect.right() - sz, y2 = swapFgBgRect.bottom();
    QPoint pts2[] = {{x2, y2}, {x2-sz, y2-sz}, {x2+sz, y2-sz}, {x2, y2}};
    painter.drawPolygon(pts2, 4);
    QPoint pts3[] = {{x1+sz, y1}, {x2, y1}, {x2, y2-sz}};
    painter.drawPolyline(pts3, 3);

    // set fg/bg to black/white
    painter.drawRect(bwRect.x() + bwSize, bwRect.y() + bwSize, bwSize, bwSize);
    painter.setPen(Qt::black);
    painter.setBrush(Qt::black);
    painter.drawRect(bwRect.x(), bwRect.y(), bwSize+1, bwSize+1);

    // current color area
    painter.setPen(Qt::white);
    painter.setBrush(color.toQColor());
    painter.drawRect(currClrX1, pd, currClrAreaSize, currClrAreaSize);
    int x = currClrX1 + currClrAreaSize - currClrSize;
    painter.fillRect(x, pd+1, currClrSize, currClrSize, fgColor.toQColor());
    sz = currClrSize / 3;
    painter.fillRect(x+sz+1, pd+sz+2, sz, sz, color.toQColor());
    int y = pd + currClrAreaSize - currClrSize;
    painter.fillRect(currClrX1+1, y, currClrSize, currClrSize, bgColor.toQColor());
    x = currClrX1 + sz + 2;
    painter.fillRect(x, y+sz+1, sz, sz, color.toQColor());

    // sample text
    auto text = QStringLiteral("Lorem ipsum");
    QFont font = painter.font();
    font.setPixelSize(14);
    font.setWeight(QFont::Bold);
    painter.setFont(font);
    constexpr int stX1 = pd + cbSize * 6 + spacing * 6;
    constexpr int stHeight = 27;
    QRect box(stX1, pd, cbSize * 4 + spacing * 3, stHeight);

    painter.fillRect(box, bgColor.toQColor());
    painter.setPen(color.toQColor());
    painter.setBrush(bgColor.toQColor());
    painter.drawText(box, Qt::AlignCenter, text);

    box.moveTop(box.top() + stHeight + 6);
    painter.fillRect(box, color.toQColor());
    painter.setPen(bgColor.toQColor());
    painter.setBrush(color.toQColor());
    painter.drawText(box, Qt::AlignCenter, text);

    box.moveTop(box.top() + stHeight + 12);
    painter.fillRect(box, fgColor.toQColor());
    painter.setPen(color.toQColor());
    painter.setBrush(bgColor.toQColor());
    painter.drawText(box, Qt::AlignCenter, text);

    box.moveTop(box.top() + stHeight + 6);
    painter.fillRect(box, color.toQColor());
    painter.setPen(fgColor.toQColor());
    painter.setBrush(color.toQColor());
    painter.drawText(box, Qt::AlignCenter, text);
}

void CurrentColorDisplay::colorChanged() {
    update(rect()); // repaint
}
