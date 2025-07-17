#include <stdlib.h>
#include <string.h>
#include "infinity.h"

//test
#include <stdio.h>
#include <string.h>

void test(void)
{
    printf("Infinity\n");
}

bool initInfNum(PInfNum num, _InfNumType type, _InfNumSign sign)
{
    num->info.type = type;
    num->info.sign = sign;
    num->info.intNodeAllocateCount = 0;
    if (type & INF_INT)
    {
        num->intPart = malloc(sizeof(InfInt));
        if (!num->intPart)
        {
            num->info.error = true;
            return false;
        } //无法分配内存
        num->intPart->firstDataNode = nullptr;
        num->intPart->lastDataNode = nullptr;
        num->intPart->nodeCount = 0;
    }
    else
    {
        num->intPart = nullptr; //未使用则置空
    }
    if (type & INF_FRACT)
    {
        num->fractPart = malloc(sizeof(InfFract));
        if (!num->fractPart)
        {
            num->info.error = true;
            return false;
        } //无法分配内存
        num->fractPart->value = nullptr;
        num->fractPart->byteLength = 0;
    }
    else
    {
        num->fractPart = nullptr; //未使用则置空
    }
    return true;
}

bool extendIntPart(PInfNum num, unsigned short byteLength)
{
    if (num->intPart->nodeCount==INF_MAX_NODE_COUNT){
        num->info.error = true;
        return false;
    } //节点数量达到上限
    PInfIntDataNode newNode = malloc(sizeof(InfIntDataNode));
    if (!newNode)
    {
        num->info.error = true;
        return false;
    } //无法分配内存
    newNode->nextNode = nullptr;
    newNode->data = malloc(byteLength);
    if (!newNode->data)
    {
        num->info.error = true;
        return false;
    } //无法分配内存
    memset(newNode->data, 0, byteLength);
    num->intPart->nodeCount++;
    newNode->byteLength = byteLength;
    if (num->intPart->nodeCount)
    {
        newNode->prevNode = num->intPart->lastDataNode;
        newNode->prevNode->nextNode = newNode;
        num->intPart->lastDataNode = newNode;
    }
    else
    {
        num->intPart->firstDataNode = newNode;
        num->intPart->lastDataNode = newNode;
    }
    if (num->info.intNodeAllocateCount<INF_MAX_NODE_ALLOC_COUNT)
    {
        num->info.intNodeAllocateCount++;
    }
    return true;
}

bool initFractPart(PInfNum num, unsigned char byteLength)
{
    num->fractPart->byteLength = byteLength;
    num->fractPart->value = malloc(byteLength);
    if (!num->fractPart->value)
    {
        num->info.error = true;
        return false;
    } //无法分配内存
    memset(num->fractPart->value, 0, byteLength);
    return true;
}

//test
