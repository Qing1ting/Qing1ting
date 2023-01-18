#include <iostream>
#include <thread>
#include <mutex>

#include "MyThreadTest.h"

using namespace std;
mutex mutex1;
//单例模式：只能创建一个实例对象。把构造函数私有化就不能再类外创建对象了。
//构造对象可以创建一个静态类类型的成员变量，用来接收唯一的类对象
//创建一个成员函数，判断静态对象是否为空，为空就new一个对象给静态对象赋值。返回静态变量
class MySingle {
private:
	//将构造函数私有化
	MySingle(){}
	MySingle(MySingle &mysingle){}
/**************************************************/

public:
	//回收资源可以创建另一个类进行回收
	class ClernMySingle
	{
	public:
		~ClernMySingle() {
			if (MySingle::m_initiObj)
			{
				delete MySingle::m_initiObj;
				MySingle::m_initiObj = nullptr;
			}
		}
	};
/**************************************************/
public:
	//静态对象指针，保存唯一的对象
	static MySingle *m_initiObj;
	//用于创建对象，返回唯一对象
	static MySingle *GetObject() {
		//先判断对象是否为空
		if (m_initiObj==nullptr)
		{
			//多线程进时行加锁
			std::unique_lock<std::mutex> uniquelock(mutex1);
			//判断静态成员对象是否为空，为空就new一个
			if (m_initiObj == nullptr)
			{
				m_initiObj = new MySingle;
				//类中套类用于析构对象，只是一种参考写法
				static ClernMySingle desturc;
			}
		}
		
		return m_initiObj;
	}
};
//静态对象初始化
MySingle* MySingle::m_initiObj = nullptr;

int main() {
	MySingle *mysingle = MySingle::GetObject();
	MySingle *mysingle1 = MySingle::GetObject();
	MySingle *mysingle2 = MySingle::GetObject();

	return 0;
}