#include "infinity.h"

//test
#include <stdio.h>
void test(void)
{
    printf("Infinity\n");
}

bool initInfNum(const PInfNum num, const _InfNumType type){
    if(!type)return false;
    num->info.type=type;

    num->info.sign=INF_POSITIVE;
    num->info.intNodeAllocateCount=0;

    num->intPart->length=0;
    if(!(type&INF_INT)){
        num->intPart=nullptr;
    }
    if(!(type&INF_FRACT)){
        num->fractPart=nullptr;
    }
    return true;
}



//test

