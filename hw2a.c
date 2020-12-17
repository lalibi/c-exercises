#include <stdio.h>

/* Function declaration */
int abs(int x);

int main() {
	int x;

	scanf("%d", &x);

	printf("The absolute value is %d\n", abs(x));

	return 0;
}

int abs(int x) {
	if (x > 0) {
		return x;
	} else {
		return -x;
	}
}
