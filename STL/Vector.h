#ifndef VECTOR_H
#define VECTOR_H
#include <iostream>
#include <algorithm>


typedef int Rank;//��
#define DEFAULT_CAPACITY 3//define���治Ҫ�ӷֺŰ�������������������������������������
	
template <typename T>
class Vector {

protected:
	Rank _size;int  _capacity;T* _elem;//��ģ , ���� ��ֵ
	void copyFrom(T const* A, int lo, int hi);//��������A[lo,hi]
	void expand();//����
	void shrink();	//ѹ��
	bool bubble(Rank lo, Rank hi);		//ɨ�轻��				x
	void bubbleSort(Rank lo, Rank hi);	//ð��					x
	Rank max(Rank lo, Rank hi); //ѡ���Ԫ��		
	void insertSort(int st, int end, int gap);
	void selectionSort(Rank lo, Rank hi); //ѡ������			
	void insertSort() { insertSort(0, _size - 1, 1); }
	void shellSort(int st, int ed);		//ϣ������
	void merge(Rank lo, Rank mi, Rank hi); //�鲢�㷨			x
	void mergeSort(Rank lo, Rank hi); //�鲢�����㷨				x
	Rank partition(Rank lo, Rank hi); //��㹹���㷨				x
	void quickSort(Rank lo, Rank hi); //���������㷨			x
	void heapSort(Rank lo, Rank hi); //������			x


public:

	//temp
	void shellSort1() { shellSort(0, _size); }


	//���캯��
	Vector(int c = DEFAULT_CAPACITY, Rank s = 0, T v = T()) {
		_elem = new T[_capacity = c];
		for (_size = 0; _size < s; _elem[_size++] = v) {
			// ��ѭ���г�ʼ��Ԫ��
		}
	}


	Vector(T const* A, Rank n) { copyFrom(A, 0, n); }//������������,���������������飬��ģ
	Vector(T const* A, Rank lo, Rank hi) { copyFrom(A, lo, hi); }//��������
	Vector(Vector<T> const& V) { copyFrom(V._elem, 0, V._size); }//�������帴�� !
	Vector(Vector<T> const& V, int lo, int hi) { copyFrom(V._elem, lo, hi); }
	//��������
	//~Vector() { delete[] _elem;_elem = nullptr;} //?????????????????????????????nm?????

	//ֻ�����ʽӿ�
	void info() const { std::cout << "capacity = " <<capacityOfVector() << "  size = " <<size(); }
	int capacityOfVector() const { return _capacity; }
	Rank size() const { return _size; }
	bool empty() const { return !_size; }
	int disordered() const;
	Rank find(T const& e) const { return find(e, 0, _size); }//���������������
	Rank find(T const& e, Rank lo, Rank hi) const;//ʧ�ܷ���lo-1
	Rank search(T const& e) const//���������������
	{ return( 0 >= _size ) ? -1 : search ( e, 0, _size ); }//	!!!
	Rank search ( T const& e, Rank lo, Rank hi ) const; 

	//��д���ʽӿ�
	T& operator[] (Rank r);//�����±������������������
	//vector<T>& operator= (vector<T> const&);//���ظ�ֵ
	T removeV(Rank r);//ɾ����Ϊr��Ԫ��
	int removeV(Rank lo, Rank hi);//ɾ������[lo,hi]��Ԫ��
	Rank insert(Rank r, T const& e);//����r�����e
	Rank insert(T const& e) { return insert(_size, e); }//Ĭ�ϲ���ĩβ
	void sort(Rank lo, Rank hi);//��������
	void sort() { sort(0, _size); }//��������
	void unsort(Rank lo, Rank hi);//����
	void unsort() { unsort(0, _size); }
	int deduplicate(); //����ȥ��
	int uniquify(); //����ȥ��
	void reverse();//��ת

	//����
	void traverse(void (*)(T&));//����ָ��
	template <typename VST> void  traverse(VST&);

