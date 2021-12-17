#include "mainwindow.h"

#include <QtCore>
#include <QtWidgets>

const QColor mainBackground(70, 70, 70);
const QColor editBackground(50, 50, 50);
const QColor btnBackground(97, 97, 152);
const QColor hilight(86, 131, 198);

static void setPalette() {
    auto pal = QGuiApplication::palette();
    pal.setColor(QPalette::Window,     mainBackground);
    pal.setColor(QPalette::WindowText, Qt::white);
    pal.setColor(QPalette::Base,       editBackground);
    pal.setColor(QPalette::Text,       Qt::white);
    pal.setColor(QPalette::Button,     btnBackground);
    pal.setColor(QPalette::ButtonText, Qt::white);
    pal.setColor(QPalette::BrightText, Qt::white);
    pal.setColor(QPalette::Highlight,  hilight);
    QApplication::setPalette(pal);
}

int main(int argc, char **argv) {
    QApplication app(argc, argv);

    setPalette();

    MainWindow mainWin;
    mainWin.show();

    return app.exec();
}
