#include <iostream>
using namespace std;

//������ʵ��,ֻ���ڶ��ϴ�������
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
	HeapType(const HeapType& ht);//1.ֻ������ʵ�� 2.������˽�У���Ϊ�ɹ��У����ⲿ����ͻ������
	//or HeapType(const HeapType& ht) = delete;���øú���ʵ��(���﷨���ú���û���κ�ʵ�ֵĿ�����
};

int main()
{
	HeapType* p1 = HeapType::GetHeapObj();

	return 0;
}


