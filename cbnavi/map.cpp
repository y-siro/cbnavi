#include "map.h"
using namespace std;

bool Map::find_parent(vector<int>& path, int i) {
	int parent = path[i];
	if (parent == 0) return false;
	else if (parent == 1) return true;
	if (find_parent(path, parent)) {
		cout << component[parent - 1] << " -> ";
		load[parent-1] = 2;
	}
	return true;
}

void Map::add_Vertex(const int a, const int b, int c) {
	graphlist[a].pb({ b,c });
	graphlist[b].pb({ a,c });
}

void Map::setLoadmap() {
	ifstream ifs;
	ifs.open("load.txt");
	if (!ifs.is_open()) cout << "Error opening load file" << endl;
	for (int i = 0; i < 70; ++i) {
		for (int j = 0; j < 130; ++j) {
			int in;
			ifs >> in;
			map[i][j] = in;
		}
	}
}

void Map::setcomponent() {
	ifstream ifs;
	ifs.open("cost_graph.txt");
	if (!ifs.is_open()) cout << "Error opening graph file" << endl;
	for (int i = 1; i <= gc; ++i) {
		for (int j = 1; j <= gc; ++j) {
			int val;
			ifs >> val;
			if (val) add_Vertex(i, j, val);
		}
	}	
}

void Map::showMap() {
	for (int i = 0; i < 70; ++i) {
		for (int j = 0; j < 130; ++j) {
			if (map[i][j] == 1) cout << "*";
			else if (map[i][j] == 2) cout << "*";
			else if (map[i][j] == 3) cout << "┌";
			else if (map[i][j] == 4) cout << "┐";
			else if (map[i][j] == 5) cout << "└";
			else if (map[i][j] == 6)cout << "┘";
			else if (map[i][j] == 7)cout << "─";
			else if (map[i][j] == 8)cout << "│";
			else if (map[i][j] == 9) cout << " ";
			else if (map[i][j] == 10) cout << "0";
			else if (map[i][j] == 11) cout << "1";
			else if (map[i][j] == 12) cout << "2";
			else if (map[i][j] == 13) cout << "3";
			else if (map[i][j] == 14) cout << "4";
			else if (map[i][j] == 15) cout << "5";
			else if (map[i][j] == 16) cout << "6";
			else if (map[i][j] == 17) cout << "7";
			else if (map[i][j] == 18) cout << "8";
			else if (map[i][j] == 19) cout << "9";
			else if (map[i][j] == 20) cout << "-";
			else if (map[i][j] == 21) cout << "N";
			else if (map[i][j] == 22) cout << "E";
			else if (map[i][j] == 23) cout << "S";
			else if (map[i][j] == 24) cout << "|";
			else cout << " ";
			
		}
		cout << endl;
	}
}

void Map::shortest_path(int cur,int end) {
	cout << component[cur - 1] << " -> ";
	
	for (int i = 1; i <= gc; ++i) {
		if (i == cur) continue;
		if(i == end and find_parent(path, i)) cout << component[i - 1] << "   " << dist[i];
	}
	cout << "분 정도 소요가 예상됩니다." << endl;
}