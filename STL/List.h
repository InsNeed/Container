//#ifndef LIST_H
//#define LIST_H
#pragma once

#include "ListNode.h"
#include "Vector.h"

//链表
template <typename T>
class List {
private:
	int _size;ListNode<T>* header;ListNode<T>* trailer;   //成员只有规模，头尾哨兵 !?
	
protected:


	void init();//列表创建时初始化
	int clear();//清空
	void copyNodes(ListNode<T>* p, int n);//复制自p起的n个项
	

public:
	//构造函数
	List() {
		header = new ListNode<T>;//！！写法，创建
		trailer = new ListNode<T>;
		header->succ = trailer;header->pred = trailer;//双向链表头指尾
		trailer->succ = header;trailer->pred = header;
		_size = 0;
	};//注意init
	List(List<T> const& L);//整体复制列表L  看写法！const
	List(List<T> const& L, int r, int n);	//复制列表L自r起的n项
	List(ListNode<T>* p, int n);		//复制列表中自位置p起的n项

	//析构函数
	~List();//释放所有节点（包含头尾哨兵

	//只读访问接口
	Rank sizeOfList() const { return _size; }//规模
	bool empty() const { return _size <= 0; }//判空 
	ListNode<T>* operator [] (Rank r);//重载，支持循秩访问 低效  !!!
	ListNode<T>* first() const { return header->succ; }//!!!!! 是 header 的 succ
	ListNode<T>* last() const { return trailer->pred; }	//尾节点位置
	bool valid(ListNode<T>* p)//判断节点p是否合法				
	{return p && (p != header) && (p != trailer);}
	int disordered()const;	//逆序对个数						//x
	
	ListNode<T>* find(T const& e, int n, ListNode<T>* p) const;	//无序区间查找
	ListNode<T>* find(T const& e) const	//无序列表查找		const& e
	{return find(e, _size, trailer);}
	ListNode<T>* search(T const& e) const//有序区间查找
	{return search(e, _size, trailer);}
	ListNode<T>* search(T const& e, int n, ListNode<T>* p) const;
	ListNode<T>* selectMax(ListNode<T>* p, int n);//在p及其n个后继中选出最大者
	ListNode<T>* selectMax()//整体最大者
	{return selectMax(trailer->pred, _size);}

	//可写访问接口
	ListNode<T>* insertAsFirst(T const& e);//将e当作首节点插入
	ListNode<T>* insertAsLast(T const& e);//将e当作末节点插入
	ListNode<T>* insertA(ListNode<T>* p, T const& e);//将e当作p的后继插入	After
	ListNode<T>* insertB(ListNode<T>* p, T const& e);//将e当作p的前驱插入 Behind
	T remove(ListNode<T>* p); //删除合法位置p处的节点,反回被删除节点的值


	void sort(ListNode<T>* p,int n);//列表区间排序
	void sort() { sort(first(),_size); }//列表整体排序

	int deduplicate();//无序去重			
	int uniquify() ;//有序去重
	void reverse(); //前后倒置				x	

	//遍历
	//void traverse(void (*)(T&));//遍历

	template<typename VST> //操作器
	void traverse ( VST& ); //遍历，visit操作（函数对象，可全局性修改）

	//排序
	ListNode<T>* merge(ListNode<T>*&, int, List<T>&, ListNode<T>*, int); //归并排序		?
	void mergeSort(ListNode<T>*&, int);//自p开始对n个节点归并排序			?x
	void selectionSort(ListNode<T>*, int);//选择排序			
	void insertionSort(ListNode<T>*, int);//插入排序	

	void mergeSort() { mergeSort(header->succ, _size); }
	void selectionSort() { selectionSort(header->succ, _size+1); }
	void insertionSort() { insertionSort(header->succ, _size+1); }
};



/*




  /$$$$$$                  /$$                                           /$$
 /$$__  $$                | $$                                          | $$
| $$  \__/  /$$$$$$   /$$$$$$$  /$$$$$$      /$$   /$$ /$$$$$$$   /$$$$$$$  /$$$$$$   /$$$$$$
| $$       /$$__  $$ /$$__  $$ /$$__  $$    | $$  | $$| $$__  $$ /$$__  $$ /$$__  $$ /$$__  $$
| $$      | $$  \ $$| $$  | $$| $$$$$$$$    | $$  | $$| $$  \ $$| $$  | $$| $$$$$$$$| $$  \__/
| $$    $$| $$  | $$| $$  | $$| $$_____/    | $$  | $$| $$  | $$| $$  | $$| $$_____/| $$
|  $$$$$$/|  $$$$$$/|  $$$$$$$|  $$$$$$$    |  $$$$$$/| $$  | $$|  $$$$$$$|  $$$$$$$| $$
 \______/  \______/  \_______/ \_______/     \______/ |__/  |__/ \_______/ \_______/|__/






*/







