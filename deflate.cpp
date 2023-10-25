#include "deflate.h"
#include "functions.h"
#include "math.h"
#include <QDebug>
#include <QVector>
#include <QByteArray>
#include <QBitArray>

//данные для представления вне функции обработки
QVector <std::pair<int, QBitArray>>  globalBitAlf;
QVector <std::pair<int, intpair>>  globalLenAlf;
QVector <std::pair<QBitArray, intpair>> globalMoveAlf;
bool endOfBlock = false;

void Deflate::decodeDynamicCompression(const QByteArray inputArray, int decodedBitsCount, bool type, bool useDynamicBlocks, bool useStaticBlocks, bool useBlocksWithoutCompression)
{
    qDebug()<<"Deflate::decodeDynamicCompression";

    globalBitAlf.clear();
    globalLenAlf.clear();
    globalMoveAlf.clear();

    QBitArray bitInput(inputArray.count() * 8, false);

    //перевод байтового входного массива в битовый
    for (int i = 0; i < inputArray.count(); i++) {
        unsigned char byte = inputArray[i];

        for (int j = 0; j < 8; j++) {
            bitInput.setBit(i * 8 + j, byte & 1);
            byte = byte >> 1;
        }
    }

    unsigned int seek = decodedBitsCount, skip = 0, h = 0;
    endOfBlock = bitInput.at(0 + seek);
    bool end = false, decodingError = false, codeFound = false, notEnoughBits = false;
    int hclenPositions[] = {16, 17, 18 ,0, 8, 7, 9, 6, 10, 5, 11, 4, 12, 3, 13, 2, 14, 1, 15};
    QBitArray bit;
    QVector <QBitArray> hclenComandLengths;
    QVector <std::pair<int, int>> hclenLengths, hclenArray, alf, moveArr;
    QVector <std::pair<int, QBitArray>> hclength, bitAlf, bitMove;
    QVector <std::pair<QBitArray, intpair>> moveAlf;
    QVector <std::pair<int, intpair>> lengthAlf;
    QByteArray fullText;//весь текст (для ссылок) возможно будет замена на вызов из текстового браузера


    //ГЛАВНАЯ ФУНКЦИЯ ОБРАБОТКИ
    do {
        //очистка буферов и таблиц после последнего блока обработки
        alf.clear();
        bitAlf.clear();
        hclenComandLengths.clear();
        hclenLengths.clear();
        hclenArray.clear();
        moveArr.clear();
        hclength.clear();
        bitMove.clear();
        moveAlf.clear();
        lengthAlf.clear();


        //защита от бесконечного цикла в случае остаточных битов заполнения
        if (bitInput.count() - seek < 16) {
            end = true;
        }

        //ошибка определения кодов
        if (decodingError) {
            seek++;
            decodingError = false;
        }

        //ДИНАМИЧЕСКОЕ СЖАТИЕ
        if (useDynamicBlocks && (bitInput.count() - seek) > 65 && bitInput.testBit(2 + seek)) {

            bool check = true;
            unsigned int hlit = 0, hdist = 0, hclen = 0, errorSeek = 0;
            QByteArray errorText;
            seek += 2;
            errorSeek += 2;
            emit sendDecodedBitsCount(seek);

            //определение числа символов и длин
            for (int i = seek + 5; i > seek; i--) {
                hlit = hlit << 1;

                if (bitInput.testBit(i)) {
                    hlit = hlit | 1;
                }
            }

            seek += 5; //выравнивание битового сдвига на величину прочитанных битов заголовка
            errorSeek += 5;
            emit sendDecodedBitsCount(seek);

            //определение числа смещений
            for (int i = seek + 5; i > seek; i--) {
                hdist = hdist << 1;

                if (bitInput.testBit(i)) {
                    hdist = hdist | 1;
                }
            }

            //установка максимальных значений для progressbar'ов
            emit sendAlfCount(256, true, 1);
            emit sendAlfCount(hlit - 256, true, 2);
            emit sendAlfCount(hdist, true, 3);

            seek += 5; //выравнивание битового сдвига на величину прочитанных битов заголовка
            errorSeek += 5;
            emit sendDecodedBitsCount(seek);

            //определение числа команд
            for (int i = seek + 4; i > seek; i--) {
                hclen = hclen << 1;

                if (bitInput.testBit(i)) {
                    hclen = hclen | 1;
                }
            }

            seek += 4; //выравнивание битового сдвига на величину прочитанных битов заголовка
            errorSeek += 4;
            emit sendDecodedBitsCount(seek);
            hlit += 257;
            hdist += 1;
            hclen += 4;

            //формирование массива команд
            for (int i = 0; i < hclen; i++) {
                QBitArray comand(3, false);

                for (int j = 3; j > 0; j--) {
                    comand.setBit(3 - j, bitInput.testBit(seek + j));
                }

                hclenComandLengths.append(comand);
                seek += 3;
                errorSeek += 3;
                emit sendDecodedBitsCount(seek);
            }

            //генерация двумерного массива (номер кода, длина кода)
            for (int i = 0; i < 19; i++) {
                int a = 0;

                if (i < hclen) {
                    a = makeIntFromBit(hclenComandLengths[i]);
                }

                if (a != 0) {
                    hclenLengths.append(std::make_pair(hclenPositions[i], a));
                } else {
                    hclenLengths.append(std::make_pair(hclenPositions[i], NULL));
                }
            }
            hclenComandLengths.clear();

            //сортировка массива длин кодов по их номерам
            for (int i = 1; i < hclenLengths.count(); ++i) {
                for (int j = 0; j < hclenLengths.count() - i; j++) {
                    if (hclenLengths[j].first > hclenLengths[j + 1].first) {
                        QVector <std::pair<int, int>> vector;

                        vector.append(hclenLengths[j]);
                        hclenLengths[j] = hclenLengths[j + 1];
                        hclenLengths[j + 1] = vector[0];
                        vector.remove(0, 1);
                    }
                }
            }

            //генерация двумерного массива (номер кода, код)
            hclength = generateHuffmanCodes(hclenLengths);
            hclenLengths.clear();
            seek++; //выравнивание (неизвестный пропуск)
            errorSeek++;

            //защита от заполнения таблицы символов, длин и смещений нулями
//            decodingError = true;

            //запись символов в алфавит
            for (int i = 0; i < (hlit + hdist); i++) {

                //возникла ошибка выхода за границу массива
                if (notEnoughBits) {
                    break;
                }

                for (int j = 0; j < hclength.count(); j++) {
                    bit.clear();
                    bit.resize(hclength[j].second.count());

                    //защита от выхода за границу массива
                    if (bit.count() > bitInput.count() - seek) {
                        notEnoughBits = true;
                        break;
                    }

                    //запись битов из массива в буфер
                    for (int k = 0; k < bit.count(); k++) {
                        bit.setBit(k, bitInput.testBit(seek + k));
                    }

                    //команда задачи длины кода 1-15
                    if (bit == hclength[j].second && hclength[j].first < 16)
                    {
//                        decodingError = false;
                        codeFound = true;

                        alf.push_back(std::make_pair(i, hclength[j].first));
                        seek += bit.count();
                        errorSeek += bit.count();

                        if (i < 257) {
                            emit sendAlfCount(i, false, 1);
                        } else if (i > 256 && i < hlit + 1) {
                            emit sendAlfCount(i - 256, false, 2);
                        } else if (i > hlit) {
                            emit sendAlfCount(i - hlit, false, 3);
                        }

                        break;
                    }
                    //команда повторить предыдущую длину кода 3-6 раз (2 уточняющих бита)
                    if (bit == hclength[j].second && hclength[j].first == 16)
                    {
//                        decodingError = false;
                        codeFound = true;

                        seek += bit.count();
                        errorSeek += bit.count();

                        emit sendDecodedBitsCount(seek);

                        skip = 0;

                        //защита от выхода за границу массива
                        if (bitInput.count() - seek < 2) {
                            notEnoughBits = true;
                            break;
                        }

                        for (int k = 0; k < 2; k++)
                        {
                            h = 0;

                            if (bitInput.testBit(k + seek))
                            {
                                h |= 2;
                                h = h >> (1 - k);
                                skip |= h;
                            }
                        }

                        skip += 3;

                        for (int k = 0; k < skip; k++)
                        {
                            alf.push_back(std::make_pair(i, alf[i - 1].second));
                            i++;
                        }

                        i--;
                        seek += 2;
                        errorSeek += 2;

                        emit sendDecodedBitsCount(seek);

                        if (i < 257) {
                            emit sendAlfCount(i, false, 1);
                        } else if (i > 256 && i < hlit + 1) {
                            emit sendAlfCount(i - 256, false, 2);
                        } else if (i > hlit) {
                            emit sendAlfCount(i - hlit, false, 3);
                        }

                        break;
                    }
                    //команда повторить нулевую длину кода 3-10 раз (3 уточняющих битов)
                    if (bit == hclength[j].second && hclength[j].first == 17)
                    {
                        codeFound = true;

                        seek += bit.count();
                        errorSeek += bit.count();

                        emit sendDecodedBitsCount(seek);

                        skip = 0;

                        //защита от выхода за границу массива
                        if (bitInput.count() - seek < 3) {
                            notEnoughBits = true;
                            break;
                        }

                        for (int k = 0; k < 3; k++)
                        {
                            h = 0;

                            if (bitInput.testBit(k + seek))
                            {
                                h |= 4;
                                h = h >> (2 - k);
                                skip |= h;
                            }
                        }

                        skip += 3;

                        for (int k = 0; k < skip; k++)
                        {
                            alf.push_back(std::make_pair(i, NULL));
                            i++;
                        }

                        i--;
                        seek += 3;
                        errorSeek += 3;

                        emit sendDecodedBitsCount(seek);

                        if (i < 257) {
                            emit sendAlfCount(i, false, 1);
                        } else if (i > 256 && i < hlit + 1) {
                            emit sendAlfCount(i - 256, false, 2);
                        } else if (i > hlit) {
                            emit sendAlfCount(i - hlit, false, 3);
                        }

                        break;
                    }
                    //команда повторить нулевую длину кода 11-138 раз (7 уточняющих битов)
                    if (bit == hclength[j].second && hclength[j].first == 18)
                    {
                        codeFound = true;

                        seek += bit.count();
                        errorSeek += bit.count();

                        emit sendDecodedBitsCount(seek);

                        skip = 0;

                        //защита от выхода за границу массива
                        if (bitInput.count() - seek < 7) {
                            notEnoughBits = true;
                            break;
                        }

                        for (int k = 0; k < 7; k++)
                        {
                            h = 0;

                            if (bitInput.testBit(k + seek))
                            {
                                h |= 64;
                                h = h >> (6 - k);
                                skip |= h;
                            }
                        }

                        skip += 11;

                        for (int k = 0; k < skip; k++)
                        {
                            alf.push_back(std::make_pair(i, NULL));
                            i++;
                        }

                        i--;
                        seek += 7;
                        errorSeek += 7;

                        emit sendDecodedBitsCount(seek);

                        if (i < 257) {
                            emit sendAlfCount(i, false, 1);
                        } else if (i > 256 && i < hlit + 1) {
                            emit sendAlfCount(i - 256, false, 2);
                        } else if (i > hlit) {
                            emit sendAlfCount(i - hlit, false, 3);
                        }

                        break;
                    }
                    //ошибка определения кода
                    if (j == hclength.count() - 1) {
                        decodingError = true;
                        i = hlit + hdist;

                        seek -= errorSeek;//удаление неверно обработанных битов

                        break;
                    }
                }
            }

            //возникла ошибка определения кодов
            if (decodingError) {
                continue;
            }

            //возникла ошибка выхода за границу массива
            if (notEnoughBits) {
                break;
            }

            //алфавит длин частично не сформирован
            if (alf.count() <= hlit && alf.count() > 256) {
                bitAlf = generateHuffmanCodes(alf);
                globalBitAlf = bitAlf;
                alf.clear();
                lengthAlf = generateLengthAlf();
                globalLenAlf = lengthAlf;
            }

            //алфавит смещений полностью или частично не сформирован
            if (alf.count() > hlit) {
                //задаем размер массиву смещений и записываем в него данные
                moveArr.resize(alf.count() - hlit);

                for (int i = hlit; i < alf.count(); i++)
                {
                    moveArr[i - hlit] = alf[i];
                }

                alf.resize(hlit);

                bitAlf = generateHuffmanCodes(alf);
                bitMove = generateHuffmanCodes(moveArr);
                globalBitAlf = bitAlf;
                alf.clear();
                moveArr.clear();

                //формируем итоговые алфавиты длин и смещений
                moveAlf = generateMoveAlf(bitMove);
                globalMoveAlf = moveAlf;
                lengthAlf = generateLengthAlf();
                globalLenAlf = lengthAlf;
                bitMove.clear();
            }

            emit sendElementsInAlfCount(bitAlf.count(), 1);
            emit sendElementsInAlfCount(lengthAlf.count(), 2);
            emit sendElementsInAlfCount(moveAlf.count(), 3);

            codeFound = false;

            //непосредственно декомпрессия
            while (check) {
                //возникла ошибка в определении кода
                if (decodingError) {
                    seek -= errorSeek; //вычитываем ошибочно обработанные биты
                    fullText.remove(fullText.count() - errorText.count(), errorText.count()); //удаляем неверно записанные символы
                    errorText.clear();

                    break;
                }

                //возникла ошибка выхода за границу массива
                if (notEnoughBits) {
                    break;
                }

                for (int i = 0; i < bitAlf.count(); i++) {
                    bit.clear();
                    bit.resize(bitAlf[i].second.count());

                    //защита от выхода за границу массива
                    if (bit.count() > bitInput.count() - seek) {
                        notEnoughBits = true;
                        break;
                    }

                    //запись битов из массива в буфер
                    for (int j = 0; j < bit.count(); j++) {
                        bit.setBit(j, bitInput.testBit(seek + j));
                    }

                    //найдено совпадение с кодом символов
                    if (bit == bitAlf[i].second && bitAlf[i].first < 256) {
                        codeFound = true;

                        //добавляем длину кода к отработанным битам
                        seek += bit.count();
                        errorSeek += bit.count();
                        emit sendDecodedBitsCount(seek);

                        //добавление символа в полный текст
                        fullText.append(bitAlf[i].first);
                        errorText.append(bitAlf[i].first);

                        //отправка сигнала на передачу данных в контроллер
                        emit sendTextAndCode(presentIntInASCII(bitAlf[i].first), presentBitsInBytes(bit));

                        break;
                    }

                    //найдено совпадение с кодом конца блока
                    if (bit == bitAlf[i].second && bitAlf[i].first == 256) {
                        codeFound = true;

                        //ставим флаги конца блока
                        check = false;

                        if (type) {
                            endOfBlock = true;
                        }

                        //добавляем длину кода к отработанным битам
                        seek += bit.count();
                        errorSeek += bit.count();
                        emit sendDecodedBitsCount(seek);

                        break;
                    }

                    //найдено совпадение с кодом длины
                    if (bit == bitAlf[i].second && bitAlf[i].first > 256) {
                        //коды длины и смещения + доп биты
                        QBitArray length, move, lengthExtraBits, moveExtraBits;

                        //записываем биты длины
                        length = bit;

                        //добавляем длину кода к отработанным битам
                        seek += bit.count();
                        errorSeek += bit.count();
                        emit sendDecodedBitsCount(seek);
                        bit.clear();

                        //определяем диапозон и количество уточняющих битов
                        int len = lengthAlf[bitAlf[i].first - 257].second.diapozon;
                        int extrabits = lengthAlf[bitAlf[i].first - 257].second.extrabit;

                        bit.resize(extrabits);

                        //защита от выхода за границу массива
                        if (bit.count() > bitInput.count() - seek) {
                            notEnoughBits = true;
                            break;
                        }

                        //переписываем уточняющие биты в буфер
                        for (int k = 0; k < extrabits; k++) {
                            bit.setBit(k, bitInput.testBit(seek + k));
                        }

                        //записываем дополнительные биты длины
                        lengthExtraBits = bit;

                        //выравнивание битового сдвига на длину уточняющих битов и вычисление длины копируемых символов
                        seek += bit.count();
                        errorSeek += bit.count();
                        emit sendDecodedBitsCount(seek);
                        extrabits = makeIntFromBit(bit, true);
                        len += extrabits;
                        bit.clear();

                        //moveAlf содержит .first = QBitArray / .second.diaposon = int / .second.extrabits = int
                        for (int j = 0; j < moveAlf.count(); j++) {
                            bit.resize(moveAlf[j].first.count());

                            //защита от выхода за границу массива
                            if (bit.count() > bitInput.count() - seek) {
                                notEnoughBits = true;
                                break;
                            }

                            //запись битов из массива в буфер
                            for (int k = 0; k < bit.count(); k++) {
                                bit.setBit(k, bitInput.testBit(k + seek));
                            }

                            //поиск совпадения с кодом смещения
                            if (bit == moveAlf[j].first) {
                                codeFound = true;

                                //записываем биты смещения
                                move = bit;

                                seek += bit.count();
                                errorSeek += bit.count();
                                emit sendDecodedBitsCount(seek);
                                bit.clear();

                                //определение длины смещения
                                int mlen = moveAlf[j].second.diapozon;
                                int mextrabits = moveAlf[j].second.extrabit;

                                bit.resize(mextrabits);

                                //защита от выхода за границу массива
                                if (bit.count() > bitInput.count() - seek) {
                                    notEnoughBits = true;
                                    break;
                                }

                                //запись битов из массива в буфер
                                for (int k = 0; k < mextrabits; k++) {
                                    bit.setBit(k, bitInput.testBit(k + seek));
                                }

                                //записываем дополнительные биты смещения
                                moveExtraBits = bit;

                                seek += bit.count();
                                errorSeek += bit.count();
                                emit sendDecodedBitsCount(seek);
                                mextrabits = makeIntFromBit(bit, true);
                                mlen += mextrabits;
                                bit.clear();

                                //проверка корректности ссылки
                                if (fullText.count() - mlen >= 0 && mlen >= len) {
                                    //добавление в полный текст скопированных символов
                                    QByteArray copy;

                                    for (int k = 0; k < len; k++) {
                                        copy.append(fullText.at(fullText.count() - mlen + k));
                                    }

                                    //добавляем скопированные символы в общий текст
                                    fullText.append(copy);

                                    //составляем строку(QByteArray) в формате "код длины:доп.биты длины   код смещения:доп. биты смещения"
                                    QByteArray LMCode;

                                    LMCode.append(presentBitsInBytes(length) + ":");

                                    if (lengthExtraBits.count() != 0) {
                                        LMCode.append("(" + presentBitsInBytes(lengthExtraBits) + ")");
                                    } else {
                                        LMCode.append("(null)");
                                    }

                                    LMCode.append(" ");
                                    LMCode.append(presentBitsInBytes(move) + ":");

                                    if (lengthExtraBits.count() != 0) {
                                        LMCode.append("(" + presentBitsInBytes(moveExtraBits) + ")");
                                    } else {
                                        LMCode.append("(null)");
                                    }

                                    emit sendTextWithLengthAndMove(copy, LMCode);

                                    LMCode.clear();
                                    copy.clear();

                                    break;
                                } else {
                                    j = moveAlf.count();
                                }
                            }
                            //код смещения не найден
//                            if (/*j >= moveAlf.count() - 1*/!codeFound) {
//                                decodingError = true; //помечаем вид ошибки
//                                i = bitAlf.count() - 1; // выход из внешнего цикла

//                                break; //выход из внутреннего цикла
//                            }
                        }

                        break;
                    }

                    //ошибка определения кодов
                    if (i == bitAlf.count() - 1) {
                        decodingError = true;

                        break;
                    }
                }
            }

            //ошибка чтения кодов
            if (decodingError) {
                continue;
            }

            //ошибка выхода за границу массива
            if (notEnoughBits) {
                break;
            }
        }
        else if (!useDynamicBlocks && (bitInput.count() - seek) > 65 && bitInput.testBit(2 + seek)) {
            decodingError = true;
            continue;
        }

        //СТАТИЧЕСКОЕ СЖАТИЕ
        if (useStaticBlocks && (bitInput.count() - seek) > 50 && bitInput.testBit(1 + seek)) {

            emit sendText("Позиция первого бита: " + QString::number(seek));

            bitAlf.clear();

            int errorSeek = 0;
            bool check = true;
            QByteArray errorText;
            seek += 3;
            errorSeek += 3;
            emit sendDecodedBitsCount(seek);

            //формирование масссива символов и длин
            for (int i = 0; i < 144; i++) {
                bitAlf.append(std::make_pair(i, generateCode(i + 48, 8)));
            }

            for (int i = 144; i < 256; i++) {
                bitAlf.append(std::make_pair(i, generateCode(i + 256, 9)));
            }

            for (int i = 256; i < 280; i++) {
                bitAlf.append(std::make_pair(i, generateCode(i - 256, 7)));
            }

            for (int i = 280; i < 286; i++) {
                bitAlf.append(std::make_pair(i, generateCode(i - 88, 8)));
            }

            //создание шаблонного массива длин
            lengthAlf = generateLengthAlf();

            //формирование массива смещений
            for (int i = 0; i < 30; i++) {
                moveArr.append(std::make_pair(i, 5));
            }

            bitMove = generateHuffmanCodes(moveArr);
            moveArr.clear();
            moveAlf = generateMoveAlf(bitMove);
            bitMove.clear();

            //дополнение массива смещений
            for (int i = 4; i > 0; i--) {
                intpair extra;
                extra.diapozon = i;
                extra.extrabit = 0;
                moveAlf.prepend(std::make_pair(generateCode(i - 1, 5), extra));
            }

            //непосредственно декомпрессия
            while (check) {
                //возникла ошибка в определении кода
                if (decodingError) {
                    seek -= errorSeek; //вычитываем ошибочно обработанные биты
                    fullText.remove(fullText.count() - errorText.count(), errorText.count()); //удаляем неверно записанные символы
                    errorText.clear();

                    break;
                }

                //выход за границу массива
                if (notEnoughBits) {
                    break;
                }

                for (int i = 0; i < bitAlf.count(); i++) {
                    bit.clear();
                    bit.resize(bitAlf[i].second.count());

                    //защита от выхода за границу массива
                    if (bit.count() > bitInput.count() - seek) {
                        notEnoughBits = true;
                        break;
                    }

                    //запись битов из массива в буфер
                    for (int j = 0; j < bit.count(); j++) {
                        bit.setBit(j, bitInput.testBit(seek + j));
                    }

                    //найдено совпадение с кодом символов
                    if (bit == bitAlf[i].second && bitAlf[i].first < 256) {
                        //добавляем длину кода к отработанным битам
                        seek += bit.count();
                        errorSeek += bit.count();
                        emit sendDecodedBitsCount(seek);

                        //добавление символа в полный текст
                        fullText.append(bitAlf[i].first);
                        errorText.append(bitAlf[i].first);

                        //отправка сигнала на передачу данных в контроллер
                        emit sendTextAndCode(presentIntInASCII(bitAlf[i].first), presentBitsInBytes(bit));

                        break;
                    }

                    //найдено совпадение с кодом конца блока
                    if (bit == bitAlf[i].second && bitAlf[i].first == 256) {
                        //ставим флаги конца блока
                        check = false;

                        if (type) {
                            endOfBlock = true;
                        }

                        //добавляем длину кода к отработанным битам
                        seek += bit.count();
                        errorSeek += bit.count();
                        emit sendDecodedBitsCount(seek);

                        break;
                    }

                    //найдено совпадение с кодом длины
                    if (bit == bitAlf[i].second && bitAlf[i].first > 256) {
                        //коды длины и смещения + доп биты
                        QBitArray length, move, lengthExtraBits, moveExtraBits;

                        //записываем биты длины
                        length = bit;

                        //добавляем длину кода к отработанным битам
                        seek += bit.count();
                        errorSeek += bit.count();
                        emit sendDecodedBitsCount(seek);
                        bit.clear();

                        //определяем диапозон и количество уточняющих битов
                        int len = lengthAlf[bitAlf[i].first - 257].second.diapozon;
                        int extrabits = lengthAlf[bitAlf[i].first - 257].second.extrabit;

                        bit.resize(extrabits);

                        //защита от выхода за границу массива
                        if (bit.count() > bitInput.count() - seek) {
                            notEnoughBits = true;
                            break;
                        }

                        //переписываем уточняющие биты в буфер
                        for (int k = 0; k < extrabits; k++) {
                            bit.setBit(k, bitInput.testBit(seek + k));
                        }

                        //записываем дополнительные биты длины
                        lengthExtraBits = bit;

                        //выравнивание битового сдвига на длину уточняющих битов и вычисление длины копируемых символов
                        seek += bit.count();
                        errorSeek += bit.count();
                        emit sendDecodedBitsCount(seek);
                        extrabits = makeIntFromBit(bit, true);
                        len += extrabits;
                        bit.clear();

                        //moveAlf содержит .first = QBitArray / .second.diaposon = int / .second.extrabits = int
                        for (int j = 0; j < moveAlf.count(); j++) {
                            bit.resize(moveAlf[j].first.count());

                            //защита от выхода за границу массива
                            if (bit.count() > bitInput.count() - seek) {
                                notEnoughBits = true;
                                break;
                            }

                            //запись битов из массива в буфер
                            for (int k = 0; k < bit.count(); k++) {
                                bit.setBit(k, bitInput.testBit(k + seek));
                            }

                            //поиск совпадения с кодом смещения
                            if (bit == moveAlf[j].first) {
                                //код найден
                                codeFound = true;

                                //записываем биты смещения
                                move = bit;

                                seek += bit.count();
                                errorSeek += bit.count();
                                emit sendDecodedBitsCount(seek);
                                bit.clear();

                                //определение длины смещения
                                int mlen = moveAlf[j].second.diapozon;
                                int mextrabits = moveAlf[j].second.extrabit;

                                bit.resize(mextrabits);

                                //защита от выхода за границу массива
                                if (bit.count() > bitInput.count() - seek) {
                                    notEnoughBits = true;
                                    break;
                                }

                                for (int k = 0; k < mextrabits; k++) {
                                    bit.setBit(k, bitInput.testBit(k + seek));
                                }

                                //записываем дополнительные биты смещения
                                moveExtraBits = bit;

                                seek += bit.count();
                                errorSeek += bit.count();
                                emit sendDecodedBitsCount(seek);
                                mextrabits = makeIntFromBit(bit, true);
                                mlen += mextrabits;
                                bit.clear();

                                //проверка корректности ссылки
                                if (fullText.count() - mlen >= 0 && len < mlen ) {
                                    //добавление в полный текст скопированных символов
                                    QByteArray copy;

                                    for (int k = 0; k < len; k++) {
                                        copy.append(fullText.at(fullText.count() - mlen + k));
                                    }

                                    //добавляем скопированные символы в общий текст
                                    fullText.append(copy);

                                    //составляем строку(QByteArray) в формате "код длины:доп.биты длины   код смещения:доп. биты смещения"
                                    QByteArray LMCode;

                                    LMCode.append(presentBitsInBytes(length) + ":");

                                    if (lengthExtraBits.count() != 0) {
                                        LMCode.append("(" + presentBitsInBytes(lengthExtraBits) + ")");
                                    } else {
                                        LMCode.append("(null)");
                                    }

                                    LMCode.append(" ");
                                    LMCode.append(presentBitsInBytes(move) + ":");

                                    if (lengthExtraBits.count() != 0) {
                                        LMCode.append("(" + presentBitsInBytes(moveExtraBits) + ")");
                                    } else {
                                        LMCode.append("(null)");
                                    }

                                    emit sendTextWithLengthAndMove(copy, LMCode);

                                    LMCode.clear();
                                    copy.clear();

                                    break;
                                } else {
                                    j = moveAlf.count() - 1;
                                }
                            }

                            //код смещения не найден
                            if (j >= moveAlf.count() - 1) {
                                decodingError = true; //помечаем вид ошибки
                                i = bitAlf.count() - 1; // выход из внешнего цикла

                                break; //выход из внутреннего цикла
                            }
                        }

                        break;
                    }

                    //код не найден
                    if (i == bitAlf.count() - 1) {
                        decodingError = true;

                        break;
                    }
                }
            }

            emit sendText("Позиция последнего бита:" + QString::number(seek) + "\nОбработано " + QString::number(errorSeek) + " бит");

            //смещение начальной позиции обработки
            if (decodingError) {
                continue;
            }

            //=================================================
            //конец обработки из-за выхода за границу массива
            if (notEnoughBits) {
                emit sendErrorMessage("Недостаточно данных для дальнейшей обработки");
                break;
            }
            //=================================================
        }
        else if (!useStaticBlocks && (bitInput.count() - seek) > 50 && bitInput.testBit(1 + seek)) {
            decodingError = true;
            continue;
        }

        //БЕЗ СЖАТИЯ
        if (useBlocksWithoutCompression && (bitInput.count() - seek) > 50 && !bitInput.testBit(1 + seek) && !bitInput.testBit(2 + seek)) {

            unsigned int errorSeek = 0;
            seek += 3;
            errorSeek += 3;

            QBitArray n;
            QByteArray symbol;
            int len = 0, nlen = 0;

            for (int i = 0; i < 8; i++) {

                n.clear();
                n.resize(16);

                //защита от выхода за границу массива
                if (bitInput.count() - seek < 32) {
                    notEnoughBits = true;
                    break;
                }

                //запись битов из массива в буфер для формирования значения len
                for (int i = 0; i < 16; i++) {
                    n.setBit(i, bitInput.testBit(seek));
                    seek++;
                    errorSeek++;
                }

                len = makeIntFromBit(n);

                n.clear();
                n.resize(16);

                //запись битов из массива в буфер для формирования значения nlen
                for (int i = 0; i < 16; i++) {
                    n.setBit(i, bitInput.testBit(seek));
                    seek++;
                    errorSeek++;
                }

                nlen = makeIntFromBit(n);

                if ((len | nlen) == 65535 && len > 0) {

                    decodingError = false;

                    //защита от выхода за границу массива
                    if (bitInput.count() - seek < len * 8) {
                        notEnoughBits = true;
                        break;
                    }

                    for (int i = 0; i < len; i++) {

                        n.clear();
                        n.resize(8);

                        for (int j = 0; j < 8; j++) {
                            n.setBit(j, bitInput.testBit(seek));
                            seek++;
                        }

                        symbol.append(makeIntFromBit(n));

                        emit sendTextAndCode(symbol, presentBitsInBytes(n));

                        symbol.clear();
                        n.clear();
                    }

                    break;
                } else {
                    //код не найден
                    decodingError = true;

                    seek -= errorSeek;
                    errorSeek = 0;
                    seek += 4;
                }

                //возникла ошибка выхода за границу массива
                if (notEnoughBits) {
                    break;
                }
            }

            //ошибка определения кода
            if (decodingError) {
                //вычитываем неверно обработанные биты
                seek -= 4;

                continue;
            }
        }
        else if (!useBlocksWithoutCompression && (bitInput.count() - seek) > 50 && !bitInput.testBit(1 + seek) && !bitInput.testBit(2 + seek)) {
            decodingError = true;
            continue;
        }

        //ОШИБКА. ПОИСК СЛЕДУЮЩЕГО СОВПАДЕНИЯ
        if (bitInput.testBit(1 + seek) && bitInput.testBit(2 + seek))
        {
            seek++;
        }
    } while (!endOfBlock);

    qDebug()<<"stop";
    //    emit sendResult(text);
}

