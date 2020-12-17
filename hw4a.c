#include <stdio.h>
#include <string.h>
#include <math.h>

int main(int argc, char *argv[]) {
	int i, j, nos, nog;
	char *prev_arg = "", *in, *out;

	FILE *fin, *fout;
	char first_name[33], last_name[33];
	char max_first_name[33], max_last_name[33], min_first_name[33], min_last_name[33];
	float grade, avg, total_avg, sum, max, min;

	for (i = 1; i < argc; i++) {
		if (strcmp(prev_arg, "-in") == 0) {
			in = argv[i];
		} else if (strcmp(prev_arg, "-out") == 0) {
			out = argv[i];
		}

		prev_arg = argv[i];
	}

	fin = fopen(in, "r");
	fout = fopen(out, "w");

	if (fin == (FILE *) NULL || fout == (FILE *) NULL) return -1;

	fscanf(fin, "%d %d", &nos, &nog);

	max = -1;
	min = 11;

	total_avg = 0;

	for (i = 0; i < nos; i++) {				/* students */
		fscanf(fin, "%s %s", first_name, last_name);

		sum = 0;
		for (j = 0; j < nog; j++) {			/* grades */
			fscanf(fin, "%f", &grade);
			sum += grade;
		}

		avg = sum / nog;

		if (avg > max) {
			max = avg;
			strcpy(max_first_name, first_name);
			strcpy(max_last_name, last_name);
		}

		if (avg < min) {
			min = avg;
			strcpy(min_first_name, first_name);
			strcpy(min_last_name, last_name);
		}

		total_avg += avg / nos;

		fprintf(fout, "Name: %s %s avg %.2f\n", first_name, last_name, avg);
	}

	fclose(fin);

	fprintf(fout, "max: %s %s %.2f\n", max_first_name, max_last_name, max);
	fprintf(fout, "min: %s %s %.2f\n", min_first_name, min_last_name, min);
	fprintf(fout, "average: %.2f\n", total_avg);

	fclose(fout);

	return 0;
}