	//�еȺͱȽ���
	//static���Բ�ʵ��������ʹ�ø�����ĺ��� �� vector::lt()
	//��һ�� ����Ϊ ��������ΪT �� ������ָ�룬������ָ������ָ��
	template <typename T> static bool lt(T* a, T* b) { return lt(*a, *b); }//С��
	template <typename T> static bool lt(T& a, T& b) { return a < b; }
	template <typename T> static bool eq(T* a, T* b) { return eq(*a, *b); }//����
	template <typename T> static bool eq(T& a, T& b) { return a == b; }

	void shellSort() { shellSort(0, _size); }
};





//����A[lo,hi]
template <typename T>
void Vector<T>::copyFrom(T const* A, Rank lo, Rank hi) {
	_elem = new T[_capacity = 2 * (hi - lo)];
	_size = 0; //!!!
	while (lo < hi) {
		_elem[_size++] = A[lo++];//������_elem[0,hi - lo]
	}
}

////���� = ���������帳ֵ
//template <typename T>
//vector<T>& vector<T>::operator= (vector<T> const& V) {
//	if (_elem) delete[] _elem;
//	copyFrom(V._elem, 0, V._size);//!!!
//	return *this;//?????
//}

//����
//��instertǰӦ����expand�����ö�һ���ж��Ƿ��Ѿ�����ĺ���
template <typename T>
void Vector<T>::expand() {
	if (_size < _capacity) return;//��������
	if (_capacity < DEFAULT_CAPACITY) _capacity = DEFAULT_CAPACITY;//��������С����
	T* oldElem = _elem;_elem = new T[_capacity <<= 1];//�����ӱ�����
	for (int i = 0;i < _size;i++)
		_elem[i] = oldElem[i];
	delete[] oldElem;//һ��Ҫ�� [] ����
	oldElem = nullptr;
}

//����
//װ�����ӹ�Сʱѹ��������ռ�ռ�
template <typename T>
void Vector<T>::shrink() {
	if (_capacity < DEFAULT_CAPACITY << 2) return;//Ĭ�ϲ�������DEFAULT_CAPACITY����
	if (_size << 2 > _capacity) return;//��װ������25%Ϊ�߽�  _size ����2λ ������4
	T* oldElem = _elem;_elem = new T[_capacity >> 1];//������
	for (int i = 0;i < _size;i++)
		_elem[i] = oldElem[i];
	delete[] oldElem;
}

//����[],ֱ������
template <typename T>
T& Vector<T>::operator[] (Rank r){ //const
	return _elem[r];//
}

//������
template <typename T>
void Vector<T>::unsort(Rank lo, Rank hi) {
	T* V = _elem + lo;//ʹ��T[0] = _elem[lo]
	for (Rank i = hi - lo;i > 0;i--) {
		std::swap(V[i - 1], V[rand() % 1]);
	}
}

//�������:˳����� ����[lo,hi]e���±�
//ʧ�ܷ���lo - 1
template <typename T>
Rank Vector<T>::find(T const& e, Rank lo, Rank hi) const {
	//!!!const��������Ҫ���ҵ�ֵ�Ҳ����ģ��󲻸�Vectorֵ
	while ((lo < hi--) && (_elem[hi] != e));//!!!!!!!!
	return hi;
}

//����
//���ز����Rank
template <typename T>
Rank Vector<T>::insert(Rank r, T const& e) {
	expand();
	for (int i = _size;i > r;i--)_elem[i] = _elem[i - 1];//_size = 3,0,1,2
	_elem[r] = e; _size++;//size
	return r;
}

//ɾ�� ����[lo,hi)
//����ɾ���ĸ���int
//ɾ����������������ɾ��������
template <typename T>
int Vector<T>::removeV(Rank lo, Rank hi) {
	if (lo == hi) return 0;//Ч�ʿ��ǵ�������
	while (hi < _size) _elem[lo++] = _elem[hi++];//!!!!!
	_size = lo; //!!!!!
	shrink();
	return hi - lo;
}

//ɾ�����������ر�ɾ��Ԫ�ص�ֵ
template <typename T>
T Vector<T>::removeV(Rank r) {
	T e = _elem[r];//����e�����ڷ���
	removeV(r, r + 1);
	return e;
}

