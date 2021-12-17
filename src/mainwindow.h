#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "color.h"

#include <QWidget>

class HueSlider;
class SaturationValue;

class MainWindow : public QWidget {
    Q_OBJECT
public:
    explicit MainWindow();

private:
    Color color;
    SaturationValue *satval;
    HueSlider *hueslider;
};

#endif // MAINWINDOW_H
