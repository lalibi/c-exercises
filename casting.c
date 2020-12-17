#include <stdio.h>

int main() {
	char c = "B", *pc = &c;
	int *ip;

	ip = (int *)pc;

	printf("%d", *ip);

	return 0;
}
