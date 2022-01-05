/* mainwindow.h - MainWindow class for YColorPicker
 * Copyright 2022 Matthew S. Bishop
 *
 * This program is licensed under the terms of the GNU GPL version 3. See the
 * file LICENSE.txt or <https://www.gnu.org/licenses/> for details.
 */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "color.h"

#include <QChar>
#include <QLabel>
#include <QString>
#include <QWidget>

class AboutDialog;
class Palette;

class MainWindow : public QWidget {
    Q_OBJECT
public:
    explicit MainWindow();

public slots:
    void showAbout();

protected:
    virtual void closeEvent(QCloseEvent *event) override;

private:
    Color color;
    Palette *userPalette;
    AboutDialog *aboutDlg;

    void readUserPalette();
    QString paletteFile();
};

class CmpLabel : public QLabel {
    Q_OBJECT
public:
    CmpLabel(QWidget *parent, QChar c);
};

#endif // MAINWINDOW_H
