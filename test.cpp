

#include <iostream>
using namespace std;

class bar {
    public:
        int blah;
        
        bar() {
            cout << "basic ocnstructor" << endl;
            blah = 0;
        }

        bar(int x) {
            blah = x;
            cout << "int constructor" << endl;
        }

        bar(bar& b) {
            cout << "copy constructor" << endl;
        }

        ~bar() {
            cout << "destructor for "<< this->blah << endl;
        }
        void foo(const int x) const {
            cout << "the value of x is: " << x << endl;
        }

        static void lol() {
            cout << "this is a static method" << endl;
        }
};

char* rindex(char str[], char val) {
    if (str[0] == 0) return NULL;

}

int main() {
    bar f;
    f.~bar();
   
}


