#include "controller.h"
#include <QByteArray>
#include <QMessageBox>
#include <QDebug>
#include <QMetaType>
#include <QBitArray>
#include <mainwindow.h>
#include "errorfixerwindow.h"
#include "ui_mainwindow.h"

Controller::Controller(MainWindow *wnd)
    : window(wnd)
{
    array = new Deflate;
    deflateThread = new QThread;

    connect(this, SIGNAL(sendData(const QByteArray, int, bool, bool, bool, bool)), array, SLOT(decodeDynamicCompression (const QByteArray, int, bool, bool, bool, bool)));
    connect(this, SIGNAL(askAlf(const int)), array, SLOT(prepareAlf(const int)));
    connect(this, SIGNAL(sendStopSignal(const bool)), SLOT(getStopSignal(const bool)));

    connect(array, SIGNAL(sendResult(const QByteArray)), this, SLOT(handleResults(const QByteArray)));
    connect(array, SIGNAL(sendTextAndCode(const QByteArray, const QByteArray)), this, SLOT(getTextAndCode(const QByteArray, const QByteArray)));
    connect(array, SIGNAL(sendTextWithLengthAndMove(const QByteArray, const QByteArray)), this, SLOT(getTextWithLengthAndMove(const QByteArray, const QByteArray)));
    connect(array, SIGNAL(sendDecodedBitsCount(const int)), this, SLOT(getDecodedBitsCount(const int)));
    connect(array, SIGNAL(sendAlf(const QByteArray, const int)), this, SLOT(getAlf(const QByteArray, const int)));
    connect(array, SIGNAL(sendError(const int)), this, SLOT(getError(const int)));
    connect(array, SIGNAL(sendErrorMessage(const QByteArray)), this, SLOT(getErrorMessage(const QByteArray)));
    connect(array, SIGNAL(sendAlfCount(const int, const bool, const int)), this, SLOT(getAlfCount(const int, const bool, const int)));
    connect(array, SIGNAL(sendElementsInAlfCount(const int, const int)), this, SLOT(getElementsInAlfCount(const int, const int)));
    connect(array, SIGNAL(sendText(const QString)), this, SLOT(getText(const QString)));

    array->moveToThread(deflateThread);

    deflateThread->start();
}

Controller::~Controller() {
    deflateThread->quit();
    deflateThread->wait();
}

void Controller::decode(const QByteArray inputArray, int decodedBitsCount, bool type, bool useDynamicBlocks, bool useStaticBlocks, bool useBlocksWithoutCompression)
{
    //type 1 => block, 2 => flow
    emit sendData(inputArray, decodedBitsCount, type, useDynamicBlocks, useStaticBlocks, useBlocksWithoutCompression);
}

void Controller::prepareAlf(const int type)
{
    emit askAlf(type);
}

QString Controller::getOutputArray()
{
    return outputArray;
}

QString Controller::getText()
{
    return text;
}

QString Controller::getCode()
{
    return code;
}

void Controller::handleResults(const QByteArray text)
{
    qDebug()<<text;
}

int bytes = 0;

void Controller::getTextAndCode(const QByteArray text, const QByteArray code)
{
    window->getUi()->textBrowser->append("символ: \"" + QString::fromUtf8(text) + "\" код: " + code);
}

void Controller::getTextWithLengthAndMove(const QByteArray text, const QByteArray codes)
{
    window->getUi()->textBrowser->append("символы: \"" + QString::fromUtf8(text) + "\" коды: " + codes);
}

void Controller::getDecodedBitsCount(const int count)
{
    window->getUi()->readedBitCountLabel->setText("Прочитано бит: " + QString::number(count));
    window->getUi()->decompressionProgressBar->setValue(count);
//    window->getUi()->seekSpinBox->setValue(count);//не требуется
}
void Controller::getAlf(const QByteArray alf, const int type)
{
    QTextEdit *alfPresentation = new QTextEdit();
    alfPresentation->setWindowFlags(Qt::Window);
    alfPresentation->setReadOnly(true);

    if (type == 1) {
        alfPresentation->setWindowTitle("Алфавит символов");
        alfPresentation->append(alf);
        alfPresentation->show();
    } else if (type == 2) {
        alfPresentation->setWindowTitle("Алфавит длин");
        alfPresentation->append(alf);
        alfPresentation->show();
    } else if (type == 3) {
        alfPresentation->setWindowTitle("Алфавит смещений");
        alfPresentation->append(alf);
        alfPresentation->show();
    }
}

void Controller::getError(const int)
{
    ErrorFixerWindow *errorFixedWindow = new ErrorFixerWindow;
    errorFixedWindow->setWindowTitle("Исправление ошибок (версия 0.1)");
    errorFixedWindow->show();
}

void Controller::getErrorMessage(const QByteArray msg)
{
    QMessageBox errorMessage;
    errorMessage.setText(msg);
    errorMessage.exec();
}

void Controller::getAlfCount(const int count, const bool max, const int alfType)
{
    //count - число полученных символов алфавита
    //max - true = максимальное значение для установки максимума progressbar, false = значение для progressbar
    //alfType - 1 = charAlf, 2 = lenAlf, 3 = moveAlf
    if (max) {
        switch (alfType) {
        case 1:
            window->getUi()->charAlfProgress->setMaximum(count);
            break;
        case 2:
            window->getUi()->lenAlfProgress->setMaximum(count);
            break;
        case 3:
            window->getUi()->moveAlfProgress->setMaximum(count);
            break;
        }
    } else {
        switch (alfType) {
        case 1:
            window->getUi()->charAlfProgress->setValue(count);

            break;
        case 2:
            window->getUi()->lenAlfProgress->setValue(count);

            break;
        case 3:
            window->getUi()->moveAlfProgress->setValue(count);

            break;
        }
    }
}

void Controller::getElementsInAlfCount(const int count, const int alfType)
{
    switch (alfType) {
    case 1:
        window->getUi()->charAlfCount->setText("Элементы: " + QString::number(count));
        window->getUi()->charAlfStatus->setText("Сформирован");
        break;
    case 2:
        window->getUi()->lenAlfCount->setText("Элементы: " + QString::number(count));
        window->getUi()->lenAlfStatus->setText("Сформирован");
        break;
    case 3:
        window->getUi()->moveAlfCount->setText("Элементы: " + QString::number(count));
        window->getUi()->moveAlfStatus->setText("Сформирован");
        break;
    }
}

void Controller::getText(const QString text)
{
    window->getUi()->textBrowser->append(text);
}
