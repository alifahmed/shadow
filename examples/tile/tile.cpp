#include <cstdio>
#include <cstdlib>

#define I	6
#define J	4
#define K	10000

int main(){
	int arr[K];
	for(int k = 0; k < K; k++){
		arr[k] = 2;
	}

	int sum = 0;
	for(int i = 0; i < I; i++){
		for(int j = 0; j < J; j++){
			for(int k = 0; k < K; k++){
				sum += arr[k];
			}
		}
	}

	printf("%d\n", sum);

	return 0;
}
