#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "color.h"

#include <QWidget>

class SaturationValue;

class MainWindow : public QWidget {
    Q_OBJECT
public:
    explicit MainWindow();

private:
    Color color;
    SaturationValue *satval;
};

#endif // MAINWINDOW_H
