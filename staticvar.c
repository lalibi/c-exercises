#include <stdio.h>

void f()
{
	static int static_var = 500;
	printf("%d\n", static_var);
	static_var++;
}

int main()
{
	f();
	f();
	f();
}
