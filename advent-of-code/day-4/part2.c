#include <stdio.h>
#include <string.h>

#define MAX_LINE_WIDTH 100						/* 100 counting the \n character */
#define TOTAL_NO_OF_FIELDS 8

int main() {
	char line[MAX_LINE_WIDTH + 1] = "";			/* +1 to account for the \000 character */
	char *part, fields[TOTAL_NO_OF_FIELDS][16];
	int no_of_fields = 0, total_valid = 0;

	FILE *fin;

	if ((fin = fopen("input.txt", "r")) == (FILE *) NULL) { fprintf(stderr, "File error"); return -1; }

	while (1) {
		char *res = fgets(line, sizeof(line), fin);

		if (res != NULL && res[0] != '\n') {
			char first_iteration = 1;

			while (part = strtok(first_iteration ? line : NULL, " ")) {
				first_iteration = 0;
				strcpy(fields[no_of_fields++], part);
			}
		} else {
			int i;
			char valid = 1, cid_is_present = 0;

			for (i = 0; i < no_of_fields; i++) {
				char *field = strtok(fields[i], ":");
				char *value = strtok(NULL, "\n");

				printf("%s: %-12s", field, value);

				if (!strcmp(field, "byr")) {
					int num = atoi(value);

					if (num >= 1920 && num <= 2002) {
						printf("✔");
					} else {
						printf("✗");
						valid = 0;
					}
				} else if (!strcmp(field, "iyr")) {
					int num = atoi(value);

					if (num >= 2010 && num <= 2020) {
						printf("✔");
					} else {
						printf("✗");
						valid = 0;
					}
				} else if (!strcmp(field, "eyr")) {
					int num = atoi(value);

					if (num >= 2020 && num <= 2030) {
						printf("✔");
					} else {
						printf("✗");
						valid = 0;
					}
				} else if (!strcmp(field, "hgt")) {
					char a = value[strlen(value)-2],
					     b = value[strlen(value)-1],
						 cm = (a == 'c' && b == 'm'),
						 in = (a == 'i' && b == 'n'),
						 vf = cm || in;

					if (vf) {
						int j, num;
						char temp[3] = "";

						for (j = 0; j < strlen(value) - 2; j++) {
							temp[j] = value[j];
						}

						num = atoi(temp);

						vf = (cm && num >= 150 && num <= 193) || (in && num >= 59 && num <= 76);
					}

					if (vf) {
						printf("✔");
					} else {
						printf("✗");
						valid = 0;
					}
				} else if (!strcmp(field, "hcl")) {
					char vf = value[0] == '#' && strlen(value) == 7;

					if (vf) {
						int j;
						for (j = 1; j < 6; j++) {
							if ((value[j] < '0' || value[j] > '9') && (value[j] < 'a' || value[j] > 'f')) {
								vf = 0;
								break;
							}
						}
					}

					if (vf) {
						printf("✔");
					} else {
						printf("✗");
						valid = 0;
					}
				} else if (!strcmp(field, "ecl")) {
					int j;
					char found = 0, *choices[7] = { "amb", "blu", "brn", "gry", "grn" ,"hzl", "oth" };

					for (j = 0; j < 7; j++) {
						if (!strcmp(value, choices[j])) {
							found = 1;
							break;
						}
					}

					if (found) {
						printf("✔");
					} else {
						printf("✗");
						valid = 0;
					}
				} else if (!strcmp(field, "pid")) {
					char vf = strlen(value) == 9;

					if (vf) {
						int j;
						for (j = 0; j < strlen(value); j++) {
							if (value[j] < '0' || value[j] > '9') {
								vf = 0;
								break;
							}
						}
					}

					if (vf) {
						printf("✔");
					} else {
						printf("✗");
						valid = 0;
					}
				} else if (!strcmp(field, "cid")) {
					cid_is_present = 1;
					printf("-");
				}

				printf("\n");
			}

			printf("----------------------------------\n");

			if (valid && (no_of_fields == TOTAL_NO_OF_FIELDS || (no_of_fields == (TOTAL_NO_OF_FIELDS - 1) && !cid_is_present))) {
				total_valid++;
				printf("✅");
			} else {
				printf("❌");
			}

			printf(" fields: %d cid: %s - valid: %d\n", no_of_fields, cid_is_present ? "yes" : "no", total_valid);

			printf("----------------------------------\n\n");

			/* memset(line, '\000', sizeof(line)); */
			no_of_fields = 0;
			cid_is_present = 0;

			if (res == NULL) break;
		}
	}

	printf("Total: %d\n\n", total_valid);

	fclose(fin);

	return 0;
}
