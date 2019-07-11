#pragma once
//闭散列：线性探测
#include <iostream>
#include <vector>
using namespace std;

#if 0
enum STATE {
	EMPTY,
	DELETE,
	EXIST
};

template <class K, class V>
struct HashNode {
	pair<K, V> _kv;
	STATE _state = EMPTY;
};

template<class K, class V>
class HashTable {
public:
	typedef HashNode<K, V> Node;
	typedef Node* pNode;

	HashTable(size_t N = 5) {
		_table.resize(N); // []
		_size = 0;

	}

	bool insert(const pair<K, V>& kv)
	{
		CheckCapacity();//考虑增容
		//位置映射
		size_t index = kv.first % _table.size();
		while (_table[index]._state == EXIST) {
			//unordered_map/set不允许key重复
			if (_table[index]._kv.first == kv.first) {
				return false;
			}
			++index;
			if (index == _table.size()) {
				index = 0;
			}
		}
		_table[index]._kv = kv;
		_table[index]._state = EXIST;
		++_size;
		return true;
	}

	pNode Find(const K& key) {
		size_t index = key % _table.size();
		while (_table[index]._state != EMPTY) {
			if (_table[index]._state == EXIST && _table[index]._kv.first == key)
				return &_table[index];
			++index;
			if (index == _table.size()) {
				index = 0;
			}
		}

		return nullptr;
	}

	bool Erase(const K& key) {
		pNode ret = Find(key);
		if (ret) {
			ret->_state = DELETE;
			--_size;
			return true;
		}
		return false;
	}

	void CheckCapacity() {
		//_size / _table.size() 负载因子 -- > 减少哈希冲突
		//判断是否达到负载值
		if (_table.size() == 0 || _size * 10 / _table.size() >= 7) {
			size_t newC = _table.size() == 0 ? 10 : 2 * _table.size();
			HashTable<K, V> newHt(newC);
			for (int i = 0; i < _table.size(); i++) {
				if (_table[i]._state == EXIST) {
					newHt.insert(_table[i]._kv);
				}
			}
			_table.swap(newHt._table);
		}
	}



private:
	vector<Node> _table;
	size_t _size;
};

#endif

template<class V>
struct HashNode {
	HashNode<V>* _next;
	V _data;

	HashNode(const V& data)
		:_next(nullptr)
		, _data(data)
	{}
};


//前置声明
//解决依赖关系，private成员无法访问的问题
template<class K, class V, class KeyOfValue>
class HashTable;

template<class K,class V,class KeyOfValue>
struct _HIterator {
	typedef HashNode<V> Node;
	typedef Node* pNode;

	typedef _HIterator<K,V,KeyOfValue> Self;
	typedef HashTable<K, V, KeyOfValue> HashT;

	pNode _node;
	HashT* _ht;

	_HIterator(pNode node, HashT* ht)
		:_node(node)
		,_ht(ht)
	{}

	V& operator*() {
		return _node->_data;
	}

	V* operator->() {
		return &operator*();
	}

	bool operator!=(const Self& it) {
		return _node != it._node;
	}

	Self& operator++() {
		if (_node->_next) {
			_node = _node->_next;
		}
		else {
			//计算迭代器中节点在表中的索引
			KeyOfValue kov;
			size_t index = kov(_node->_data) % _ht->_table.size();
			++index;
			//向后搜索找到第一个非空链表得头结点，即为下一个元素的位置
			for (; index < _ht->_table.size(); ++index) {
				if (_ht->_table[index]) {
					_node = _ht->_table[index];
					break;
				}
			}
			//如果走到表尾，说明无有效元素
			if (index == _ht->_table.size()) {
				_node = nullptr;
			}
		}
		return *this;
	}



};

template<class K, class V, class KeyOfValue>
class HashTable {
public:
	typedef HashNode<V> Node;
	typedef Node* pNode;

	template<class K, class V, class KeyOfValue>
	friend struct _HIterator;

	typedef _HIterator<K, V, KeyOfValue> iterator;

	iterator begin() {
		//begin: 第一个非空链表得头结点
		for (size_t i = 0; i < _table.size(); ++i) {
			if (_table[i]) {
				return iterator(_table[i], this);
			}
		}
		//空表
		return iterator(nullptr, this);
	}

	iterator end() {
		return iterator(nullptr, this);
	}

	bool Insert(const V& data) {
		CheckCapacity();
		KeyOfValue kov;
		size_t index = kov(data) % _table.size();
		pNode cur = _table[index];
		while (cur) {
			if (kov(cur->_data) == kov(data))
				return false;
			cur = cur->_next;
		}
		cur = new Node(data);
		//头插
		cur->_next = _table[index];
		_table[index] = cur;

		++_size;
		return true;
	}

	void CheckCapacity() {
		if (_size == _table.size()) {
			size_t newC = _table.size() == 0 ? 1 : 2 * _table.size();
			vector<pNode> newTable;
			//新建一个表，旧表元素挂到新表当中
			newTable.resize(newC);
			KeyOfValue kov;
			//遍历旧表
			for (size_t i = 0; i < _table.size(); i++){
				pNode cur = _table[i];
				while (cur) {
					pNode next = cur->_next;
					//位置重新计算
					size_t index = kov(cur->_data) % newTable.size();
					//头插
					cur->_next = newTable[index];
					newTable[index] = cur;

					cur = next;
				}
				_table[i] = nullptr;
			}
			//旧表新表交换
			_table.swap(newTable);
		}
	}



private:
	vector<pNode> _table;
	size_t _size = 0;
};

