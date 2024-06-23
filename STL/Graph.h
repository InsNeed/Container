#pragma once
#include "Vector.h"
#include "Stack.h"
#include "Queue.h"
#include <vector>

//��ͨ·����ֻ����һ�Σ����Զ�ξ�������
//��·���ص�������
//�򵥻�·����ֻ����һ��
//ŷ����·��ÿ���߶�Ҫ��һ�����γɻ�·
//���׶�����·��ÿ�������߹�ֻһ�εĻ�·

//����״̬
typedef enum{ UNDISCOVERED, DISCOVERED, VISITED } VStatus;
//���ڱ������е��������ͣ�δ����/��/·��/ǰ������
typedef enum{ UNDETERMINED, TREE, CROSS, FORWARD, BACKWARD } EType;


template <typename Tv, typename Te> //�������͡�������
class Graph
{
private:
	void reset() {//���ж��㣬�ߵ���Ϣ ��λ
		for (int i = 0;i < n;i++) {
			status(i) = UNDISCOVERED;//״̬
			dTime(i) = fTime(i) = -1;//ʱ���ǩ��
			parent(i) = -1; //�ڱ������еĸ��ڵ�
			priority(i) = INT_MAX; //���ȼ���
			for (int j = 0; j < n; j++) //���б�
				if( exists ( i, j) ) 
					type ( i, j ) = UNDETERMINED; //����
		}
	}
	
	void BFS(int, int&);//��ͨ���������㷨 Breadth First Search
	void DFS(int, int&);//��ͨ����������㷨 Deep F S
	void BCC(int, int&, Stack<int>&); //��ͨ�����DFS��˫��ͨ�����ֽ��㷨 ??
	bool TSort(int, int&, Stack<Tv>*); //��ͨ�����DFS�����������㷨 ?? 
	template<typename PU> 
	void PFS(int, PU); //����ͨ�����ȼ�������� Priority-First Search ����

public:
//����
	int n;//�������
	virtual int insert(Tv const&) = 0;//���붥��,���ر�ţ����麯����
	virtual Tv remove(int) = 0;//ɾ�����㼰������ߣ����ض�����Ϣ
	virtual Tv& vertex(int) = 0;//����v�����ݣ��������)
	virtual int inDegree(int) = 0;//�������
	virtual int outDegree(int) = 0;//����
	virtual int firstNbr(int, int) = 0;//����v���׸��ڽӶ���
	virtual int nextNbr(int, int) = 0;//����v����ڶ���j����һ�ڽӶ���
	virtual VStatus& status(int) = 0;//����״̬
	//??
	virtual int& dTime(int) = 0;//�����ʱ���ǩdTime
	virtual int& fTime(int) = 0;//fTime
	virtual int& parent(int) = 0;//�����ڱ������еĸ���
	virtual int& priority(int) = 0;//�����ڱ������е����ȼ�
//�ߣ���������ͼͳһΪ�������һ�������
	int e;//����
	virtual bool exists(int, int) = 0;//��(u,v)�Ƿ����
	virtual void insert(Te const&,int, int) = 0;//��(u,v)�����Ȩ��Ϊw�ı�e
	virtual Te remove(int, int) = 0; //ɾ������v��u��ı�e�����ر���Ϣ
	virtual EType& type(int, int) = 0;//������
	virtual Te& edge(int, int) = 0;//�ߵ�����
	virtual int& weight(int, int) = 0;//��v,u��Ȩ��
//�㷨
	void bfs(int); //������������㷨
	void dfs(int); //������������㷨
	void bcc(int); //����DFS��˫��ͨ�����ֽ��㷨
	Stack<Tv>* tSort(int); //DFS�����������㷨
	void prim(int); //��С֧����Prim�㷨 
	void dijkstra(int); //���·��Dijkstra�㷨
	template<typename PU> 
	void pfs(int, PU); //���ȼ��������
};







//����
template <typename Tv> 
struct Vertex
{
	Tv data;
	int inDegree, outDegree;
	VStatus status;	//���ݣ���ȳ��ȣ�״̬

	int dTime, fTime;//discorvery & finishʱ���ǩ
	int parent; int priority;//�������еĸ��ڵ㣬���ȼ���
	Vertex(Tv const& data = (Tv)0) :
		data(data), inDegree(0), outDegree(0), status(UNDISCOVERED),
		dTime(-1), fTime(-1), parent(-1), priority(INT_MAX) {}
	//�ݲ�����Ȩ����� ��
};
//��
template <typename Te> 
struct Edge
{
	Te data;int weight; EType type;//���ݡ�Ȩ�ء�����
	Edge(Te const& d, int w) : data(d), weight(w), type(UNDETERMINED) {}
};



template<typename Tv, typename Te> //ͼ���ڽӾ���                                                       
class GraphMatrix : public Graph <Tv, Te>
{
private:
	Vector<Vertex<Tv>> V;//���㼯 (��������
	Vector<Vector<Edge<Te>*>> E;//�߼� ���ڽӾ���!!!!!!!!!!!!!!!!!!!!!!!!!!
	
