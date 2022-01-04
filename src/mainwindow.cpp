/* mainwindow.cpp - MainWindow class for YColorPicker
 * Copyright 2022 Matthew S. Bishop
 *
 * This program is licensed under the terms of the GNU GPL version 3. See the
 * file LICENSE.txt or <https://www.gnu.org/licenses/> for details.
 */
#include "colorpicker.h"
#include "color.h"
#include "color_formats.h"
#include "currcolordisplay.h"
#include "hueslider.h"
#include "mainwindow.h"
#include "palette.h"
#include "push_button.h"
#include "rgbsliders.h"
#include "component_spinners.h"
#include "satval.h"

#include <QtWidgets>

static QHBoxLayout *mkRgbBox(MainWindow *win, RgbSlider *slider, RgbSpinner *spinner, QChar c) {
    auto box = new QHBoxLayout();
    box->setSpacing(3);
    box->addStretch();
    box->addWidget(slider);
    box->addWidget(new CmpLabel(win, c));
    box->addWidget(spinner);
    box->addSpacing(indicatorSize);
    return box;
}

static QHBoxLayout *mkHsvBox(MainWindow *win, HsvSpinner *spinner, QChar c) {
    auto box = new QHBoxLayout();
    box->setSpacing(0);
    box->addSpacing(indicatorSize);
    box->addWidget(new CmpLabel(win, c));
    box->addSpacing(3);
    box->addWidget(spinner);
    box->addStretch();
    return box;
}

static ImageButton *addFmtField(MainWindow *win, QHBoxLayout *box, QWidget *fmt, const QString &text) {
    auto lbl = new QLabel(win);
    lbl->setText(text);
    box->addWidget(lbl);
    box->addSpacing(3);
    box->addWidget(fmt);
    box->addSpacing(3);
    auto clip = new ImageButton(win, ":images/to_clipboard.png");
    clip->setToolTip(QStringLiteral("Copy to clipboard"));
    box->addWidget(clip);
    box->addSpacing(indicatorSize);
    return clip;
}

MainWindow::MainWindow()
    : QWidget(nullptr),
      color(0.0f, 0.8f, 0.8f)
{
    setWindowTitle("Color Picker");
    setAutoFillBackground(true);

    auto satval = new SaturationValue(this, color);
    auto hueslider = new HueSlider(this, color);

    auto redslider = new RedSlider(this, color);
    auto redSpinner = new RedSpinner(this, color);
    auto redBox = mkRgbBox(this, redslider, redSpinner, 'R');

    auto greenslider = new GreenSlider(this, color);
    auto greenSpinner = new GreenSpinner(this, color);
    auto greenBox = mkRgbBox(this, greenslider, greenSpinner, 'G');

    auto blueslider = new BlueSlider(this, color);
    auto blueSpinner = new BlueSpinner(this, color);
    auto blueBox = mkRgbBox(this, blueslider, blueSpinner, 'B');

    auto hueSpinner = new HueSpinner(this, color);
    auto hueBox = mkHsvBox(this, hueSpinner, 'H');

    auto satSpinner = new SatSpinner(this, color);
    auto satBox = mkHsvBox(this, satSpinner, 'S');

    auto valSpinner = new ValSpinner(this, color);
    auto valBox = mkHsvBox(this ,valSpinner, 'V');

    auto stdPalette  = new Palette(this, QStringLiteral("Standard Palette"), color, stdPalColors, stdPalCount);
    userPalette = new Palette(this, QStringLiteral("User Palette"), color);
    userPalette->setDroppable();
    readUserPalette();

    auto currColor = new CurrentColorDisplay(this, color);

    auto hexFmt = new HexFmt(this, color);
    auto clip = addFmtField(this, satBox, hexFmt, QStringLiteral("Hex:"));
    connect(clip, SIGNAL(clicked()), hexFmt, SLOT(toClipboard()));

    auto rgbFmt = new RgbFmt(this, color);
    clip = addFmtField(this, valBox, rgbFmt, QStringLiteral("RGB:"));
    connect(clip, SIGNAL(clicked()), rgbFmt, SLOT(toClipboard()));

    auto vbox = new QVBoxLayout();
    vbox->setSpacing(spacing);
    vbox->addWidget(stdPalette);
    vbox->addWidget(userPalette);
    vbox->addStretch();
    vbox->addWidget(currColor);
    vbox->addSpacing(1);

    auto grid = new QGridLayout(this);
    grid->setSizeConstraint(QLayout::SetFixedSize); // no resize window
    constexpr int m = margin - indicatorSize;
    grid->setContentsMargins(m, m, m, m);
    grid->setHorizontalSpacing(spacing);
    grid->setVerticalSpacing(spacing);
    grid->addWidget(satval, 0, 0, Qt::AlignTop);
    grid->addWidget(hueslider, 0, 1, Qt::AlignTop);
    grid->addLayout(redBox, 1, 0);
    grid->addLayout(greenBox, 2, 0);
    grid->addLayout(blueBox, 3, 0);
    grid->addLayout(hueBox, 1, 1, 1, 2);
    grid->addLayout(satBox, 2, 1, 1, 2);
    grid->addLayout(valBox, 3, 1, 1, 2);
    grid->addLayout(vbox, 0, 2);
    setLayout(grid);

    connect(&color, &Color::changed, satval, &SaturationValue::colorChanged);
    connect(&color, &Color::changed, hueslider, &HueSlider::colorChanged);
    connect(&color, &Color::changed, redslider, &RedSlider::colorChanged);
    connect(&color, &Color::changed, redSpinner, &RedSpinner::colorChanged);
    connect(&color, &Color::changed, greenslider, &GreenSlider::colorChanged);
    connect(&color, &Color::changed, greenSpinner, &GreenSpinner::colorChanged);
    connect(&color, &Color::changed, blueslider, &BlueSlider::colorChanged);
    connect(&color, &Color::changed, blueSpinner, &BlueSpinner::colorChanged);
    connect(&color, &Color::changed, hueSpinner, &HueSpinner::colorChanged);
    connect(&color, &Color::changed, satSpinner, &SatSpinner::colorChanged);
    connect(&color, &Color::changed, valSpinner, &ValSpinner::colorChanged);
    connect(&color, &Color::changed, currColor, &CurrentColorDisplay::colorChanged);
    connect(&color, &Color::changed, hexFmt, &HexFmt::colorChanged);
    connect(&color, &Color::changed, rgbFmt, &RgbFmt::colorChanged);

    color.setHue(204.0f);

    satval->setFocus();
}

