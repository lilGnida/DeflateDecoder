#ifndef DEFLATE_H
#define DEFLATE_H

#include <QByteArray>
#include <QThread>

class Deflate: public QObject
{
    Q_OBJECT

public slots:
    void decodeDynamicCompression (const QByteArray, int, bool, bool, bool, bool);
    void prepareAlf(const int);

signals:
    void sendResult(const QByteArray);
    void sendTextAndCode(const QByteArray, const QByteArray);
    void sendTextWithLengthAndMove(const QByteArray, const QByteArray);
    void sendDecodedBitsCount(const int);
    void sendAlf(const QByteArray, const int);
    void sendError(const int);
    void sendErrorMessage(const QByteArray);
    void sendAlfCount(const int, const bool, const int);
    void sendElementsInAlfCount(const int, const int);
    void sendText(const QString);
};

#endif // DEFLATE_H
