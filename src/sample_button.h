/* sample_button.h - widget for reading a pixel from somewhere on the screen in YColorPicker
 * Copyright 2022 Matthew S. Bishop
 *
 * This program is licensed under the terms of the GNU GPL version 3. See the
 * file LICENSE.txt or <https://www.gnu.org/licenses/> for details.
 */
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
    void readPixel();

protected slots:
    void startGrab();

private:
    Color &color;
    bool grabbing;
};

#endif // SAMPLE_BUTTON_H
