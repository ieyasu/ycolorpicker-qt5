#include "mainwindow.h"

#include <QtCore>
#include <QtWidgets>

const QColor mainBackground(70, 70, 70);

static void setPalette() {
    auto pal = QGuiApplication::palette();
    pal.setColor(QPalette::Window, mainBackground);
    pal.setColor(QPalette::WindowText, Qt::white);
    pal.setColor(QPalette::Text, Qt::white);
    QApplication::setPalette(pal);
}

int main(int argc, char **argv) {
    QApplication app(argc, argv);

    setPalette();

    MainWindow mainWin;
    mainWin.show();

    return app.exec();
}
