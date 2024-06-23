//#ifndef LIST_H
//#define LIST_H
#pragma once

#include "ListNode.h"
#include "Vector.h"

//����
template <typename T>
class List {
private:
	int _size;ListNode<T>* header;ListNode<T>* trailer;   //��Աֻ�й�ģ��ͷβ�ڱ� !?
	
protected:


	void init();//�б���ʱ��ʼ��
	int clear();//���
	void copyNodes(ListNode<T>* p, int n);//������p���n����
	

public:
	//���캯��
	List() {
		header = new ListNode<T>;//����д��������
		trailer = new ListNode<T>;
		header->succ = trailer;header->pred = trailer;//˫������ͷָβ
		trailer->succ = header;trailer->pred = header;
		_size = 0;
	};//ע��init
	List(List<T> const& L);//���帴���б�L  ��д����const
	List(List<T> const& L, int r, int n);	//�����б�L��r���n��
	List(ListNode<T>* p, int n);		//�����б�����λ��p���n��

	//��������
	~List();//�ͷ����нڵ㣨����ͷβ�ڱ�

	//ֻ�����ʽӿ�
	Rank sizeOfList() const { return _size; }//��ģ
	bool empty() const { return _size <= 0; }//�п� 
	ListNode<T>* operator [] (Rank r);//���أ�֧��ѭ�ȷ��� ��Ч  !!!
	ListNode<T>* first() const { return header->succ; }//!!!!! �� header �� succ
	ListNode<T>* last() const { return trailer->pred; }	//β�ڵ�λ��
	bool valid(ListNode<T>* p)//�жϽڵ�p�Ƿ�Ϸ�				
	{return p && (p != header) && (p != trailer);}
	int disordered()const;	//����Ը���						//x
	
	ListNode<T>* find(T const& e, int n, ListNode<T>* p) const;	//�����������
	ListNode<T>* find(T const& e) const	//�����б����		const& e
	{return find(e, _size, trailer);}
	ListNode<T>* search(T const& e) const//�����������
	{return search(e, _size, trailer);}
	ListNode<T>* search(T const& e, int n, ListNode<T>* p) const;
	ListNode<T>* selectMax(ListNode<T>* p, int n);//��p����n�������ѡ�������
	ListNode<T>* selectMax()//���������
	{return selectMax(trailer->pred, _size);}

	//��д���ʽӿ�
	ListNode<T>* insertAsFirst(T const& e);//��e�����׽ڵ����
	ListNode<T>* insertAsLast(T const& e);//��e����ĩ�ڵ����
	ListNode<T>* insertA(ListNode<T>* p, T const& e);//��e����p�ĺ�̲���	After
	ListNode<T>* insertB(ListNode<T>* p, T const& e);//��e����p��ǰ������ Behind
	T remove(ListNode<T>* p); //ɾ���Ϸ�λ��p���Ľڵ�,���ر�ɾ���ڵ��ֵ


	void sort(ListNode<T>* p,int n);//�б���������
	void sort() { sort(first(),_size); }//�б���������

	int deduplicate();//����ȥ��			
	int uniquify() ;//����ȥ��
	void reverse(); //ǰ����				x	

	//����
	//void traverse(void (*)(T&));//����

	template<typename VST> //������
	void traverse ( VST& ); //������visit�������������󣬿�ȫ�����޸ģ�

