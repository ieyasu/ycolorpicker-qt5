#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "color.h"

#include <QChar>
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

class CmpLabel : public QLabel {
    Q_OBJECT
public:
    CmpLabel(QWidget *parent, QChar c);
};

#endif // MAINWINDOW_H
