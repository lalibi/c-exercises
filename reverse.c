#include <stdio.h>
#include <string.h>

#define N 100

void inversion(char *s) {
	int i;

	for (i = strlen(s) - 1; i >= 0; --i) {
		printf("%c", s[i]);
	}
	printf("\n");
}

int main(void) {
	char s[N];

	printf("Please enter a word up to %d characters long: ", N);
	scanf("%s", s);
	inversion(s);

	return 0;
}
