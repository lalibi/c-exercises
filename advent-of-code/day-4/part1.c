#include <stdio.h>
#include <string.h>

#define MAX_LINE_WIDTH 100						/* 100 counting the \n character */

int main() {
	char line[MAX_LINE_WIDTH + 1] = "";			/* +1 to account for the \000 character */
	char *part, *t, *fields[8] = { "byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid", "cid" };
	int no_of_fields = 0, first_iteration , cid_is_present = 0, valid = 0;

	FILE *fin;

	if ((fin = fopen("input.txt", "r")) == (FILE *) NULL) { fprintf(stderr, "File error"); return -1; }

	while (1) {
		t = fgets(line, sizeof(line), fin);

		if (t == NULL || line[0] == '\n') {
			printf("--------------------------------\n");

			if (no_of_fields == 8 || (no_of_fields == 7 && !cid_is_present)) {
				valid++;
				printf("✔");
			} else {
				printf("❌");
			}

			printf(" fields: %d cid: %s - valid: %d\n\n", no_of_fields, cid_is_present ? "yes" : "no", valid);

		//	memset(line, '\000', sizeof(line));
			no_of_fields = 0;
			cid_is_present = 0;

			if (t == NULL) break;
			else continue;
		}

		first_iteration = 1;

		while (part = strtok(first_iteration ? line : NULL, " ")) {
			printf("%s\n", part);

			if (strstr(part, "cid:") != NULL) cid_is_present = 1;

			first_iteration = 0;
			no_of_fields++;
		}
	}

	printf("Total: %d", valid);

	fclose(fin);

	return 0;
}
