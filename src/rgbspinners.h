#ifndef RGBSPINNERS_H
#define RGBSPINNERS_H

#include <QSpinBox>

class Color;

class RgbSpinner : public QSpinBox {
    Q_OBJECT
public:
    RgbSpinner(QWidget *parent, Color &c);

protected:
    Color &color;
};

class RedSpinner : public RgbSpinner {
    Q_OBJECT
public:
    RedSpinner(QWidget *parent, Color &c);

public Q_SLOTS:
    void changed(int x);
    void colorChanged();
};

class GreenSpinner : public RgbSpinner {
    Q_OBJECT
public:
    GreenSpinner(QWidget *parent, Color &c);

public Q_SLOTS:
    void changed(int x);
    void colorChanged();
};

class BlueSpinner : public RgbSpinner {
    Q_OBJECT
public:
    BlueSpinner(QWidget *parent, Color &c);

public Q_SLOTS:
    void changed(int x);
    void colorChanged();
};

#endif // RGBSPINNERS_H