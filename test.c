#include <stdlib.h>
#include <stdio.h>

static int a = 'c';
int main(int argc, char** argv);
void other_function();
void say_hello_and_die_maybe(int s);

int main(int argc, char** argv)
{
	int b = a;
	int i;
	for (i = b>a?-b:b ; i < 10 ; ++i) {
		printf("coucou %i %i\n", b, a);
		printf("coucou %i %i\n", a, b);
	}
	{
		int t = 0;
		b = i+a -t;
	}
	return 0;
}

void other_function()
{
	a;
}

void say_hello_and_check_if_equal(int s)
{
	exit(1);
	printf("hello %i %i\n",s,a);
	if (a == s)
		printf("equal\n");	
}

