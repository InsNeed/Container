#ifndef BINTREE_H
#define BINTREE_H


/*
	完全二叉树规模应该介于2^h至2^(h+1) - 1
*/


//构造哈夫曼树
//BinNode<char>* te;
//BinTree<char> huffTree;
//te = huffTree.insertAsRoot('A');te->fred = 20;//构造树
//te = huffTree.insertAsLC(huffTree.root(), 'B');te->fred = 30;
//BinNode<char>* n2 = huffTree.insertAsRC(huffTree.root(), 'C');n2->fred = 10;
//auto ptr = node->insertAsLc('D');ptr->fred = 5;
//ptr = node->insertAsRc('E');ptr->fred = 35;
//// 此时树： A(B,C(D,E));
////权值	20,30,10,5,35


//BinTree<char>* hufTree = BinTreeUse::buildHuffmanTree<char>(&huffTree);
//travPre_R(hufTree->root(), visitT2);//递归版先序遍历
//std::cout << '\n';

#include "BinNode.h"
#include "Stack.h"
#include "Vector.h"

#define stature(p) ((p) ? (p)->height : -1)//!!!

template <typename T>
class BinTree {
protected:
	int _size;BinNode<T>* _root;
	virtual int updateHeight(BinNode<T>* x);//更新节点x的坐标  
	void updateHeightAbove(BinNode<T>* x); //更新节点x及其祖先高度)
	void release(BinNode<T>* x);
public:
	BinTree() : _size(0), _root(NULL) { } //构造函数

	~BinTree() {if (0 < _size)  remove(_root);}
	//只读
	int sizeOfBinTree() const { return _size; }//大小
	bool empty() const { return !_root; }//判空 ??!
	BinNode<T>* root() const { return _root; }//树根
	//可写
	BinNode<T>* insertAsRoot(T const& e);//插入根节点
	BinNode<T>* insertAsRoot(T const& e, int fred);//插入根节点

	BinNode<T>* insertAsLC(BinNode<T>* x, T const& e);//e作为x的左孩子(原无)插入
	BinNode<T>* insertAsRC(BinNode<T>* x, T const& e);//e作为x的右孩子(原无)插入
	// 指针的引用

	BinNode<T>* attachAsLC(BinNode<T>* x,BinTree<T>* &tree);//tree作为x左子树接入
	BinNode<T>* attachAsRC(BinNode<T>* x,BinTree<T>* &tree);//tree作为x右子树接入
	int remove(BinNode<T>* x);
	BinTree<T>* secede(BinNode<T>* x);//将子树从当前树提出并转换成一个独立的树

	//分别释放节点和树
	void releaseTree(BinTree<T>*& tree);
	void releaseNode(BinNode<T>*& x);

	
	//遍历

	//比较器
	bool operator< (BinTree<T> const& t) {
		return _root && t.root && lt(_root, t._root);
	}
	bool operator== (BinTree<T> const& t) {
		return _root && t.root && eq(_root, t._root);
	}

	// 哈夫曼树！！！！！！！！！！！！！！！！
};//BINTREE   






//更新节点高度，返回高度
template <typename T>
int BinTree<T>::updateHeight(BinNode<T>* x)
{
	return x->height = 1 + std::max(stature(x->lc), stature(x->rc));
}

//更新节点及以上的高度
template<typename T> 
void BinTree<T>::updateHeightAbove(BinNode<T>* x)
{
	while (x) { updateHeight(x);x = x->parent; }
}

//将e作为空树的根节点,返回指向该节点的指针
template<typename T>
BinNode<T>* BinTree<T>::insertAsRoot(T const& e)
{
	_size = 1;
	return _root = new BinNode<T>(e);//!!!!
}


//将e作为空树的根节点,返回指向该节点的指针  huff
template<typename T>
BinNode<T>* BinTree<T>::insertAsRoot(T const& e,int fred)
{
	_size = 1;
	return _root = new BinNode<T>(e,fred);//!!!!
}
//将e作为 无左孩子节点 的左孩子插入,返回指向节点new的左孩子的指针
template<typename T> 
BinNode<T>* BinTree<T>::insertAsLC(BinNode<T>* x, T const& e)
{
	_size++;//别忘
	x->insertAsLc(e);//是x->而不是直接insert
	updateHeightAbove(x);//记得更新高度
	return x->lc;
}

