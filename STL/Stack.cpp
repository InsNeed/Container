//#include "Stack.h"
//
//
////Stack的使用
////将二进制的数字转化为n进制
////转化后的数字，如栈顺序倒着，排出时顺序正确
////template <typename T>
//////!!!
////void convert(Stack<T>& S,__int64 n,int base)
////{
////	//将 digit 数组声明为一个静态数组
////	//这意味着它在程序执行期间只会被初始化一次,减少递归开支
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
////上面方法使用递归，性能不好
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
////递归实现括号匹配
////
//// 
////删除exp[lo,hi]不含括号的前缀和后缀
//void trim(const char exp[], int& lo, int& hi)
//{
//	while ((lo < hi) && (exp[lo] != '(') && (exp[lo] != ')')) lo++;
//	while ((lo < hi) && (exp[hi] != '(') && (exp[hi] != ')')) hi--;
//}
//
////切分exp ，crc 校验括号数量，初始为trim()后得到的1
////当右括号数量等于左括号时返回此时位置 mi
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
////括号匹配
////将exp通过trim除去非括号的前后缀，
////bool paren(const char exp[], int lo, int hi)
////{
////	trim(exp, lo, hi);
////	if (lo >= hi) return true;//exp已无括号
////	if (exp[lo] != '(') return false;//最左非'('
////	if (exp[hi] != ')') return false;
////	int mi = divide(exp, lo, hi); //得到切分点
////	return paren(exp, lo + 1, mi - 1) && paren(exp, mi + 1, hi);
////}
//
///**
// *迭代实现括号匹配 O(n^2)
// * 判断表达式exp [lo,hi]范围括号是否匹配
// */
//
//bool paren(const char exp[], int lo, int hi)
//{
//	//创建一个储存左括号的空栈
//	Stack<char> s;
//	for (int i = lo;i < hi;i++)
//	{
//		switch (s[lo++])
//		{
//		case '(':case '{':case '['://左括号入栈
//			s.push(s[lo]);break;
//		//若空栈或右括号不与弹出的左括号匹配 返回false
//		case ')':if ((s.empty()) || (s.pop() != '(')) return false; break;//！！
//		case '}':if ((s.empty()) || (s.pop() != '}')) return false; break;
//		case ']':if ((s.empty()) || (s.pop() != ']')) return false; break;
//		default: break;//!!非括号忽略
//		}
//	}
//	return s.empty();//若空栈则所有前括号已匹配
//}
//
//
////------------------------
////延迟缓冲  ， 表达式求值 P116
//
//
//
//
//////八皇后————————————————————————————————————————————————————————————————————
/////*皇后类
//// *
//// *
//// */
////class Queen
////{
////public:
////	int x, y;
////	Queen(int x = 0, int y = 0) :x(x), y(y) {};//!! 记得设置默认值
////	bool operator ==(Queen const& q)const //!!  const!!
////	//前者不可修改传入的q，后者不可修改当前对象 ！！！
////	{
////		return (this->x == q.x)
////			|| (this->y == q.y)//判断相等，当然是||
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
////		if (q.x < n && solution.find(q) <= 0) {//x小于n且可以放
////			solution.push(q); q.y++;q.x = 0;//进栈，y++，x=0
////		}
////		else {//若不能放:x 小于等于n则x++，否则回溯q = 上一位置，x++
////			if (q.x <= n) {
////				q.x++;
////			}
////			else {//x越界，回溯并x+1
////				solution.pop();q = solution.top();q.x++;
////			}
////		}
////		if (q.y > n)//若y越界
////		{
////			solutions.insert(solution);//一种解决方案
////			solution.pop();//弹出最后一节点
////			q.y--;q.x++;//y回溯至原节点x+1位置
////		}
////	}
////	return solutions;
////}
////
////
////
//////迷宫回溯————————————————————————————————————————————————————————————————
////// 
//////迷宫单元状态,可用，路径，折返，墙
////typedef enum{ AVAILABLE , ROUTE,BACKTRACKED,WALL } Status;
//////单元的相对邻接方向 
////typedef enum{UNKNOW, EAST,SOUTH,WEST,NORTH,NO_WAY} ESWN;
//////依次至下一临界方向，注意是inline！！！，用于小的大量重复使用的不递归代码
////inline ESWN nextESWN(ESWN eswn) { return ESWN(eswn + 1); }
//////迷宫房间
////struct Cell
////{
////	int x, y; Status status;
////	ESWN outgoing, incoming;//进出方向
////};
////
//////迷宫尺寸
////#define LABY_MAX 24 
//////
////Cell laby[LABY_MAX][LABY_MAX];