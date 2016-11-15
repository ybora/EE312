
#include <iostream>

bool isEqual(int x[], int n) {
    if (n == 1) return true;
    if (x[0] != x[1]) return false;
    return isEqual(x + 1, n - 1);
}

bool isUp(int x[], int n) {
    if (n == 1) return true;
    if (x[1] < x[0]) return false;
    return isUp(x + 1, n - 1);
}

bool isDown(int x[], int n) {
    if (n == 1) return true;
    if (x[1] > x[0]) return false;
    return isDown(x + 1, n - 1);
}


int sorted(int x[], int n) {
    if (isEqual(x, n)) return 0; 
    if (isUp(x, n)) return -1;
    if (isDown(x, n)) return 1;
    return -99;
}

bool sumsTo(int x[], int n, int k, int v) {
    if (k == 0 && v == 0) return true;
    if (v < 0) return false;
    if (n == 0) return false;
    return sumsTo(x + 1, n - 1, k - 1, v - x[0]) || sumsTo(x + 1, n - 1, k - 1, v);
}

int main() {
    using namespace std;
    int* x = new int[3];
    x[0] = 3;
    x[1] = 1;
    x[2] = 2;

    cout << sorted(x, 3) << endl;
}
