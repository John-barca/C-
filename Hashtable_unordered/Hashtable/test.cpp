#include "UnorderedMapSet.h"
using namespace std;
#if 0
void TestHash() {
	HashTable<int, int> ht;
	ht.insert(make_pair(1, 1));
	ht.insert(make_pair(2, 2));
	ht.insert(make_pair(3, 3));
	ht.insert(make_pair(4, 4));
	ht.insert(make_pair(5, 5));
	ht.insert(make_pair(6, 6));

}

int main() {
	TestHash();
	return 0;
}
#endif

void TestUnordered() {
	UnorderedMap<int, int> uMap;
	UnorderedSet<int> uSet;

	uMap.Insert(make_pair(4, 0));
	uMap.Insert(make_pair(8, 1));
	uMap.Insert(make_pair(16, 2));

	UnorderedMap<int, int>::iterator uit = uMap.begin();
	while (uit != uMap.end()) {
		cout << uit->first << "--->" << uit->second << endl;
		++uit;
	}

	cout << "Uset:" << endl;
	uSet.Insert(0);
	uSet.Insert(1);
	uSet.Insert(2);

	UnorderedSet<int>::iterator sit = uSet.begin();
	while (sit != uSet.end()) {
		cout << *sit << endl;
		++sit;
	}

}

int main() {
	TestUnordered();
	system("pause");
	return 0;
}