void MainWindow::closeEvent(QCloseEvent *event) {
    if (!userPalette->anyChanged()) return; // nothing to save

    // save user palette
    auto path = paletteFile();
    if (path.isEmpty()) return;
    QSaveFile fout(path);
    if (!fout.open(QIODevice::WriteOnly)) {
        QMessageBox::critical(this, QStringLiteral("Error Opening User Palette"), fout.errorString());
        return;
    }

    QString line;
    for (int i = 0; i < userPalette->size(); i++) {
        auto colorBox = userPalette->at(i);
        if (!colorBox->isWhite()) {
            line = QString("[%1] = #%2%3%4\n")
                .arg(i)
                .arg(colorBox->getR(), 2, 16, QChar('0'))
                .arg(colorBox->getG(), 2, 16, QChar('0'))
                .arg(colorBox->getB(), 2, 16, QChar('0'));
            if (fout.write(line.toUtf8()) == -1) break;
        }
    }

    if (!fout.commit()) {
        QMessageBox::critical(this, QStringLiteral("Error Saving User Palette"), fout.errorString());
    }
}

void MainWindow::readUserPalette() {
    auto path = paletteFile();
    if (path.isEmpty()) return;
    QFile fin(path);
    if (!fin.exists()) return;
    if (!fin.open(QIODevice::ReadOnly)) {
        QMessageBox::critical(this, QStringLiteral("Error Opening User Palette"), fin.errorString());
        return;
    }

    while (!fin.atEnd()) {
        QByteArray line = fin.readLine(80); // [n] = #001122
        if (line.size() < 14) continue;
        if (line[0] != '[') continue;
        int i = line.indexOf("] = #");
        if (i < 2) continue;
        bool ok;
        int index = line.mid(1, i-1).toInt(&ok);
        if (!ok || index < 0 || index >= stdPalCount) continue;
        i += 5;
        if (i+6 > line.size()) continue;
        int r = line.mid(i, 2).toInt(&ok, 16);
        if (!ok) continue;
        int g = line.mid(i+2, 2).toInt(&ok, 16);
        if (!ok) continue;
        int b = line.mid(i+4, 2).toInt(&ok, 16);
        if (!ok) continue;

        userPalette->at(index)->setRGB(r, g, b);
    }
    fin.close();
}

QString MainWindow::paletteFile() {
    QDir cfgDir(QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation));
    if (!cfgDir.exists()) {
        if (!cfgDir.mkpath(".")) {
            QMessageBox::critical(this,
                QStringLiteral("Error Creating App Config Directory"),
                QStringLiteral("There was an error creating the directory ") + cfgDir.path());
            return QStringLiteral("");
        }
    }
    return cfgDir.filePath("userpalette.txt");
}


CmpLabel::CmpLabel(QWidget *parent, QChar c)
    : QLabel(parent)
{
    QString text(c);
    text.append(':');
    setText(text);
    setAlignment(Qt::AlignRight);
    setMinimumWidth(rgbLabelWidth);
    setMaximumWidth(rgbLabelWidth);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
}
