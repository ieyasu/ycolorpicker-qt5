#include "colorpicker.h"
#include "mainwindow.h"

#include <QtCore>
#include <QtWidgets>

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
    QApplication::setWindowIcon(QIcon(":images/app-128.png"));

    setPalette();

    MainWindow mainWin;
    mainWin.show();

    return app.exec();
}