void Deflate::prepareAlf(const int type)
{
    if (type == 1) {
        QByteArray charAlf;

        for (int i = 0; i < globalBitAlf.count(); i++) {
            if (globalBitAlf[i].first < 256) {
                charAlf.append("символ: ");
                charAlf.append(globalBitAlf[i].first);
                charAlf.append(" код: ");
                charAlf.append(presentBitsInBytes(globalBitAlf[i].second));
                charAlf.append("\n");
            } else if (globalBitAlf[i].first == 256) {
                charAlf.append("код конца блока: ");
                charAlf.append(presentBitsInBytes(globalBitAlf[i].second));
                charAlf.append("\n");
            } else if (globalBitAlf[i].first == 32) {
                charAlf.append("символ: 'пробел' код: ");
                charAlf.append(presentBitsInBytes(globalBitAlf[i].second));
            }
        }

        emit sendAlf(charAlf, 1);
    } else if (type == 2) {
        QByteArray lenAlf;

        for (int i = 0; i < globalBitAlf.count(); i++) {
            if (globalBitAlf[i].first > 256) {
                lenAlf.append("диапозон: ");
                lenAlf.append(QString::number(globalLenAlf[globalBitAlf[i].first - 257].second.diapozon));
                lenAlf.append(" уточняющие биты: ");
                lenAlf.append(QString::number(globalLenAlf[globalBitAlf[i].first - 257].second.extrabit));
                lenAlf.append(" код: ");
                lenAlf.append(presentBitsInBytes(globalBitAlf[i].second));
                lenAlf.append("\n");
            }
        }

        emit sendAlf(lenAlf, 2);
    } else if (type == 3) {
        QByteArray moveAlf;

        for (int i = 0; i < globalMoveAlf.count(); i++) {
            moveAlf.append("диапозон: ");
            moveAlf.append(QString::number(globalMoveAlf[i].second.diapozon));
            moveAlf.append(" уточняющие биты: ");
            moveAlf.append(QString::number(globalMoveAlf[i].second.extrabit));
            moveAlf.append(" код: ");
            moveAlf.append(presentBitsInBytes(globalMoveAlf[i].first));
            moveAlf.append("\n");
        }

        emit sendAlf(moveAlf, 3);
    }
}

