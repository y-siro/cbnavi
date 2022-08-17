#pragma once
#include <windows.h>
#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <vector>
#include <list>
#include <queue>
#include <string>
#include <fcntl.h>
#include <fstream>
#define fast ios_base::sync_with_stdio(false); cin.tie(NULL), cout.tie(NULL)
#define pb push_back
#define mp make_pair
#define vi vector<int>
#define pii pair<int,int>
#define F first
#define S second
#define endl "\n"
#define rib(x1,x2,y1,y2) if(x>=x1 && x<=x2 && y>=y1 && y<=y2)
using namespace std;

const int M = 1001;
const int gc = 54;

class Map {	
public:
	vi* map;
	list<pii>* graphlist;
	list<pii>::iterator iter;
	priority_queue<pii, vector<pii>, greater<pii>> q;
	vi path;
	vi dist;
	vi load;
	
	string component[gc] = {"N2(N3,N4,N5,N6,N7,N8,N9)", "S21","N10","S18,S19","S20","S17(�缺��)","S14","S8(������, ����)","S9(�ڹ���)","S3","S4-1","S4-2","S2","N11","SN(�ָ�)","N13","N14","N16-2","N17(������)","N18","S1-5","S1-4","S1-1","S1-2","S1-7","S1-3","N12(������)","N15","E2(�����߾Ӱ�)","N16-1","E1","N21","N20","N19","E3-1(����)","NH��","E8-1","E8-2","E8-7","E9","E8-3","E8-4","E8-5","E8-8","E8-6","E10","E8-10","E4-1(�ҿ��)","E8-11(������)","E7-3","E4-2(����)","E7-1","E7-2","E7-4(��ϴ��б� ����)"};
	void add_Vertex(const int a, const int b, int c); // using in add Vertex
	bool find_parent(vector<int>& path, int i);
	void setcomponent(); // component(construct)		
	void setLoadmap(); // load - usual, sheer part
	void shortest_path(int cur,int end); // dijkstra load		
	void showMap(); // show map
};


class pathfind :public Map {
public:
	pathfind();
	void clear(); // if cls, repos initialization
	void search(int s, int e);
	void dijkstra(int start);
	void track_finding(int start, int end, int num, vector<int>& load);
	int matching(string str);
};