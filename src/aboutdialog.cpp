/* aboutdialog.cpp - about dialog for YColorPicker
 * Copyright 2022 Matthew S. Bishop
 *
 * This program is licensed under the terms of the GNU GPL version 3. See the
 * file LICENSE.txt or <https://www.gnu.org/licenses/> for details.
 */
#include "colorpicker.h"
#include "aboutdialog.h"
#include "push_button.h"

#include <QtGui>
#include <QtWidgets>

AboutDialog::AboutDialog()
    : QWidget(nullptr, Qt::Dialog)
{
    auto vbox = new QVBoxLayout(this);
    vbox->setContentsMargins(margin, margin, margin, margin);

    auto lbl = new QLabel(
        "<big><b>YColorPicker</b></big> " COLORPICKER_VERSION
        "<p>A neato color selection tool.</p>"
        "<p>Copyright 2022 <a href=\"mailto:mattsbishop@gmail.com\">Matthew S. Bishop</a></p>"
        "<p>License: <a href=\"https://www.gnu.org/licenses/#GPL\">GNU General Public License Version 3</a></p>"
        "<p>Website: <a href=\"https://github.com/ieyasu/ycolorpicker\">github.com/ieyasu/ycolorpicker</a></p>"
    );
    lbl->setOpenExternalLinks(true);
    vbox->addWidget(lbl);

    vbox->addStretch();
    vbox->addSpacing(margin);

    auto btnBox = new QHBoxLayout();
    vbox->addLayout(btnBox);

    auto aboutQt = new TextButton(this, "About Qt");
    btnBox->addWidget(aboutQt);
    connect(aboutQt, &TextButton::clicked, qApp, &QApplication::aboutQt);

    btnBox->addStretch();

    auto close = new TextButton(this, "Close");
    btnBox->addWidget(close);
    connect(close, &TextButton::clicked, this, &QWidget::hide);
}
