#pragma once
#include <stdlib.h>
#ifndef CONVERT_H
#define CONVERT_H

typedef unsigned long long _stringLen;
#define STRING_SEGMENT_LENGTH (9)

// bool _strToInfNum2(char* str, PInfNum num)
// {
//     unsigned long long i = 0;//处理位置记录
//     if (str[0] == '-')
//     {
//         num->info.sign = INF_NEGATIVE;
//     }
//     else
//     {
//         num->info.sign = INF_POSITIVE;
//     }
//     return false;
// }

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



    return false;
}

inline unsigned int _9charSegmentTo32bitInteger(const char* str) {
    char strBuf[STRING_SEGMENT_LENGTH + 1 << 1] = {
	    	1,0,0,0,0,0,0,0,0,0,
	    	1,0,0,0,0,0,0,0,0,0//1:溢出标志位置位（如果减法溢出，则该位会退位为0
		},//1位溢出位，剩余9位数据位
        *currentBuf = strBuf + 1,//9或19，对应2段缓冲区（从右至左）
        *nextBuf = currentBuf + STRING_SEGMENT_LENGTH + 1,
    	cascadesLUT[] = {
            5,3,6,8,7,0,9,1,2,
            2,6,8,4,3,5,4,5,6,
            1,3,4,2,1,7,7,2,8,
            0,6,7,1,0,8,8,6,4,
            0,3,3,5,5,4,4,3,2,
            0,1,6,7,7,7,2,1,6,
            0,0,8,3,8,8,6,0,8,
            0,0,4,1,9,4,3,0,4,
            0,0,2,0,9,7,1,5,2,
            0,0,1,0,4,8,5,7,6,
            0,0,0,5,2,4,2,8,8,
            0,0,0,2,6,2,1,4,4,
            0,0,0,1,3,1,0,7,2,
            0,0,0,0,6,5,5,3,6,
            0,0,0,0,3,2,7,6,8,
            0,0,0,0,1,6,3,8,4,
            0,0,0,0,0,8,1,9,2,
            0,0,0,0,0,4,0,9,6,
            0,0,0,0,0,2,0,4,8,
            0,0,0,0,0,1,0,2,4,
            0,0,0,0,0,0,5,1,2,
            0,0,0,0,0,0,2,5,6,
            0,0,0,0,0,0,1,2,8,
            0,0,0,0,0,0,0,6,4,
            0,0,0,0,0,0,0,3,2,
            0,0,0,0,0,0,0,1,6,
            0,0,0,0,0,0,0,0,8
        },//27个9位字符串
        *currentCascade = cascadesLUT;//9的倍数，在lut中读取对应的界限值
    for (char j = STRING_SEGMENT_LENGTH - 1; j >= 0; j--) {
        currentBuf[j] = str[j] - '0';
    }//数据归一化后输入到buffer
    unsigned int num = 0;//32位,输出结果存于此
    for (char i = 0; i < 27; i++) {
        for (char j = STRING_SEGMENT_LENGTH - 1; j >= 0; j--) {
            nextBuf[j] += currentBuf[j] - currentCascade[j];
            if (nextBuf[j] < 0) {
                nextBuf[j] += 10;
                nextBuf[j - 1] = -1;
            }
        }
        num <<= 1;
        if (nextBuf[-1] == 1) {//是0则说明被退位了
            num |= 1;//该位如果够减，则存一位到数字中
            currentBuf = (char*)((unsigned long long)currentBuf ^ (unsigned long long)nextBuf);//交换一下缓冲区
            nextBuf = (char*)((unsigned long long)nextBuf ^ (unsigned long long)currentBuf);
            currentBuf = (char*)((unsigned long long)currentBuf ^ (unsigned long long)nextBuf);
        }
    	memset(nextBuf, 0, STRING_SEGMENT_LENGTH);
    	nextBuf[-1] = 1;
        currentCascade += STRING_SEGMENT_LENGTH;
    }
    num <<= 3;
    num += currentBuf[STRING_SEGMENT_LENGTH - 1];//最后3位只能代表0-8，那么十进制只有一位，直接拷过来减少3轮循环
    return num;
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
