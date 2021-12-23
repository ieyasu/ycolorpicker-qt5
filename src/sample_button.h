#ifndef SAMPLE_BUTTON_H
#define SAMPLE_BUTTON_H

#include "push_button.h"

class Color;
class QMouseEvent;

class SampleButton : public ImageButton {
    Q_OBJECT
public:
    SampleButton(QWidget *parent, Color &c);

protected:
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void clicked();
    void readPixel();

private:
    Color &color;
    bool grabbing;
};

#endif // SAMPLE_BUTTON_H
