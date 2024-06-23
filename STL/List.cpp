//
//
//#include "List.h"
//
//template <typename T>
//void List<T>::connection()
//{
//	vector<int> i;
//}
//
//template <typename T>
//void List<T>::init()//初始化
//{
//	header = new ListNode<T>;//！！写法，创建
//	trailer = new ListNode<T>;
//	header->succ = trailer;header->pred = trailer;//双向链表头指尾
//	trailer->succ = header;trailer->pred = header;
//	_size = 0;     
//}
//
////返回的是值
////重载[],返回秩为r的节点的值  !!!!!!
//template <typename T>
//T& List<T>::operator[] (Rank r) const
//{
//	ListNode<T>* p = first();
//	while (r-- > 0)
//		p = p->succ;
//	return p->data;
//}
//
////在无序列表中的节点p的前n个前驱节点中寻找e，返回等于e的后者
//template <typename T>
//ListNode<T>* List<T>::find(T const& e,int n,ListNode<T>* p) const
//{
//	while (n-- > 0)
//		//不能使用 while(n--) ，先完成内部然后才while判断真假 吗？？？？
//		if (e == (p = p->pred)->data) return p;
//	return nullptr;//建议nullptr
//}
//
////!!!!!属于类 ListNode，!!!??
////前插入
////!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!重点
////每个都是当前对象的属性，没有越界
//template <typename T>
//ListNode<T>* ListNode<T>::insertAsPred(T const& e)
//{
//	//new一个节点，前驱为当前对象的前驱，后继为当前对象，值为e
//	ListNode<T>* x = new ListNode(e, pred, this);
//	pred->succ = x;pred = x;
//	return x;
//}
////后插入
//template <typename T>
//ListNode<T>* ListNode<T>::insertAsSucc(T const& e)
//{
//	ListNode<T>* x = new ListNode(e, this, succ);
//	succ->pred = x;succ = x;
//}
//
//
//
////e作为首节点插入
//template <typename T>
//ListNode<T>* List<T>::insertAsFirst(T const& e)
//{	
//	_size++;	
//	return header->insertAsSucc(e);
//}
//
////e作末节点插入
//template <typename T>
//ListNode<T>* List<T>::insertAsLast(T const& e)
//{
//	_size++;
//	return trailer->insertAsPred(e);
//}
//
////e作为p的后继插入
//template <typename T>
//ListNode<T>* List<T>::insertA(ListNode<T>*  p,T const& e)
//{
//	_size++;	return p->insertAsSucc(e);
//	//size别忘++
//}
//
////e作为p的前驱插入
//template <typename T>
//ListNode<T>* List<T>::insertB(ListNode<T>* p, T const& e)
//{
//	_size++;
//	return p->insertAsPred(e);
//}
//
////新建一个列表(init)，节点为 节点p后面的n个节点
//template <typename T>
//void List<T>::copyNodes(ListNode<T>* p, int n)
//{
//	init();
//	while (n--)
//	{
//		insertAsLast(p->succ->data);
//		p = p->succ;
//	}
//}
//
////复刢列表中自位置p起得n项（assert: p为合法位置，且至少有n-1个后继节点）
//template<typename T>
//List<T>::List(ListNode<T>* p, int n) { copyNodes(p, n); }
//
////整体复制列表
//template<typename T>
//List<T>::List(List<T> const& L)//别忘了 const
//{
//	copyNodes(L.first(), L._size);
//}
//
////复制L中自第r项起的n项
//template<typename T>
//List<T>::List(List<T> const& L, int r, int n)
//{
//	copyNodes(L[r], n);
//}
//
////删除
//template<typename T>
//T List<T>::remove(ListNode<T>* p)	//别忘了用传入的p，而不是直接pred
//{
//	T e = p->data;
//	p->pred->succ = p->succ;
//	p->succ->pred = p->pred;
//	delete p;//！！！还要delete p！！   ListNode被删除
//	_size--;
//	return e;//返回备份值
//}
//
////列表析构器
//template <typename T> 
//List<T>::~List()
//{
//	clear();delete header;delete trailer;
//}
//
//template <typename T>
//int List<T>::clear()
//{
//	int oldSize = _size;
//	while (_size > 0)
//		remove(header->succ);//我去，不是delete啊，这也...
//	return oldSize;
//}
//
////剔除无序列表中癿重复节点 , 返回剔除个数 !!
//template<typename T> 
//int List<T>::deduplicate() 
//{
//	if (_size < 2)
//		return 0;
//	int oldSize = _size;
//	ListNode<T>* p = header;
//	Rank r = 0;
//	while ((p = p->succ) != trailer)
//	{
//		ListNode<T>* q = find(p->data, r, p);
//		q ? remove(q) : r++;
//	}
//	return oldSize - _size;
//}
//
////遍历，可使用一个函数操作整个列表中的值!!!!
//template <typename T>
//void List<T>::traverse(void (*visit)(T&))//!!!!!!
//{
//	for (ListNode<T>* p = header;(p = p->succ) != trailer;visit(p->data));
//}
//
////！！！！！！通过函数对象遍历，本是一个对象，但重载了运算符
//template<typename T>template<typename VST>
//void List<T>::traverse( VST& visit )
//{  
//	for( ListNode<T>* p = header->succ;
//	p != trailer; p = p->succ ) visit ( p->data );  
//}
//
////函数对象例子,用于把列表里每个值乘n
//template<typename T>
//struct visit
//{
//	void operator() (T& e,int n) const //!!!!俩括号  带个const
//	{
//		return e *= n;
//	}
//};
//
//
////有序列表的唯一化
//template <typename T>
//int List<T>::uniquify()
//{
//	int oldSize = _size;
//	if (_size < 2) return 0;
//	ListNode<T>* p = header, q;
//	while ((q = p->succ) != trailer )
//		if (q->data == p->data) remove(q);
//			else p = q;//记得前进 当然也可以p= p->succ;但别sd直接p->succ
//	return oldSize - _size;
//}
//
////有序列表的查找e,在p（可以是trailer）的n个真前驱中查找到后者, 返回其指针
//// 不是找到，是找到不大于e的后者，若都大于返回自己，都小于返回前一节点   P100
//template <typename T>
//ListNode<T>* List<T>::search(T const& e,int n,ListNode<T>* p) const//每次都忘const，记得想！
//{
//	while (n-- > 0)
//		if ((p = p->pred->data) >= e)//这是有序的！
//			break;
//	return p;
//}
//
//
//template<typename T> 
//void List<T>::sort(ListNode<T>* p, int n)
//{
//	switch (rand() % 3)
//	{
//	case 1:  insertionSort(p, n); break;
//	case 2: selectionSort(p, n); break;
//	default: mergeSort(p, n); break;
//	}
//}
//
////插入排序 On2
////对于起始位置p的n个元素排序，（包含p）！！！！！！
////n = 1即排序自己，将自己插入在前一值后面，然后位置向后移动，并删除原自己
//template <typename T>
//void List<T>::insertionSort(ListNode<T>* p, int n)
//{
//	for (int i = 0; i < n; i++)
//	{
//		insertA(search(p->data, i, p), p->data);//search用到的地方
//		//e小于前面全部，search返回header，insertA header
//		//e小于某一值，返回该值位置p，insetA  
//
//		p = p->succ;remove(p->pred);
//	}
//}
//
////选择排序
//template <typename T>
//void List<T>::selectionSort(ListNode<T>* p, int n)
//{
//
//}
//
//
////从起始位置p的n个中选择最大值！！！
////终于知道从哪开始了
//template <typename T>
//ListNode<T>* List<T>::selectMax(ListNode<T>* p, int n)
//{
//	ListNode<T> p;
//	//?????????
//}