template <typename T>
void List<T>::init()//初始化
{
	header = new ListNode<T>;//！！写法，创建
	trailer = new ListNode<T>;
	header->succ = trailer;header->pred = trailer;//双向链表头指尾
	trailer->succ = header;trailer->pred = header;
	_size = 0;
}

//返回的是值
//重载[],返回秩为r的节点的值  !!!!!!
template <typename T>
ListNode<T>* List<T>::operator[] (Rank r)
{
	ListNode<T>* p = first();
	while (r-- > 0)
		p = p->succ;
	return p;
}

//在无序列表中的节点p的前n个前驱节点中寻找e，返回等于e的后者
template <typename T>
ListNode<T>* List<T>::find(T const& e, int n, ListNode<T>* p) const
{
	while (n-- > 0)
		//不能使用 while(n--) ，先完成内部然后才while判断真假 吗？？？？
		if (e == (p = p->pred)->data) return p;
	return nullptr;//建议nullptr
}

//!!!!!属于类 ListNode，!!!??
//前插入
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!重点
//每个都是当前对象的属性，没有越界
template <typename T>
ListNode<T>* ListNode<T>::insertAsPred(T const& e)
{
	//new一个节点，前驱为当前对象的前驱，后继为当前对象，值为e
	ListNode<T>* x = new ListNode(e, pred, this);
	pred->succ = x;pred = x;
	return x;
}
//后插入
template <typename T>
ListNode<T>* ListNode<T>::insertAsSucc(T const& e)
{
	ListNode<T>* x = new ListNode(e, this, succ);
	succ->pred = x;succ = x;
	return x;
}



//e作为首节点插入
template <typename T>
ListNode<T>* List<T>::insertAsFirst(T const& e)
{
	_size++;
	return header->insertAsSucc(e);
}

//e作末节点插入
template <typename T>
ListNode<T>* List<T>::insertAsLast(T const& e)
{
	_size++;
	return trailer->insertAsPred(e);
}

//e作为p的后继插入
template <typename T>
ListNode<T>* List<T>::insertA(ListNode<T>* p, T const& e)
{
	_size++;	return p->insertAsSucc(e);
	//size别忘++
}

//e作为p的前驱插入
template <typename T>
ListNode<T>* List<T>::insertB(ListNode<T>* p, T const& e)
{
	_size++;
	return p->insertAsPred(e);
}

//新建一个列表(init)，节点为 节点p后面的n个节点
template <typename T>
void List<T>::copyNodes(ListNode<T>* p, int n)
{
	init();
	while (n--)
	{
		insertAsLast(p->succ->data);
		p = p->succ;
	}
}

//复刢列表中自位置p起得n项（assert: p为合法位置，且至少有n-1个后继节点）
template<typename T>
List<T>::List(ListNode<T>* p, int n) { copyNodes(p, n); }

//整体复制列表
template<typename T>
List<T>::List(List<T> const& L)//别忘了 const
{
	copyNodes(L.first(), L._size);
}

//复制L中自第r项起的n项
template<typename T>
List<T>::List(List<T> const& L, int r, int n)
{
	copyNodes(L[r], n);
}

//删除
template<typename T>
T List<T>::remove(ListNode<T>* p)	//别忘了用传入的p，而不是直接pred
{
	T e = p->data;
	p->pred->succ = p->succ;
	p->succ->pred = p->pred;
	delete p;//！！！还要delete p！！   ListNode被删除
	_size--;
	return e;//返回备份值
}

//列表析构器
template <typename T>
List<T>::~List()
{
	clear();delete header;delete trailer;
}

template <typename T>
int List<T>::clear()
{
	int oldSize = _size;
	while (_size > 0)
		remove(header->succ);//我去，不是delete啊，这也...
	return oldSize;
}

//剔除无序列表中癿重复节点 , 返回剔除个数 !!
template<typename T>
int List<T>::deduplicate()
{
	if (_size < 2)
		return 0;
	int oldSize = _size;
	ListNode<T>* p = header;
	Rank r = 0;
	while ((p = p->succ) != trailer)
	{
		ListNode<T>* q = find(p->data, r, p);
		q ? remove(q) : r++;
	}
	return oldSize - _size;
}

template<typename T>
inline void List<T>::reverse()
{
	ListNode<T>* p = header->succ;  // 初始化为第一个节点
	ListNode<T>* q = trailer->pred;       // 初始化为尾节点

	for(int i = 0;i < _size/2;i++)
	{
		std::swap(p->data, q->data);
		p = p->succ;
		q = q->pred;  // 这里应该使用尾节点的前驱
	}
}


//遍历，可使用一个函数操作整个列表中的值!!!!
//template <typename T>
//void List<T>::traverse(void (*visit)(T&))//!!!!!!
//{
//	for (ListNode<T>* p = header;(p = p->succ) != trailer;visit(p->data));
//}

