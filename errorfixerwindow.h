#ifndef ERRORFIXERWINDOW_H
#define ERRORFIXERWINDOW_H

#include <QDialog>

namespace Ui {
class ErrorFixerWindow;
}

class ErrorFixerWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ErrorFixerWindow(QWidget *parent = nullptr);
    ~ErrorFixerWindow();

private:
    Ui::ErrorFixerWindow *ui;
};

#endif // ERRORFIXERWINDOW_H
