#include <stdio.h>

int main() {
	int n;
	int w = 2*(n-1) + 1;
	int i, j;

	while (1) {
		scanf("%d", &n);
		if (n >= 4 && n <= 20) break;
		printf("Bad input\n");
	}

	for (i = 0; i < n-1; i++) {
		int noa = 2*i + 1;
		int pad = n - 2 - i;

		for (j = 0; j < pad; j++) {
			printf(" ");
		}

		for (j = 0; j < noa; j++) {
			printf("*");
		}

		printf("\n");
	}

	for (j = 0; j < n-2; j++) {
		printf(" ");
	}

	printf("*\n");

	return 0;
}
