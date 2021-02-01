/*******************************************************************************
 *
 * File: neg_dom.c
 * Description: Negative dominator
 * 
 * Author:  Alif Ahmed
 * Email:   alifahmed@virginia.edu
 * Updated: Aug 06, 2019
 *
 ******************************************************************************/
#include <stdlib.h>
#include <stdio.h>

#define N  100000
#define ITER	2

static int a[N];

// initialize
void init(){
	for(int i = N - 1; i >= 0; i--){
		a[i] = rand();
	}
}

//sum
int getSum(const int* arr){
	int sum = 0;
	for(int i = N - 1; i >= 0; --i){
		sum += arr[i];
	}
	return sum;
}


int main(int argc, const char** argv) {
	for(int i = 0; i < ITER; i++){
		// initialize
		init();

		// print result
		printf("%d\n", getSum(a));
	}

	return 0;
}
