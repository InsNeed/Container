//
//template <typename Te>
//struct Edge
//{
//	Te data;
//	int weight;
//	int type; // 数据、权重、类型
//	Edge(Te const& d, int w) : data(d), weight(w), type(0) {}
//	Edge() : data(Te()), weight(0), type(0) {}//使用Te的默认构造函数
//	~Edge() {}
//};
//
//using namespace std;
//template <typename Te>
//std::vector<std::vector<Edge<Te>>> createGraph(int numRows, int numCols)
//{
//	// 创建二维数组
//	std::vector<std::vector<Edge<Te>>> graph(numRows, std::vector<Edge<Te>>(numCols));
//
//	// 初始化二维数组中的每个元素
//	for (int i = 0; i < numRows; ++i)
//	{
//		for (int j = 0; j < numCols; ++j)
//		{
//			// 使用Edge的默认构造函数初始化每个元素
//			graph[i][j] = Edge<Te>();
//		}
//	}
//
//	return graph;
//}

//template <typename T>
//void aaa()
//{
//	vector<vector<Edge<int>>> vec1(10, vector<Edge<int>>(3, 0));
//	vector<vector<Edge<T>>> vec2(10, vector<Edge<T>>(3, 0));  // 2行3列的二维向量!!!!!!!!!!!!!!!!
//	vec1[1].push_back(Edge<int>(0, 0));
//	vec2[1].push_back(Edge<int>(0, 0));
//}


//using namespace std;
//template <typename T>
//struct aaa {
//	T data;
//	aaa() :data() {  }
//};
//
//template <typename T>
//void shit() {
//	//vector<vector<aaa<T>>> vec(5, vector<aaa<T>()>); xxxxxxxxxxxxxx
//	vector<vector<aaa<T>>> vec(5, vector<aaa<T>>(5, aaa<T>()));
//	vec[1][1].data = 42;
//	vec.
//		std::cout << vec[1][1].data;
//
//}
