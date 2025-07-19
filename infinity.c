#include "infinity.h"
#include "initial.h"

//test
#include <stdio.h>

void test(void)
{
    printf("Infinity\n");
}

inline bool isByteAddOverflow(unsigned char byte1, unsigned char byte2, bool hasCarriedBit)
//判断两个字节相加是否溢出（考虑上一位），用于计算同符号数相加时的进位
{
    //1字节内可表示的数中 255是最大的无符号数
    //直接加可能会溢出，所以用一次减法，用差来判断
    //又因为被减数是255（全1），可以等效为按位取反，提升效率
    return hasCarriedBit ? ~byte1 <= byte2 : ~byte1 < byte2;
}



//test