	//void A() {
	//	vector<vector<Edge<Te>*>> vec4;
	//	vec4[1];
	//	using namespace std;
	//	vector<vector<Edge<Te>*>> vec1(10,vector<Edge<Te>*>(5,Edge<Te>(0,nullptr);
	//}
	
public:
	//����������
	GraphMatrix() { this->n = 0;this->e = 0; }//�̳���Graph,������ n �� e���������ͱ�����
	~GraphMatrix() {
		for (int i = 0; i < this->n; i++) {
			for (int j = 0;j < this->n;j++) {
				delete E[i][j];//����ɾ�����б߼�¼
			}
		}
	}

//�����������,��ѯ��i������
	virtual Tv& vertex(int i) { return V[i].data; }
	virtual int inDegree(int i) { return V[i].inDegree; }
	virtual int outDegree(int i) { return V[i].outDegree; }
	virtual int firstNbr(int i) { return nextNbr(i, this->n); }
	//��Զ���j����һ�ڽӶ��㣨�����ڽӱ�����Ч�ʣ�������
	virtual int nextNbr(int i, int j) {
		while ((j > -1) && (!exists(i, --j))); return j; //����������̽???
	}
	virtual VStatus& status(int i) { return V[i].status; }//����VStatus

	//???
	virtual int& dTime(int i) { return V[i].dTime; } //ʱ���ǩdTime
	virtual int& fTime(int i) { return V[i].fTime; } //ʱ���ǩfTime

	virtual int& parent(int i) { return V[i].parent; } //�ڱ������еĸ���
	virtual int& priority(int i) { return V[i].priority; }//�ڱ������е����ȼ�
//����Ķ�̬����
	virtual int insert(Tv const& vertex) {//���붥�㣬���ر��

		for (int j = 0; j < this->n; j++) {
			E[j].insert(NULL);//������Ԥ��һ��Ǳ�ڵĹ�����
		}
		E.insert(Vector<Edge<Te>*>(this->n,this->n, (Edge<Te>*) NULL)); //�����¶����Ӧ�ı�����
		//��������NULLΪ (Edge<Te>*������
		return V.insert(Vertex<Tv>(vertex)); //������������һ������
	}

	virtual Tv remove(int i) { //ɾ����i�����㼰������ߣ�0 <=i < n��
		for (int j = 0; j < this->n; j++) {
			if (exists(i, j)) { delete E[i][j]; V[j].inDegree--; } //��������
		}
		E.removeV(i); this->n--; //ɾ����i��
		Tv vBak = vertex(i); 
		V.removeV(i); //ɾ������i
		for (int j = 0; j < this->n; j++) //�������
			if (Edge<Te>* e = E[j].removeV(i)) { delete e; V[j].outDegree--; } //����ɾ��
		return vBak; //���ر�ɾ���������Ϣ
	}

	//�ߵ�ȷ�ϲ���
	virtual bool exists(int i, int j) {//�� ij�Ƿ����
		return ((i >= 0) && (i < this->n) && (j >= 0) && (j < this->n) && (E[i][j] != NULL));
	}
	virtual EType& type(int i, int j) { return E[i][j]->type; }//������
	virtual Te& edge(int i, int j) { return E[i][j]->data; }
	virtual int& weight(int i, int j) { return E[i][j]->weight; }
	//�߶�̬����
	virtual bool insert(Te const& data, int weight, int i, int j) {//����Ȩ��Ϊw�ı�e=(i,j)
		if (exists(i, j)) return false;
		E[i][j] = new Edge<Te>(data, weight);//�����±�
		this->e++;//����
		V[i].outDegree++;
		V[j].inDegree++;//���ߵ���ȳ���
	}
	virtual Te remove(int i,int j) {//ɾ���ڵ�i->j������ ����  exists(i,j)
		Te vBak = edge(i, j);
		delete E[i][j];//����ɾ��
		E[i][j] = NULL;//ָ���ÿ�
		this->e--;
		V[i].outDegree--;
		V[j].inDegree--;
		return vBak;
	}

};



//ͼ�ı���
template <typename Tv,typename Te>
void Graph<Tv, Te>::bfs(int s) {//assert: 0 <= s < n
	reset();//reset
	int clock = 0;int v = s;//��ʼ��ʱ���ǩ��v
	do
	{
		if (status(v) == UNDISCOVERED) {
			BFS(v, clock);
		}
	} while (s !=(v = (++v%n)));//����ż��
}

template <typename Tv,typename Te>
void Graph<Tv, Te>::BFS(int v, int& clock) { //assert: 0 <=v < n
	Queue<int> que;//����ջ
	status(v) = DISCOVERED;que.enqueue(v);
	while (!que.empty()) {
		int v = que.dequeue();
		dTime(v) == ++clock;
		for (int u = firstNbr(v);u > -1;u = nextNbr(v, u))
			if (status(u) == DISCOVERED) {
				que.enqueue(u);
				type(v, u) = TREE;
				parent(u) = v;
			}else {
				type(v, u) = CROSS;
			}
		status(v) = VISITED;
	}
}
