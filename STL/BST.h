#pragma once

#include "BinTree.h"

template <typename T>
class BST:BinTree<T>
{
protected:
	BinNode<T>* _hot;//命中节点父亲？
	BinNode<T>* connect34(//按3+4结构连接3节点和4子树？？
		BinNode<T>*, BinNode<T>*, BinNode<T>*, BinNode<T>*, BinNode<T>*, BinNode<T>*
	);
	BinNode<T>* rotateAt(BinNode<T>* x);//旋转节点
public:
	virtual BinNode<T>* & search(const T& e);//查找
	virtual BinNode<T>* insert(const T& e);//插入
	virtual bool remove(const T& e);//删除
};


//在以v为根的（AVL、SPLAY、rbTree等）BST子树中查找关键码？
template <typename T>
static BinNode<T>*& searchIn(BinNode<T>* & x, const T& e, BinNode<T>*& hot) {
	if (!x || (e == x->data)) return x;//递归基：在节点x或假象通配节点处命中
	hot = x;//记录命中当前节点 ,到最后指向父节点
	return searchIn((e < x->data ? x->lc : x->rc), e, hot);
}

template<typename T> 
BinNode<T>*& BST<T>::search(const T& e) {
	return searchIn(_root, e, _hot = NULL);
}

template <typename T> 
BinNode<T>* BST<T>::insert(const T& e) { //将关键码e插入BST树中
	BinNode<T>* & x = search(e); if (x) return x; 
	x = new BinNode<T>(e, _hot);
	_size++;
	updateHeightAbove(x);//更新树状态
	return x;//新插入节点为叶子
}

template <typename T> 
bool BST<T>::remove(const T& e) { //从BST树中初除关键码e
	BinNode<T>* & x = search(e); if (!x) return false;//找不到
	removeAt(x);//:BinTree
	_size--;updateHeightAbove(_hot);//更新_hot及其先祖
	return true;
}