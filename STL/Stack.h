#pragma once
#include "Vector.h"

//八皇后问题			x
 //迷宫问题			x
//std::cout << stackUse::placeQueens(4);
//注意是：，不加<T>,继承自Vector，可使用其中函数，包括析构
template <typename T>
class Stack :public Vector<T>
{
public:
	//栈顶：新加的

	Rank r = 1;
	void push(T const& e) { Vector<T>::insert(this->_size, e); }
	//要用 this->size() 或 vector<T>::size() !!!!!
	T pop() { return  Vector<T>::removeV(this->_size - 1); }
	T& top() { return (*this)[this->_size - 1]; }
};




namespace stackUse {





	//将十进制数n转化为base进制存于S
	template <typename T>
	//避免重复初始化的常量数组
	static void convert(Stack<T>& S, unsigned long long int n, int base)
	{
		char digit[]{ '0','1','2','3','4','5','6','7','8',
			'9','A','B','C','D','E','F' };
		while (n > 0)
		{
			int remainder = (int)(n % base);
			S.push(digit[remainder]);
			n /= base;
		}
	}




	/**
	 *迭代实现括号匹配 O(n^2)
	 * 判断表达式exp [lo,hi]范围括号是否匹配
	 */

	bool paren(const char exp[], int lo, int hi)
	{
		//储存左括号的空栈
		Stack<char> s;
		for (size_t i = lo;i < hi && i < strlen(exp);i++)
		{
			switch (exp[i])
			{
			case '(':case '{':case '['://左括号入栈
				s.push(exp[i]);break;
				//若空栈或右括号不与弹出的左括号匹配 返回false
			case ')':if ((s.empty()) || (s.pop() != '(')) return false; break;
			case '}':if ((s.empty()) || (s.pop() != '{')) return false; break;
			case ']':if ((s.empty()) || (s.pop() != '[')) return false; break;
			default: break;//!!非括号忽略
			}
		}
		return s.empty();//若空栈则所有前括号已匹配
	}


	//------------------------
	//延迟缓冲  ， 表达式求值 P116




	//八皇后————————————————————————————————————————————————————————————————————
	/*皇后类
	 *
	 *
	 */
	class Queen
	{
	public:
		int x, y;
		Queen(int x = 0, int y = 0) :x(x), y(y) {};//!! 记得设置默认值

		//前者不可修改传入的q，后者不可修改当前对象
		bool operator ==(Queen const& q) const {
			return (this->x == q.x) || (this->y == q.y) ||
				(x + y == q.x + q.y) || (x - y == q.x - q.y);
		}
		bool operator !=(Queen const& q)const { return !(*this == q); }//*
	};


	int placeQueens(int N)
	{
		Stack<Queen> solution;
		Queen q(0, 0);
		int n = 0;//方案数
		do {
			//若越界回到上一节点的x+1位置，若是y越界则n++；
			if (q.x >= N || q.y >= N) {
				q.x = solution.top().x;
				q.y = solution.top().y;
				solution.pop();
				q.x++;
				if (q.y >= N) {
					n++;
					std::cout << "aaa???";
				}
				continue;
			}

		
			//std::cout << q.x << "," << q.y << "   " << solution.find(q) << std::endl;
			if (solution.find(q) == -1) {//可以放置
				solution.push(q);
				q.y++;
				q.x = 0;
			}
			else {
				q.x++;
			}
			if (!solution.empty()) {
				for (int i = 0;i < solution.size();i++)
					std::cout << solution[i].x << solution[i].x<<std::endl;
			}
		} while (!solution.empty());
		return n;
	}
}

//	Stack<Queen> solution;
//	Queen q(0, 0);
//	do {
//		if (solution.size() >= N || q.y >= N) {
//			q = solution.pop(); q.y++;
//		}
//		else {
//			while ((q.y < N) && (solution.find(q) >= 0))
//			{q.y++; nCheck++;}
//			if (q.y < N) {
//				solution.push(q);
//				if (solution.size() >= N) nSolu++;
//				q.x++;q.y = 0;
//			}
//		}
//	} while ((q.x) > 0 || (q.y < N));
//}