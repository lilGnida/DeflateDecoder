#include "errorfixerwindow.h"
#include "ui_errorfixerwindow.h"

ErrorFixerWindow::ErrorFixerWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ErrorFixerWindow)
{
    ui->setupUi(this);
}

ErrorFixerWindow::~ErrorFixerWindow()
{
    delete ui;
}
