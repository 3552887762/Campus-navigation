#include "Graph.hpp" 
#include <easyx.h> 
#include <conio.h> 
#include <graphics.h> 
#include <string>
#pragma comment(lib,"winmm.lib") 

Graph::Graph() :arcnum(0), vernum(0)
{
	ifstream infile("E:\\Documents\\111.txt");
	if (!infile) {
		cerr << "无法打开文件" << endl;
		return;
	}
	infile >> vernum >> arcnum;
	verlists.resize(vernum);
	edges.resize(vernum, vector<int>(vernum, INF));

	// 读取节点名称
	for (int i = 0; i < vernum; ++i) {
		infile >> verlists[i];
	}

	int start, end, weight;
	// 读取边的信息
	for (int i = 0; i < arcnum; ++i) {
		infile >> start >> end >> weight;
		edges[start][end] = weight;
		edges[end][start] = weight;
	}

	infile.close();  // 关闭文件
}

void Graph::PrintGraph() {
	cout << "顶点信息：";
	for (int i = 0; i < this->vernum; i++) {
		cout << this->verlists[i] << " ";
	}
	cout << endl;
	cout << "邻接矩阵：" << endl;
	for (int i = 0; i < this->vernum; i++) {
		for (int j = 0; j < this->vernum; j++) {
			if (edges[i][j] == INF) {
				cout << "INF ";
			}
			else {
				cout << edges[i][j] << " ";
			}
		}
		cout << endl;
	}
}

void Graph::DijkstraShortestPath(int src) {
	vector<int> dist(vernum, INF);
	vector<int> prev(vernum, -1); // 前驱数组，记录最短路径上每个顶点的前一个顶点  
	dist[src] = 0;
	//按照升序排列
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
	pq.push({ 0, src });

	while (!pq.empty()) {
		int u = pq.top().second;
		int curr_dist = pq.top().first;
		pq.pop();

		if (curr_dist > dist[u]) continue;

		for (int v = 0; v < vernum; ++v) {
			if (edges[u][v] != INF) {
				int weight = edges[u][v];
				if (dist[u] + weight < dist[v]) {
					dist[v] = dist[u] + weight;
					prev[v] = u; // 更新前驱顶点  
					pq.push({ dist[v], v });
				}
			}
		}
	}

	cout << '\n';

#if 1
	cout << '\n';
	while (true) {
		char inputBuffer[100];
		if (InputBox(inputBuffer, 100, "请输入终点顶点编号(从0开始): \n输入\"end\"退出程序"))
		{
			string inputStr(inputBuffer);
			if (inputStr == "end") {
				break;
			}
			try {
				int src_vertex = std::stoi(inputBuffer);
				if (src_vertex >= 13 || src_vertex < 0)
				{
					MessageBox(NULL, "输入的数字不在范围内\n请重新输入", "校园导航", MB_OKCANCEL);
					continue;
				}
				ans.clear();
				cout << verlists[src] << " 到 " << verlists[src_vertex] << " 的最短路径长度为 " << dist[src_vertex] << endl;
				ans += verlists[src];
				ans += "到";
				ans += verlists[src_vertex];
				ans += "的最短路径长度为：";
				ans += to_string(dist[src_vertex]);
				ans += '\n';
				PrintPath(src, src_vertex, prev);
				ans += '\n';
				cout << '\n';
				MessageBox(NULL, ans.c_str(), "校园导航", MB_OKCANCEL);
				break;
				cout << '\n';
				cout << '\n';
			}
			catch (const std::invalid_argument& e) {
				MessageBox(NULL, "输入的不是数字\n请重新输入", "校园导航", MB_OKCANCEL);
				continue;
			}
		}
	}
	ans.clear();
}

void Graph::PrintPath(int src, int target, const vector<int>& prev) {
	if (target == src) {
		cout << "路径经历：" << verlists[target]; // 路径起点
		ans += verlists[target];
	}
	else {
		PrintPath(src, prev[target], prev); // 先打印前一个顶点  
		cout << " -> " << verlists[target]; // 当前顶点
		ans += " -> ";
		ans += verlists[target];
	}
}
#endif