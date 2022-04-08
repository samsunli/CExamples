#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef unsigned char uint8_t;
typedef unsigned int uint;
/*
 * buf -  'read buffer' [h .. t)
 */
typedef struct buf {
	uint8_t * p;   // head of data
	uint8_t * e;   // tail of data

} buf_t;

int main(void) {
    uint8_t val2;
    buf_t bits;

    val2 = 10;
    bits.p = &val2;
    bits.e = bits.p + 1;//如果是uint8，加一后就是指向一个未定义的地址
    //bits.e = bits.p+ sizeof(val2);
    
    printf("bit p: %d, e: %d, %d \n", *bits.p, *bits.e, sizeof(val2));
        printf("bit p: %d, e: %d, %d \n", bits.p, bits.e, sizeof(val2));
}

