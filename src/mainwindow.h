#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "color.h"

#include <QWidget>

class HueSlider;
class RedSlider;
class GreenSlider;
class BlueSlider;
class SaturationValue;

class MainWindow : public QWidget {
    Q_OBJECT
public:
    explicit MainWindow();

private:
    Color color;
    SaturationValue *satval;
    HueSlider *hueslider;
    RedSlider *redslider;
    GreenSlider *greenslider;
    BlueSlider *blueslider;
};

#endif // MAINWINDOW_H
