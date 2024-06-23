#pragma once
#include "Vector.h"
#include "Stack.h"
#include "Queue.h"
#include <vector>

//简单通路：边只能走一次，可以多次经过顶点
//环路：回到出发点
//简单环路：边只能走一次
//欧拉环路：每个边都要走一次且形成环路
//哈米尔环顿路：每个顶点走过只一次的环路

//顶点状态
typedef enum{ UNDISCOVERED, DISCOVERED, VISITED } VStatus;
//边在遍历树中的所属类型，未定义/树/路口/前进后退
typedef enum{ UNDETERMINED, TREE, CROSS, FORWARD, BACKWARD } EType;


template <typename Tv, typename Te> //顶点类型、边类型
class Graph
{
private:
	void reset() {//所有顶点，边的信息 复位
		for (int i = 0;i < n;i++) {
			status(i) = UNDISCOVERED;//状态
			dTime(i) = fTime(i) = -1;//时间标签？
			parent(i) = -1; //在遍历树中的父节点
			priority(i) = INT_MAX; //优先级数
			for (int j = 0; j < n; j++) //所有边
				if( exists ( i, j) ) 
					type ( i, j ) = UNDETERMINED; //类型
		}
	}
	
	void BFS(int, int&);//连通域广度优先算法 Breadth First Search
	void DFS(int, int&);//连通域深度优先算法 Deep F S
	void BCC(int, int&, Stack<int>&); //连通域基于DFS的双连通分量分解算法 ??
	bool TSort(int, int&, Stack<Tv>*); //连通域基于DFS的拓扑排序算法 ?? 
	template<typename PU> 
	void PFS(int, PU); //（连通域）优先级搜索框架 Priority-First Search ？？

public:
//顶点
	int n;//顶点个数
	virtual int insert(Tv const&) = 0;//插入顶点,返回编号（纯虚函数）
	virtual Tv remove(int) = 0;//删除顶点及其关联边，返回顶点信息
	virtual Tv& vertex(int) = 0;//顶点v的数据（顶点存在)
	virtual int inDegree(int) = 0;//顶点入度
	virtual int outDegree(int) = 0;//出度
	virtual int firstNbr(int, int) = 0;//顶点v的首个邻接顶点
	virtual int nextNbr(int, int) = 0;//顶点v相对于顶点j的下一邻接顶点
	virtual VStatus& status(int) = 0;//顶点状态
	//??
	virtual int& dTime(int) = 0;//顶点的时间标签dTime
	virtual int& fTime(int) = 0;//fTime
	virtual int& parent(int) = 0;//顶点在遍历树中的父亲
	virtual int& priority(int) = 0;//顶点在遍历树中的优先级
//边：其中无向图统一为方向互逆的一对有向边
	int e;//边数
	virtual bool exists(int, int) = 0;//边(u,v)是否存在
	virtual void insert(Te const&,int, int) = 0;//在(u,v)间插入权重为w的边e
	virtual Te remove(int, int) = 0; //删除顶点v和u间的边e，返回边信息
	virtual EType& type(int, int) = 0;//边类型
	virtual Te& edge(int, int) = 0;//边的数据
	virtual int& weight(int, int) = 0;//边v,u的权重
//算法
	void bfs(int); //广度优先搜索算法
	void dfs(int); //深度优先搜索算法
	void bcc(int); //基于DFS的双连通分量分解算法
	Stack<Tv>* tSort(int); //DFS的拓扑排序算法
	void prim(int); //最小支撑树Prim算法 
	void dijkstra(int); //最短路径Dijkstra算法
	template<typename PU> 
	void pfs(int, PU); //优先级搜索框架
};







//顶点
template <typename Tv> 
struct Vertex
{
	Tv data;
	int inDegree, outDegree;
	VStatus status;	//数据，入度出度，状态

	int dTime, fTime;//discorvery & finish时间标签
	int parent; int priority;//遍历树中的父节点，优先级数
	Vertex(Tv const& data = (Tv)0) :
		data(data), inDegree(0), outDegree(0), status(UNDISCOVERED),
		dTime(-1), fTime(-1), parent(-1), priority(INT_MAX) {}
	//暂不考虑权重溢出 ？
};
//边
template <typename Te> 
struct Edge
{
	Te data;int weight; EType type;//数据、权重、类型
	Edge(Te const& d, int w) : data(d), weight(w), type(UNDETERMINED) {}
};



template<typename Tv, typename Te> //图的邻接矩阵                                                       
class GraphMatrix : public Graph <Tv, Te>
{
private:
	Vector<Vertex<Tv>> V;//顶点集 (顶点向量
	Vector<Vector<Edge<Te>*>> E;//边集 （邻接矩阵!!!!!!!!!!!!!!!!!!!!!!!!!!
	
