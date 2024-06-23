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

//银行多窗口排队

namespace queueUse {
	struct Customer { int window; unsigned int time; };//窗口和时间


	//选择人最少窗口
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
		Queue<Customer>* windows = new Queue<Customer>[nWin];//n个窗口队列
		int total = 0;int leave = 0;
		for (int now = 0; now < servTime; now++) {
			if (rand() % (1 + nWin)) {//新顾客以该概率到达
				Customer c; c.time = /*1 +*/ rand() % avTime*2;//服务时间[1,9]
				c.window = bestWindow(windows, nWin);
				windows[c.window].enqueue(c);
				std::cout << "新顾客进入" << c.window << "窗口" << '\n';
				total++;
			}

			for (int i = 0; i < nWin; i++) //每个窗口
				if (!windows[i].empty())//非空窗口等待时间-
				{
					std::cout << i << "窗口人数" << windows[i].sizeOfList() << '\n';
					if (--windows[i].front().time <= 0) {
						windows[i].dequeue();
						std::cout << "顾客从" << i << "窗口离开" << '\n';
						leave++;
					}
				}
		}
		std::cout << "结束--------------------" <<"总人数 "<<total \
			<< "离开人数 " << leave << '\n';
		delete[] windows;//同时~List()会清空每个队列
	}
}
