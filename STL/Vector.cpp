//#include "vector.h"
//
//template <typename T>
//void vector<T>::connection()
//{
//	vector<int> i;
//}
//
////复制A[lo,hi]
//template <typename T>
//void vector<T>::copyFrom(T const* A, Rank lo, Rank hi) {
//	_elem = new T[_capacity = 2 * (hi - lo)];
//	_size = 0; //!!!
//	while (lo < hi) {
//		_elem[_size++] = A[lo++];//复制至_elem[0,hi - lo]
//	}
//}
//
////重载 = ，用于整体赋值
//template <typename T>
//vector<T>& vector<T>::operator= (vector<T> const& V) {
//	if (_elem) delete[] _elem;
//	copyFrom(V._elem, 0, V._size);//!!!
//	return *this;//?????
//}
//
////扩容
////在instert前应调用expand，不用多一个判断是否已经更大的函数
//template <typename T>
//void vector<T>::expand() {
//	if (_size < _capacity) return;//无需扩容
//	if (_capacity < DEFAULT_CAPACITY) _capacity = DEFAULT_CAPACITY;//不低于最小容量
//	T* oldElem = _elem;_elem = new T[_capacity <<= 1];//容量加倍！！
//	for (int i = 0;i < _size;i++)
//		_elem[i] = oldElem[i];
//	delete[] oldElem;//一定要带 [] ！！
//}
//
////缩容
////装填因子过小时压缩向量所占空间
//template <typename T>
//void vector<T>::shrink() {
//	if (_capacity < DEFAULT_CAPACITY << 2) return;//默认不收缩至DEFAULT_CAPACITY以内
//	if (_size << 2 > _capacity) return;//填装因子以25%为边界  _size 左移2位 ，即×4
//	T* oldElem = _elem;_elem = new T[_capacity >> 1];//用右移
//	for (int i = 0;i < _size;i++)
//		_elem[i] = oldElem[i];
//	delete[] oldElem;
//}
//
////重载[],直接引用
//template <typename T>
//T& vector<T>::operator[] (Rank r) const { //别忘了const ???!
//	return _elem[r];//_elem是个数组，别忘了！ 
//}
//
////置乱器
//template <typename T>
//void vector<T>::unsort(Rank lo, Rank hi) {
//	T* V = _elem + lo;//使用T[0] = _elem[lo]
//	for (Rank i = hi - lo;i > 0;i--) {
//		swap(V[i - 1], V[rand() % 1]);
//	}
//}
//
////无序查找:顺序查找 区间[lo,hi]是否存在e
////失败返回lo - 1,从后往前为此？
//template <typename T>
//Rank vector<T>::find(T const& e, Rank lo, Rank hi) const {
//	//!!!const用于引用要查找的值且不更改，后不改Vector值
//	while ((lo < hi--) && (_elem[hi] != e));//!!!!!!!!
//	return hi;
//}
//
////插入
////返回插入的Rank
//template <typename T>
//Rank vector<T>::insert(Rank r, T const& e) {
//	expand();
//	for (int i = _size;i > r;i--)_elem[i] = _elem[i - 1];//_size = 3,0,1,2
//	_elem[r] = e; _size++;//别忘了size大了
//	return r;
//}
//
////删除 区间[lo,hi)
////返回删除的个数int
////删除单个反而是区间删除的特例
//template <typename T>
//int vector<T>::removeV(Rank lo, Rank hi) {
//	if (lo == hi) return 0;//效率考虑单独处理
//	while (hi < _size) _elem[lo++] = _elem[hi++];//!!!!!
//	_size = lo; //!!!!!
//	shrink();
//	return hi - lo;
//}
//
////删除单个，返回被删除元素的值
//template <typename T>
//T vector<T>::removeV(Rank r) {
//	T e = _elem[r];//备份e，用于返回
//	removeV(r, r + 1);
//	return e;
//}
//
////唯一化
////返回被删除元素个数int
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
////遍历操作接口:函数指针
//template <typename T>
//void vector<T>::traverse(void (*visit)(T&)) {
//	for (int i = 0;i < _size;i++) visit(_elem[i]);
//}
//template <typename T> template <typename VST>
//void vector<T>::traverse(VST& visit) {
//	for (int i = 0;i < _size;i++) visit(_elem[i]);
//}
//
////..??!!!???遍历的实例
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
////有序性甄别
////返回逆序对个数
//template <typename T>
//int vector<T>::disordered() const {
//	int n = 0;
//	for (int i = 1;i < _size;i++)
//		if (_elem[i] < _elem[i - 1])  n++;
//	return n;
//}
//
////有序数组的唯一化
////返回删除个数
////如果仍使用无序时的uniquify，时间复杂度没优化，要想办法用到有序性
////无序的uniquify主要费时在于 遍历每个元素的后每遇到一个重复就remove一次，所以
////!!!
//template <typename T>
//int vector<T>::uniquify() {
//	Rank i = 0, j = 0;
//	while (++j < _size) {
//		if (_elem[i] != _elem[j])
//			_elem[++i] = _elem[j];
//	}
//	_size = ++i;shrink();//别忘
//	return j - i;
//}
//
////有序数组 查找
////为区别于无序向量的查找接口find()，有序向量的查找接口将统一命名为search()
//template <typename T>
//Rank vector<T>::search(T const& e, Rank lo, Rank hi) const {
//	return(rand() % 2) ? binSearch(_elem, e, lo, hi) : fibSearch(_elem, e, lo, hi);
//	//!!!
//}
//
////二分查找 binSearch  查找[lo,hi)
////!!!参数是 T* 而不是 T&（不修改）  ； 也不是 vector<T> (static，尽量通用)
////成功返回目标秩，失败-1
////复杂度：因为每次都会减少一半，所以log2 n;
//template <typename T>
//static Rank binSearch(T* A, T const& e, Rank lo, Rank hi) {
//	while (lo < hi) {
//		T* mid = (lo + hi) >> 1;//右移
//		if (e < A[mid]) mid = hi;
//		else if (e > A[mid]) mid = lo;
//		else return mid;
//	}
//	return -1;
//}
////查找算法很大程度取决于比较的次数，不同数据类型间比较时间可以有很大的差距（字符串比较）
////为此需要确定 查找长度，如对于search（A，0，7)中， 详见笔记本
//
////Fibonacci
////不会！！！没写！！
//
//
