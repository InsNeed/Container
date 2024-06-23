#pragma once
#include <iostream>
#include "List.h"

template <typename T>
class Queue : public List<T>
{
public:
	void enqueue(T const& e) {List<T>::insertAsLast(e); }
	T dequeue() { return List<T>::remove(this->first()); }
	T& front() { return List<T>::first()->data; };
};

//���жര���Ŷ�

namespace queueUse {
	struct Customer { int window; unsigned int time; };//���ں�ʱ��


	//ѡ�������ٴ���
	static int bestWindow(Queue<Customer> windows[], int nWin) {
		int minSize = windows[0].sizeOfList(), optiWin = 0;
		for (int i = 1; i < nWin; i++)
			if (minSize > windows[i].sizeOfList())
			{
				minSize = windows[i].sizeOfList(); optiWin = i;
			}
		return optiWin;
	}

	static void simulate(int nWin, int servTime,int avTime) {
		Queue<Customer>* windows = new Queue<Customer>[nWin];//n�����ڶ���
		int total = 0;int leave = 0;
		for (int now = 0; now < servTime; now++) {
			if (rand() % (1 + nWin)) {//�¹˿��Ըø��ʵ���
				Customer c; c.time = /*1 +*/ rand() % avTime*2;//����ʱ��[1,9]
				c.window = bestWindow(windows, nWin);
				windows[c.window].enqueue(c);
				std::cout << "�¹˿ͽ���" << c.window << "����" << '\n';
				total++;
			}

			for (int i = 0; i < nWin; i++) //ÿ������
				if (!windows[i].empty())//�ǿմ��ڵȴ�ʱ��-
				{
					std::cout << i << "��������" << windows[i].sizeOfList() << '\n';
					if (--windows[i].front().time <= 0) {
						windows[i].dequeue();
						std::cout << "�˿ʹ�" << i << "�����뿪" << '\n';
						leave++;
					}
				}
		}
		std::cout << "����--------------------" <<"������ "<<total \
			<< "�뿪���� " << leave << '\n';
		delete[] windows;//ͬʱ~List()�����ÿ������
	}
}
