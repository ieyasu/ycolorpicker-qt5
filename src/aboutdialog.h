/* aboutdialog.h - about dialog for YColorPicker
 * Copyright 2022 Matthew S. Bishop
 *
 * This program is licensed under the terms of the GNU GPL version 3. See the
 * file LICENSE.txt or <https://www.gnu.org/licenses/> for details.
 */
#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include <QWidget>

class AboutDialog : public QWidget {
    Q_OBJECT
public:
    AboutDialog();

protected:
    virtual bool eventFilter(QObject *target, QEvent *event) override;
};

#endif // ABOUTDIALOG_H
