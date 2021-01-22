#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>


int main(){
	uint64_t sum1 = 0;
	uint64_t sum5 = 0;
	uint64_t sum2 = 0;
	uint64_t sum3 = 0;

block1:
	sum1++;
	static uint64_t out_1 = 0;
    out_1++;
    switch(out_1) {
    case 1 ... 5000000:
        goto block5;
    case 5000001 ... 8000000:
        goto block3;
	case 8000001 ... 10000000:
		goto block2;
    }


block5:
	sum5++;
	goto block1;


block3:
	sum3++;
	goto block1;


block2:
	sum2++;
	static uint64_t out_2 = 0;
	out_2++;
	if(out_2 >= 2000000){
		goto block0;
	}
	goto block1;

block0:

	printf("1:%lu  5:%lu  3:%lu  2:%lu\n", sum1, sum5, sum3, sum2);
	return 0;
}
