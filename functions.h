#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <QBitArray>
#include <QByteArray>
#include <QVector>

//структура для хранения дополнительной информации алфавитов
struct intpair {
    int diapozon = 0;//диапозон длин
    int extrabit = 0;//количество уточняющих битов
};

//поиск наиболее совпадающих кодов и их подставление
//depth = глубина проверки - количество правильных символов, следующих за исправленным
//fixBitCount = количество битов, которые могут быть исправлены
QVector <std::pair<int, QBitArray>> sutableCodesFinder (QBitArray &bitInput,
                              QVector <std::pair<int, QBitArray>> &charAlf,
                              int seek, int fixBitCount = 1, int depth = 5);

//дебаговая функция просмотра битов на месте остановки
QBitArray showBits (QBitArray &array, int seek, int length = 32);

//создание кода определенной длины из числа
QBitArray generateCode (int num, int codeLength);

//представление битов в виде чисел
int makeIntFromBit (QBitArray &bit, bool revers = false);

//представление числа символом таблицы ASCII
const QByteArray presentIntInASCII (int number);
const QString presentIntInASCIIStr (int number);

//представление битов байтами
const QByteArray presentBitsInBytes (QBitArray &bits);

//создание кодов хаффмана по длине кода
QVector <std::pair<int, QBitArray>> generateHuffmanCodes(QVector<std::pair<int, int>> &vector);

//создание алфавита смещений с кодами, диапозонами и уточняющими битами
QVector <std::pair<QBitArray, intpair>> generateMoveAlf (QVector <std::pair<int, QBitArray>> &vector);

//создание алфавита длин с кодами, диапозонами и уточняющими битами
QVector <std::pair<int, intpair>> generateLengthAlf();

#endif // FUNCTIONS_H
