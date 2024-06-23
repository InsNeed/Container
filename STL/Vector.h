#ifndef VECTOR_H
#define VECTOR_H
#include <iostream>
#include <algorithm>


typedef int Rank;//秩
#define DEFAULT_CAPACITY 3//define后面不要加分号啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊
	
template <typename T>
class Vector {

protected:
	Rank _size;int  _capacity;T* _elem;//规模 , 容量 ，值
	void copyFrom(T const* A, int lo, int hi);//复制区间A[lo,hi]
	void expand();//扩容
	void shrink();	//压缩
	bool bubble(Rank lo, Rank hi);		//扫描交换				x
	void bubbleSort(Rank lo, Rank hi);	//冒泡					x
	Rank max(Rank lo, Rank hi); //选最大元素		
	void insertSort(int st, int end, int gap);
	void selectionSort(Rank lo, Rank hi); //选择排序			
	void insertSort() { insertSort(0, _size - 1, 1); }
	void shellSort(int st, int ed);		//希尔排序
	void merge(Rank lo, Rank mi, Rank hi); //归并算法			x
	void mergeSort(Rank lo, Rank hi); //归并排序算法				x
	Rank partition(Rank lo, Rank hi); //轴点构造算法				x
	void quickSort(Rank lo, Rank hi); //快速排序算法			x
	void heapSort(Rank lo, Rank hi); //堆排序			x


public:

	//temp
	void shellSort1() { shellSort(0, _size); }


	//构造函数
	Vector(int c = DEFAULT_CAPACITY, Rank s = 0, T v = T()) {
		_elem = new T[_capacity = c];
		for (_size = 0; _size < s; _elem[_size++] = v) {
			// 在循环中初始化元素
		}
	}


	Vector(T const* A, Rank n) { copyFrom(A, 0, n); }//复制整个数组,参数：被复制数组，规模
	Vector(T const* A, Rank lo, Rank hi) { copyFrom(A, lo, hi); }//复制区间
	Vector(Vector<T> const& V) { copyFrom(V._elem, 0, V._size); }//向量整体复制 !
	Vector(Vector<T> const& V, int lo, int hi) { copyFrom(V._elem, lo, hi); }
	//析构函数
	//~Vector() { delete[] _elem;_elem = nullptr;} //?????????????????????????????nm?????

	//只读访问接口
	void info() const { std::cout << "capacity = " <<capacityOfVector() << "  size = " <<size(); }
	int capacityOfVector() const { return _capacity; }
	Rank size() const { return _size; }
	bool empty() const { return !_size; }
	int disordered() const;
	Rank find(T const& e) const { return find(e, 0, _size); }//无序向量整体查找
	Rank find(T const& e, Rank lo, Rank hi) const;//失败返回lo-1
	Rank search(T const& e) const//有序向量整体查找
	{ return( 0 >= _size ) ? -1 : search ( e, 0, _size ); }//	!!!
	Rank search ( T const& e, Rank lo, Rank hi ) const; 

	//可写访问接口
	T& operator[] (Rank r);//重载下标用于类似数组的引用
	//vector<T>& operator= (vector<T> const&);//重载赋值
	T removeV(Rank r);//删除秩为r的元素
	int removeV(Rank lo, Rank hi);//删除秩在[lo,hi]的元素
	Rank insert(Rank r, T const& e);//在秩r后插入e
	Rank insert(T const& e) { return insert(_size, e); }//默认插入末尾
	void sort(Rank lo, Rank hi);//区间排序
	void sort() { sort(0, _size); }//整体排序
	void unsort(Rank lo, Rank hi);//打乱
	void unsort() { unsort(0, _size); }
	int deduplicate(); //无序去重
	int uniquify(); //有序去重
	void reverse();//翻转

	//遍历
	void traverse(void (*)(T&));//函数指针
	template <typename VST> void  traverse(VST&);

	//判等和比较器
	//static可以不实例化对象，使用该类里的函数 如 vector::lt()
	//第一个 参数为 数据类型为T 的 变量的指针，而不是指向对象的指针
	template <typename T> static bool lt(T* a, T* b) { return lt(*a, *b); }//小于
	template <typename T> static bool lt(T& a, T& b) { return a < b; }
	template <typename T> static bool eq(T* a, T* b) { return eq(*a, *b); }//等于
	template <typename T> static bool eq(T& a, T& b) { return a == b; }

	void shellSort() { shellSort(0, _size); }
};





//复制A[lo,hi]
template <typename T>
void Vector<T>::copyFrom(T const* A, Rank lo, Rank hi) {
	_elem = new T[_capacity = 2 * (hi - lo)];
	_size = 0; //!!!
	while (lo < hi) {
		_elem[_size++] = A[lo++];//复制至_elem[0,hi - lo]
	}
}

////重载 = ，用于整体赋值
//template <typename T>
//vector<T>& vector<T>::operator= (vector<T> const& V) {
//	if (_elem) delete[] _elem;
//	copyFrom(V._elem, 0, V._size);//!!!
//	return *this;//?????
//}

//扩容
//在instert前应调用expand，不用多一个判断是否已经更大的函数
template <typename T>
void Vector<T>::expand() {
	if (_size < _capacity) return;//无需扩容
	if (_capacity < DEFAULT_CAPACITY) _capacity = DEFAULT_CAPACITY;//不低于最小容量
	T* oldElem = _elem;_elem = new T[_capacity <<= 1];//容量加倍！！
	for (int i = 0;i < _size;i++)
		_elem[i] = oldElem[i];
	delete[] oldElem;//一定要带 [] ！！
	oldElem = nullptr;
}

