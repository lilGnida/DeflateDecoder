#ifndef PACKET_H
#define PACKET_H

#include <QByteArray>
#include <QBitArray>

class packet
{
public:
    packet(QByteArray, int);

    int packetNumber;

    QByteArray getCompressedPacket();
    QByteArray getUncompressedPacket();
private:
    QByteArray compressedPacket;
    QByteArray uncompressedPacket;
};

#endif // PACKET_H