//将e作为 无左孩子节点 的左孩子插入,返回指向节点new的左孩子的指针
template<typename T> 
BinNode<T>* BinTree<T>::insertAsRC(BinNode<T>* x, T const& e)
{
	_size++;
	x->insertAsRc(e);
	updateHeightAbove(x);
	return x->rc;
}

//释放树的空间
template<typename T>
void BinTree<T>::releaseTree(BinTree<T>*& tree) {
	if (tree) {
		release(tree->_root);  
		delete tree;         
		tree = nullptr;        // 将指针置为空
	}
}

//释放节点空间
template<typename T>
void  BinTree<T>::releaseNode(BinNode<T>*& x) {
	if (!x) {//x为空指针
		return;
	}

	release(x->lc);  
	release(x->rc);  
	delete x;        
	x = nullptr;      // 将指针置为空
}


//将tree当作 无左孩子节点x 的左子树插入，S本身置空，返回 ！接入位置！
//!!!!!!!
template <typename T>//参数居然是tree的指针的引用！？？
BinNode<T>* BinTree<T>::attachAsLC(BinNode<T>* x, BinTree<T>*& tree)
{
	//!!!!!!!!!!!!!
	//下面代码用于判断tree是否为空树，防止对空树进行操作
	/*delete tree 将释放 tree 指针指向的内存，
	这意味着 tree 对象本身会被销毁，包括 tree 对象的成员和数据成员。
	但这不会影响 tree 中的节点
	因为节点是通过指针相互连接的，而不是存储在 tree 对象本身内部的。*/
	if (x->lc = tree->_root) x->lc->parent = x;//接入
	_size += tree->_size;updateHeightAbove(x);//更新size和全树高度
	delete tree;//置空S，这么写吗？
	return x;
}

//将tree作为 无右孩子节点x 的右子树插入，S本身置空，返回接入位置
template <typename T>
BinNode<T>* BinTree<T>::attachAsRC(BinNode<T>* x, BinTree<T>*& tree)
{
	if (x->lc = tree->_root) x->lc.parent = x;
	_size += tree->_size;updateHeightAbove(x);
	delete tree;
	return x;
}

//删除子树并返回删除的个数
template <typename T>
int BinTree<T>::remove(BinNode<T>* x)//assert: x为树中合法位置
{
	FromParentTo(*x) = NULL;//x解引用 切断来自父亲节点的指针
	updateHeightAbove(x->parent);//更新 !祖先! 高度
	int n = removeAt(x);
	_size -= n;return n;
}

//删除子树并返回删除的个数
template <typename T>
static int removeAt(BinNode<T>* x)  //assert: x为二叉树中癿合法位置
{
	if (!x) return 0;
	int n = 1 + removeAt(x->lc) + removeAt(x->rc);
	delete x;return n;
}

//secede (脱离)
//将以x为根的树脱离，返回其树指针
template <typename T>
BinTree<T>* BinTree<T>::secede(BinNode<T>* x)
{
	FromParentTo(*x) = NULL;//切断来自父节点的指针
	updateHeightAbove(x->parent);//更新原树高度
	BinTree<T>* newTree = new BinTree<T>;//new一个树
	newTree->_root = x; x->parent = NULL;//树根状态（root，parent）
	newTree->_size = x->size();//树大小
	_size -= newTree->_size; return newTree;//this树大小
}


//————————————————————————————————————————————————————————
//递归版本(recursion） ,当树太大可能有性能、栈溢出 问题
//先序遍历 先X，后Lc，Rc
template<typename T, typename VST>
void travPre_R(BinNode<T>* x, VST& visit) {
	if (!x) return;
	visit(x->data);
	travPre_R(x->lc,visit);//先所有的左子
	travPre_R(x->rc,visit);//然后最后x的右子
}

//同上的 中序遍历
template<typename T,typename VST>
void travIn_R(BinNode<T>* x, VST& visit){
	if (!x) return;
	travPre_R(x->lc,visit);
	visit(x->data);
	travPre_R(x->rc,visit);
}

