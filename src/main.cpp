#include <QtCore>
#include <QtWidgets>

int main(int argc, char **argv) {
    QApplication app(argc, argv);

    QWidget window;
    window.resize(250, 150);
    window.setWindowTitle("Color Picker");
    window.show();

    return app.exec();
}
