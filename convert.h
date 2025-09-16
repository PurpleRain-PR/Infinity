#pragma once
#include <stdlib.h>
#include <string.h>
#ifndef CONVERT_H
#define CONVERT_H

typedef unsigned long long _stringLen;
#define STRING_SEGMENT_LENGTH (9)

bool _strToInfNum2(char* str, PInfNum num)
{
    unsigned long long i = 0;//处理位置记录
    if (str[0] == '-')
    {
        num->info.sign = INF_NEGATIVE;
    }
    else
    {
        num->info.sign = INF_POSITIVE;
    }
    return false;
}

bool _strToInfNum10(char* str, PInfNum num)
{
    _stringLen start = 0, end, point = 0;//不动的标记位 //start指向数据的首有效位，point指向小数点，end指向整个数字最后一位的下一位
    //这里把point初值设0，是因为point最小值是1，不可能为0，如果处理后，point还是0，就代表这个数是整数
    num->info.sign = str[start] == '-';
    for (_stringLen i = 0; ; i++) {//预处理，标定重要分界点的位置
        start += str[start] == '0';
        if (str[i] == '.') point = i;
        else if (str[i] == '\0'){
            end = i;
            break;
        }
    }
    start -= point &&start == point;//如果是0.几，需要start向前移位指向0

    char strBuf[STRING_SEGMENT_LENGTH << 1],
        bufOffset = 0,//0或9，对应2段缓冲区
        lutOffset = 0,//9的倍数，在lut中读取对应的界限值
        cascadesLUT[234] = "536870912268435456134217728067108864033554432016777216008388608004194304002097152001048576000524288000262144000131072000065536000032768000016384000008192000004096000002048000001024000000512000000256000000128000000064000000032000000016";//26个9位字符串
    return false;
}

// bool strToInfNum(char* str, PInfNum num, const char decimal)
// {
//     if (decimal == 2)
//     {
//         //2进制拉出来单独处理
//         return _strToInfNum2(str, num);
//     }
// }


#endif //CONVERT_H
