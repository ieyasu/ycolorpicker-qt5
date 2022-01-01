#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "color.h"

#include <QChar>
#include <QLabel>
#include <QString>
#include <QWidget>

class Palette;

class MainWindow : public QWidget {
    Q_OBJECT
public:
    explicit MainWindow();

protected:
    virtual void closeEvent(QCloseEvent *event) override;

private:
    Color color;
    Palette *userPalette;

    void readUserPalette();
    QString paletteFile();
};

class CmpLabel : public QLabel {
    Q_OBJECT
public:
    CmpLabel(QWidget *parent, QChar c);
};

#endif // MAINWINDOW_H