//缩容
//装填因子过小时压缩向量所占空间
template <typename T>
void Vector<T>::shrink() {
	if (_capacity < DEFAULT_CAPACITY << 2) return;//默认不收缩至DEFAULT_CAPACITY以内
	if (_size << 2 > _capacity) return;//填装因子以25%为边界  _size 左移2位 ，即×4
	T* oldElem = _elem;_elem = new T[_capacity >> 1];//用右移
	for (int i = 0;i < _size;i++)
		_elem[i] = oldElem[i];
	delete[] oldElem;
}

//重载[],直接引用
template <typename T>
T& Vector<T>::operator[] (Rank r){ //const
	return _elem[r];//
}

//置乱器
template <typename T>
void Vector<T>::unsort(Rank lo, Rank hi) {
	T* V = _elem + lo;//使用T[0] = _elem[lo]
	for (Rank i = hi - lo;i > 0;i--) {
		std::swap(V[i - 1], V[rand() % 1]);
	}
}

//无序查找:顺序查找 区间[lo,hi]e的下标
//失败返回lo - 1
template <typename T>
Rank Vector<T>::find(T const& e, Rank lo, Rank hi) const {
	//!!!const用于引用要查找的值且不更改，后不改Vector值
	while ((lo < hi--) && (_elem[hi] != e));//!!!!!!!!
	return hi;
}

//插入
//返回插入的Rank
template <typename T>
Rank Vector<T>::insert(Rank r, T const& e) {
	expand();
	for (int i = _size;i > r;i--)_elem[i] = _elem[i - 1];//_size = 3,0,1,2
	_elem[r] = e; _size++;//size
	return r;
}

//删除 区间[lo,hi)
//返回删除的个数int
//删除单个反而是区间删除的特例
template <typename T>
int Vector<T>::removeV(Rank lo, Rank hi) {
	if (lo == hi) return 0;//效率考虑单独处理
	while (hi < _size) _elem[lo++] = _elem[hi++];//!!!!!
	_size = lo; //!!!!!
	shrink();
	return hi - lo;
}

//删除单个，返回被删除元素的值
template <typename T>
T Vector<T>::removeV(Rank r) {
	T e = _elem[r];//备份e，用于返回
	removeV(r, r + 1);
	return e;
}

//唯一化(去重
//返回被删除元素个数int
template <typename T>
int Vector<T>::deduplicate() {
	int oldSize = _size;
	Rank i = 1;
	while (i < _size)
		find(_elem[i], 0, i) < 0 ?
		i++ : removeV(i);
	return oldSize - _size;
}

//遍历操作接口:函数指针
template <typename T>
void Vector<T>::traverse(void (*visit)(T&)) {
	for (int i = 0;i < _size;i++) visit(_elem[i]);
}
template <typename T> template <typename VST>
void Vector<T>::traverse(VST& visit) {
	for (int i = 0;i < _size;i++) visit(_elem[i]);
}

//遍历的实例
template <typename T>
struct Increase {
	virtual void operator() (T& e) { e++; }
};

template <typename T>
void increase(Vector<T>& V) {
	V.traverse(Increase<T>());
}

//有序性甄别
//返回逆序对个数
template <typename T>
int Vector<T>::disordered() const {
	int n = 0;
	for (int i = 1;i < _size;i++)
		if (_elem[i] < _elem[i - 1])  n++;
	return n;
}

//有序数组的唯一化
//返回删除个数
//如果仍使用无序时的uniquify，时间复杂度没优化，要想办法用到有序性
//无序的uniquify主要费时在于 遍历每个元素的后每遇到一个重复就remove一次，所以
template <typename T>
int Vector<T>::uniquify() {
	Rank i = 0, j = 0;
	while (++j < _size) {
		if (_elem[i] != _elem[j])
			_elem[++i] = _elem[j];
	}
	_size = ++i;shrink();//别忘
	return j - i;
}
//翻转
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

//有序数组 查找
//为区别于无序向量的查找接口find()，有序向量的查找接口将统一命名为search()
template <typename T>
Rank Vector<T>::search(T const& e, Rank lo, Rank hi) const {
	return(rand() % 2) ? binSearch(_elem, e, lo, hi) : fibSearch(_elem, e, lo, hi);
}

//二分查找 binSearch  查找[lo,hi)
//成功返回目标秩，失败-1
//log2 n;
template <typename T>
static Rank binSearch(T* A, T const& e, Rank lo, Rank hi) {
	while (lo < hi) {
		T* mid = (lo + hi) >> 1;//右移
		if (e < A[mid]) mid = hi;
		else if (e > A[mid]) mid = lo;
		else return mid;
	}
	return -1;
}
//查找算法很大程度取决于比较的次数，不同数据类型间比较时间可以有很大的差距（字符串比较）

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

//希尔排序
template<typename T>
inline void Vector<T>::shellSort(int st, int ed)
{
	for (int gap = ed - st; gap; gap /= 2)
		for (int i = 0; i < gap; i++)
			insertSort(st + i, ed, gap);
}



#endif //VECTOR_H
