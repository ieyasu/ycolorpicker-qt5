#include "mainwindow.h"

#include <QtCore>
#include <QtWidgets>

int main(int argc, char **argv) {
    QApplication app(argc, argv);

    MainWindow mainWin;
    mainWin.show();

    return app.exec();
}
