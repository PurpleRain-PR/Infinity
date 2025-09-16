// #pragma once
// #include <stdint.h>

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
    unsigned intNodeAllocateCount : 3; //上一次节点合并重组后新开辟数据节点的次数，用于自动合并重组，每15次时达到强制重组标准，若没有整数部分，该值为0
    unsigned lockShrink : 1; //是否锁定缩小，若为真，则不允许缩小整数部分
    unsigned error : 1; //记录运行时是否发生错误,为真则该数据不可用于读取值（作为被运算数以及被转换为其它类型），只能写入值
} InfNumInfo, *PInfNumInfo;

typedef struct _InfinityIntegerDataNode //整数数据链表的节点
{
    unsigned long long byteLength;//直接longlong算了，因为要对齐字节数，用short还是白白填充了6字节
    unsigned char* data; //指向一个数组
    struct _InfinityIntegerDataNode* nextNode;
    struct _InfinityIntegerDataNode* prevNode;
} InfIntDataNode, *PInfIntDataNode;

typedef struct _InfinityInteger //整数
{
    unsigned long long nodeCount;
    PInfIntDataNode firstDataNode;
    PInfIntDataNode lastDataNode;
} InfInt, *PInfInt;

typedef struct _InfinityFract //小数
{
    unsigned long long byteLength;
    unsigned char* value;
} InfFract, *PInfFract;

typedef struct _InfinityNumber //数字
{
    InfNumInfo info;
    PInfInt intPart;
    PInfFract fractPart;
} InfNum, *PInfNum;

typedef struct _Byte
{
    unsigned _1:1;
    unsigned _2:1;
    unsigned _3:1;
    unsigned _4:1;
    unsigned _5:1;
    unsigned _6:1;
    unsigned _7:1;
    unsigned _8:1;
}Byte,*PByte;

#endif //INFINITY_LIBRARY_H
