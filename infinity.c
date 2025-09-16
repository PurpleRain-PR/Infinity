#include "infinity.h"
#include "initial.h"
#include "convert.h"

//test
#include <stdio.h>

inline bool isByteAddOverflow(unsigned char byte1, unsigned char byte2, bool hasCarriedBit)
//判断两个字节相加是否溢出（考虑上一位），用于计算同符号数相加时的进位
{
    //1字节内可表示的数中 255是最大的无符号数
    //直接加可能会溢出，所以用一次减法，用差来判断
    //又因为被减数是255（全1），可以等效为按位取反，提升效率
    return hasCarriedBit ?
    (unsigned char)~byte1 <= byte2 :
    (unsigned char)~byte1 < byte2;//如果取反后不做强制类型转换，会导致问题
}//逻辑过于简单，但还是打包一下，在宏和内联函数之间选了函数



//test
void test(void)
{
    puts("### Infinity TEST ###\n");

    char a = 0b11001010;
    PByte b = (PByte)&a;
    printf("%u %u %u %u %u %u %u %u\n", b->_1, b->_2, b->_3, b->_4, b->_5, b->_6, b->_7, b->_8);

    while (1);
}