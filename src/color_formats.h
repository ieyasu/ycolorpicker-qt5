/* color_formats.h - output format display widgets for YColorPicker
 * Copyright 2022 Matthew S. Bishop
 *
 * This program is licensed under the terms of the GNU GPL version 3. See the
 * file LICENSE.txt or <https://www.gnu.org/licenses/> for details.
 */
#ifndef COLOR_FORMATS_H
#define COLOR_FORMATS_H

#include "color.h"

#include <QLineEdit>

class HexFmt : public QLineEdit {
    Q_OBJECT
public:
    HexFmt(QWidget *parent, Color &c);

public Q_SLOTS:
    void colorChanged();
    void edited(const QString &);
    void toClipboard();

private:
    Color &color;
    bool inhibit;
};


class RgbFmt : public QLineEdit {
    Q_OBJECT
public:
    RgbFmt(QWidget *parent, Color &c);

public Q_SLOTS:
    void colorChanged();
    void edited(const QString &);
    void toClipboard();

private:
    Color &color;
    bool inhibit;
};

#endif // COLOR_FORMATS_H
