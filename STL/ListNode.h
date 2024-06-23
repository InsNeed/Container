#pragma once

#include <iostream>

typedef int Rank;//��
//#define ListNodePosi(T) ListNode<T>*

//�ڵ�
template <typename T> struct ListNode
{
	//��Ա
	T data;
	ListNode<T>* pred; ListNode<T>* succ;//ǰ���ͺ��
	//���캯��
	ListNode() {};//��� header �� trailer �Ĺ��� ??
	ListNode(T e, ListNode<T>* p = NULL, ListNode<T>* s = NULL)//ֵ,ǰ�ڵ㣬��ڵ�
		:data(e), pred(p), succ(s) {};

	//�����ӿ�    //����ô��
	ListNode<T>* insertAsPred(T const& e);//T const & e !!!!??
	ListNode<T>* insertAsSucc(T const& e);
};

#pragma once
