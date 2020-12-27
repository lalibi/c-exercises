#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define BOARDING_PASS_LENGTH 10

typedef struct node {
	char pass[11];

	int id;
	int row;
	int column;

	struct node *next;
} node_t;

node_t *add(node_t *root, char *pass, int id, int row, int column) {
	node_t *new, *t;

	new = malloc(sizeof(node_t));
	strcpy(new->pass, pass);
	new->id = id;
	new->row = row;
	new->column = column;

	if (root == NULL) {				/* Empty list */
		new->next = NULL;

		return new;
	}

	if (root->id > id) {	/* Insert at front */
		new->next = root;

		return new;
	}

	t = root;

	while (t->next != NULL) {
		if (t->next->id > id) {
			break;
		}

		t = t->next;
	}

	new->next = t->next;
	t->next = new;

	return root;
}

int main() {
	int max;
	char pass[BOARDING_PASS_LENGTH + 2] = "";			/* +2 to account for new line & the \000 character */
	node_t *root, *t, *p;
	FILE *fin;

	if ((fin = fopen("input.txt", "r")) == (FILE *) NULL) { fprintf(stderr, "File error"); return -1; }

	max = -1;
	root = NULL;
	while (fgets(pass, sizeof(pass), fin)) {
		int i, lower, upper, middle, row = 0, column = 0, id = 0;

		pass[BOARDING_PASS_LENGTH] = '\0'; /* Get rid of \n */

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
		root = add(root, pass, id, row, column);
	}

	printf("--------\n");
	printf("max: %d\n", max);

	fclose(fin);

	t = root;

	while (t != NULL) {
		printf("pass: %s | row: %3d | column: %d | seat id: %3d\n", t->pass, t->row, t->column, t->id);

		t = t->next;
	}

	t = root;

	while (t != NULL) {
		if (t->next != NULL && t->next->id - t->id == 2) {
			printf("\nFound my seat: %d!", t->id + 1);
		}

		t = t->next;
	}

	return 0;
}
