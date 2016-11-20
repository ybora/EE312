#include "HashMap.h"
#include "String.h"

using namespace std;
int main() {
	String k = "hello";
	int v = 2;
	HashMap<String, int> map;
	map.put(k, v);
	cout << map.get(k) << endl;
}