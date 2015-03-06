#include <stdlib.h>
#include <stdio.h>

static int a = 'c';
static int arr[12] = {0};

struct greetings {
	int hello;
	char goodbye;
};

struct greetings r;

void minifunc()
{
	int a;
	int b;
	return minifunc();
}

int main(int argc, char** argv);
char other_function();
void function_with_numerous_args(int a, char b, struct greetings* c, int* d,
		unsigned long long int e, char f, char* g, int h);

int main(int argc, char** argv)
{
	int b = a;
	int* c = &b;
	int i;
	if (i == b)
	{
	}
	else
	{
	}

	arr[8] = 9+(6 & a);
	for (i = b>a?-b:*c, b = 0 ; i < 10 ; ++i) {
		r.hello = i;
		printf("coucou %i %i\n", b, a);
		printf("coucou %i %i\n", a, b);
	}
	{
		int t = 0;
		b = i+arr[7] -t;
	}
	return 0;
}


void function_with_numerous_args(int a, char b, struct greetings* c, int* d,
		unsigned long long int e, char f, char* g, int h)
{
	struct greetings hi = {
		.hello = b,
		.goodbye = *g
	};
	if (hi.hello + c->hello == *d)
		(*d)++;
	g = c->goodbye ? c->goodbye + f : (char)(e++,h+e);
}

char other_function()
{
	while(1)
		for (;;)
			continue;

	char other_a = 'a';
	function_with_numerous_args(a,a,&r,&a,a,a,&other_a,a);

	return main(0,(char**)0);
}

void say_hello_and_check_if_equal(int s)
{
	//exit(1);
	printf("hello %i %i\n",s,a);
	struct greetings* ptr = &r;
	if (ptr->goodbye)
		return;

	switch (a * s) {
		case 0:
			printf("either a or s is null\n");
			break;
		case 1:
			printf("identity?\n");
			break;
		case 2:
			printf("parity?\n");
			break;
		default:
			other_function();
			return;
	}
	if (a && a == (s+3)) {
		printf("a is equal to 3\n");
		a = s+3;
	} else {
		printf("not equal\n");
	}

	return;
}

