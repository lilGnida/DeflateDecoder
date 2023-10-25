#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "errorfixerwindow.h"
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QDateTime>
#include <QVector>
#include <QByteArray>
#include <QTableWidget>
#include "packet.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->controller = new Controller(this);

    ui->errorFixerButton->hide();
    ui->pushButton->hide();

}

MainWindow::~MainWindow()
{
    delete ui;
}

Ui::MainWindow *MainWindow::getUi() const
{
    return ui;
}

QByteArray block, text;
QVector <packet> listOfPackets;
bool isChar = false, isBin = false, isDec = false, isHex = false, isDecoded = false;

void MainWindow::on_fileOpenButton_clicked()
{
    block.clear();

    QFile fileIn (QFileDialog::getOpenFileName(this));
    QFileInfo fileInfo (fileIn);
    QByteArray size;
    int packCount = 0, minLen = 1000000, maxLen = 0;

    if (fileIn.open(QIODevice::ReadOnly)) {
        if (fileIn.fileName().remove(0, fileIn.fileName().count() - 3) == "sig") {
            while (!fileIn.atEnd()) {
                size = fileIn.read(2);
                quint8 a = size[0];
                quint8 b = size[1];
                int packLength = ((b * 256) + a);

                //Определение максимальной и минимальной длины пакетов
                if (maxLen < packLength) {
                    maxLen = packLength;
                }

                if (minLen > packLength) {
                    minLen = packLength;
                }

                QByteArray pack = fileIn.read(packLength);
                block.append(pack);
                packCount++;

                //добавление данных в контейнер пакетов класса packet
                packet packet(pack, packCount);
                listOfPackets.append(packet);
            }
        } else {
            block = fileIn.readAll();
            packCount++;
            maxLen = minLen = block.count();
            packet packet(block, 1);
            listOfPackets.append(packet);
        }
    }
    fileIn.close();

    ui->sigViewer->setColumnCount(maxLen);
    ui->sigViewer->setRowCount(packCount);

    ui->pushButton->show();
    ui->decodeBlocs->setChecked(true);
    ui->staticBlocks->setChecked(true);

    //вывод исходных данных в sigviewer
    for (int i = 0; i < packCount; i++) {
        QByteArray pack = listOfPackets[i].getCompressedPacket();

        for (int j = 0; j < pack.count(); j++) {
            QTableWidgetItem *item = new QTableWidgetItem(QString::number(static_cast <quint8> (pack[j])));
            ui->sigViewer->setItem(i, j, item);
            ui->sigViewer->setColumnWidth(j, 40);
            ui->sigViewer->setRowHeight(i, 20);
        }
    }

    ui->decompressionProgressBar->setMaximum(block.count() * 8);
    ui->decompressionProgressBar->setMinimum(0);

    ui->pathLineEdit->setText(fileInfo.filePath());
    ui->sizeLabel->setText("Размер файла: " + QString::number(fileInfo.size()) + "байт (" + QString::number(fileInfo.size() * 8) + " бит)");
    ui->creationLabel->setText("Дата и время создания файла: " + fileInfo.birthTime().toString());
    ui->modificationLabel->setText("Дата и время последнего изменения: " + fileInfo.lastModified().toString());
    ui->packCountLabel->setText("Количество пакетов: " + QString::number(packCount));
    ui->maxLenLabel->setText("Максимальная длина пакета: " + QString::number(maxLen));
    ui->minLenLabel->setText("Минимальная длина пакета: " + QString::number(minLen));
}

void MainWindow::on_pushButton_clicked()
{
//    int decodedBitsCount = ui->readedBitCountLabel->text().remove(0, 15).toInt();
//    int mass[] = {/*0x73*/0x1b, /*0x49*/0x4f, 0x4D, 0xCB, 0x49, 0x2C, 0x49, 0x55, 0x00, 0x11, 0x00}; //проверка статического сжатия
//    QByteArray block;

//    for (int i = 0; i < 11; i++) {
//        block.append(mass[i]);
//    }

//    this->controller->decode(block, decodedBitsCount);

    bool useDynamicBlocks = false, useStaticBlocks = false, useBlocksWithoutCompression = false;

    if (ui->dynamicBlocks->isChecked()) {
        useDynamicBlocks = true;
    }
    if (ui->staticBlocks->isChecked()) {
        useStaticBlocks = true;
    }
    if (ui->noCompressionBlocks->isChecked()) {
        useBlocksWithoutCompression = true;
    }

    //декодировать поток или блок?
    if (ui->decodeFlow->isChecked()) {
        this->controller->decode(block, ui->seekSpinBox->value(), false, useDynamicBlocks, useStaticBlocks, useBlocksWithoutCompression);
    }
    else if (ui->decodeBlocs->isChecked()) {
        this->controller->decode(block, ui->seekSpinBox->value(), true, useDynamicBlocks, useStaticBlocks, useBlocksWithoutCompression);
    }
}

