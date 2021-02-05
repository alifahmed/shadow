#include <stdlib.h>
#include <stdio.h>

int b = 0;
int a = 0;

void pp(){
	static double x = 0.0;
	if (x >= 32.44424491326279281) {
		x -= 32.44424491326279281;
	}
	if(x < 31.41320132013201416) a++; //printf("A\n");
	else b++; //printf("B\n");
	x = x + 1.0;
	

}

int main(int argc, const char** argv) {
	int num = 0;
	scanf("%d", &num);
	for(int i = 0; i < num; i++){
		pp();
	}
	printf("a: %d\nb: %d\n", a, b);
	return 0;
}
