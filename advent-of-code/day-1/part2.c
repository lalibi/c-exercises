#include <stdio.h>

int main() {
	int x1, x2, x3, b = 0;
	FILE *f1, *f2, *f3;

	if ((f1 = fopen("input.txt", "r")) == (FILE *) NULL) { printf("File error"); return -1; }
	if ((f2 = fopen("input.txt", "r")) == (FILE *) NULL) { printf("File error"); return -1; }
	if ((f3 = fopen("input.txt", "r")) == (FILE *) NULL) { printf("File error"); return -1; }

	while (!feof(f1)) {
		fscanf(f1, "%d", &x1);

		fseek(f2, 0, SEEK_SET);

		while (!feof(f2)) {
			fscanf(f2, "%d", &x2);

			fseek(f3, 0, SEEK_SET);

			while (!feof(f3)) {
				fscanf(f3, "%d", &x3);

				if (x1 + x2 + x3 == 2020) {
					printf("%d %d %d %d %d\n", x1, x2, x3, x1 + x2 + x3, x1 * x2 * x3);
					b = 1;
					break;
				}
			}

			if (b == 1) break;
		}

		if (b == 1) break;
	}

	fclose(f1);
	fclose(f2);
	fclose(f3);

	return 0;
}
