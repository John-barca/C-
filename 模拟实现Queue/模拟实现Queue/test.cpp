#include<iostream>
#include<deque>
#include<vector>
using namespace std;

template<class T,class Container=deque<T>>
class Queue {
public:
	void Push(const T& val)
	{
		_con.push_back(val);
	}
	void Pop()
	{
		_con.pop_front();
	}

	T& front()
	{
		return _con.front();
	}

	size_t size()
	{
		return _con.size();
	}
	bool empty()
	{
		return _con.empty();
	}
	T& Back()
	{
		return _con.back();
	}
private:
	Container _con;
};
//��������һ������ת��Ϊ��һ����������Ʒ�������������һ��ת��
//stack��������list,vector,deque��Ĭ����deque����:β��βɾʱ�临�Ӷ�o(1),���ݴ��۽�С��ÿ��ֻ��Ҫ�����µ�buffer��

//����п����أ�ֻ��Ҫ����һ����������򣬰�ָ�����鿽��,����Ҫ�������ݣ�Ҳ��������ڴ���Ƭ
//queue��������list��deque��Ĭ��Ϊdeque��������vectorʵ�֣�vector���ṩpop_front�ӿ�
//�涨�ӿڣ�empty,size,front,pop_front,push_front
//priority_queue,������vector,deque��Ĭ������Ϊvector,��Ϊvector�������Ч�ʸߣ����ײ���߼��ṹ�Ƕѣ�������listʵ�֣�
//�ڲ����ɾ����ʱ�򣬲���ͨ��������ʵ���ʽ����Ԫ�ص���,ÿ��pop��push֮����Ҫ����ѵ����ʣ�˳���+�ѵĽṹ
//�涨�ӿڣ�push_back,pop_back,front,empty,size
//�޷���֤�ѵ�����
//push:push_back,���ϵ���shiftup(size-1)
//pop:swap(_con[0],_con[size-1]),_con.pop_back(),shiftdown(0)

//�º�������������һ��ʹ�õĶ����ֳ�Ϊ�º������󣬱���Ϊ�������������operator()(int x,int y)
//���� a->a(x,y)->a.operator()(x,y)
//template<class T>
//������+�º�����������ã���ǿ���븴����

template<class T,class Container = vector<T>>
class PriorityQueue
{
public:
	void Push(const T& val)
	{
		//�Ȱ�Ԫ�طŵ���������һ��λ��
		_con.push_back(val);
		//���ϵ�����ʹ������ѵ�����
		shiftup(_con.size() - 1);
	}
	void shiftup(size_t child)
	{
		//��˫�׽��Ƚϴ�С
		size_t parent = (child - 1) / 2;
		while (child > 0)
		{
			if (_con[child] > _con[parent])
			{
				swap(_con[child], _con[parent]);
				//���½ڵ�λ��
				child = parent;
				parent = (child - 1) / 2;
			}
			else
			{
				//�������
				break;
			}
		}
	}

	void shiftdown(size_t root)
	{
		size_t child = root * 2 + 1;
		//����Һ��Ӵ��ڣ��Ҵ������ӵ�ֵ��ȡ�Һ��ӵ�ֵ
		if (child + 1 < _con.size() && _con[child + 1] > _con[child])
		{
			child++;
		}
		if (_con[child] > _con[root])
		{
			swap(_con[child], _con[root]);
			parent = child;

			child = 2 * root + 1;
		}
		else
		{
			//�ѵ������Ѿ����㣬��������
			break;
		}
	}

	void Pop()
	{
		//������Ԫ�غ����һ��Ҷ�ӽ��
		swap(_con[0], _con[_con->size() - 1]);
		//ɾ�����һ��Ԫ��
		_con.pop_back();
		//�Ը�λ��Ԫ�ؽ������µ���
		shiftdown(0);
	}
	T& top()
	{
		return _con[0];
	}
	bool Empty()
	{
		return _con.empty();
	}

	size_t size()
	{
		return _con.size();
	}


private:
	Container _con;
};

int main()
{
	PriorityQueue<int> q;
	q.Push(5);
	q.Push(4);
	q.Push(7);
	q.Push(9);
	for (auto& e : q)
	{

	}

}