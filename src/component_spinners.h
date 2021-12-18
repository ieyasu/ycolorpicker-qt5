#ifndef CMPSPINNERS_H
#define CMPSPINNERS_H

#include <QDoubleSpinBox>
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
    void colorChanged();
};

class GreenSpinner : public RgbSpinner {
    Q_OBJECT
public:
    GreenSpinner(QWidget *parent, Color &c);

public Q_SLOTS:
    void colorChanged();
};

class BlueSpinner : public RgbSpinner {
    Q_OBJECT
public:
    BlueSpinner(QWidget *parent, Color &c);

public Q_SLOTS:
    void colorChanged();
};



class HsvSpinner : public QDoubleSpinBox {
    Q_OBJECT
public:
    HsvSpinner(QWidget *parent, Color &c, double max, double step);

protected:
    Color &color;
};

class HueSpinner : public HsvSpinner {
    Q_OBJECT
public:
    HueSpinner(QWidget *parent, Color &c);

public Q_SLOTS:
    void colorChanged();
};

class SatSpinner : public HsvSpinner {
    Q_OBJECT
public:
    SatSpinner(QWidget *parent, Color &c);

public Q_SLOTS:
    void colorChanged();
};

class ValSpinner : public HsvSpinner {
    Q_OBJECT
public:
    ValSpinner(QWidget *parent, Color &c);

public Q_SLOTS:
    void colorChanged();
};

#endif // CMPSPINNERS_H
