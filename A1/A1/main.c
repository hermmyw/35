//
//  main.c
//  A1
//
//  Created by Huimin Wang on 4/5/18.
//  Copyright © 2018 Huimin Wang. All rights reserved.
//

#include <stdio.h>
#include <limits.h>
typedef unsigned packed_t;
int xbyte(packed_t word, int bytenum)
{
    bytenum = 3 - bytenum;
    int temp = word << (bytenum << 3);
    int temp2 = temp >> 24;
    return temp2;
}

int
main (void)
{
    int x = -2;
    int y = 3;
    unsigned ux = (unsigned) x;
    unsigned uy = (unsigned) y;
    unsigned m = (x<y) == (-x>-y);
    unsigned n = ((x+y) << 4) + y - x == 17*y + 15*x;
    unsigned p = ~x+~y+1 == ~(x+y);
    int a = ux - uy;
    int b = -(unsigned)(y-x);
    unsigned q = (ux - uy) == -(unsigned)(y-x);
    int c = (x >> 2) << 2;
    unsigned s = ((x >> 2) << 2) <= x;
    printf("%d\n", m);
}
