#ifndef BINTREE_H
#define BINTREE_H


/*
	��ȫ��������ģӦ�ý���2^h��2^(h+1) - 1
*/


//�����������
//BinNode<char>* te;
//BinTree<char> huffTree;
//te = huffTree.insertAsRoot('A');te->fred = 20;//������
//te = huffTree.insertAsLC(huffTree.root(), 'B');te->fred = 30;
//BinNode<char>* n2 = huffTree.insertAsRC(huffTree.root(), 'C');n2->fred = 10;
//auto ptr = node->insertAsLc('D');ptr->fred = 5;
//ptr = node->insertAsRc('E');ptr->fred = 35;
//// ��ʱ���� A(B,C(D,E));
////Ȩֵ	20,30,10,5,35


//BinTree<char>* hufTree = BinTreeUse::buildHuffmanTree<char>(&huffTree);
//travPre_R(hufTree->root(), visitT2);//�ݹ���������
//std::cout << '\n';

#include "BinNode.h"
#include "Stack.h"
#include "Vector.h"

#define stature(p) ((p) ? (p)->height : -1)//!!!

template <typename T>
class BinTree {
protected:
	int _size;BinNode<T>* _root;
	virtual int updateHeight(BinNode<T>* x);//���½ڵ�x������  
	void updateHeightAbove(BinNode<T>* x); //���½ڵ�x�������ȸ߶�)
	void release(BinNode<T>* x);
public:
	BinTree() : _size(0), _root(NULL) { } //���캯��

	~BinTree() {if (0 < _size)  remove(_root);}
	//ֻ��
	int sizeOfBinTree() const { return _size; }//��С
	bool empty() const { return !_root; }//�п� ??!
	BinNode<T>* root() const { return _root; }//����
	//��д
	BinNode<T>* insertAsRoot(T const& e);//������ڵ�
	BinNode<T>* insertAsRoot(T const& e, int fred);//������ڵ�

	BinNode<T>* insertAsLC(BinNode<T>* x, T const& e);//e��Ϊx������(ԭ��)����
	BinNode<T>* insertAsRC(BinNode<T>* x, T const& e);//e��Ϊx���Һ���(ԭ��)����
	// ָ�������

	BinNode<T>* attachAsLC(BinNode<T>* x,BinTree<T>* &tree);//tree��Ϊx����������
	BinNode<T>* attachAsRC(BinNode<T>* x,BinTree<T>* &tree);//tree��Ϊx����������
	int remove(BinNode<T>* x);
	BinTree<T>* secede(BinNode<T>* x);//�������ӵ�ǰ�������ת����һ����������

	//�ֱ��ͷŽڵ����
	void releaseTree(BinTree<T>*& tree);
	void releaseNode(BinNode<T>*& x);

	
	//����

	//�Ƚ���
	bool operator< (BinTree<T> const& t) {
		return _root && t.root && lt(_root, t._root);
	}
	bool operator== (BinTree<T> const& t) {
		return _root && t.root && eq(_root, t._root);
	}

	// ����������������������������������������
};//BINTREE   






//���½ڵ�߶ȣ����ظ߶�
template <typename T>
int BinTree<T>::updateHeight(BinNode<T>* x)
{
	return x->height = 1 + std::max(stature(x->lc), stature(x->rc));
}

//���½ڵ㼰���ϵĸ߶�
template<typename T> 
void BinTree<T>::updateHeightAbove(BinNode<T>* x)
{
	while (x) { updateHeight(x);x = x->parent; }
}

//��e��Ϊ�����ĸ��ڵ�,����ָ��ýڵ��ָ��
template<typename T>
BinNode<T>* BinTree<T>::insertAsRoot(T const& e)
{
	_size = 1;
	return _root = new BinNode<T>(e);//!!!!
}


//��e��Ϊ�����ĸ��ڵ�,����ָ��ýڵ��ָ��  huff
template<typename T>
BinNode<T>* BinTree<T>::insertAsRoot(T const& e,int fred)
{
	_size = 1;
	return _root = new BinNode<T>(e,fred);//!!!!
}
//��e��Ϊ �����ӽڵ� �����Ӳ���,����ָ��ڵ�new�����ӵ�ָ��
template<typename T> 
BinNode<T>* BinTree<T>::insertAsLC(BinNode<T>* x, T const& e)
{
	_size++;//����
	x->insertAsLc(e);//��x->������ֱ��insert
	updateHeightAbove(x);//�ǵø��¸߶�
	return x->lc;
}

//��e��Ϊ �����ӽڵ� �����Ӳ���,����ָ��ڵ�new�����ӵ�ָ��
template<typename T> 
BinNode<T>* BinTree<T>::insertAsRC(BinNode<T>* x, T const& e)
{
	_size++;
	x->insertAsRc(e);
	updateHeightAbove(x);
	return x->rc;
}

//�ͷ����Ŀռ�
template<typename T>
void BinTree<T>::releaseTree(BinTree<T>*& tree) {
	if (tree) {
		release(tree->_root);  
		delete tree;         
		tree = nullptr;        // ��ָ����Ϊ��
	}
}

//�ͷŽڵ�ռ�
template<typename T>
void  BinTree<T>::releaseNode(BinNode<T>*& x) {
	if (!x) {//xΪ��ָ��
		return;
	}

	release(x->lc);  
	release(x->rc);  
	delete x;        
	x = nullptr;      // ��ָ����Ϊ��
}


