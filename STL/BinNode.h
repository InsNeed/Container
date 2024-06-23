#ifndef TREE_H
#define TREE_H

#include <iostream>
#include "Queue.h"


//x为节点对象，p为节点对象的指针
//如果x.parent会得到指向父节点的指针，所以需要解引用 *

/*
 *BinNode节点判断
 */
#define IsRoot(x) (!((x).parent))
//参数是一个节点对象，而不是指向节点的指针
//lc就是个指针，所以取地址
#define IsLChild(x) (!IsRoot(x) && ( & (x) == (x).parent->lc) ) 
#define IsRChild(x) (!IsRoot(x)) && (& (x) == (x).parent->lc)

#define HasParent(x) (!IsRoot(x))
#define HasLChild(x) ((x).lc)
#define HasRChild(x) ((x).rc)
#define HasChild(x) (HasLChild(x) || HasRChild(x))
#define HasBothChild(x) (HasLChild(x) && HasRChild(x))
#define IsLeaf(x) (!HasChild(x))//无子即叶

/*
 * BinNode具有特定关系的 节点 及 指针
 */

//参数是一个节点指针 返回兄弟节点指针
#define sibling(p)/*兄弟 \用于连接下一行 */ \
    (IsLChild(*(p)) ? (p)->parent->rc : (p)->parent->lc)
//参数是节点对象
#define uncle(x) /*叔叔，父亲的兄弟*/ \
    (IsLChild(*((x)->parent)) ? (x)->parent->parent->lc:(x)->parent->parent->rc)
#define FromParentTo(x) /*来自父亲的引用，如 parent->lc*/\
    (IsRoot(x) ? _root : (IsLChild(x) ? (x).parent->lc : (x).parent->rc))



typedef enum { RB_RED, RB_BLACK } RBColor;
template <typename T> struct BinNode
{
    //成员
    T data;
    BinNode<T>* parent, * lc, * rc;
    int height;
    int npl;//Null Path Length  左式堆
    int fred;
    RBColor color;

    //构造函数
    BinNode() :
        parent(NULL), lc(NULL), rc(NULL), height(0), npl(1), color(RB_RED) {};//RED
    BinNode(T e, BinNode<T>* p = nullptr, BinNode<T>* lc = nullptr, BinNode<T>* rc = nullptr,
        int h = 0, int l = 1, RBColor c = RB_RED) :
        data(e), parent(p), lc(lc), rc(rc), height(h), npl(l), color(c) {};
    //BinNode(T e, int fred = 0,BinNode<T>* p = nullptr, BinNode<T>* lc = nullptr, BinNode<T>* rc = nullptr,
    //    int h = 0, int l = 1, RBColor c = RB_RED) :
    //    data(e), fred(fred),parent(p), lc(lc), rc(rc), height(h), npl(l), color(c) {};

    //操作接口
    int size();//该节点后代总数
    //作为当前节点的左孩子插入新节点，返回指向子节点的指针,默认当前节点无左子
    BinNode<T>* insertAsLc(T const&);
    BinNode<T>* insertAsRc(T const&);
    BinNode<T>* succ();//取得当前节点的直接后继

    template<typename VST> void travLevel(VST& );//子树层次遍历
    template<typename VST> void travPre(VST&);//子树先序遍历
    template<typename VST> void travIn(VST&);//子树中序遍历
    template<typename VST> void travPost(VST&);//子树后序遍历

    bool operator< (BinNode const& bn) { return data < bn.data; }
    bool operator> (BinNode const& bn) { return data > bn.data; }
    bool operator== (BinNode const& bn) { return data == bn.data; }
    bool operator!= (BinNode const& bn) { return data != bn.data; }

};

//SIZE!!!! 
//!!!!!!!!!!!!!!!!!!!
template <typename T>
int  BinNode<T>::size()
{
    int size = 1;
    if (lc) size += lc->size();
    if (rc) size += rc->size();
    return size;
}

template <typename T>
BinNode<T>* BinNode<T>::insertAsLc(T const& e) {
    return lc = new BinNode(e, this);
}

template <typename T>
BinNode<T>* BinNode<T>::insertAsRc(T const& e) {
    return rc = new BinNode(e, this);
}

//!!!!!!!!!!!!!!!!!!
template <typename T> template <typename VST>//子树中序遍历
void BinNode<T>::travIn(VST& visit) {
    switch (rand() % 5){
    case 1:travIn_I1(this, visit);break;// 迭代版#1
    case 2:travIn_I2(this, visit);break;// 迭代版#2
    case 3:travIn_I3(this, visit);break;// 迭代版#3
    case 4:travIn_I4(this, visit);break;// 迭代版#4
    default:travIn_R(this, visit);break;// 递归版
        break;
    }
}

///// <summary>
///// 哈夫曼树节点类型：BinNode
///// </summary>
///// <typeparam name="T"></typeparam>
//template <typename T>
//class HuffmanNode : public BinNode<T> {
//private:
//    unsigned frequency;  // 权值（频率）
//
//    // 构造函数
//    HuffmanNode(T data, unsigned frequency) :data(data), frequency(frequency), this->lc(nullptr), this->rc(nullptr) {}
//
//    // 重载比较运算符
//    bool operator>(const HuffmanNode& other) const {
//        return frequency > other.frequency;
//    }
//protected:
//    //hufm树层序遍历 visit节点
//    template<typename T> template<typename VST>
//    void BinNode<T>::travLevel(VST& visit) {
//        Queue<BinNode<T>*> que;
//        que.enqueue(this );
//        while (!que.empty())
//        {
//            BinNode<T>* x = que.dequeue();
//            visit(x);
//            if (HasLChild(*x)) que.enqueue(x->lc);
//            if (HasRChild(*x)) que.enqueue(x->rc);
//        }
//    }
//};



#endif // !TREE_H
