#include "packet.h"

packet::packet(QByteArray pack, int i)
{
    compressedPacket = pack;
    packetNumber = i;
}

QByteArray packet::getCompressedPacket()
{
    return compressedPacket;
}

QByteArray packet::getUncompressedPacket()
{
    return uncompressedPacket;
}
