#include <stdio.h>

int main(void){
	int x = 0;
	int i;
	for(i = 0;i<10000;i++){
		x = x + i;
		// compare the time before and after commenting the following line
		printf("x=%d\n",x);
	}
	return 0;
}