#pragma once
#include <stdlib.h>
#include <string.h>
#ifndef INITIAL_H
#define INITIAL_H

bool initInfNum(PInfNum num, _InfNumType type, _InfNumSign sign) //初始化Num，包括属性录入，内存开辟等，若操作失败，返回false
{
    num->info.type = type;
    num->info.sign = sign;
    num->info.intNodeAllocateCount = 0;
    if (type & INF_INT) //有这部分才开辟对应内存区，否则置空
    {
        num->intPart = malloc(sizeof(InfInt));
        if (!num->intPart)
        {
            num->info.error = true; //记录错误
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
    if (type & INF_FRACT) //有这部分才开辟对应内存区，否则置空
    {
        num->fractPart = malloc(sizeof(InfFract));
        if (!num->fractPart)
        {
            num->info.error = true; //记录错误
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

bool extendIntPart(PInfNum num, unsigned short byteLength) //增加整数部分链表的节点，并为该节点分配指定字节大小的存储区，若失败，返回false
{
    if (num->intPart->nodeCount == INF_MAX_NODE_COUNT) //整数部分节点数量达到上限，报错
    {
        num->info.error = true;
    } //节点数量达到上限
    PInfIntDataNode newNode = malloc(sizeof(InfIntDataNode)); //为新的节点开辟内存
    if (!newNode)
    {
        num->info.error = true;
    } //无法分配内存
    newNode->nextNode = nullptr;
    newNode->data = malloc(byteLength); //为新节点的数据段开辟内存
    if (!newNode->data)
    {
        num->info.error = true;
    } //无法分配内存
    memset(newNode->data, 0, byteLength); //初始化新的数据段
    num->intPart->nodeCount++;
    newNode->byteLength = byteLength;
    if (num->intPart->nodeCount) //更新链表结构
    {
        newNode->prevNode = num->intPart->lastDataNode;
        newNode->prevNode->nextNode = newNode;
        num->intPart->lastDataNode = newNode;
    }
    else //特判：若链表为空，则新节点为第一个节点
    {
        num->intPart->firstDataNode = newNode;
        num->intPart->lastDataNode = newNode;
    }
    if (num->info.intNodeAllocateCount < INF_MAX_NODE_ALLOC_COUNT)
    {
        num->info.intNodeAllocateCount++;
    }
    if (num->info.error) //在此处统一退出，杜绝内存泄漏
    {
        free(newNode->data);
        free(newNode);
        return false;
    }
    return true;
}

bool initFractPart(PInfNum num, unsigned char byteLength) //初始化小数部分，并根据指定的字节数目开辟固定数据段
{
    num->fractPart->byteLength = byteLength;
    num->fractPart->value = malloc(byteLength);
    if (!num->fractPart->value)
    {
        num->info.error = true;
        //这里不用free，因为这里只malloc了一次，若失败也就没有分配任何内存了
        return false;
    } //无法分配内存
    memset(num->fractPart->value, 0, byteLength);
    return true;
}

#endif //INITIAL_H
