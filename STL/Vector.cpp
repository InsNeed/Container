//#include "vector.h"
//
//template <typename T>
//void vector<T>::connection()
//{
//	vector<int> i;
//}
//
////����A[lo,hi]
//template <typename T>
//void vector<T>::copyFrom(T const* A, Rank lo, Rank hi) {
//	_elem = new T[_capacity = 2 * (hi - lo)];
//	_size = 0; //!!!
//	while (lo < hi) {
//		_elem[_size++] = A[lo++];//������_elem[0,hi - lo]
//	}
//}
//
////���� = ���������帳ֵ
//template <typename T>
//vector<T>& vector<T>::operator= (vector<T> const& V) {
//	if (_elem) delete[] _elem;
//	copyFrom(V._elem, 0, V._size);//!!!
//	return *this;//?????
//}
//
////����
////��instertǰӦ����expand�����ö�һ���ж��Ƿ��Ѿ�����ĺ���
//template <typename T>
//void vector<T>::expand() {
//	if (_size < _capacity) return;//��������
//	if (_capacity < DEFAULT_CAPACITY) _capacity = DEFAULT_CAPACITY;//��������С����
//	T* oldElem = _elem;_elem = new T[_capacity <<= 1];//�����ӱ�����
//	for (int i = 0;i < _size;i++)
//		_elem[i] = oldElem[i];
//	delete[] oldElem;//һ��Ҫ�� [] ����
//}
//
////����
////װ�����ӹ�Сʱѹ��������ռ�ռ�
//template <typename T>
//void vector<T>::shrink() {
//	if (_capacity < DEFAULT_CAPACITY << 2) return;//Ĭ�ϲ�������DEFAULT_CAPACITY����
//	if (_size << 2 > _capacity) return;//��װ������25%Ϊ�߽�  _size ����2λ ������4
//	T* oldElem = _elem;_elem = new T[_capacity >> 1];//������
//	for (int i = 0;i < _size;i++)
//		_elem[i] = oldElem[i];
//	delete[] oldElem;
//}
//
////����[],ֱ������
//template <typename T>
//T& vector<T>::operator[] (Rank r) const { //������const ???!
//	return _elem[r];//_elem�Ǹ����飬�����ˣ� 
//}
//
////������
//template <typename T>
//void vector<T>::unsort(Rank lo, Rank hi) {
//	T* V = _elem + lo;//ʹ��T[0] = _elem[lo]
//	for (Rank i = hi - lo;i > 0;i--) {
//		swap(V[i - 1], V[rand() % 1]);
//	}
//}
//
////�������:˳����� ����[lo,hi]�Ƿ����e
////ʧ�ܷ���lo - 1,�Ӻ���ǰΪ�ˣ�
//template <typename T>
//Rank vector<T>::find(T const& e, Rank lo, Rank hi) const {
//	//!!!const��������Ҫ���ҵ�ֵ�Ҳ����ģ��󲻸�Vectorֵ
//	while ((lo < hi--) && (_elem[hi] != e));//!!!!!!!!
//	return hi;
//}
//
////����
////���ز����Rank
//template <typename T>
//Rank vector<T>::insert(Rank r, T const& e) {
//	expand();
//	for (int i = _size;i > r;i--)_elem[i] = _elem[i - 1];//_size = 3,0,1,2
//	_elem[r] = e; _size++;//������size����
//	return r;
//}
//
////ɾ�� ����[lo,hi)
////����ɾ���ĸ���int
////ɾ����������������ɾ��������
//template <typename T>
//int vector<T>::removeV(Rank lo, Rank hi) {
//	if (lo == hi) return 0;//Ч�ʿ��ǵ�������
//	while (hi < _size) _elem[lo++] = _elem[hi++];//!!!!!
//	_size = lo; //!!!!!
//	shrink();
//	return hi - lo;
//}
//
////ɾ�����������ر�ɾ��Ԫ�ص�ֵ
//template <typename T>
//T vector<T>::removeV(Rank r) {
//	T e = _elem[r];//����e�����ڷ���
//	removeV(r, r + 1);
//	return e;
//}
//
////Ψһ��
////���ر�ɾ��Ԫ�ظ���int
////!!!	
//template <typename T>
//int vector<T>::deduplicate() {
//	int oldSize = _size;
//	Rank i = 1;
//	while (i < _size)
//		find(_elem[i], 0, i) < 0 ?
//		i++ : removeV(i);
//	return oldSize - _size;
//}
//
////���������ӿ�:����ָ��
//template <typename T>
//void vector<T>::traverse(void (*visit)(T&)) {
//	for (int i = 0;i < _size;i++) visit(_elem[i]);
//}
//template <typename T> template <typename VST>
//void vector<T>::traverse(VST& visit) {
//	for (int i = 0;i < _size;i++) visit(_elem[i]);
//}
//
////..??!!!???������ʵ��
//template <typename T>
//struct Increase {
//	virtual void operator() (T& e) { e++; }
//};
//
//template <typename T>
//void increase(vector<T>& V) {
//	V.traverse(Increase<T>());
//}
//
////���������
////��������Ը���
//template <typename T>
//int vector<T>::disordered() const {
//	int n = 0;
//	for (int i = 1;i < _size;i++)
//		if (_elem[i] < _elem[i - 1])  n++;
//	return n;
//}
//
////���������Ψһ��
////����ɾ������
////�����ʹ������ʱ��uniquify��ʱ�临�Ӷ�û�Ż���Ҫ��취�õ�������
////�����uniquify��Ҫ��ʱ���� ����ÿ��Ԫ�صĺ�ÿ����һ���ظ���removeһ�Σ�����
////!!!
//template <typename T>
//int vector<T>::uniquify() {
//	Rank i = 0, j = 0;
//	while (++j < _size) {
//		if (_elem[i] != _elem[j])
//			_elem[++i] = _elem[j];
//	}
//	_size = ++i;shrink();//����
//	return j - i;
//}
//
////�������� ����
////Ϊ���������������Ĳ��ҽӿ�find()�����������Ĳ��ҽӿڽ�ͳһ����Ϊsearch()
//template <typename T>
//Rank vector<T>::search(T const& e, Rank lo, Rank hi) const {
//	return(rand() % 2) ? binSearch(_elem, e, lo, hi) : fibSearch(_elem, e, lo, hi);
//	//!!!
//}
//
////���ֲ��� binSearch  ����[lo,hi)
////!!!������ T* ������ T&�����޸ģ�  �� Ҳ���� vector<T> (static������ͨ��)
////�ɹ�����Ŀ���ȣ�ʧ��-1
////���Ӷȣ���Ϊÿ�ζ������һ�룬����log2 n;
//template <typename T>
//static Rank binSearch(T* A, T const& e, Rank lo, Rank hi) {
//	while (lo < hi) {
//		T* mid = (lo + hi) >> 1;//����
//		if (e < A[mid]) mid = hi;
//		else if (e > A[mid]) mid = lo;
//		else return mid;
//	}
//	return -1;
//}
////�����㷨�ܴ�̶�ȡ���ڱȽϵĴ�������ͬ�������ͼ�Ƚ�ʱ������кܴ�Ĳ�ࣨ�ַ����Ƚϣ�
////Ϊ����Ҫȷ�� ���ҳ��ȣ������search��A��0��7)�У� ����ʼǱ�
//
////Fibonacci
////���ᣡ����ûд����
//
//
