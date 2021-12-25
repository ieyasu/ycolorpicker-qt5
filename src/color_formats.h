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