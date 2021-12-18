// colorpicker.h - application general header file.
#ifndef COLORPICKER_H
#define COLORPICKER_H

static constexpr int spacing = 12;
static constexpr int margin = 20;
static constexpr int indicatorSize = 7;
static constexpr int indicatorSize1 = indicatorSize - 1;

// saturation/value square
static constexpr int svSize = 360;
static constexpr int svSize1 = svSize - 1;

// hue slider
static constexpr int barWidth = margin;
static constexpr int hsWidth = 2 * indicatorSize + barWidth;
static constexpr int hsHeight = 2 * indicatorSize + svSize;

// rgb sliders
static constexpr int rgbSize = 256;
static constexpr int rgbSize1 = rgbSize - 1;
static constexpr int rgbWidth = rgbSize + 2 * indicatorSize;
static constexpr int barHeight = 12;
static constexpr int rgbHeight = barHeight + 2 * indicatorSize;
static constexpr int rgbLabelWidth = 18;

// color palette
static constexpr int cbSize = 24;
static constexpr int cbSize1 = cbSize - 1;

// current color display
static constexpr int fgbgSize = cbSize;
static constexpr int fgbgOff = fgbgSize / 4;
static constexpr int fgbgAreaSize = 2 * fgbgSize - fgbgOff;
static constexpr int currClrAreaSize = cbSize * 4 + spacing * 3 - 1;
static constexpr int currcdWidth = cbSize * 10 + spacing * 9 + indicatorSize * 2;
static constexpr int currcdHeight = currClrAreaSize + indicatorSize * 2;


struct RgbTriple {
    int r, g, b;
};

#endif // COLORPICKER_H
