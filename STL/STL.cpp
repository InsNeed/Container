// 仿函数（Functor）、容器（Container）、算法（Algorithm）、迭代器（Iterator）、适配器（Adapter）和分配器（Allocator）。
////
//

#define CC_SAFE_DELETE(p)   if(p) { delete (p); (p) = NULL; }  
#include <iostream>
//#include <vector>
#include "List.h"
#include "Vector.h"
#include "Stack.h"
#include "BinNode.h"
#include "BinTree.h"
#include "Graph.h"


void visitV(int e) {
	std::cout << e << ",";
}
void visitL(int e) {
	std::cout << e << "-->";
}
void visitT(int e) {
	std::cout << e << ",";
}
void visitT2(char e) {
	std::cout << e << ",";
}




int main()
{





	//------------------图------------------------------------------------------
	//char c;
	//std::cin >> c;
	//while (c != '#')
	{



		std::cout << "//-------------------二叉树--------------------------------------------------<<" << std::endl;
		BinTree<int>* tree1 = new BinTree<int>;

		tree1->insertAsRoot(0);//构造树
		tree1->insertAsLC(tree1->root(), 1);
		BinNode<int>* node = tree1->insertAsRC(tree1->root(), 2);
		node->insertAsLc(3);
		node->insertAsRc(4);
		// 此时树： 0(1,2(3,4));

		travPre_R(tree1->root(), visitT);//递归版先序遍历
		std::cout << '\n';
		//0 1 2 3 4
		travIn_I1(tree1->root(), visitT);//迭代版中序遍历
		std::cout << '\n';
		//1 0 3 2 4
		tree1->root()->travLevel(visitT);//层次遍历
		std::cout << '\n';
		//0 1 2 3 4

		BinTree<int>* tree2 = tree1->secede(node);//将以node为根的树脱离
		travPre_I(tree2->root(), visitT);
		std::cout << '\n';
		//2 3 4

		tree2->remove(node);//删除node及其孩子
		std::cout << tree2->empty();//树是否空
		std::cout << '\n';
		//1

		std::cout << '\n';

		std::cout << "//-----------------------------队列----------------------------------------" << std::endl;

		Queue<int>* que = new Queue<int>;
		que->enqueue(1);//入队
		que->enqueue(2);
		que->dequeue();//出队
		std::cout << que->front() << '\n';
		//2
		// 
		//模拟排队过程(窗口数，营业时间，每人平均服务时间)
		//queueUse::simulate(5,100,20);


		std::cout << "//-------------------------------栈--------------------------------------" << std::endl;
		Stack<int>* sta = new Stack<int>;
		sta->push(1);//入栈
		sta->push(2);
		std::cout << sta->pop() << '\n';//输出栈顶并出栈
		//2

		Stack<char>* st = new Stack<char>;//char
		//将十进制10转换为2进制存于st
		stackUse::convert(*st, 10, 2);
		while (!st->empty()) {
			std::cout << st->pop();
		}
		//1010
		delete st;
		std::cout << '\n';

		//判断字符串括号是否符合
		const char* s1 = { "{[()]}" };
		const char* s2 = { "{[())]}" };
		std::cout << stackUse::paren(s1, 0, strlen(s1));
		std::cout << '\n';
		std::cout << stackUse::paren(s2, 0, strlen(s2));
		std::cout << '\n';
		//1  0




		std::cout << "//-------------------------数组------------------------------" << std::endl;


		Vector<int>* t = new Vector<int>(10, 9, 1);//capacity,size,value 
		t->traverse(visitV);//vector为
		//1,1,1,1,1,1,1,1,1

		t->info();//capacity = 10 , size = 5
		std::cout << '\n';

		Vector<int>* vec = new Vector<int>(*t, 0, 3);//另一构造函数，复制t[0,4]
		vec->traverse(visitV);
		//1,1,1
		vec->info();//capacity = 4,size = 2
		std::cout << '\n';

		(*vec)[0] = 3;
		//3,1,1
		vec->insert(vec->size(), 2);
		//3,1,1,2
		std::cout << '\n';
		vec->insert(vec->find(3), 4);
		vec->traverse(visitV);
		std::cout << '\n';
		//4,3,1,1,2

		vec->deduplicate();//去重
		vec->shellSort1();//排序
		vec->traverse(visitV);
		std::cout << '\n';
		//1,2,3,4
		vec->unsort();//打乱 
		vec->traverse(visitV);
		std::cout << '\n';
		vec->info();
		//size = 4
		std::cout << '\n';


		struct student
		{
			int id;
			std::string name;
			student() :id(0), name("null") {};
			student(int id, std::string name) :id(id), name(name) {};
		};

		//一维数组，班级1
		Vector<student> classA;
		classA.insert(student(101, "mike"));
		classA.insert(student(102, "jack"));
		classA.insert(student(103, "duck"));
		//一维数组，班级2
		Vector<student> classB;
		classB.insert(student(201, "suck"));
		classB.insert(student(202, "funk"));
		classB.insert(student(203, "sock"));
		//二维数组，年级
		Vector<Vector<student>> classes;
		classes.insert(classA);
		//classes.insert(classB);
		////输出一班1号id
		std::cout << classes[0][0].id;
		std::cout << '\n';
		//101

		std::cout << "//------------------------链表--------------------------------------------" << std::endl;

		List<int>* ls = new List<int>();
		ls->insertAsFirst(1);
		ls->insertAsLast(2);

		//ListNode<int>* n = ls->operator[](1);

		ls->insertA((*ls)[1], 3);
		ls->insertB(ls->search(2), 4);
		//1 2 4 3
		ls->insertB(ls->find(3), 5);
		//1 2 4 5 3
		ls->insertAsLast(2);
		//1 2 4 5 3 2
		ls->traverse(visitL);//链表为//1 2 4 5 3 2
		std::cout << '\n';

		ls->insertionSort();//排序
		ls->traverse(visitL);
		std::cout << '\n';
		//5 4 3 2 2 1

		ls->deduplicate();//去重
		ls->traverse(visitL);
		std::cout << '\n';
		//5 4 3 2 1

		ls->reverse();//翻转
		ls->traverse(visitL);
		std::cout << '\n';
		//1 2 3 4 5

		ls->remove((*ls)[1]);//删除
		ls->traverse(visitL);
		std::cout << '\n';
		//1 3 4 5

		std::cout << ls->selectMax()->data << std::endl;//最大值
		//5

		delete ls;
		std::cout << ls->empty() << std::endl;
		//1

		List<char> ls2;//其他数据类型
		ls2.insertAsLast('h');
		ls2.insertAsLast('i');
		std::cout << ls2[1]->data <<std::endl;
		//i

	}
}