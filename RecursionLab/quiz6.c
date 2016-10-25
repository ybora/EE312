#include <stdlib.h>
#include <stdio.h>


int main(void) {
	int x[] = {1, 2, 3, 3};
	printf("%d\n", sorted(x, 4));
}

int sorted(int x[], int n) {
	if (isAllSame(x, n) == 1) {
		return 0;
	} else {
		return helperSorted(x, n, 999);
	}
}

int helperSorted(int x[], int n, int last) {
	if (n == 2) {
		if (x[0] >= x[1] && last == 1) {
			return 1;
		} else if (x[0] >= x[1] && last != 1) {
			return -99;
		} else if (x[0] <= x[1] && last == -1) {
			return -1;
		} else if (x[0] <= x[1] && last != 1) {
			return -99;
		}
	}
	if (last != 999) {
		if (x[0] <= x[1] && last == -1) {
			return helperSorted(x + 1, n - 1, -1);
		} else if (x[0] <= x[1] && last != -1) {
			return -99;
		} else if (x[0] >= x[1] && last == 1) {
			return helperSorted(x + 1, n - 1, 1);
		} else if (x[0] >= x[1] && last != 1) {
			return -99;
		}
	} else {
		if (x[0] <= x[1]) {
			return helperSorted(x + 1, n - 1, -1);
		} else if (x[0] >= x[1]) {
			return helperSorted(x + 1, n - 1, 1);
		}

	}

}

int isAllSame(int x[], int n) {
	if (n == 2) {
		if (x[0] == x[1])
			return 1;
		else 
			return 0;
	}
	if (x[0] == x[1])
		return isAllSame(x + 1, n - 1);
	else 
		return 0;
}
