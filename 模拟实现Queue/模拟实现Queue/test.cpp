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
//适配器是一种容器转换为另一种容器的设计方法，本质上是一种转换
//stack：可以用list,vector,deque，默认用deque队列:尾插尾删时间复杂度o(1),增容代价较小，每次只需要开辟新的buffer，

//如果中控满载，只需要开辟一个更大的区域，把指针数组拷贝,不需要拷贝数据，也不会造成内存碎片
//queue：可以用list和deque，默认为deque，不能用vector实现，vector不提供pop_front接口
//规定接口：empty,size,front,pop_front,push_front
//priority_queue,可以用vector,deque，默认容器为vector,因为vector随机访问效率高，他底层的逻辑结构是堆，不能用list实现，
//在插入和删除的时候，不能通过随机访问的形式进行元素调整,每次pop，push之后都需要满足堆的性质：顺序表+堆的结构
//规定接口：push_back,pop_back,front,empty,size
//无法保证堆的性质
//push:push_back,向上调整shiftup(size-1)
//pop:swap(_con[0],_con[size-1]),_con.pop_back(),shiftdown(0)

//仿函数：可以像函数一样使用的对象，又称为仿函数对象，本质为重载运算符函数operator()(int x,int y)
//类型 a->a(x,y)->a.operator()(x,y)
//template<class T>
//适配器+仿函数：灵活配置，增强代码复用性

template<class T,class Container = vector<T>>
class PriorityQueue
{
public:
	void Push(const T& val)
	{
		//先把元素放到数组的最后一个位置
		_con.push_back(val);
		//向上调整，使其满足堆的性质
		shiftup(_con.size() - 1);
	}
	void shiftup(size_t child)
	{
		//和双亲结点比较大小
		size_t parent = (child - 1) / 2;
		while (child > 0)
		{
			if (_con[child] > _con[parent])
			{
				swap(_con[child], _con[parent]);
				//更新节点位置
				child = parent;
				parent = (child - 1) / 2;
			}
			else
			{
				//调整完毕
				break;
			}
		}
	}

	void shiftdown(size_t root)
	{
		size_t child = root * 2 + 1;
		//如果右孩子存在，且大于左孩子的值，取右孩子的值
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
			//堆的性质已经满足，结束调整
			break;
		}
	}

	void Pop()
	{
		//交换根元素和最后一个叶子结点
		swap(_con[0], _con[_con->size() - 1]);
		//删除最后一个元素
		_con.pop_back();
		//对根位置元素进行向下调整
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