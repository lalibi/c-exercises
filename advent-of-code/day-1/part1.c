#include <stdio.h>

int main() {
	int x1, x2, b;

	FILE *f1, *f2;

	if ((f1 = fopen("input.txt", "r")) == (FILE *) NULL) { printf("File error"); return -1; }
	if ((f2 = fopen("input.txt", "r")) == (FILE *) NULL) { printf("File error"); return -1; }

	while (!feof(f1)) {
		fscanf(f1, "%d", &x1);

		fseek(f2, 0, SEEK_SET);

		if (f2 == (FILE *) NULL) return -1;

		b = 0;
		while (!feof(f2)) {
			fscanf(f2, "%d", &x2);

			if (x1 + x2 == 2020) {
				printf("%d %d %d %d\n", x1, x2, x1 + x2, x1 * x2);
				b = 1;
				break;
			}
		}

		if (b == 1) break;
	}

	fclose(f1);
	fclose(f2);

	return 0;
}
