#include <stdio.h>
#include <string.h>

int main() {
	char line[100 + 1] = "", *part1, *part2, *part3, *temp, ch;
	int pos1, pos2, valid;

	FILE *fin;

	if ((fin = fopen("input.txt", "r")) == (FILE *) NULL) return -1;

	valid = 0;

	while (fgets(line, sizeof(line), fin)) {
		printf("%s", line);

		part1 = strtok(line, " ");
		part2 = strtok(NULL, " ");
		part3 = strtok(NULL, " ");

		pos1 = atoi(strtok(part1, "-"));
		pos2 = atoi(strtok(NULL, "-"));

		temp = strtok(part2, ":"); ch = temp[0];

		if ((part3[pos1-1] == ch && part3[pos2-1] != ch) || (part3[pos1-1] != ch && part3[pos2-1] == ch)) {
			printf("✔");
			valid++;
		} else {
			printf("❌");
		}

		printf(" %c: %c %c\n", ch, part3[pos1-1], part3[pos2-1]);
	}

	printf("----------\nCount: %d", valid);

	fclose(fin);

	return 0;
}
