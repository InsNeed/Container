#ifndef TREE_H
#define TREE_H

#include <iostream>
#include "Queue.h"


//xΪ�ڵ����pΪ�ڵ�����ָ��
//���x.parent��õ�ָ�򸸽ڵ��ָ�룬������Ҫ������ *

/*
 *BinNode�ڵ��ж�
 */
#define IsRoot(x) (!((x).parent))
//������һ���ڵ���󣬶�����ָ��ڵ��ָ��
//lc���Ǹ�ָ�룬����ȡ��ַ
#define IsLChild(x) (!IsRoot(x) && ( & (x) == (x).parent->lc) ) 
#define IsRChild(x) (!IsRoot(x)) && (& (x) == (x).parent->lc)

#define HasParent(x) (!IsRoot(x))
#define HasLChild(x) ((x).lc)
#define HasRChild(x) ((x).rc)
#define HasChild(x) (HasLChild(x) || HasRChild(x))
#define HasBothChild(x) (HasLChild(x) && HasRChild(x))
#define IsLeaf(x) (!HasChild(x))//���Ӽ�Ҷ

/*
 * BinNode�����ض���ϵ�� �ڵ� �� ָ��
 */

//������һ���ڵ�ָ�� �����ֵܽڵ�ָ��
#define sibling(p)/*�ֵ� \����������һ�� */ \
    (IsLChild(*(p)) ? (p)->parent->rc : (p)->parent->lc)
//�����ǽڵ����
#define uncle(x) /*���壬���׵��ֵ�*/ \
    (IsLChild(*((x)->parent)) ? (x)->parent->parent->lc:(x)->parent->parent->rc)
#define FromParentTo(x) /*���Ը��׵����ã��� parent->lc*/\
    (IsRoot(x) ? _root : (IsLChild(x) ? (x).parent->lc : (x).parent->rc))



typedef enum { RB_RED, RB_BLACK } RBColor;
template <typename T> struct BinNode
{
    //��Ա
    T data;
    BinNode<T>* parent, * lc, * rc;
    int height;
    int npl;//Null Path Length  ��ʽ��
    int fred;
    RBColor color;

    //���캯��
    BinNode() :
        parent(NULL), lc(NULL), rc(NULL), height(0), npl(1), color(RB_RED) {};//RED
    BinNode(T e, BinNode<T>* p = nullptr, BinNode<T>* lc = nullptr, BinNode<T>* rc = nullptr,
        int h = 0, int l = 1, RBColor c = RB_RED) :
        data(e), parent(p), lc(lc), rc(rc), height(h), npl(l), color(c) {};
    //BinNode(T e, int fred = 0,BinNode<T>* p = nullptr, BinNode<T>* lc = nullptr, BinNode<T>* rc = nullptr,
    //    int h = 0, int l = 1, RBColor c = RB_RED) :
    //    data(e), fred(fred),parent(p), lc(lc), rc(rc), height(h), npl(l), color(c) {};

    //�����ӿ�
    int size();//�ýڵ�������
    //��Ϊ��ǰ�ڵ�����Ӳ����½ڵ㣬����ָ���ӽڵ��ָ��,Ĭ�ϵ�ǰ�ڵ�������
    BinNode<T>* insertAsLc(T const&);
    BinNode<T>* insertAsRc(T const&);
    BinNode<T>* succ();//ȡ�õ�ǰ�ڵ��ֱ�Ӻ��

    template<typename VST> void travLevel(VST& );//������α���
    template<typename VST> void travPre(VST&);//�����������
    template<typename VST> void travIn(VST&);//�����������
    template<typename VST> void travPost(VST&);//�����������

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
template <typename T> template <typename VST>//�����������
void BinNode<T>::travIn(VST& visit) {
    switch (rand() % 5){
    case 1:travIn_I1(this, visit);break;// ������#1
    case 2:travIn_I2(this, visit);break;// ������#2
    case 3:travIn_I3(this, visit);break;// ������#3
    case 4:travIn_I4(this, visit);break;// ������#4
    default:travIn_R(this, visit);break;// �ݹ��
        break;
    }
}

///// <summary>
///// ���������ڵ����ͣ�BinNode
///// </summary>
///// <typeparam name="T"></typeparam>
//template <typename T>
//class HuffmanNode : public BinNode<T> {
//private:
//    unsigned frequency;  // Ȩֵ��Ƶ�ʣ�
//
//    // ���캯��
//    HuffmanNode(T data, unsigned frequency) :data(data), frequency(frequency), this->lc(nullptr), this->rc(nullptr) {}
//
//    // ���رȽ������
//    bool operator>(const HuffmanNode& other) const {
//        return frequency > other.frequency;
//    }
//protected:
//    //hufm��������� visit�ڵ�
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
