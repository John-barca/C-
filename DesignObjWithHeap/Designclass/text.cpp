#include <iostream>
using namespace std;

//防拷贝实现,只能在堆上创建对象
class HeapType
{
public:
	static HeapType* GetHeapObj()
	{
		return new HeapType;
	}
private:
	HeapType()
	{}
	HeapType(const HeapType& ht);//1.只声明不实现 2.声明成私有，因为成公有，在外部可能突破限制
	//or HeapType(const HeapType& ht) = delete;不让该函数实现(在语法上让函数没有任何实现的可能性
};

int main()
{
	HeapType* p1 = HeapType::GetHeapObj();

	return 0;
}


