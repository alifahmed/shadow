#include <stdlib.h>
#include <stdio.h>

#define N  100000
#define ITER	3

static int a[N];

int main(int argc, const char** argv) {
	for(int j = 0; j < N; j++){
		a[j] = rand();
	}

	long sum = 0;
	for(int i = 0; i < ITER; i++){
		for(int j = 0; j < N; j++){
			sum += a[j];
		}
	}

	printf("%ld\n", sum);
	return 0;
}
