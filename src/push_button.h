/* push_button.h - custom-look push button for YColorPicker
 * Copyright 2022 Matthew S. Bishop
 *
 * This program is licensed under the terms of the GNU GPL version 3. See the
 * file LICENSE.txt or <https://www.gnu.org/licenses/> for details.
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

signals:
    void clicked();

protected:
    virtual void enterEvent(QEvent *event) override;
    virtual void leaveEvent(QEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;

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

class TextButton : public PushButton {
    Q_OBJECT
public:
    TextButton(QWidget *parent, const QString &label);

    virtual QSize sizeHint() const;

protected:
    virtual void keyPressEvent(QKeyEvent *event) override;
    virtual void paintEvent(QPaintEvent *event) override;
    virtual void focusInEvent(QFocusEvent *event) override;
    virtual void focusOutEvent(QFocusEvent *event) override;

private:
    QString text;
};

#endif // PUSH_BUTTON_H
