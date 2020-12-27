#include <stdio.h>
#include <string.h>

#define LINE_WIDTH 32						/* 32 counting the \n character */

int main() {
	int x, y, trees;
	char line[LINE_WIDTH + 1] = "";			/* +1 to account for the \000 character */

	FILE *fin;

	if ((fin = fopen("input.txt", "r")) == (FILE *) NULL) { fprintf(stderr, "File error"); return -1; }

	x = 0; y = 0;

	trees = 0;

	while (fgets(line, sizeof(line), fin)) {
		if (line[x] == '#') {
			line[x] = 'X';
			trees += 1;
		} else {
			line[x] = 'O';
		}

		printf("%s", line);

		x = (x + 3) % (LINE_WIDTH - 1);		/* -1 so we don't count the \n character */
		y += 1;
	}

	printf("----------\nCount: %d", trees);

	fclose(fin);

	return 0;
}