//后序遍历
template<typename T, typename VST>
void travPost_R(BinNode<T>* x, VST& visit) {
	if (!x) return;
	travPre_R(x->lc, visit);
	travPre_R(x->rc, visit);
	visit(x->data);
}


//————————————————————————————————————————————————————————————————
//迭代版 (iteration)
//先序遍历!!
/* 
 * static ： 
 * 1.不用实例化对象就可直接使用（std::cout
 * 2.可读性：这是一个内部辅助函数，不依赖内部的任何实例状态的成员函数
 * 3.节省内存：不是每个对象各一个，而是只有一个
 */
//
template<typename T,typename VST>
static void visitAlongLeftBranch(BinNode<T>* x, VST& visit, Stack<BinNode<T>*>& S)
{
	while (x)																		
	{
		visit(x->data);
		if (x->rc) S.push(x->rc);
		x = x->lc;
	}
}

//迭代先序遍历  iteration
template<typename T, typename VST>
void travPre_I(BinNode<T>* x, VST& visit)
{
	Stack<BinNode<T>*> S;
	while (true)
	{
		visitAlongLeftBranch(x, visit,S);
		if (S.empty()) break;
		x = S.pop();
	}
}

//迭代中序遍历
template <typename T>
static void goAlongLeftBranch(BinNode<T>* x, Stack<BinNode<T>*>& S)//go
{
	while (x) {S.push(x);x = x->lc; }
}

template<typename T,typename VST>
void travIn_I1(BinNode<T>* x, VST& visit)
{
	Stack<BinNode<T>*> S;//*	!!!
	while (1)
	{
		goAlongLeftBranch(x, S);
		if (S.empty()) break;
		x = S.pop();visit(x->data);
		x = x->rc;
	}
}

//层序遍历
template<typename T> template<typename VST>
void BinNode<T>::travLevel(VST& visit) {
	Queue<BinNode<T>*> que;
	que.enqueue(this);
	while (!que.empty())
	{
		BinNode<T>* x = que.dequeue();
		visit(x->data);
		if (HasLChild(*x)) que.enqueue(x->lc);
		if (HasRChild(*x)) que.enqueue(x->rc);
	}
}
//直接后继
//在二叉搜索树中左孩子小于x，右孩子大于x，
//直接后继是指大于x且最接近x的，即右孩子的左底（若存在
//否则是最接近它的大者（父节点
template <typename T>
BinNode<T>* BinNode<T>::succ()
{
	
}




//------------------------------------------------------------------------------------------
namespace BinTreeUse
{
	// 构造哈夫曼树的函数
	template <typename T>
	BinTree<T>* buildHuffmanTree(const BinTree<T>* tree) {
		// 使用优先队列作为最小堆，存储节点

		Vector<BinNode<T>*> vec;
		
		//auto insert = [&](BinNode<T>* node)->void{		?
		//	vec.insert(node);
		//};
		//travPre_I(tree->root(), insert);
		Stack<BinNode<T>*> S;
		BinNode<T>* x = tree->root();
		while (true)
		{
			while (x)
			{
				vec.insert(x);
				if (x->rc) S.push(x->rc);
				x = x->lc;
			}
			if (S.empty()) break;
			x = S.pop();
		}

		vec.shellSort();
		//vec.reverse();
		Stack<BinNode<T>*> st;

		auto toStack = [&](BinNode<T>* node)->void{
			st.push(node);
		};
		vec.traverse(toStack);
		


		// 构建哈夫曼树
		while (st.size() > 1) {
			// 从队列中取出两个最小的节点
			BinNode<T>* left = st.top();
			st.pop();
			BinNode<T>* right = st.top();
			st.pop();

			// 创建一个新节点，作为合并后的节点
			BinNode<T>* mergedNode = new BinNode<T>('#');
			mergedNode->fred = left->fred + right->fred;
			mergedNode->lc = left;
			mergedNode->rc = right;

			// 将新节点放
			st.push(mergedNode);
		};

		// 返回哈夫曼树的根节点
		 BinTree<T>* t = new BinTree<T>;
		return t->secede(st.top());
	}

}


#endif // !BINTREE_H
