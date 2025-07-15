#pragma once
#include <stdint.h>

#ifndef INFINITY_LIBRARY_H
#define INFINITY_LIBRARY_H

void test(void);

typedef struct _InfNumInfo
{
    unsigned int sign : 1;
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
} InfNum, *PInfNum;

#endif //INFINITY_LIBRARY_H
