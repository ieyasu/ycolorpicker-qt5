#include "color_formats.h"

#include <QClipboard>
#include <QGuiApplication>
#include <QRegularExpression>

static QRegularExpression hexPat(QStringLiteral("^#?[0-9a-fA-F]{3}(?:[0-9a-fA-F]{3})?$"));

HexFmt::HexFmt(QWidget *parent, Color &c)
    : QLineEdit(parent), color(c), inhibit(false)
{
    connect(this, SIGNAL(textEdited(const QString &)), this, SLOT(edited(const QString &)));
}

void HexFmt::edited(const QString &text) {
    if (!hexPat.match(text).hasMatch()) return;

    QString s(text);
    if (s[0] == '#') s = s.mid(1);
    if (s.length() == 3) {
        QString t;
        t += s[0]; t += s[0];
        t += s[1]; t += s[1];
        t += s[2]; t += s[2];
        s = t;
    }
    if (s.length() == 6) {
        int r = s.mid(0, 2).toInt(nullptr, 16);
        int g = s.mid(2, 2).toInt(nullptr, 16);
        int b = s.mid(4, 2).toInt(nullptr, 16);
        inhibit = true;
        color.setRGB(r, g, b);
        inhibit = false;
    }
}

void HexFmt::colorChanged() {
    if (inhibit) return;

    QString s(QStringLiteral("#"));
    QString n;
    s += n.setNum(color.getR(), 16);
    s += n.setNum(color.getG(), 16);
    s += n.setNum(color.getB(), 16);
    setText(s.toUpper());
}

void HexFmt::toClipboard() {
    QGuiApplication::clipboard()->setText(text());
}



static QRegularExpression rgbPat(QStringLiteral("^(\\d{1,3}),(\\d{1,3}),(\\d{1,3})$"));

RgbFmt::RgbFmt(QWidget *parent, Color &c)
    : QLineEdit(parent), color(c), inhibit(false)
{
    connect(this, SIGNAL(textEdited(const QString &)), this, SLOT(edited(const QString &)));
}

void RgbFmt::edited(const QString &text) {
    auto m = rgbPat.match(text);
    if (!m.hasMatch()) return;

    int r = m.captured(1).toInt();
    int g = m.captured(2).toInt();
    int b = m.captured(3).toInt();
    inhibit = true;
    color.setRGB(r, g, b);
    inhibit = false;
}

void RgbFmt::colorChanged() {
    if (inhibit) return;

    QString s, n;
    s += n.setNum(color.getR());
    s += ',';
    s += n.setNum(color.getG());
    s += ',';
    s += n.setNum(color.getB());
    setText(s);
}

void RgbFmt::toClipboard() {
    QGuiApplication::clipboard()->setText(text());
}
