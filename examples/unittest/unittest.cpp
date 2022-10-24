#include <iostream>

using namespace std;

const int PAGE_SIZE = 0x1000;
const int PAGE_MAX = 0x5000;
const int LINE_SIZE = 0x40;

void test()
{
	int *arr = (int *) aligned_alloc(LINE_SIZE, PAGE_SIZE * PAGE_MAX);
	int INTNUM_TOTAL = PAGE_SIZE * PAGE_MAX / sizeof(int);
	for (int i = 0; i < 1000000; ++i) {
		if (i % 2 == 0) {
			arr[i] = i; 
		}
	}
}


int main()
{
	test();
	return 0;
}