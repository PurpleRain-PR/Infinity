#pragma once
#include <stdint.h>

#ifndef INFINITY_LIBRARY_H
#define INFINITY_LIBRARY_H

void test(void);

//类型
typedef const unsigned char _InfNumType;
#define INF_INT (1)
#define INF_FRACT (2)
#define INF_INT_FRACT (3)

//正负
typedef const unsigned char _InfNumSign;
#define INF_POSITIVE (0)
#define INF_NEGATIVE (1)

//内存管理
#define INF_MAX_NODE_ALLOC_COUNT (15)
#define INF_MAX_NODE_COUNT (255)

typedef struct _InfNumInfo //数字的元数据
{
    unsigned sign : 1; //符号，如宏所示
    unsigned type : 2; //数字类型，如宏所示，高位代表整数，低位代表小数，即1:纯小数,2:纯整数,3:整数与小数
    unsigned intNodeAllocateCount : 4; //上一次节点合并重组后新开辟数据节点的次数，用于自动合并重组，每15次时达到强制重组标准，若没有整数部分，该值为0
    unsigned error : 1; //记录运行时是否发生错误,为真则该数据不可用
} InfNumInfo, *PInfNumInfo;

typedef struct _InfinityIntegerDataNode //整数数据链表的节点
{
    unsigned short byteLength;
    unsigned char* data; //指向一个数组
    struct _InfinityIntegerDataNode* nextNode;
    struct _InfinityIntegerDataNode* prevNode;
} InfIntDataNode, *PInfIntDataNode;

typedef struct _InfinityInteger
{
    unsigned char nodeCount;
    PInfIntDataNode firstDataNode;
    PInfIntDataNode lastDataNode;
} InfInt, *PInfInt;

typedef struct _InfinityFract
{
    unsigned char byteLength;
    unsigned char* value;
} InfFract, *PInfFract;

typedef struct _InfinityNumber
{
    InfNumInfo info;
    PInfInt intPart;
    PInfFract fractPart;
} InfNum, *PInfNum;

#endif INFINITY_LIBRARY_H