//��tree���� �����ӽڵ�x �����������룬S�����ÿգ����� ������λ�ã�
//!!!!!!!
template <typename T>//������Ȼ��tree��ָ������ã�����
BinNode<T>* BinTree<T>::attachAsLC(BinNode<T>* x, BinTree<T>*& tree)
{
	//!!!!!!!!!!!!!
	//������������ж�tree�Ƿ�Ϊ��������ֹ�Կ������в���
	/*delete tree ���ͷ� tree ָ��ָ����ڴ棬
	����ζ�� tree ������ᱻ���٣����� tree ����ĳ�Ա�����ݳ�Ա��
	���ⲻ��Ӱ�� tree �еĽڵ�
	��Ϊ�ڵ���ͨ��ָ���໥���ӵģ������Ǵ洢�� tree �������ڲ��ġ�*/
	if (x->lc = tree->_root) x->lc->parent = x;//����
	_size += tree->_size;updateHeightAbove(x);//����size��ȫ���߶�
	delete tree;//�ÿ�S����ôд��
	return x;
}

//��tree��Ϊ ���Һ��ӽڵ�x �����������룬S�����ÿգ����ؽ���λ��
template <typename T>
BinNode<T>* BinTree<T>::attachAsRC(BinNode<T>* x, BinTree<T>*& tree)
{
	if (x->lc = tree->_root) x->lc.parent = x;
	_size += tree->_size;updateHeightAbove(x);
	delete tree;
	return x;
}

//ɾ������������ɾ���ĸ���
template <typename T>
int BinTree<T>::remove(BinNode<T>* x)//assert: xΪ���кϷ�λ��
{
	FromParentTo(*x) = NULL;//x������ �ж����Ը��׽ڵ��ָ��
	updateHeightAbove(x->parent);//���� !����! �߶�
	int n = removeAt(x);
	_size -= n;return n;
}

//ɾ������������ɾ���ĸ���
template <typename T>
static int removeAt(BinNode<T>* x)  //assert: xΪ�������аm�Ϸ�λ��
{
	if (!x) return 0;
	int n = 1 + removeAt(x->lc) + removeAt(x->rc);
	delete x;return n;
}

//secede (����)
//����xΪ���������룬��������ָ��
template <typename T>
BinTree<T>* BinTree<T>::secede(BinNode<T>* x)
{
	FromParentTo(*x) = NULL;//�ж����Ը��ڵ��ָ��
	updateHeightAbove(x->parent);//����ԭ���߶�
	BinTree<T>* newTree = new BinTree<T>;//newһ����
	newTree->_root = x; x->parent = NULL;//����״̬��root��parent��
	newTree->_size = x->size();//����С
	_size -= newTree->_size; return newTree;//this����С
}


//����������������������������������������������������������������������������������������������������������������
//�ݹ�汾(recursion�� ,����̫����������ܡ�ջ��� ����
//������� ��X����Lc��Rc
template<typename T, typename VST>
void travPre_R(BinNode<T>* x, VST& visit) {
	if (!x) return;
	visit(x->data);
	travPre_R(x->lc,visit);//�����е�����
	travPre_R(x->rc,visit);//Ȼ�����x������
}

//ͬ�ϵ� �������
template<typename T,typename VST>
void travIn_R(BinNode<T>* x, VST& visit){
	if (!x) return;
	travPre_R(x->lc,visit);
	visit(x->data);
	travPre_R(x->rc,visit);
}

//�������
template<typename T, typename VST>
void travPost_R(BinNode<T>* x, VST& visit) {
	if (!x) return;
	travPre_R(x->lc, visit);
	travPre_R(x->rc, visit);
	visit(x->data);
}


//��������������������������������������������������������������������������������������������������������������������������������
//������ (iteration)
//�������!!
/* 
 * static �� 
 * 1.����ʵ��������Ϳ�ֱ��ʹ�ã�std::cout
 * 2.�ɶ��ԣ�����һ���ڲ������������������ڲ����κ�ʵ��״̬�ĳ�Ա����
 * 3.��ʡ�ڴ棺����ÿ�������һ��������ֻ��һ��
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

//�����������  iteration
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

//�����������
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

//�������
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
//ֱ�Ӻ��
//�ڶ���������������С��x���Һ��Ӵ���x��
//ֱ�Ӻ����ָ����x����ӽ�x�ģ����Һ��ӵ���ף�������
//��������ӽ����Ĵ��ߣ����ڵ�
template <typename T>
BinNode<T>* BinNode<T>::succ()
{
	
}




//------------------------------------------------------------------------------------------
namespace BinTreeUse
{
	// ������������ĺ���
	template <typename T>
	BinTree<T>* buildHuffmanTree(const BinTree<T>* tree) {
		// ʹ�����ȶ�����Ϊ��С�ѣ��洢�ڵ�

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
		


		// ������������
		while (st.size() > 1) {
			// �Ӷ�����ȡ��������С�Ľڵ�
			BinNode<T>* left = st.top();
			st.pop();
			BinNode<T>* right = st.top();
			st.pop();

			// ����һ���½ڵ㣬��Ϊ�ϲ���Ľڵ�
			BinNode<T>* mergedNode = new BinNode<T>('#');
			mergedNode->fred = left->fred + right->fred;
			mergedNode->lc = left;
			mergedNode->rc = right;

			// ���½ڵ��
			st.push(mergedNode);
		};

		// ���ع��������ĸ��ڵ�
		 BinTree<T>* t = new BinTree<T>;
		return t->secede(st.top());
	}

}


#endif // !BINTREE_H
