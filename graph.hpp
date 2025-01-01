
#pragma once
#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <string>
#include <fstream>
#include <string>

using namespace std;

const int INF = numeric_limits<int>::max();

using namespace std;

typedef string NameType;

class Graph {
private:
	vector<NameType> verlists;//�������б�
	vector<vector<int>> edges; //�ڽӾ���
	int vernum;
	int arcnum;
	string ans;

public:
	Graph();

	void PrintGraph();

	void DijkstraShortestPath(int src);

	void PrintPath(int src, int target, const vector<int>& prev);

};