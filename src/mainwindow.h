#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "color.h"

#include <QLabel>
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

class RgbLabel : public QLabel {
    Q_OBJECT
public:
    RgbLabel(QWidget *parent, const QString &text);
};

#endif // MAINWINDOW_H
