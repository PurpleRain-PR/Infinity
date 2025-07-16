#include <stdlib.h>
#include "infinity.h"

//test
#include <stdio.h>

void test(void)
{
    printf("Infinity\n");
}

bool initInfNum(const PInfNum num, const _InfNumType type, _InfNumSign sign){
    if(!type)return false;//类型错误
    num->info.type=type;
    num->info.sign=sign;
    num->info.intNodeAllocateCount=0;
    if(type&INF_INT){
        num->intPart=malloc(sizeof(InfInt));
        if (!num->intPart)return false;//无法分配内存
        num->intPart->firstDataNode=nullptr;
        num->intPart->nodeCount=0;
    }
    else{
        num->intPart=nullptr;
    }
    if(type&INF_FRACT){
        num->fractPart=malloc(sizeof(InfFract));
        if (!num->fractPart)return false;//无法分配内存
        num->fractPart->value=nullptr;
        num->fractPart->byteLength=0;
    }
    else{
        num->fractPart=nullptr;
    }
    return true;
}



//test

