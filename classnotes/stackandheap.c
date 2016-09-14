#include <stdio.h>

void exploreStack(int, double, int);

double multiplyByTwo(double input) {
	/* Pushed onto stack */
	double twice = input * 2;
	/* Removed from stack */
	return twice;
}

int main(void) {
	int age  = 0;
	double salary = 12345.67;
	double myList[3] = {1.2, 2.3, 3.4};

	exploreStack(100, 10.0, 200);
	return 0;
}

void exploreStack(int n, double m, int o) {
	int* pn = &n;
	double* pm = &m;
	int* po = &o;

	/* print out pointers on stack */
	printf("n is at \t%p, m is at \t%p, o is at \t%p\n", pn, pm, po);
	printf("n+! is at \t%p, m+1 is at \t%p, o+1 is at \t%p\n", pn+1, pm+1, po+1);

	char* c = (char*)pn;
	printf("c is at %p, c+1 is at %p\n", c, c+1);

}