	//void A() {
	//	vector<vector<Edge<Te>*>> vec4;
	//	vec4[1];
	//	using namespace std;
	//	vector<vector<Edge<Te>*>> vec1(10,vector<Edge<Te>*>(5,Edge<Te>(0,nullptr);
	//}
	
public:
	//构造与析构
	GraphMatrix() { this->n = 0;this->e = 0; }//继承自Graph,里面有 n ， e（顶点数和边数）
	~GraphMatrix() {
		for (int i = 0; i < this->n; i++) {
			for (int j = 0;j < this->n;j++) {
				delete E[i][j];//逐条删除所有边记录
			}
		}
	}

//顶点基本操作,查询第i个顶点
	virtual Tv& vertex(int i) { return V[i].data; }
	virtual int inDegree(int i) { return V[i].inDegree; }
	virtual int outDegree(int i) { return V[i].outDegree; }
	virtual int firstNbr(int i) { return nextNbr(i, this->n); }
	//相对顶点j的下一邻接顶点（改用邻接表可提高效率）？？？
	virtual int nextNbr(int i, int j) {
		while ((j > -1) && (!exists(i, --j))); return j; //逆向线性试探???
	}
	virtual VStatus& status(int i) { return V[i].status; }//返回VStatus

	//???
	virtual int& dTime(int i) { return V[i].dTime; } //时间标签dTime
	virtual int& fTime(int i) { return V[i].fTime; } //时间标签fTime

	virtual int& parent(int i) { return V[i].parent; } //在遍历树中的父亲
	virtual int& priority(int i) { return V[i].priority; }//在遍历树中的优先级
//顶点的动态操作
	virtual int insert(Tv const& vertex) {//插入顶点，返回编号

		for (int j = 0; j < this->n; j++) {
			E[j].insert(NULL);//各顶点预留一条潜在的关联边
		}
		E.insert(Vector<Edge<Te>*>(this->n,this->n, (Edge<Te>*) NULL)); //创建新顶点对应的边向量
		//上面其中NULL为 (Edge<Te>*）类型
		return V.insert(Vertex<Tv>(vertex)); //顶点向量增加一个顶点
	}

	virtual Tv remove(int i) { //删除第i个顶点及其关联边（0 <=i < n）
		for (int j = 0; j < this->n; j++) {
			if (exists(i, j)) { delete E[i][j]; V[j].inDegree--; } //逐条初除
		}
		E.removeV(i); this->n--; //删除第i行
		Tv vBak = vertex(i); 
		V.removeV(i); //删除顶点i
		for (int j = 0; j < this->n; j++) //所有入边
			if (Edge<Te>* e = E[j].removeV(i)) { delete e; V[j].outDegree--; } //逐条删除
		return vBak; //返回被删除顶点的信息
	}

	//边的确认操作
	virtual bool exists(int i, int j) {//边 ij是否存在
		return ((i >= 0) && (i < this->n) && (j >= 0) && (j < this->n) && (E[i][j] != NULL));
	}
	virtual EType& type(int i, int j) { return E[i][j]->type; }//边类型
	virtual Te& edge(int i, int j) { return E[i][j]->data; }
	virtual int& weight(int i, int j) { return E[i][j]->weight; }
	//边动态操作
	virtual bool insert(Te const& data, int weight, int i, int j) {//插入权重为w的边e=(i,j)
		if (exists(i, j)) return false;
		E[i][j] = new Edge<Te>(data, weight);//创建新边
		this->e++;//边数
		V[i].outDegree++;
		V[j].inDegree++;//两者的入度出度
	}
	virtual Te remove(int i,int j) {//删除节点i->j的联边 ！？  exists(i,j)
		Te vBak = edge(i, j);
		delete E[i][j];//数据删除
		E[i][j] = NULL;//指针置空
		this->e--;
		V[i].outDegree--;
		V[j].inDegree--;
		return vBak;
	}

};



//图的遍历
template <typename Tv,typename Te>
void Graph<Tv, Te>::bfs(int s) {//assert: 0 <= s < n
	reset();//reset
	int clock = 0;int v = s;//初始化时间标签和v
	do
	{
		if (status(v) == UNDISCOVERED) {
			BFS(v, clock);
		}
	} while (s !=(v = (++v%n)));//按序号检查
}

template <typename Tv,typename Te>
void Graph<Tv, Te>::BFS(int v, int& clock) { //assert: 0 <=v < n
	Queue<int> que;//辅助栈
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
