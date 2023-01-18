#include <iostream>
#include <thread>
#include <mutex>

#include "MyThreadTest.h"

using namespace std;
mutex mutex1;
//����ģʽ��ֻ�ܴ���һ��ʵ�����󡣰ѹ��캯��˽�л��Ͳ��������ⴴ�������ˡ�
//���������Դ���һ����̬�����͵ĳ�Ա��������������Ψһ�������
//����һ����Ա�������жϾ�̬�����Ƿ�Ϊ�գ�Ϊ�վ�newһ���������̬����ֵ�����ؾ�̬����
class MySingle {
private:
	//�����캯��˽�л�
	MySingle(){}
	MySingle(MySingle &mysingle){}
/**************************************************/

public:
	//������Դ���Դ�����һ������л���
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
	//��̬����ָ�룬����Ψһ�Ķ���
	static MySingle *m_initiObj;
	//���ڴ������󣬷���Ψһ����
	static MySingle *GetObject() {
		//���ж϶����Ƿ�Ϊ��
		if (m_initiObj==nullptr)
		{
			//���߳̽�ʱ�м���
			std::unique_lock<std::mutex> uniquelock(mutex1);
			//�жϾ�̬��Ա�����Ƿ�Ϊ�գ�Ϊ�վ�newһ��
			if (m_initiObj == nullptr)
			{
				m_initiObj = new MySingle;
				//��������������������ֻ��һ�ֲο�д��
				static ClernMySingle desturc;
			}
		}
		
		return m_initiObj;
	}
};
//��̬�����ʼ��
MySingle* MySingle::m_initiObj = nullptr;

int main() {
	MySingle *mysingle = MySingle::GetObject();
	MySingle *mysingle1 = MySingle::GetObject();
	MySingle *mysingle2 = MySingle::GetObject();

	return 0;
}