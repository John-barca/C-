#include <vector>
#include <iostream>
#include <string>
using namespace std;

class bitset {
public:
	bitset(size_t range) {
		_bits.resize((range >> 5) + 1);
	}

	//把x对应的位设为1，表示存在
	void Set(size_t x) {
		size_t index = x >> 5;
		size_t bitNum = x % 32;
		_bits[index] |= (1 << bitNum);
	}

	//把x对应的位设为0，表示不存在
	void ReSet(size_t x) {
		size_t index = x >> 5;
		size_t bitNum = x % 32;
		_bits[index] &= (~(1 << bitNum));
	}

	//判断x对应的位是否为1
	bool Test(size_t x) {
		size_t index = x >> 5;
		size_t bitNum = x % 32;
		return _bits[index] & (1 << bitNum);
	}

private:
	vector<int> _bits;
};

template<class K, class HashFun1, class HashFun2, class HashFun3>
class BloomFilter {
public: 
	BloomFilter(size_t range) :bs(range), _bitcount(range){}

	void Set(const K& key) {
		size_t index1 = HashFun1()(key) % _bitcount;
		size_t index2 = HashFun2()(key) % _bitcount;
		size_t index3 = HashFun3()(key) % _bitcount;
		bs.Set(index1);
		bs.Set(index2);
		bs.Set(index3);
	}

	bool Test(const K& key) {
		size_t index1 = HashFun1()(key) % _bitcount;
		if (!bs.Test(index1))
			return false;
		size_t index2 = HashFun2()(key) % _bitcount;
		if (!bs.Test(index2))
			return false;
		size_t index3 = HashFun3()(key) % _bitcount;
		if (!bs.Test(index3))
			return false;

		return true;//误判
	}

private:
	bitset bs;
	size_t _bitcount;
};

struct HF1 {
	size_t operator()(const string& str) {
		size_t hash = 0;
		for (const auto& e : str) {
			hash = hash * 131 + e;
		}
		return hash;
	}
};

struct HF2 {
	size_t operator()(const string& str) {
		size_t hash = 0;
		for (const auto& e : str) {
			hash = hash * 65599 + e;
		}
		return hash;
	}
};

struct HF3 {
	size_t operator()(const string& str) {
		size_t hash = 0;
		size_t magic = 63689;
		for (const auto& e : str) {
			hash = hash * magic + e;
			magic *= 378551;
		}
		return hash;
	}
};

void testbloom() {
	BloomFilter<string, HF1, HF2, HF3> bf(100);
	string http1 = "https://www.baidu.com";
	string http2 = "https://www.baidu.com";
	string http3 = "https://www.baidu.com";
	string http4 = "https://www.baidu.com";

}