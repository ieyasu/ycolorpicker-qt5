/* colorpicker.h - constants for YColorPicker
 * Copyright 2022 Matthew S. Bishop
 *
 * This program is licensed under the terms of the GNU GPL version 3. See the
 * file LICENSE.txt or <https://www.gnu.org/licenses/> for details.
 */
#ifndef COLORPICKER_H
#define COLORPICKER_H

#define COLORPICKER_VERSION "1.0"

#include <QColor>

static constexpr int spacing = 12;
static constexpr int margin = 20;
static constexpr int indicatorSize = 7;
static constexpr int indicatorSize1 = indicatorSize - 1;
static constexpr int inputHeight = 26;
static constexpr int closeBtnWidth = 80;
static constexpr int fmtLabelWidth = 36;

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

// colors
static const QRgb mainBackground = qRgb( 70, 70, 70);
static const QRgb editBackground = qRgb( 50, 50, 50);
static const QRgb btnBackground  = qRgb( 97, 97,152);
static const QRgb btnHover       = qRgb( 86, 86,137);
static const QRgb hilight        = qRgb( 86,131,198);
static const QRgb outline        = qRgb(122,122,122);
static const QRgb linkColor      = qRgb(139,139,255);
static const QRgb visitedLink    = qRgb(255,121,255);

struct RgbTriple {
    int r, g, b;
};

#endif // COLORPICKER_H
