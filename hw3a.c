#include <stdio.h>

int determinant(int a[10][10]/* **a */, int n) {
	int j, k, l, s = 1, ret = 0;
	switch (n) {
		case 2:
			return a[0][0]*a[1][1] - a[0][1]*a[1][0];
		default:
			for (j = 0; j < n; j++) {
				int m = 0, b[10][10];

				for (k = 1; k < n; k++) {
					for (l = 0; l < n; l++) {
						if (l == j) continue;
						b[m/(n-1)][m%(n-1)] = a[k][l];
						m++;
					}
				}

				ret += s * a[0][j] * determinant(b, n-1);
				s *= -1;
			}
			return ret;
	}
}

int main() {
	int n;
	int i, j, a[10][10];

	while (1) {
		scanf("%d", &n);
		if (n >= 2 && n <= 10) break;
		printf("Bad input\n");
	}

	/* int a[n][n];

	a = malloc(n * sizeof *a);
	for (i = 0; i < n; i++)
	{
		a[i] = malloc(n * sizeof *a[i]);
	} */

	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			while (1) {
				scanf("%d", &a[i][j]);
				if (a[i][j] >= -9 && a[i][j] <= 9) break;
				printf("Bad input\n");
			}
		}
	}

	printf("%d", determinant(a, n));

	return 0;
}