void MainWindow::on_charAlfPresentButton_clicked()
{
    this->controller->prepareAlf(1);
}

void MainWindow::on_lenAlfPresentButton_clicked()
{
    this->controller->prepareAlf(2);
}

void MainWindow::on_moveAlfPresentButton_clicked()
{
    this->controller->prepareAlf(3);
}

void MainWindow::on_errorFixerButton_clicked()
{
    this->controller->getError(NULL);
}

void MainWindow::on_textButton_clicked()
{
    if (isDecoded == false) {
        if (isChar == false) {
            for (int i = 0; i < ui->sigViewer->rowCount(); i++) {
                QByteArray pack = listOfPackets[i].getCompressedPacket();

                for (int j = 0; j < pack.count(); j++) {
                    QTableWidgetItem *item = new QTableWidgetItem(tr("%1").arg(pack.at(j)));
                    ui->sigViewer->setItem(i, j, item);
                    ui->sigViewer->setColumnWidth(j, 40);
                    ui->sigViewer->setRowHeight(i, 20);
                }
            }
        }
    }
}

void MainWindow::on_binaryButton_clicked()
{
    if (isDecoded == false) {
        if (isBin == false) {
            QString binstr;

            for (int i = 0; i < ui->sigViewer->rowCount(); i++) {
                QByteArray pack = listOfPackets[i].getCompressedPacket();

                for (int j = 0; j < pack.count(); j++) {
                    quint8 num = pack.at(j);

                    for (int k = 0; k < 8; k++) {
                        if (num & 1) {
                            binstr.prepend("1");
                        } else {
                            binstr.prepend("0");
                        }

                        num = num >> 1;
                    }

                    QTableWidgetItem *item = new QTableWidgetItem(binstr);
                    ui->sigViewer->setItem(i, j, item);
                    ui->sigViewer->setColumnWidth(j, 75);
                    ui->sigViewer->setRowHeight(i, 20);

                    binstr.clear();
                }
            }
        }
    }
}

void MainWindow::on_decButton_clicked()
{
    if (isDecoded == false) {
        if (isDec == false) {
            for (int i = 0; i < ui->sigViewer->rowCount(); i++) {
                QByteArray pack = listOfPackets[i].getCompressedPacket();

                for (int j = 0; j < pack.count(); j++) {
                    QTableWidgetItem *item = new QTableWidgetItem(QString::number(static_cast <quint8> (pack.at(j))));
                    ui->sigViewer->setItem(i, j, item);
                    ui->sigViewer->setColumnWidth(j, 40);
                    ui->sigViewer->setRowHeight(i, 20);
                }
            }
        }
    }
}

void MainWindow::on_clearTextBrowserButton_clicked()
{
    //очистка поля символов и кодов
    ui->textBrowser->clear();
    //выставление значения прочитанных битов на ноль
    ui->readedBitCountLabel->setText("Прочитано бит: 0");
    //сброс прогресс бара чтения битов
    ui->decompressionProgressBar->setValue(0);
}

void MainWindow::on_hexButton_clicked()
{
    if (isDecoded == false) {
        if (isHex == false) {
            for (int i = 0; i < ui->sigViewer->rowCount(); i++) {
                QByteArray pack = listOfPackets[i].getCompressedPacket();

                for (int j = 0; j < pack.count(); j++) {
                    QByteArray byte;
                    byte.append(pack.at(j));
                    QTableWidgetItem *item = new QTableWidgetItem(static_cast <QString> (byte.toHex()));
                    ui->sigViewer->setItem(i, j, item);
                    ui->sigViewer->setColumnWidth(j, 40);
                    ui->sigViewer->setRowHeight(i, 20);
                }
            }
        }
    }
}
