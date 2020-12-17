#include <stdio.h>

int EKP(int a, int b);

void sol(int ak1, int ar1, int pa1, int ak2, int ar2, int pa2, char pr);

int main() {
	int ak1, ar1, pa1, ak2, ar2, pa2;
	char pr;

	scanf("%d %d %d %d %d %d %c", &ak1, &ar1, &pa1, &ak2, &ar2, &pa2, &pr);
	sol(ak1, ar1, pa1, ak2, ar2, pa2, pr);

	return 0;
}

void sol(int ak1, int ar1, int pa1, int ak2, int ar2, int pa2, char pr) {
	int n1, n2, n3, kar, kpa;

	int klar1 = ak1 * pa1 + ar1;
	int klpa1 = pa1;
	int klar2 = ak2 * pa2 + ar2;
	int klpa2 = pa2;

	int ekp = EKP(klpa1, klpa2);

	switch (pr)
	{
		case '*':
			kar = klar1 * klar2;
			kpa = klpa2 * klpa1;
			break;

		case '/':
			kar = klar1 * klpa2;
			kpa = klpa1 * klar2;
			break;

		case '+':
			kar = klar1 * (ekp/klpa1) + klar2 * (ekp/klpa2);
			kpa = ekp;
			break;

		case '-':
			kar = klar1 * (ekp/klpa1) - klar2 * (ekp/klpa2);
			kpa = ekp;
			break;
	}

	/* TODO */
	n1 = kar/kpa;
	n2 = kar - (n1 * kpa);
	n3 = kpa;

	printf("%d %d %d", n1, n2, n3);
}

int EKP(int a, int b) {
	int i, t;

	/* return a * b; */

	if (a < b) {
		t = a;
		a = b;
		b = t;
	}

	for (i = 1; i <= b; i++) {
		if (a * i % b == 0) {
			return a * i;
		}
	}
}
