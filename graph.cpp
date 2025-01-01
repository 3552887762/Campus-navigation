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
		cerr << "�޷����ļ�" << endl;
		return;
	}
	infile >> vernum >> arcnum;
	verlists.resize(vernum);
	edges.resize(vernum, vector<int>(vernum, INF));

	// ��ȡ�ڵ�����
	for (int i = 0; i < vernum; ++i) {
		infile >> verlists[i];
	}

	int start, end, weight;
	// ��ȡ�ߵ���Ϣ
	for (int i = 0; i < arcnum; ++i) {
		infile >> start >> end >> weight;
		edges[start][end] = weight;
		edges[end][start] = weight;
	}

	infile.close();  // �ر��ļ�
}

void Graph::PrintGraph() {
	cout << "������Ϣ��";
	for (int i = 0; i < this->vernum; i++) {
		cout << this->verlists[i] << " ";
	}
	cout << endl;
	cout << "�ڽӾ���" << endl;
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
	vector<int> prev(vernum, -1); // ǰ�����飬��¼���·����ÿ�������ǰһ������  
	dist[src] = 0;
	//������������
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
					prev[v] = u; // ����ǰ������  
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
		if (InputBox(inputBuffer, 100, "�������յ㶥����(��0��ʼ): \n����\"end\"�˳�����"))
		{
			string inputStr(inputBuffer);
			if (inputStr == "end") {
				break;
			}
			try {
				int src_vertex = std::stoi(inputBuffer);
				if (src_vertex >= 13 || src_vertex < 0)
				{
					MessageBox(NULL, "��������ֲ��ڷ�Χ��\n����������", "У԰����", MB_OKCANCEL);
					continue;
				}
				ans.clear();
				cout << verlists[src] << " �� " << verlists[src_vertex] << " �����·������Ϊ " << dist[src_vertex] << endl;
				ans += verlists[src];
				ans += "��";
				ans += verlists[src_vertex];
				ans += "�����·������Ϊ��";
				ans += to_string(dist[src_vertex]);
				ans += '\n';
				PrintPath(src, src_vertex, prev);
				ans += '\n';
				cout << '\n';
				MessageBox(NULL, ans.c_str(), "У԰����", MB_OKCANCEL);
				break;
				cout << '\n';
				cout << '\n';
			}
			catch (const std::invalid_argument& e) {
				MessageBox(NULL, "����Ĳ�������\n����������", "У԰����", MB_OKCANCEL);
				continue;
			}
		}
	}
	ans.clear();
}

void Graph::PrintPath(int src, int target, const vector<int>& prev) {
	if (target == src) {
		cout << "·��������" << verlists[target]; // ·�����
		ans += verlists[target];
	}
	else {
		PrintPath(src, prev[target], prev); // �ȴ�ӡǰһ������  
		cout << " -> " << verlists[target]; // ��ǰ����
		ans += " -> ";
		ans += verlists[target];
	}
}
#endif