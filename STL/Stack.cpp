//#include "Stack.h"
//
//
////Stack��ʹ��
////�������Ƶ�����ת��Ϊn����
////ת��������֣���ջ˳���ţ��ų�ʱ˳����ȷ
////template <typename T>
//////!!!
////void convert(Stack<T>& S,__int64 n,int base)
////{
////	//�� digit ��������Ϊһ����̬����
////	//����ζ�����ڳ���ִ���ڼ�ֻ�ᱻ��ʼ��һ��,���ٵݹ鿪֧
////	static char digit[]{ '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F' };
////	if (n > 0) {
////		convert(S, n/base, base);
////		S.push(digit(n %= base));//!!!!  1%2 = 1
////	}
////}
//template <typename T>
//void connection()
//{
//	Stack<int> i;
//}
//
////���淽��ʹ�õݹ飬���ܲ���
//template <typename T>
//void convert(Stack<T>& S, __int64 n, int base)
//{
//	static char digit[]{ '0','1','2','3','4','5','6','7','8',
//		'9','A','B','C','D','E','F' };
//	while (n > 0)
//	{
//		//!!!
//		int remainder = (int)(n % base);
//		S.push(digit[remainder]);
//		n /= base;
//	}
//}
//
//
////----------------------------------
////�ݹ�ʵ������ƥ��
////
//// 
////ɾ��exp[lo,hi]�������ŵ�ǰ׺�ͺ�׺
//void trim(const char exp[], int& lo, int& hi)
//{
//	while ((lo < hi) && (exp[lo] != '(') && (exp[lo] != ')')) lo++;
//	while ((lo < hi) && (exp[hi] != '(') && (exp[hi] != ')')) hi--;
//}
//
////�з�exp ��crc У��������������ʼΪtrim()��õ���1
////����������������������ʱ���ش�ʱλ�� mi
////
//int divide(const char exp[], int lo, int hi)
//{
//	int mi = lo;int crc = 1;
//	while ((++mi < hi ) && (crc > 0))//++mi
//	{
//		if (exp[mi] == '(') crc++;
//		if (exp[mi] == ')')crc--;
//	}
//	return mi;
//}
//
////����ƥ��
////��expͨ��trim��ȥ�����ŵ�ǰ��׺��
////bool paren(const char exp[], int lo, int hi)
////{
////	trim(exp, lo, hi);
////	if (lo >= hi) return true;//exp��������
////	if (exp[lo] != '(') return false;//�����'('
////	if (exp[hi] != ')') return false;
////	int mi = divide(exp, lo, hi); //�õ��зֵ�
////	return paren(exp, lo + 1, mi - 1) && paren(exp, mi + 1, hi);
////}
//
///**
// *����ʵ������ƥ�� O(n^2)
// * �жϱ��ʽexp [lo,hi]��Χ�����Ƿ�ƥ��
// */
//
//bool paren(const char exp[], int lo, int hi)
//{
//	//����һ�����������ŵĿ�ջ
//	Stack<char> s;
//	for (int i = lo;i < hi;i++)
//	{
//		switch (s[lo++])
//		{
//		case '(':case '{':case '['://��������ջ
//			s.push(s[lo]);break;
//		//����ջ�������Ų��뵯����������ƥ�� ����false
//		case ')':if ((s.empty()) || (s.pop() != '(')) return false; break;//����
//		case '}':if ((s.empty()) || (s.pop() != '}')) return false; break;
//		case ']':if ((s.empty()) || (s.pop() != ']')) return false; break;
//		default: break;//!!�����ź���
//		}
//	}
//	return s.empty();//����ջ������ǰ������ƥ��
//}
//
//
////------------------------
////�ӳٻ���  �� ���ʽ��ֵ P116
//
//
//
//
//////�˻ʺ󡪡�������������������������������������������������������������������������������������������������������������������������������������
/////*�ʺ���
//// *
//// *
//// */
////class Queen
////{
////public:
////	int x, y;
////	Queen(int x = 0, int y = 0) :x(x), y(y) {};//!! �ǵ�����Ĭ��ֵ
////	bool operator ==(Queen const& q)const //!!  const!!
////	//ǰ�߲����޸Ĵ����q�����߲����޸ĵ�ǰ���� ������
////	{
////		return (this->x == q.x)
////			|| (this->y == q.y)//�ж���ȣ���Ȼ��||
////			|| (x + y == q.x + q.y)
////			|| (x - y == q.x - q.y);
////	}
////	bool operator !=(Queen const& q)const { return !(*this == q); }//*
////};
////
////vector<Stack<Queen>> placeQueen(int n)
////{
////	Stack<Queen> solution;
////	vector<Stack<Queen>> solutions;//NOT solution,It's S..<Q..>
////	Queen q(0,0);
////	while (solutions.size() < n)
////	{
////		if (q.x < n && solution.find(q) <= 0) {//xС��n�ҿ��Է�
////			solution.push(q); q.y++;q.x = 0;//��ջ��y++��x=0
////		}
////		else {//�����ܷ�:x С�ڵ���n��x++���������q = ��һλ�ã�x++
////			if (q.x <= n) {
////				q.x++;
////			}
////			else {//xԽ�磬���ݲ�x+1
////				solution.pop();q = solution.top();q.x++;
////			}
////		}
////		if (q.y > n)//��yԽ��
////		{
////			solutions.insert(solution);//һ�ֽ������
////			solution.pop();//�������һ�ڵ�
////			q.y--;q.x++;//y������ԭ�ڵ�x+1λ��
////		}
////	}
////	return solutions;
////}
////
////
////
//////�Թ����ݡ�������������������������������������������������������������������������������������������������������������������������������
////// 
//////�Թ���Ԫ״̬,���ã�·�����۷���ǽ
////typedef enum{ AVAILABLE , ROUTE,BACKTRACKED,WALL } Status;
//////��Ԫ������ڽӷ��� 
////typedef enum{UNKNOW, EAST,SOUTH,WEST,NORTH,NO_WAY} ESWN;
//////��������һ�ٽ緽��ע����inline������������С�Ĵ����ظ�ʹ�õĲ��ݹ����
////inline ESWN nextESWN(ESWN eswn) { return ESWN(eswn + 1); }
//////�Թ�����
////struct Cell
////{
////	int x, y; Status status;
////	ESWN outgoing, incoming;//��������
////};
////
//////�Թ��ߴ�
////#define LABY_MAX 24 
//////
////Cell laby[LABY_MAX][LABY_MAX];