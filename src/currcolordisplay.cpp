#include "colorpicker.h"
#include "color.h"
#include "currcolordisplay.h"
#include "sample_button.h"

#include <QtGui>
#include <QtWidgets>

constexpr int swapSize = fgbgSize - fgbgOff - 3;
constexpr int bwSize = swapSize/2;
constexpr int pd = indicatorSize;
constexpr int currClrX1 = pd + (cbSize + spacing) * 2;
constexpr int currClrSize = cbSize * 2 + spacing - 1;

static QColor white(255, 255, 255);
static QColor black(0, 0, 0);

CurrentColorDisplay::CurrentColorDisplay(QWidget *parent, Color &c)
    : QWidget(parent), color(c),
      fgColor(black), bgColor(white),
      fgRect(pd, pd, fgbgSize, fgbgSize),
      bgRect(pd + fgbgSize - fgbgOff, pd + fgbgSize - fgbgOff, fgbgSize, fgbgSize),
      swapFgBgRect(pd + fgbgAreaSize - swapSize, pd, swapSize, swapSize),
      bwRect(pd, pd + fgbgAreaSize - swapSize + 1, swapSize, swapSize),
      currClrRect(currClrX1, pd, currClrAreaSize, currClrAreaSize),
      downOver(OVER_NONE)
{
    setMinimumSize(currcdWidth, currcdHeight);
    setAcceptDrops(true);

    auto sample = new SampleButton(this, c);
    auto sz = sample->sizeHint();
    sample->move(bgRect.right() - sz.width(), pd + currClrAreaSize - currClrSize);
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
    painter.drawRect(currClrRect);
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

void CurrentColorDisplay::dragEnterEvent(QDragEnterEvent *event) {
    event->acceptProposedAction();
}

void CurrentColorDisplay::dragMoveEvent(QDragMoveEvent *event) {
    if (event->mimeData()->hasColor()) {
        QRect r = event->answerRect();
        if (fgRect.intersects(r) || bgRect.intersects(r) || currClrRect.intersects(r)) {
            event->acceptProposedAction();
        }
    }
}

void CurrentColorDisplay::dropEvent(QDropEvent *event) {
    auto data = event->mimeData();
    auto pa = event->proposedAction();
    if (!data->hasColor() || (pa != Qt::MoveAction && pa != Qt::CopyAction)) return;

    auto c = qvariant_cast<QColor>(data->colorData());
    if (fgRect.contains(event->pos())) {
        fgColor = c;
    } else if (bgRect.contains(event->pos())) {
        bgColor = c;
    } else if (currClrRect.contains(event->pos())) {
        color = c;
    }
    update(rect());
}

void CurrentColorDisplay::leaveEvent(QEvent *event) {
    if (downOver != OVER_NONE) startDrag();
}

void CurrentColorDisplay::mouseMoveEvent(QMouseEvent *event) {
    if ((event->pos() - pt).manhattanLength() >= QApplication::startDragDistance() &&
        downOver != OVER_NONE) startDrag();
}

void CurrentColorDisplay::mousePressEvent(QMouseEvent *event) {
    if ((event->buttons() & Qt::LeftButton) == 0) return;

    if (fgRect.contains(event->pos())) {
        downOver = OVER_FG;
        pt = event->pos();
    } else if (bgRect.contains(event->pos())) {
        downOver = OVER_BG;
        pt = event->pos();
    } else if (currClrRect.contains(event->pos())) {
        downOver = OVER_CURR;
        pt = event->pos();
    } else if (bwRect.contains(event->pos())) { // reset fg/bg to black/white
        fgColor = black;
        bgColor = white;
        update(rect());
    } else if (swapFgBgRect.contains(event->pos())) { // swap bg/fg colors
        Color tmp = fgColor;
        fgColor = bgColor;
        bgColor = tmp;
        update(rect());
    }
}

void CurrentColorDisplay::mouseReleaseEvent(QMouseEvent *event) {
    if (downOver != OVER_NONE && (event->buttons() & Qt::LeftButton) == 0) {
        downOver = OVER_NONE;
    }
}

void CurrentColorDisplay::colorChanged() {
    update(rect()); // repaint
}

void CurrentColorDisplay::startDrag() {
    auto over = downOver;
    downOver = OVER_NONE; // prevent other events from starting drag
    QColor c;
    switch (over) {
    case OVER_NONE:
        abort();
        break;
    case OVER_FG:
        c = fgColor.toQColor();
        break;
    case OVER_BG:
        c = bgColor.toQColor();
        break;
    case OVER_CURR:
        c = color.toQColor();
        break;
    }
    auto drag = new QDrag(this);
    auto data = new QMimeData;
    data->setColorData(c);
    drag->setMimeData(data);
    drag->exec(Qt::CopyAction | Qt::MoveAction);
}
