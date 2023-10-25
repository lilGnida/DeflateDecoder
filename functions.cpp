#include "functions.h"

//дебаговая функция просмотра битов на месте остановки
QBitArray showBits (QBitArray &array, int seek, int length) {
    QBitArray bits;

    bits.resize(length);

    for (int i = 0; i < length; i++) {
        bits.setBit(i, array.testBit(i + seek));
    }

    return bits;
}

//создание кода определенной длины из числа
QBitArray generateCode (int num, int codeLength) {
    QBitArray code(codeLength, false);

    for (int i = 0; i < codeLength; i++) {
        if (num & 1) {
            code.setBit(codeLength - i - 1, true);
        }

        num = num >> 1;
    }

    return code;
}

//представление битов в виде чисел
int makeIntFromBit (QBitArray &bit, bool revers) {
    int a = 0;

    if (revers) {
        for (int i = bit.count() - 1; i >= 0; i--) {
            a = a << 1;

            if (bit.testBit(i)) {
                a |= 1;
            }
        }
    } else {
        for (int i = 0; i < bit.count(); i++) {
            a = a << 1;

            if (bit.testBit(i)) {
                a |= 1;
            }
        }
    }

    return a;
}

const QByteArray presentIntInASCII (int number) {
    QByteArray result;

    result.push_back(number);

    return result;
}

const QString presentIntInASCIIStr (int number) {
    QString result;

    result = QString::number(number);

    return result;
}

const QByteArray presentBitsInBytes (QBitArray &bits) {
    QByteArray bytes;

    for (int i = 0; i < bits.count(); i++) {
        if (bits[i] == true) {
            bytes.push_back("1");
        } else {
            bytes.push_back("0");
        }
    }

    return bytes;
}

//создание кодов хаффмана по длине кода
QVector <std::pair<int, QBitArray>> generateHuffmanCodes(QVector<std::pair<int, int>> &vector) {
    QVector <std::pair<int, QBitArray>> rezult;
    QBitArray bit;
    int num = 0;

    for (int j = 1; j < 16; j++)
    {
        for (int i = 0; i < vector.count(); i++)
        {
            if (vector[i].second == j)
            {
                vector[i].first = num;
                vector[i].first = vector[i].first << (16 - j);
                num++;
            }
        }
        num = num << 1;
    }

    for (int j = 1; j < 16; j++)
    {
        for (int i = 0; i < vector.size(); i++)
        {
            if (vector[i].second == j)
            {
                bit.clear();
                bit.resize(j);

                for (int k = 0; k < j; k++)
                {
                    bit.setBit(k, vector[i].first & 32768);
                    vector[i].first = vector[i].first << 1;
                }

                rezult.push_back(std::make_pair(i, bit));
            }
        }
    }

    return rezult;
}

//создание алфавита смещений с кодами, диапозонами и уточняющими битами
QVector <std::pair<QBitArray, intpair>> generateMoveAlf (QVector <std::pair<int, QBitArray>> &vector) {
    QVector <std::pair<QBitArray, intpair>> result;
    intpair pair;

    //добавление числа уточняющих битов в массив смещений
    for (int i = 0; i < 30; i++) {
        for (int j = 0; j < vector.count(); j++) {
            if (i > 3 && vector[j].first == i) {
                if (i % 2 == 0) {
                    pair.diapozon = pow(2, (vector[j].first / 2)) + 1;
                } else {
                    pair.diapozon = pow(2, (vector[j].first / 2)) + pow(2, (vector[j].first / 2) - 1) + 1;
                }
                pair.extrabit = static_cast<char>((i / 2) - 1);
                result.push_back(std::make_pair(vector[j].second, pair));
            }
        }
    }

    return result;
}

//создание алфавита длин с кодами, диапозонами и уточняющими битами
QVector <std::pair<int, intpair>> generateLengthAlf () {
    QVector <std::pair<int, intpair>> result;
    int code = 11;

    for (int i = 0; i < 29; i++) {
        intpair pair;

        if (i < 8) {
            pair.diapozon = 3 + i;
            pair.extrabit = 0;

            result.push_back(std::make_pair(i + 257, pair));
        }

        if (i > 7 && i < 12) {
            pair.diapozon = code;
            pair.extrabit = 1;
            code += 2;//переход к следующему диапозону

            result.push_back(std::make_pair(i + 257, pair));
        }

        if (i > 11 && i < 16) {
            pair.diapozon = code;
            pair.extrabit = 2;
            code += 4;

            result.push_back(std::make_pair(i + 257, pair));
        }

        if (i > 15 && i < 20) {
            pair.diapozon = code;
            pair.extrabit = 3;
            code += 8;

            result.push_back(std::make_pair(i + 257, pair));
        }

        if (i > 19 && i < 24) {
            pair.diapozon = code;
            pair.extrabit = 4;
            code += 16;

            result.push_back(std::make_pair(i + 257, pair));
        }

        if (i > 23 && i < 28) {
            pair.diapozon = code;
            pair.extrabit = 5;
            code += 32;

            result.push_back(std::make_pair(i + 257, pair));
        }

        if (i == 28) {
            pair.diapozon = 285;
            pair.extrabit = 0;

            result.push_back(std::make_pair(i + 257, pair));
        }
    }

    return result;
}

//поиск наиболее совпадающих кодов и их подставление
//depth = глубина проверки - количество правильных символов, следующих за исправленным
//fixBitCount = количество битов, которые могут быть исправлены
QVector <std::pair<int, QBitArray>> sutableCodesFinder (QBitArray &bitInput,
                              QVector <std::pair<int, QBitArray>> &charAlf,
                              int seek, int fixBitCount, int depth) {
    QVector <std::pair<int, QBitArray>> result;
    QBitArray bit;

    for (int i = 0; i < charAlf.count(); i++) {
            bit.clear();
            bit.resize(charAlf[i].second.count());

            int mistakes = 0;

            //проверка на количество ошибок кода симола или длины
            for (int j = 0; j < bit.count(); j++) {
                if (mistakes != fixBitCount) {
                    if (charAlf[i].second.testBit(j) != bitInput.testBit(j + seek)) {
                        bit.setBit(j, !bitInput.testBit(j + seek));
                        mistakes++;
                    } else {
                        bit.setBit(j, bitInput.testBit(j + seek));
                    }

                    continue;
                } else {
                    break;
                }
            }


    }

    return result;
}

