//
//template <typename Te>
//struct Edge
//{
//	Te data;
//	int weight;
//	int type; // ���ݡ�Ȩ�ء�����
//	Edge(Te const& d, int w) : data(d), weight(w), type(0) {}
//	Edge() : data(Te()), weight(0), type(0) {}//ʹ��Te��Ĭ�Ϲ��캯��
//	~Edge() {}
//};
//
//using namespace std;
//template <typename Te>
//std::vector<std::vector<Edge<Te>>> createGraph(int numRows, int numCols)
//{
//	// ������ά����
//	std::vector<std::vector<Edge<Te>>> graph(numRows, std::vector<Edge<Te>>(numCols));
//
//	// ��ʼ����ά�����е�ÿ��Ԫ��
//	for (int i = 0; i < numRows; ++i)
//	{
//		for (int j = 0; j < numCols; ++j)
//		{
//			// ʹ��Edge��Ĭ�Ϲ��캯����ʼ��ÿ��Ԫ��
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
//	vector<vector<Edge<T>>> vec2(10, vector<Edge<T>>(3, 0));  // 2��3�еĶ�ά����!!!!!!!!!!!!!!!!
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
