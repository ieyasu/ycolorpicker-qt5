/* main.cpp - main function for YColorPicker
 * Copyright 2022 Matthew S. Bishop
 *
 * This program is licensed under the terms of the GNU GPL version 3. See the
 * file LICENSE.txt or <https://www.gnu.org/licenses/> for details.
 */
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
    pal.setColor(QPalette::Link,       linkColor);
    pal.setColor(QPalette::LinkVisited,visitedLink);
    QApplication::setPalette(pal);
}

int main(int argc, char **argv) {
    QApplication app(argc, argv);
    app.setApplicationDisplayName(QStringLiteral("ycolorpicker"));
    QApplication::setWindowIcon(QIcon(":images/app-128.png"));

    setPalette();

    QFont font = app.font();
    font.setPixelSize(14);
    app.setFont(font);

    MainWindow mainWin;
    mainWin.show();

    return app.exec();
}
