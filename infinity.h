#pragma once
#include <stdint.h>

#ifndef INFINITY_LIBRARY_H
#define INFINITY_LIBRARY_H

void test(void);

//类型
typedef  unsigned char _InfNumType;
#define INF_INT (1)
#define INF_FRACT (2)
#define INF_INT_FRACT (3)

//正负
typedef  unsigned char _InfNumSign;
#define INF_POSITIVE (0)
#define INF_NEGATIVE (1)

typedef struct _InfNumInfo
{
    unsigned int sign : 1;
    unsigned int type : 2;//高位代表整数，低位代表小数，即1:纯小数,2:纯整数,3:整数与小数
    unsigned int intNodeAllocateCount:4;//上一次节点合并重组后新开辟数据节点的次数，用于自动合并重组，每15次时达到强制重组标准，若没有整数部分，该值为0

} InfNumInfo, *PInfNumInfo;

typedef struct _InfinityIntegerDataNode
{
    uint64_t dataLength;
    uint64_t* data;
    struct _InfinityIntegerDataNode* nextNode;
    struct _InfinityIntegerDataNode* lastNode;
} InfIntDataNode, *PInfIntDataNode;

typedef struct _InfinityInteger
{
    uint64_t length;
    uint64_t* firstDataNode;
} InfInt, *PInfInt;

typedef struct _InfinityFract
{
    uint64_t length;
    uint64_t* value;
} InfFract, *PInfFract;

typedef struct _InfinityNumber
{
    InfNumInfo info;
    PInfInt intPart;
    PInfFract fractPart;

} InfNum, *PInfNum;

#endif //INFINITY_LIBRARY_H