	//����
	ListNode<T>* merge(ListNode<T>*&, int, List<T>&, ListNode<T>*, int); //�鲢����		?
	void mergeSort(ListNode<T>*&, int);//��p��ʼ��n���ڵ�鲢����			?x
	void selectionSort(ListNode<T>*, int);//ѡ������			
	void insertionSort(ListNode<T>*, int);//��������	

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
void List<T>::init()//��ʼ��
{
	header = new ListNode<T>;//����д��������
	trailer = new ListNode<T>;
	header->succ = trailer;header->pred = trailer;//˫������ͷָβ
	trailer->succ = header;trailer->pred = header;
	_size = 0;
}

//���ص���ֵ
//����[],������Ϊr�Ľڵ��ֵ  !!!!!!
template <typename T>
ListNode<T>* List<T>::operator[] (Rank r)
{
	ListNode<T>* p = first();
	while (r-- > 0)
		p = p->succ;
	return p;
}

//�������б��еĽڵ�p��ǰn��ǰ���ڵ���Ѱ��e�����ص���e�ĺ���
template <typename T>
ListNode<T>* List<T>::find(T const& e, int n, ListNode<T>* p) const
{
	while (n-- > 0)
		//����ʹ�� while(n--) ��������ڲ�Ȼ���while�ж���� �𣿣�����
		if (e == (p = p->pred)->data) return p;
	return nullptr;//����nullptr
}

//!!!!!������ ListNode��!!!??
//ǰ����
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!�ص�
//ÿ�����ǵ�ǰ��������ԣ�û��Խ��
template <typename T>
ListNode<T>* ListNode<T>::insertAsPred(T const& e)
{
	//newһ���ڵ㣬ǰ��Ϊ��ǰ�����ǰ�������Ϊ��ǰ����ֵΪe
	ListNode<T>* x = new ListNode(e, pred, this);
	pred->succ = x;pred = x;
	return x;
}
//�����
template <typename T>
ListNode<T>* ListNode<T>::insertAsSucc(T const& e)
{
	ListNode<T>* x = new ListNode(e, this, succ);
	succ->pred = x;succ = x;
	return x;
}



//e��Ϊ�׽ڵ����
template <typename T>
ListNode<T>* List<T>::insertAsFirst(T const& e)
{
	_size++;
	return header->insertAsSucc(e);
}

//e��ĩ�ڵ����
template <typename T>
ListNode<T>* List<T>::insertAsLast(T const& e)
{
	_size++;
	return trailer->insertAsPred(e);
}

//e��Ϊp�ĺ�̲���
template <typename T>
ListNode<T>* List<T>::insertA(ListNode<T>* p, T const& e)
{
	_size++;	return p->insertAsSucc(e);
	//size����++
}

//e��Ϊp��ǰ������
template <typename T>
ListNode<T>* List<T>::insertB(ListNode<T>* p, T const& e)
{
	_size++;
	return p->insertAsPred(e);
}

//�½�һ���б�(init)���ڵ�Ϊ �ڵ�p�����n���ڵ�
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

//���c�б�����λ��p���n�assert: pΪ�Ϸ�λ�ã���������n-1����̽ڵ㣩
template<typename T>
List<T>::List(ListNode<T>* p, int n) { copyNodes(p, n); }

//���帴���б�
template<typename T>
List<T>::List(List<T> const& L)//������ const
{
	copyNodes(L.first(), L._size);
}

//����L���Ե�r�����n��
template<typename T>
List<T>::List(List<T> const& L, int r, int n)
{
	copyNodes(L[r], n);
}

//ɾ��
template<typename T>
T List<T>::remove(ListNode<T>* p)	//�������ô����p��������ֱ��pred
{
	T e = p->data;
	p->pred->succ = p->succ;
	p->succ->pred = p->pred;
	delete p;//��������Ҫdelete p����   ListNode��ɾ��
	_size--;
	return e;//���ر���ֵ
}

//�б�������
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
		remove(header->succ);//��ȥ������delete������Ҳ...
	return oldSize;
}

//�޳������б��аm�ظ��ڵ� , �����޳����� !!
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
	ListNode<T>* p = header->succ;  // ��ʼ��Ϊ��һ���ڵ�
	ListNode<T>* q = trailer->pred;       // ��ʼ��Ϊβ�ڵ�

	for(int i = 0;i < _size/2;i++)
	{
		std::swap(p->data, q->data);
		p = p->succ;
		q = q->pred;  // ����Ӧ��ʹ��β�ڵ��ǰ��
	}
}


//��������ʹ��һ���������������б��е�ֵ!!!!
//template <typename T>
//void List<T>::traverse(void (*visit)(T&))//!!!!!!
//{
//	for (ListNode<T>* p = header;(p = p->succ) != trailer;visit(p->data));
//}

//����һ�����󣬵������������
//ͨ�������������
template<typename T>	template<typename VST>
void List<T>::traverse(VST& visit)
{
	for (ListNode<T>* p = header->succ;p != trailer; p = p->succ) visit(p->data);
}


//������������,���ڰ��б���ÿ��ֵ��n
//template<typename T>
//struct visit
//{
//	void operator() (T& e, int n) const //!!!!������  ����const
//	{
//		return e *= n;
//	}
//};


