#include <stdio.h>

int main() {
	int x = 0;
	for (int i = 0; i < 10; i++) {
		// I JUST WANT THIS TO INCREMENT x A FEW TIMES!!!!!!!!!!!!11
		// ARG!!!!!!!!! WHY WON'T IT WORK???????/
		x += i;
	}

	if (x) {
		printf("YES!!!!!\n");
		return 0;
	} else {
		printf("Wha?!? x == 0?!?! Why is x == 0?!?!\n");
		return 1;
	}
}