//本是一个对象，但重载了运算符
//通过函数对象遍历
template<typename T>	template<typename VST>
void List<T>::traverse(VST& visit)
{
	for (ListNode<T>* p = header->succ;p != trailer; p = p->succ) visit(p->data);
}


//函数对象例子,用于把列表里每个值乘n
//template<typename T>
//struct visit
//{
//	void operator() (T& e, int n) const //!!!!俩括号  带个const
//	{
//		return e *= n;
//	}
//};


//有序列表的唯一化
template <typename T>
int List<T>::uniquify()
{
	int oldSize = _size;
	if (_size < 2) return 0;
	ListNode<T>* p = header, q;
	while ((q = p->succ) != trailer)
		if (q->data == p->data) remove(q);
		else p = q;//记得前进 当然也可以p= p->succ;但别sd直接p->succ
	return oldSize - _size;
}

//有序列表的查找e,在p（可以是trailer）的n个真前驱中查找到后者, 返回其指针
// 不是找到，是找到不大于e的后者，若都大于返回自己，都小于返回前一节点   P100
template <typename T>
ListNode<T>* List<T>::search(T const& e, int n, ListNode<T>* p) const//每次都忘const，记得想！
{
	while (n-- > 0) {
		p = p->pred;
		if (p->data >= e)//这是有序的！
			break;
	}
	return p;
}


template<typename T>
void List<T>::sort(ListNode<T>* p, int n)
{
	switch (rand() % 3)
	{
	case 1:  insertionSort(p, n); break;
	case 2: selectionSort(p, n); break;
	default: mergeSort(p, n); break;
	}
}

//插入排序 On2
//对于起始位置p的n个元素排序，（包含p）！！！！！！
//n = 1即排序自己，将自己插入在前一值后面，然后位置向后移动，并删除原自己
template <typename T> //对列表中起始于位置p、宽度为n的区间做插入排序
void List<T>::insertionSort(ListNode<T>* p, Rank n) { // valid(p) && Rank(p) + n <= size
	for (int r = 0; r < n; r++) { //逐一为各节点
		insertA(search(p->data, r, p), p->data); //查找适当的位置并插入
		p = p->succ; remove(p->pred); //转向下一节点
	}
}



template <typename T> //列表的归并排序算法：对起始于位置p的n个元素排序
void List<T>::mergeSort(ListNode<T>* & p, int n)  // valid(p) && Rank(p) + n <= size
{
	if (n < 2) return; //若待排序范围已足够小，则直接返回；否则...
	Rank m = n >> 1; //以中点为界
	ListNode<T>* q = p; for (int i = 0; i < m; i++) q = q->succ; //找到后子列表起点
	mergeSort(p, m); mergeSort(q, n - m); //前、后子列表各分别排序
	p = merge(p, m, *this, q, n - m); //归并
} //注意：排序后，p依然指向归并后区间的（新）起点


//选择排序
template <typename T>
void List<T>::selectionSort(ListNode<T>* p, int n)
{
	ListNode<T>* current = header;

	while (current != nullptr) {
		ListNode<T>* minNode = current;
		ListNode<T>* temp = current->succ;

		// 找到最小节点
		while (temp != nullptr) {
			if (temp->data < minNode->data) {
				minNode = temp;
			}
			temp = temp->succ;
		}

		// 交换数据
		int tempData = current->data;
		current->data = minNode->data;
		minNode->data = tempData;

		current = current->succ;
	}
}


//从起始位置p前以及其前n个中选择最大值
template <typename T>
ListNode<T>* List<T>::selectMax(ListNode<T>* p, int n)
{
	ListNode<T>* max = p;
	while (n-- && p != header)
	{
		if (max->data < (p = p->pred)->data) max = p; 
	}
	return max;
}

//有序列表的归并：当前列表中自p起的n个元素，与列表L中自q起的m个元素归并	?
template <typename T>
ListNode<T>* merge(ListNode<T>*& p, int n , List<T>& L, ListNode<T>* q, int m){
	// this.valid(p) && Rank(p) + n <= size && this.sorted(p, n)		?
	// L.valid(q) && Rank(q) + m <= L._size && L.sorted(q, m)			?
	// 注意：在被mergeSort()调用时，this == &L && Rank(p) + n = Rank(q)		?
	ListNode<T>* pp = p->pred; 
	while ((0 < m) && (q != p)) //q尚未出界（或在mergeSort()中，p亦尚未出界）之前
		if ((0 < n) && (p->data <= q->data)) //若p尚未出界且v(p) <= v(q)，则
		{
			p = p->succ; n--;
		} //p直接后移，即完成归入
		else //否则，将q转移至p之前，以完成归入
		{
			insert(L.remove((q = q->succ)->pred), p); m--;
		}
	return pp->succ; //更新的首节点
}
