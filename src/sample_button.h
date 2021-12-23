#ifndef SAMPLE_BUTTON_H
#define SAMPLE_BUTTON_H

#include <QPushButton>

class Color;
class QMouseEvent;

class SampleButton : public QPushButton {
    Q_OBJECT
public:
    SampleButton(QWidget *parent, Color &c);

protected Q_SLOTS:
    void startSample(bool);

protected:
    virtual void mousePressEvent(QMouseEvent *event) override;
    void readPixel();

private:
    Color &color;
    bool grabbing;
};

#endif // SAMPLE_BUTTON_H
