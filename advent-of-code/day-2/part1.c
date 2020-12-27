#include <stdio.h>
#include <string.h>

int main() {
	char line[100 + 1] = "", *part1, *part2, *part3, *l, *u, *temp, ch;
	int lo, up, i, valid, occurances;

	FILE *fin;

	if ((fin = fopen("input.txt", "r")) == (FILE *) NULL) return -1;

	valid = 0;

	while (fgets(line, sizeof(line), fin)) {
		part1 = strtok(line, " ");
		part2 = strtok(NULL, " ");
		part3 = strtok(NULL, " ");

		l = strtok(part1, "-");
		u = strtok(NULL, "-");

		lo = atoi(l);
		up = atoi(u);

		temp = strtok(part2, ":"); ch = temp[0];

		occurances = 0;
		for (i = 0; i < strlen(part3); i++) {
			if (part3[i] == ch) occurances++;
		}

		if (occurances >= lo && occurances <= up) valid++;
	}

	printf("%d", valid);

	fclose(fin);

	return 0;
}
