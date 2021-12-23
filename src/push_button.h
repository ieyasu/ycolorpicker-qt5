/* push_button.h - custom-look push button implementation.
 */
#ifndef PUSH_BUTTON_H
#define PUSH_BUTTON_H

#include <QPixmap>
#include <QSize>
#include <QWidget>

class PushButton : public QWidget {
    Q_OBJECT
public:
    PushButton(QWidget *parent);

protected:
    virtual void enterEvent(QEvent *event) override;
    virtual void leaveEvent(QEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    virtual void clicked();

    bool leftDown;
    bool hover;
};

class ImageButton : public PushButton {
    Q_OBJECT
public:
    ImageButton(QWidget *parent, const QString &filename);

    virtual QSize sizeHint() const;

protected:
    virtual void paintEvent(QPaintEvent *event) override;

private:
    QPixmap pixmap;
};

#endif // PUSH_BUTTON_H