//Ψһ��(ȥ��
//���ر�ɾ��Ԫ�ظ���int
template <typename T>
int Vector<T>::deduplicate() {
	int oldSize = _size;
	Rank i = 1;
	while (i < _size)
		find(_elem[i], 0, i) < 0 ?
		i++ : removeV(i);
	return oldSize - _size;
}

//���������ӿ�:����ָ��
template <typename T>
void Vector<T>::traverse(void (*visit)(T&)) {
	for (int i = 0;i < _size;i++) visit(_elem[i]);
}
template <typename T> template <typename VST>
void Vector<T>::traverse(VST& visit) {
	for (int i = 0;i < _size;i++) visit(_elem[i]);
}

//������ʵ��
template <typename T>
struct Increase {
	virtual void operator() (T& e) { e++; }
};

template <typename T>
void increase(Vector<T>& V) {
	V.traverse(Increase<T>());
}

//���������
//��������Ը���
template <typename T>
int Vector<T>::disordered() const {
	int n = 0;
	for (int i = 1;i < _size;i++)
		if (_elem[i] < _elem[i - 1])  n++;
	return n;
}

//���������Ψһ��
//����ɾ������
//�����ʹ������ʱ��uniquify��ʱ�临�Ӷ�û�Ż���Ҫ��취�õ�������
//�����uniquify��Ҫ��ʱ���� ����ÿ��Ԫ�صĺ�ÿ����һ���ظ���removeһ�Σ�����
template <typename T>
int Vector<T>::uniquify() {
	Rank i = 0, j = 0;
	while (++j < _size) {
		if (_elem[i] != _elem[j])
			_elem[++i] = _elem[j];
	}
	_size = ++i;shrink();//����
	return j - i;
}
//��ת
template<typename T>
void Vector<T>::reverse()
{
	int lo = 0, hi = _size - 1;
	while (lo < hi)
	{
		std::swap(_elem[lo], _elem[hi]);
		lo++;hi--;
	}
}

//�������� ����
//Ϊ���������������Ĳ��ҽӿ�find()�����������Ĳ��ҽӿڽ�ͳһ����Ϊsearch()
template <typename T>
Rank Vector<T>::search(T const& e, Rank lo, Rank hi) const {
	return(rand() % 2) ? binSearch(_elem, e, lo, hi) : fibSearch(_elem, e, lo, hi);
}

//���ֲ��� binSearch  ����[lo,hi)
//�ɹ�����Ŀ���ȣ�ʧ��-1
//log2 n;
template <typename T>
static Rank binSearch(T* A, T const& e, Rank lo, Rank hi) {
	while (lo < hi) {
		T* mid = (lo + hi) >> 1;//����
		if (e < A[mid]) mid = hi;
		else if (e > A[mid]) mid = lo;
		else return mid;
	}
	return -1;
}
//�����㷨�ܴ�̶�ȡ���ڱȽϵĴ�������ͬ�������ͼ�Ƚ�ʱ������кܴ�Ĳ�ࣨ�ַ����Ƚϣ�

//Fibonacci



template<typename T>
inline void Vector<T>::insertSort(int st, int end, int gap)
{
	for (int i = st + gap; i < end; i += gap) {
		for (int j = i; j > st; j -= gap)
			if (_elem[j] < _elem[j - gap]) std::swap(_elem[j], _elem[j - gap]);
			else break;
	}
}

template<typename T>
inline void Vector<T>::selectionSort(Rank lo, Rank hi)
{
	int n = _size;

	for (int i = 0; i < n - 1; i++) {
		int minIndex = i;
		for (int j = i + 1; j < n; ++j) {
			if (_elem[j] < _elem[minIndex]) {
				minIndex = j;
			}
		}
		std::swap(_elem[i], _elem[minIndex]);
	}

}

//ϣ������
template<typename T>
inline void Vector<T>::shellSort(int st, int ed)
{
	for (int gap = ed - st; gap; gap /= 2)
		for (int i = 0; i < gap; i++)
			insertSort(st + i, ed, gap);
}



#endif //VECTOR_H
