#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QThread>
#include <QMainWindow>
#include "deflate.h"

class MainWindow;

class Controller: public QObject
{
    Q_OBJECT

    QThread *deflateThread = nullptr;
public:
    Controller(MainWindow *wnd);
    ~Controller();

    void decode(const QByteArray, int, bool, bool, bool, bool);
    void prepareAlf(const int);

    QString getOutputArray();
    QString getText();
    QString getCode();

private:
    Deflate *array = nullptr;
    MainWindow *window = nullptr;
    QByteArray outputArray;
    QByteArray text, code;

public slots:
    void handleResults(const QByteArray);
    void getTextAndCode(const QByteArray, const QByteArray);
    void getTextWithLengthAndMove(const QByteArray, const QByteArray);
    void getDecodedBitsCount(const int);
    void getAlf(const QByteArray, const int);
    void getError(const int);
    void getErrorMessage(const QByteArray);
    void getAlfCount(const int, const bool, const int);
    void getElementsInAlfCount(const int, const int);
    void getText(const QString);
signals:
    void sendData(const QByteArray, int, bool, bool, bool, bool);
    void askAlf(const int);
    void sendStopSignal(const bool);
};

#endif // CONTROLLER_H
