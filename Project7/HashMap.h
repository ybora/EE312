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
				unsigned int hash = 7;

				for (int k = 0; k < s.size(); k++) {
					hash = hash * 31 + str[k];
				}
				return hash;
			}
	};
}

#define TABLE_SIZE 100

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

			HashEntry(const HashEntry& that) {
				this->key = that.key;
				this->value = that.value;
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
		int spotsOccupied;

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

		bool count(K key) {
			int hashValue = hashFunction(key) % TABLE_SIZE;
			if (hashValue < 0) hashValue *= -1;
 
			LinkedListSet<HashEntry>* hashEntries = table[hashValue];
			if (hashEntries == NULL) {
				return false;
			}
			return hashEntries->is_element(HashEntry(key, V()));
		}

		V& operator[](K key) {
			int hashValue = hashFunction(key) % TABLE_SIZE;
			if (hashValue < 0) hashValue *= -1;
			LinkedListSet<HashEntry>* hashEntries = table[hashValue];
			if (hashEntries == NULL) {
				spotsOccupied++;
				table[hashValue] = new LinkedListSet<HashEntry>();
			} 
			hashEntries = table[hashValue];
			hashEntries->insert_element(HashEntry(key, V()));
			return hashEntries->find_element(HashEntry(key, V())).value;

		}

		int getCount() {
			return spotsOccupied;
		}
};
