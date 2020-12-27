#include <stdio.h>
#include <string.h>
#include <math.h>

#define BOARDING_PASS_LENGTH 10


int main() {
	int max = -1;
	char pass[BOARDING_PASS_LENGTH + 2] = "";			/* +2 to account for new line & the \000 character */

	FILE *fin;

	if ((fin = fopen("input.txt", "r")) == (FILE *) NULL) { fprintf(stderr, "File error"); return -1; }

	while (fgets(pass, sizeof(pass), fin)) {
		int i, lower, upper, middle, row, column, id;

		/*
		 * Row
		 * --- */

		lower = 0;
		upper = 127;

		for (i = 0; i < 7; i++) {
			middle = floor((lower + upper) / 2);

			switch (pass[i]) {
				case 'F':
					upper = middle;
					break;
				case 'B':
					lower = middle + 1;
					break;
			}
		}

		if (lower != upper) {
			fprintf(stderr, "Some's wrong!");
			return -1;
		}

		row = lower;

		/*
		 * Column
		 * ------ */

		lower = 0;
		upper = 7;

		for (i = 7; i < 10; i++) {
			middle = floor((lower + upper) / 2);

			switch (pass[i]) {
				case 'L':
					upper = middle;
					break;
				case 'R':
					lower = middle + 1;
					break;
			}
		}

		if (lower != upper) {
			fprintf(stderr, "Some's wrong!");
			return -1;
		}

		column = lower;

		id = row * 8 + column;
		max = id > max ? id : max;

		printf("row: %3d | column: %d | seat id: %3d\n", row, column, id);
	}

	printf("--------\n");
	printf("max: %d\n", max);

	fclose(fin);

	return 0;
}