//�����б��Ψһ��
template <typename T>
int List<T>::uniquify()
{
	int oldSize = _size;
	if (_size < 2) return 0;
	ListNode<T>* p = header, q;
	while ((q = p->succ) != trailer)
		if (q->data == p->data) remove(q);
		else p = q;//�ǵ�ǰ�� ��ȻҲ����p= p->succ;����sdֱ��p->succ
	return oldSize - _size;
}

//�����б�Ĳ���e,��p��������trailer����n����ǰ���в��ҵ�����, ������ָ��
// �����ҵ������ҵ�������e�ĺ��ߣ��������ڷ����Լ�����С�ڷ���ǰһ�ڵ�   P100
template <typename T>
ListNode<T>* List<T>::search(T const& e, int n, ListNode<T>* p) const//ÿ�ζ���const���ǵ��룡
{
	while (n-- > 0) {
		p = p->pred;
		if (p->data >= e)//��������ģ�
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

//�������� On2
//������ʼλ��p��n��Ԫ�����򣬣�����p��������������
//n = 1�������Լ������Լ�������ǰһֵ���棬Ȼ��λ������ƶ�����ɾ��ԭ�Լ�
template <typename T> //���б�����ʼ��λ��p�����Ϊn����������������
void List<T>::insertionSort(ListNode<T>* p, Rank n) { // valid(p) && Rank(p) + n <= size
	for (int r = 0; r < n; r++) { //��һΪ���ڵ�
		insertA(search(p->data, r, p), p->data); //�����ʵ���λ�ò�����
		p = p->succ; remove(p->pred); //ת����һ�ڵ�
	}
}



template <typename T> //�б�Ĺ鲢�����㷨������ʼ��λ��p��n��Ԫ������
void List<T>::mergeSort(ListNode<T>* & p, int n)  // valid(p) && Rank(p) + n <= size
{
	if (n < 2) return; //��������Χ���㹻С����ֱ�ӷ��أ�����...
	Rank m = n >> 1; //���е�Ϊ��
	ListNode<T>* q = p; for (int i = 0; i < m; i++) q = q->succ; //�ҵ������б����
	mergeSort(p, m); mergeSort(q, n - m); //ǰ�������б���ֱ�����
	p = merge(p, m, *this, q, n - m); //�鲢
} //ע�⣺�����p��Ȼָ��鲢������ģ��£����


//ѡ������
template <typename T>
void List<T>::selectionSort(ListNode<T>* p, int n)
{
	ListNode<T>* current = header;

	while (current != nullptr) {
		ListNode<T>* minNode = current;
		ListNode<T>* temp = current->succ;

		// �ҵ���С�ڵ�
		while (temp != nullptr) {
			if (temp->data < minNode->data) {
				minNode = temp;
			}
			temp = temp->succ;
		}

		// ��������
		int tempData = current->data;
		current->data = minNode->data;
		minNode->data = tempData;

		current = current->succ;
	}
}


//����ʼλ��pǰ�Լ���ǰn����ѡ�����ֵ
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

//�����б�Ĺ鲢����ǰ�б�����p���n��Ԫ�أ����б�L����q���m��Ԫ�ع鲢	?
template <typename T>
ListNode<T>* merge(ListNode<T>*& p, int n , List<T>& L, ListNode<T>* q, int m){
	// this.valid(p) && Rank(p) + n <= size && this.sorted(p, n)		?
	// L.valid(q) && Rank(q) + m <= L._size && L.sorted(q, m)			?
	// ע�⣺�ڱ�mergeSort()����ʱ��this == &L && Rank(p) + n = Rank(q)		?
	ListNode<T>* pp = p->pred; 
	while ((0 < m) && (q != p)) //q��δ���磨����mergeSort()�У�p����δ���磩֮ǰ
		if ((0 < n) && (p->data <= q->data)) //��p��δ������v(p) <= v(q)����
		{
			p = p->succ; n--;
		} //pֱ�Ӻ��ƣ�����ɹ���
		else //���򣬽�qת����p֮ǰ������ɹ���
		{
			insert(L.remove((q = q->succ)->pred), p); m--;
		}
	return pp->succ; //���µ��׽ڵ�
}
