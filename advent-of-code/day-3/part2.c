#include <stdio.h>
#include <string.h>

#define LINE_WIDTH 32								/* 32 counting the \n character */

int traverse(FILE *fin, int right, int down, int output);

int main() {
	int i, r, d, t, slopes[5][2] = { {1, 1}, {3, 1}, {5, 1}, {7, 1}, {1, 2} };
	unsigned long p = 1;

	FILE *fin;

	if ((fin = fopen("input.txt", "r")) == (FILE *) NULL) { fprintf(stderr, "File error"); return -1; }

	for (i = 0; i < 5; i++) {
		r = slopes[i][0];
		d = slopes[i][1];
		t = traverse(fin, r, d, 0);

		printf("--------------\n");
		printf("Slope: → %d ↓ %d\n", r, d);
		printf("Trees: %7d\n", t);

		p *= t;
	}

	printf("\nProduct: %lu\n\n", p);

	fclose(fin);

	return 0;
}

int traverse(FILE *fin, int right, int down, int output) {
	int x = 0, y = 0, trees = 0;
	char line[LINE_WIDTH + 1] = "";					/* +1 to account for the \000 character */

	fseek(fin, 0, SEEK_SET);

	while (fgets(line, sizeof(line), fin)) {
		if (y % down == 0) {
			if (line[x] == '#') {
				if (output) line[x] = 'X';
				trees += 1;
			} else {
				if (output) line[x] = 'O';
			}

			x = (x + right) % (LINE_WIDTH - 1);		/* -1 so we don't count the \n character */
		}

		if (output) printf("%s", line);

		y += 1;
	}

	return trees;
}
