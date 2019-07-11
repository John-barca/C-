#include "Hash.h"

template<class K,class V>
class UnorderedMap {
	struct MapKeyOfValue {
		const K& operator()(const pair<K, V>& data) {
			return data.first;
		}
	};
public:
	typedef typename HashTable<K, pair<K, V>, MapKeyOfValue>::iterator iterator;

	bool Insert(const pair<K, V>& data) {
		return _ht.Insert(data);
	}

	iterator begin() {
		return _ht.begin();
	}

	iterator end() {
		return _ht.end();
	}
private:
	HashTable<K, pair<K, V>, MapKeyOfValue> _ht;
};

template<class K>
class UnorderedSet {
	struct SetKeyOfValue {
		const K& operator()(const K& data) {
			return data;
		}
	};
public:
	typedef typename HashTable<K, K, SetKeyOfValue>::iterator iterator;

	bool Insert(const K& data) {
		return _ht.Insert(data);
	}
	iterator begin() {
		return _ht.begin();
	}

	iterator end() {
		return _ht.end();
	}

private:
	HashTable<K, K, SetKeyOfValue> _ht;
};