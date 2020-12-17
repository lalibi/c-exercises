#include <stdio.h>

void minmax(int a, int b, int c, int *min, int *max) {
	*min = a;

	if (b < *min) *min = b;
	if (c < *min) *min = c;

	*max = a;

	if (b > *max) *max = b;
	if (c > *max) *max = c;
}

int main() {
	int a, b, c, min, max;

	scanf("%d %d %d", &a, &b, &c);

	minmax(a, b, c, &min, &max);

	printf("%d %d", min, max);
}

