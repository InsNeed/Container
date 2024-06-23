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
//void List<T>::init()//��ʼ��
//{
//	header = new ListNode<T>;//����д��������
//	trailer = new ListNode<T>;
//	header->succ = trailer;header->pred = trailer;//˫������ͷָβ
//	trailer->succ = header;trailer->pred = header;
//	_size = 0;     
//}
//
////���ص���ֵ
////����[],������Ϊr�Ľڵ��ֵ  !!!!!!
//template <typename T>
//T& List<T>::operator[] (Rank r) const
//{
//	ListNode<T>* p = first();
//	while (r-- > 0)
//		p = p->succ;
//	return p->data;
//}
//
////�������б��еĽڵ�p��ǰn��ǰ���ڵ���Ѱ��e�����ص���e�ĺ���
//template <typename T>
//ListNode<T>* List<T>::find(T const& e,int n,ListNode<T>* p) const
//{
//	while (n-- > 0)
//		//����ʹ�� while(n--) ��������ڲ�Ȼ���while�ж���� �𣿣�����
//		if (e == (p = p->pred)->data) return p;
//	return nullptr;//����nullptr
//}
//
////!!!!!������ ListNode��!!!??
////ǰ����
////!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!�ص�
////ÿ�����ǵ�ǰ��������ԣ�û��Խ��
//template <typename T>
//ListNode<T>* ListNode<T>::insertAsPred(T const& e)
//{
//	//newһ���ڵ㣬ǰ��Ϊ��ǰ�����ǰ�������Ϊ��ǰ����ֵΪe
//	ListNode<T>* x = new ListNode(e, pred, this);
//	pred->succ = x;pred = x;
//	return x;
//}
////�����
//template <typename T>
//ListNode<T>* ListNode<T>::insertAsSucc(T const& e)
//{
//	ListNode<T>* x = new ListNode(e, this, succ);
//	succ->pred = x;succ = x;
//}
//
//
//
////e��Ϊ�׽ڵ����
//template <typename T>
//ListNode<T>* List<T>::insertAsFirst(T const& e)
//{	
//	_size++;	
//	return header->insertAsSucc(e);
//}
//
////e��ĩ�ڵ����
//template <typename T>
//ListNode<T>* List<T>::insertAsLast(T const& e)
//{
//	_size++;
//	return trailer->insertAsPred(e);
//}
//
////e��Ϊp�ĺ�̲���
//template <typename T>
//ListNode<T>* List<T>::insertA(ListNode<T>*  p,T const& e)
//{
//	_size++;	return p->insertAsSucc(e);
//	//size����++
//}
//
////e��Ϊp��ǰ������
//template <typename T>
//ListNode<T>* List<T>::insertB(ListNode<T>* p, T const& e)
//{
//	_size++;
//	return p->insertAsPred(e);
//}
//
////�½�һ���б�(init)���ڵ�Ϊ �ڵ�p�����n���ڵ�
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
////���c�б�����λ��p���n�assert: pΪ�Ϸ�λ�ã���������n-1����̽ڵ㣩
//template<typename T>
//List<T>::List(ListNode<T>* p, int n) { copyNodes(p, n); }
//
////���帴���б�
//template<typename T>
//List<T>::List(List<T> const& L)//������ const
//{
//	copyNodes(L.first(), L._size);
//}
//
////����L���Ե�r�����n��
//template<typename T>
//List<T>::List(List<T> const& L, int r, int n)
//{
//	copyNodes(L[r], n);
//}
//
////ɾ��
//template<typename T>
//T List<T>::remove(ListNode<T>* p)	//�������ô����p��������ֱ��pred
//{
//	T e = p->data;
//	p->pred->succ = p->succ;
//	p->succ->pred = p->pred;
//	delete p;//��������Ҫdelete p����   ListNode��ɾ��
//	_size--;
//	return e;//���ر���ֵ
//}
//
////�б�������
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
//		remove(header->succ);//��ȥ������delete������Ҳ...
//	return oldSize;
//}
//
////�޳������б��аm�ظ��ڵ� , �����޳����� !!
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
////��������ʹ��һ���������������б��е�ֵ!!!!
//template <typename T>
//void List<T>::traverse(void (*visit)(T&))//!!!!!!
//{
//	for (ListNode<T>* p = header;(p = p->succ) != trailer;visit(p->data));
//}
//
////������������ͨ�������������������һ�����󣬵������������
//template<typename T>template<typename VST>
//void List<T>::traverse( VST& visit )
//{  
//	for( ListNode<T>* p = header->succ;
//	p != trailer; p = p->succ ) visit ( p->data );  
//}
//
////������������,���ڰ��б���ÿ��ֵ��n
//template<typename T>
//struct visit
//{
//	void operator() (T& e,int n) const //!!!!������  ����const
//	{
//		return e *= n;
//	}
//};
//
//
////�����б��Ψһ��
//template <typename T>
//int List<T>::uniquify()
//{
//	int oldSize = _size;
//	if (_size < 2) return 0;
//	ListNode<T>* p = header, q;
//	while ((q = p->succ) != trailer )
//		if (q->data == p->data) remove(q);
//			else p = q;//�ǵ�ǰ�� ��ȻҲ����p= p->succ;����sdֱ��p->succ
//	return oldSize - _size;
//}
//
////�����б�Ĳ���e,��p��������trailer����n����ǰ���в��ҵ�����, ������ָ��
//// �����ҵ������ҵ�������e�ĺ��ߣ��������ڷ����Լ�����С�ڷ���ǰһ�ڵ�   P100
//template <typename T>
//ListNode<T>* List<T>::search(T const& e,int n,ListNode<T>* p) const//ÿ�ζ���const���ǵ��룡
//{
//	while (n-- > 0)
//		if ((p = p->pred->data) >= e)//��������ģ�
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
////�������� On2
////������ʼλ��p��n��Ԫ�����򣬣�����p��������������
////n = 1�������Լ������Լ�������ǰһֵ���棬Ȼ��λ������ƶ�����ɾ��ԭ�Լ�
//template <typename T>
//void List<T>::insertionSort(ListNode<T>* p, int n)
//{
//	for (int i = 0; i < n; i++)
//	{
//		insertA(search(p->data, i, p), p->data);//search�õ��ĵط�
//		//eС��ǰ��ȫ����search����header��insertA header
//		//eС��ĳһֵ�����ظ�ֵλ��p��insetA  
//
//		p = p->succ;remove(p->pred);
//	}
//}
//
////ѡ������
//template <typename T>
//void List<T>::selectionSort(ListNode<T>* p, int n)
//{
//
//}
//
//
////����ʼλ��p��n����ѡ�����ֵ������
////����֪�����Ŀ�ʼ��
//template <typename T>
//ListNode<T>* List<T>::selectMax(ListNode<T>* p, int n)
//{
//	ListNode<T> p;
//	//?????????
//}