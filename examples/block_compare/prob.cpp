#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>


int main(){
	uint64_t hash = 0xC32ED012FEA8B4D3ULL;
	uint64_t sum1 = 0;
	uint64_t sum5 = 0;
	uint64_t sum2 = 0;
	uint64_t sum3 = 0;
	uint64_t tmpRnd;

block1:
	sum1++;

	static uint64_t out_1_5 = 5000000;
    static uint64_t out_1_3 = 3000000;
	static uint64_t out_1_2 = 1999998;
    tmpRnd = out_1_5 + out_1_3 + out_1_2;
    if (tmpRnd) {
        hash = (hash  << 1) ^ (((int64_t)hash < 0) ? 7 : 0);
        tmpRnd = hash % tmpRnd;
        if (tmpRnd < (out_1_5)){
            out_1_5--;
            goto block5;
        }
		else if (tmpRnd < (out_1_5 + out_1_3)){
            out_1_3--;
            goto block3;
        }
        else {
            out_1_2--;
            goto block2;
        }
    }
    goto block2;


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
