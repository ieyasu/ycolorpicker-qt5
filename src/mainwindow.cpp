#include "colorpicker.h"
#include "color.h"
#include "mainwindow.h"
#include "satval.h"

#include <QtWidgets>

MainWindow::MainWindow()
    : QWidget(nullptr),
      color(240, 0.8, 0.8, this),
      satval(new SaturationValue(this, color))
{
    setWindowTitle("Color Picker");
    setAutoFillBackground(true);

    auto grid = new QGridLayout(this);
    setLayout(grid);
    grid->setContentsMargins(margin, margin, margin, margin);
    grid->addWidget(satval, 0, 0);
}
