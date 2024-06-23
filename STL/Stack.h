#pragma once
#include "Vector.h"

//�˻ʺ�����			x
 //�Թ�����			x
//std::cout << stackUse::placeQueens(4);
//ע���ǣ�������<T>,�̳���Vector����ʹ�����к�������������
template <typename T>
class Stack :public Vector<T>
{
public:
	//ջ�����¼ӵ�

	Rank r = 1;
	void push(T const& e) { Vector<T>::insert(this->_size, e); }
	//Ҫ�� this->size() �� vector<T>::size() !!!!!
	T pop() { return  Vector<T>::removeV(this->_size - 1); }
	T& top() { return (*this)[this->_size - 1]; }
};




namespace stackUse {





	//��ʮ������nת��Ϊbase���ƴ���S
	template <typename T>
	//�����ظ���ʼ���ĳ�������
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
	 *����ʵ������ƥ�� O(n^2)
	 * �жϱ��ʽexp [lo,hi]��Χ�����Ƿ�ƥ��
	 */

	bool paren(const char exp[], int lo, int hi)
	{
		//���������ŵĿ�ջ
		Stack<char> s;
		for (size_t i = lo;i < hi && i < strlen(exp);i++)
		{
			switch (exp[i])
			{
			case '(':case '{':case '['://��������ջ
				s.push(exp[i]);break;
				//����ջ�������Ų��뵯����������ƥ�� ����false
			case ')':if ((s.empty()) || (s.pop() != '(')) return false; break;
			case '}':if ((s.empty()) || (s.pop() != '{')) return false; break;
			case ']':if ((s.empty()) || (s.pop() != '[')) return false; break;
			default: break;//!!�����ź���
			}
		}
		return s.empty();//����ջ������ǰ������ƥ��
	}


	//------------------------
	//�ӳٻ���  �� ���ʽ��ֵ P116




	//�˻ʺ󡪡�������������������������������������������������������������������������������������������������������������������������������������
	/*�ʺ���
	 *
	 *
	 */
	class Queen
	{
	public:
		int x, y;
		Queen(int x = 0, int y = 0) :x(x), y(y) {};//!! �ǵ�����Ĭ��ֵ

		//ǰ�߲����޸Ĵ����q�����߲����޸ĵ�ǰ����
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
		int n = 0;//������
		do {
			//��Խ��ص���һ�ڵ��x+1λ�ã�����yԽ����n++��
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
			if (solution.find(q) == -1) {//���Է���
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