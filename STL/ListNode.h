#pragma once

#include <iostream>

typedef int Rank;//秩
//#define ListNodePosi(T) ListNode<T>*

//节点
template <typename T> struct ListNode
{
	//成员
	T data;
	ListNode<T>* pred; ListNode<T>* succ;//前驱和后继
	//构造函数
	ListNode() {};//针对 header 和 trailer 的构造 ??
	ListNode(T e, ListNode<T>* p = NULL, ListNode<T>* s = NULL)//值,前节点，后节点
		:data(e), pred(p), succ(s) {};

	//操作接口    //就这么叫
	ListNode<T>* insertAsPred(T const& e);//T const & e !!!!??
	ListNode<T>* insertAsSucc(T const& e);
};

#pragma once
