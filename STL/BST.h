#pragma once

#include "BinTree.h"

template <typename T>
class BST:BinTree<T>
{
protected:
	BinNode<T>* _hot;//���нڵ㸸�ף�
	BinNode<T>* connect34(//��3+4�ṹ����3�ڵ��4��������
		BinNode<T>*, BinNode<T>*, BinNode<T>*, BinNode<T>*, BinNode<T>*, BinNode<T>*
	);
	BinNode<T>* rotateAt(BinNode<T>* x);//��ת�ڵ�
public:
	virtual BinNode<T>* & search(const T& e);//����
	virtual BinNode<T>* insert(const T& e);//����
	virtual bool remove(const T& e);//ɾ��
};


//����vΪ���ģ�AVL��SPLAY��rbTree�ȣ�BST�����в��ҹؼ��룿
template <typename T>
static BinNode<T>*& searchIn(BinNode<T>* & x, const T& e, BinNode<T>*& hot) {
	if (!x || (e == x->data)) return x;//�ݹ�����ڽڵ�x�����ͨ��ڵ㴦����
	hot = x;//��¼���е�ǰ�ڵ� ,�����ָ�򸸽ڵ�
	return searchIn((e < x->data ? x->lc : x->rc), e, hot);
}

template<typename T> 
BinNode<T>*& BST<T>::search(const T& e) {
	return searchIn(_root, e, _hot = NULL);
}

template <typename T> 
BinNode<T>* BST<T>::insert(const T& e) { //���ؼ���e����BST����
	BinNode<T>* & x = search(e); if (x) return x; 
	x = new BinNode<T>(e, _hot);
	_size++;
	updateHeightAbove(x);//������״̬
	return x;//�²���ڵ�ΪҶ��
}

template <typename T> 
bool BST<T>::remove(const T& e) { //��BST���г����ؼ���e
	BinNode<T>* & x = search(e); if (!x) return false;//�Ҳ���
	removeAt(x);//:BinTree
	_size--;updateHeightAbove(_hot);//����_hot��������
	return true;
}