#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "controller.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


     Ui::MainWindow *getUi() const;

private slots:
     void on_pushButton_clicked();

    void on_fileOpenButton_clicked();

    void on_charAlfPresentButton_clicked();

    void on_lenAlfPresentButton_clicked();

    void on_moveAlfPresentButton_clicked();

    void on_errorFixerButton_clicked();

    void on_textButton_clicked();

    void on_binaryButton_clicked();

    void on_decButton_clicked();


    void on_clearTextBrowserButton_clicked();

    void on_hexButton_clicked();

private:
    Ui::MainWindow *ui;
    Controller *controller = nullptr;
};
#endif // MAINWINDOW_H
