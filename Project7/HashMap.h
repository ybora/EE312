#include <iostream>
#include "LinkedListSet.h"
#include "String.h"

using namespace std;

namespace std {
	template <>
	struct hash<String> {
		public:
			int operator() (const String& s) const {
				const char* str = s.c_str();

				if (s.len == 0)
					return 0;
				if (s.len == 1) 
					return str[0] - 'a';
				return (str[0] - 'a' + 1) * (str[1] - 'a' + 1);
			}
	};
}

#define TABLE_SIZE 676

template <typename K, typename V> 
class HashMap {
	private:
		struct HashEntry {
			K key;
			V value;

			HashEntry() {
				key = K();
				value = V();
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
				table[k] = NULL;
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
