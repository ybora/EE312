#include <iostream>
#include "LinkedListSet.h"
#include "String.h"

#define A 54059 /* a prime */
#define B 76963 /* another prime */
#define START 37 /* also prime */

using namespace std;

namespace std {
	template <>
	struct hash<String> {
		public:
			int operator() (const String& s) const {
				int h = START;
				const char* str = s.c_str();

			    while (*str) {
			      h = (h * A) ^ (str[0] * B);
			      str++;
			    }
			    return h; 
			}
	};
}

#define TABLE_SIZE 128

template <typename K, typename V> 
class HashMap {
	private:
		struct HashEntry {
			K key;
			V value;

			HashEntry() {
				key = NULL;
				value = NULL;
			}

			HashEntry(K key, V value) {
				this->key = key;
				this->value = value;
			}

			bool operator==(HashEntry that) const {
				if (this->key == that.key) return true;
				return false;
			}

			bool operator<(HashEntry that) const {
				if (this->key < that.key) return true;
				return false;
			}
		};
		hash<K> hashFunction;
	public:
		// An array of pointers to LinkedLists of HashEntries
		LinkedListSet<HashEntry>** table;

		HashMap() {
			table = new LinkedListSet<HashEntry>* [TABLE_SIZE];

			for (int k = 0; k < TABLE_SIZE; k++) {
				table[k] = new LinkedListSet<HashEntry>();
			}
		}

		~HashMap() {
			for (int k = 0; k < TABLE_SIZE; k++) {
				delete table[k];
			}
			delete table;
		}

		void put(K key, V value) {
			int hashValue = hashFunction(key) % TABLE_SIZE;
			LinkedListSet<HashEntry>* hashEntries = table[hashValue];
			hashEntries->insert_element(HashEntry(key, value));
		}

		V get(K key) {
			int hashValue = hashFunction(key) % TABLE_SIZE;
			LinkedListSet<HashEntry>* hashEntries = table[hashValue];
			HashEntry* foundEntry = hashEntries->find_element(HashEntry(key, 0));
			if (foundEntry != NULL)
				return foundEntry->value;
			return NULL;
		}
};









