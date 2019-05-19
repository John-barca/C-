#include <iostream>
#include <map>
#include <vector>
using namespace std;

class Solution {
public:
	vector<string> topKFrequent(vector<string>& words, int k) {
		map<string, int> CountMap;
		vector<string> v;
		for (const auto& e : words)
			++CountMap[e];
		multimap<int, string, greater<int>> FrequentMap;
		for (const auto& e : CountMap)
		{
			FrequentMap.insert(make_pair(e.second, e.first));
		}
		for (const auto& e : FrequentMap)
		{
			if (k-- > 0)
				v.push_back(e.second);
			else
				break;
		}
		return v;
	}
};