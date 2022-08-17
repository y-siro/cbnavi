#include "map.h"
using namespace std;

pathfind::pathfind() {
	map = new vi[130];
	graphlist = new list<pii>[gc + 1];
	for (int i = 0; i < 70; ++i) {
		for (int j = 0; j < 130; ++j) {
			map[i].pb(0);
		}
	}
	path = vi(gc+1, 0);
	dist = vi(gc+1, M);
	load = vi(gc+1, 0);
}

void pathfind::clear() {
	path = vi(gc + 1, 0);
	dist = vi(gc + 1, M);
	load = vi(gc + 1, 0);
}

void pathfind::search(int s, int e) {
	dijkstra(s);
	shortest_path(s, e);
	load[s - 1] = 2; load[e - 1] = 2;
	for (int i = 0; i < 54; ++i) if (load[i] == 2) track_finding(s, e, i, load);
	cout << endl;
	clear();
}

void pathfind::dijkstra(int start) {
	dist[start] = 0;
	q.push(mp(start, 0));
	while (!q.empty()) {
		int cur = q.top().F;
		q.pop();
		for (iter = graphlist[cur].begin(); iter != graphlist[cur].end(); ++iter) {
			if (dist[(*iter).F] > dist[cur] + (*iter).S) {
				dist[(*iter).F] = dist[cur] + (*iter).second;
				q.push({iter->F,dist[iter->F]});
				path[iter->F] = cur;
			}
		}
	}
}

void pathfind::track_finding(int start, int end, int num, vector<int>& load) {
	if (num == 0) { // N2, case:1,2
		if (load[1] == 2) {
			for (int i = 10; i <= 17; ++i) map[20][i] = 2;
			for (int i = 20; i <= 27; ++i) map[i][17] = 2;
		}
		if (load[2] == 2) {
			for (int i = 9; i <= 22; ++i) map[20][i] = 2;
		}
	}
	if (num == 1) { // S21, case:2,3,4,13
		if (load[2] == 2) {
			for (int i = 20; i <= 27; ++i) map[i][17] = 2;
			for (int i = 17; i <= 22; ++i) map[20][i] = 2;
		}
		if (load[3] == 2) {
			for (int i = 27; i <= 32; ++i) map[i][17] = 2;
			for (int i = 10; i <= 17; ++i) map[32][i] = 2;
			map[33][10] = 2;
		}
		if (load[4] == 2) {
			for (int i = 27; i <= 34; ++i) map[i][17] = 2;
		}
		if (load[13] == 2) {
			for (int i = 17; i <= 37; ++i) map[27][i] = 2;
		}
	}
	if (num == 2) { // N10, case:15,16
		if (load[15] == 2) {
			for (int i = 22; i <= 43; ++i) map[20][i] = 2;
		}
		if (load[16] == 2) {
			for (int i = 22; i <= 43; ++i) map[20][i] = 2;
			for (int i = 13; i <= 20; ++i) map[i][42] = 2;
		}
	}
	if (num == 3) {// S18, case:4
		if (load[4] == 2) {
			map[34][10] = 2;
		}
	}
	if (num == 4) { // S20, case:5
		if (load[5] == 2) {
			for (int i = 34; i <= 39; ++i) map[i][17] = 2;
		}
	}
	if (num == 5) { // 양성재, case: 6,7
		if (load[6] == 2) {
			for (int i = 17; i <= 27; ++i) map[39][i] = 2;
			map[38][27] = 2;
			for (int i = 27; i <= 31; ++i) map[37][i] = 2;
		}
		if (load[7] == 2) {
			for (int i = 17; i <= 38; ++i) map[39][i] = 2;
		}
	}
	if (num == 6) { // S14(동아리방), case: 7,8,13,14,22
		if (load[7] == 2) {
			for (int i = 37; i <= 39; ++i) map[i][31] = 2;
			for (int i = 31; i <= 36; ++i) map[39][i] = 2;
		}
		if (load[8] == 2) {
			for (int i = 31; i <= 39; ++i) map[37][i] = 2;
			map[38][39] = 2;
		}
		if (load[13] == 2) {
			for (int i = 31; i <= 38; ++i) map[37][i] = 2;
			for (int i = 27; i <= 37; ++i) map[i][38] = 2;
			map[27][37] = 2;
		}
		if (load[14] == 2) {
			for (int i = 31; i <= 38; ++i) map[37][i] = 2;
			for (int i = 27; i <= 37; ++i) map[i][38] = 2;
			for (int i = 38; i <= 43; ++i) map[27][i] = 2;
			for (int i = 23; i <= 27; ++i) map[i][43] = 2;			
		}
		if (load[22] == 2) {
			for (int i = 31; i <= 38; ++i) map[37][i] = 2;
			for (int i = 27; i <= 37; ++i) map[i][38] = 2;
			for (int i = 38; i <= 47; ++i) map[27][i] = 2;
		}
	}
	if (num == 7) { //공연장(S8), case: 8,9,22,23,24,25
		if (load[8] == 2) {
			for (int i = 33; i <= 39; ++i) map[39][i] = 2;
			map[38][39] = 2;
		}
		if (load[9] == 2) {
			for (int i = 37; i <= 38; ++i) map[39][i] = 2;
			for (int i = 39; i <= 45; ++i) map[i][38] = 2;
		}
		if (load[22] == 2) {
			for (int i = 39; i <= 47; ++i) map[39][i] = 2;
			for (int i = 31; i <= 39; ++i) map[i][47] = 2;
		}
		if (load[23] == 2) {
			for (int i = 39; i <= 47; ++i) map[39][i] = 2;
			for (int i = 35; i <= 39; ++i) map[i][47] = 2;
			for (int i = 47; i <= 53; ++i) map[35][i] = 2;
		}
		if (load[24] == 2) {
			for (int i = 39; i <= 56; ++i) map[39][i] = 2;
			map[38][56] = 2;
		}
		if (load[25] == 2) {
			for (int i = 39; i <= 52; ++i) map[39][i] = 2;
			for (int i = 40; i <= 41; ++i) map[i][52] = 2;
		}
	}
	if (num == 8) { //박물관, case: 9,13,14,22,23,24,25
		if (load[9] == 2) {
			for (int i = 38; i <= 39; ++i) map[i][39] = 2;
			for (int i = 39; i <= 45; ++i) map[i][38] = 2;
		}
		if (load[13] == 2) {
			for (int i = 37; i <= 38; ++i) map[i][39] = 2;
			for (int i = 27; i <= 37; ++i) map[i][38] = 2;
		}
		if (load[14] == 2) {
			for (int i = 37; i <= 38; ++i) map[i][39] = 2;
			for (int i = 27; i <= 37; ++i) map[i][38] = 2;
			for (int i = 38; i <= 43; ++i) map[27][i] = 2;
			for (int i = 23; i <= 26; ++i) map[i][43] = 2;
		}
		if (load[22] == 2) {
			for (int i = 38; i <= 39; ++i) map[i][39] = 2;
			for (int i = 39; i <= 47; ++i) map[39][i] = 2;
			for (int i = 31; i <= 39; ++i) map[i][47] = 2;
		}
		if (load[23] == 2) {
			for (int i = 38; i <= 39; ++i) map[i][39] = 2;
			for (int i = 39; i <= 47; ++i) map[39][i] = 2;
			for (int i = 35; i <= 39; ++i) map[i][47] = 2;
			for (int i = 47; i <= 53; ++i) map[35][i] = 2;
		}
		if (load[24] == 2) {
			for (int i = 38; i <= 39; ++i) map[i][39] = 2;
			for (int i = 39; i <= 56; ++i) map[39][i] = 2;
			map[38][56] = 2;
		}
		if (load[25] == 2) {
			for (int i = 38; i <= 39; ++i) map[i][39] = 2;
			for (int i = 39; i <= 52; ++i) map[39][i] = 2;
			for (int i = 40; i <= 41; ++i) map[i][52] = 2;
		}
	}
	if (num == 9) { // S3, case: 10,22,23,24,25
		if (load[10] == 2) {
			for (int i = 45; i <= 47; ++i) map[i][38] = 2;
			for (int i = 38; i <= 41; ++i) map[47][i] = 2;
		}
		if (load[22] == 2) {
			for (int i = 39; i <= 45; ++i) map[i][38] = 2;
			for (int i = 39; i <= 47; ++i) map[39][i] = 2;
			for (int i = 31; i <= 39; ++i) map[i][47] = 2;
		}
		if (load[23] == 2) {
			for (int i = 39; i <= 45; ++i) map[i][38] = 2;
			for (int i = 39; i <= 47; ++i) map[39][i] = 2;
			for (int i = 35; i <= 39; ++i) map[i][47] = 2;
			for (int i = 47; i <= 53; ++i) map[35][i] = 2;
		}
		if (load[24] == 2) {
			for (int i = 39; i <= 45; ++i) map[i][38] = 2;
			for (int i = 39; i <= 56; ++i) map[39][i] = 2;
			map[38][56] = 2;
		}
		if (load[25] == 2) {
			for (int i = 39; i <= 45; ++i) map[i][38] = 2;
			for (int i = 39; i <= 52; ++i) map[39][i] = 2;
			for (int i = 40; i <= 41; ++i) map[i][52] = 2;
		}
	}
	if (num == 10) { // S4-1, case: 11,12
		if (load[11] == 2) {
			for (int i = 51; i <= 56; ++i) map[i][45] = 2;
		}
		if (load[12] == 2) {
			for (int i = 41; i <= 45; ++i) map[47][i] = 2;
		}		
	}
	if (num == 11) { // S4-2, case: 12,    case-ex:(고려 안해봐도 될거 같은것들 예시)21,25,38,39,46
		if (load[12] == 2) {
			for (int i = 47; i <= 56; ++i) map[i][45] = 2;
		}		
	}
	if (num == 12) { // S2, case: 20
		if (load[20] == 2) {
			for (int i = 45; i <= 53; ++i) map[47][i] = 2;
		}
	}
	if (num == 13) { // N11, case: 14, 22
		if (load[14] == 2) {
			for (int i = 37; i <= 43; ++i) map[27][i] = 2;
			for (int i = 23; i <= 27; ++i) map[i][43] = 2;
		}
		if (load[22] == 2) {
			for (int i = 37; i <= 47; ++i) map[27][i] = 2;
		}
	}
	if (num == 14) { // 솔못, case: 15,22,23,26,27,34,36
		if (load[15] == 2) {
			for (int i = 20; i <= 23; ++i) map[i][43] = 2;
			//
		}
		if (load[22] == 2) {
			for (int i = 23; i <= 27; ++i) map[i][43] = 2;
			for (int i = 43; i <= 47; ++i) map[27][i] = 2;
		}
		if (load[23] == 2) {
			for (int i = 23; i <= 27; ++i) map[i][50] = 2;
			for (int i = 51; i <= 60; ++i) map[27][i] = 2;
			for (int i = 28; i <= 33; ++i) map[i][60] = 2;
		}
		if (load[26] == 2) {
			for (int i = 23; i <= 27; ++i) map[i][50] = 2;
			for (int i = 51; i <= 60; ++i) map[27][i] = 2;
			for (int i = 24; i <= 27; ++i) map[i][60] = 2;
		}
		if (load[27] == 2) {
			for (int i = 20; i <= 23; ++i) map[i][50] = 2;
			for (int i = 50; i <= 58; ++i) map[20][i] = 2;
		}
		if (load[34] == 2) {
			for (int i = 23; i <= 27; ++i) map[i][50] = 2;
			for (int i = 51; i <= 61; ++i) map[27][i] = 2;
			for (int i = 23; i <= 27; ++i) map[i][51] = 2;
		}
		if (load[36] == 2) {
			for (int i = 23; i <= 27; ++i) map[i][50] = 2;
			for (int i = 51; i <= 67; ++i) map[27][i] = 2;
		}
	}
	if (num == 15) { // N13, case: 16,27
		if (load[16] == 2) {
			for (int i = 42; i <= 43; ++i) map[20][i] = 2;
			for (int i = 13; i <= 19; ++i) map[i][42] = 2;
		}
		if (load[27] == 2) {
			for (int i = 46; i <= 58; ++i) map[20][i] = 2;
		}
	}
	if (num == 16) { // N14, case: 17
		if (load[17] == 2) {
			for (int i = 12; i <= 13; ++i) map[i][42] = 2;
		}
	}
	if (num == 17) { //N16-2, case: 18,19
		if (load[18] == 2) {
			for (int i = 6; i <= 12; ++i) map[i][42] = 2;
			for (int i = 38; i <= 42; ++i) map[6][i] = 2;
		}
		if (load[19] == 2) {
			for (int i = 6; i <= 12; ++i) map[i][42] = 2;
			for (int i = 43; i <= 44; ++i) map[6][i] = 2;
		}
	}
	if (num == 18) { // N17, case: 19
		if (load[19] == 2) {
			for (int i = 38; i <= 44; ++i) map[6][i] = 2;
		}
	}
	if (num == 19) { // N18, case: 33
		if (load[33] == 2) {
			for (int i = 53; i <= 54; ++i) map[6][i] = 2;
		}
	}
	if (num == 20) { //S1-5, case: 21
		if (load[21] == 2) {
			for (int i = 53; i <= 56; ++i) map[47][i] = 2;
		}
	}
	if (num == 21) { //S1-4, case: 25, 38,39, ex: 46
		if (load[25] == 2) {
			for (int i = 56; i <= 60; ++i) map[47][i] = 2;
			for (int i = 42; i <= 46; ++i) map[i][60] = 2;
		}
		if (load[38] == 2) {
			for (int i = 56; i <= 61; ++i) map[47][i] = 2;
		}
		if (load[39] == 2) {
			for (int i = 56; i <= 60; ++i) map[47][i] = 2;
			for (int i = 48; i <= 50; ++i) map[i][60] = 2;
			for (int i = 61; i < 63; ++i) map[50][i] = 2;
		}
	}
	if (num == 22) { //S1-1, case: 23,24,25,26,34,36
		if (load[23] == 2) {
			for (int i = 47; i <= 52; ++i) map[31][i] = 2;
			for (int i = 32; i <= 35; ++i) map[i][52] = 2;
			map[35][53] = 2;
		}
		if (load[24] == 2) {
			for (int i = 47; i <= 52; ++i) map[31][i] = 2;
			for (int i = 32; i <= 38; ++i) map[i][52] = 2;
			for (int i = 53; i <= 56; ++i) map[38][i] = 2;
		}
		if (load[25] == 2) {
			for (int i = 47; i <= 52; ++i) map[31][i] = 2;
			for (int i = 32; i <= 41; ++i) map[i][52] = 2;
		}
		if (load[26] == 2) {
			for (int i = 47; i <= 60; ++i) map[27][i] = 2;
			for (int i = 24; i <= 27; ++i) map[i][60] = 2;
		}
		if (load[34] == 2) {
			for (int i = 47; i <= 61; ++i) map[27][i] = 2;
			for (int i = 23; i <= 26; ++i) map[i][61] = 2;
		}
		if (load[36] == 2) {
			for (int i = 47; i <= 67; ++i) map[27][i] = 2;
		}
	}
	if (num == 23) { // S1-2, case: 24,25,26,34,36
		if (load[24] == 2) {
			for (int i = 53; i <= 56; ++i) map[35][i] = 2;
			for (int i = 36; i <= 38; ++i) map[i][56] = 2;
		}
		if (load[25] == 2) {
			for (int i = 33; i <= 42; ++i) map[i][60] = 2;
		}
		if (load[26] == 2) {
			for (int i = 24; i <= 33; ++i) map[i][60] = 2;
		}
		if (load[34] == 2) {
			for (int i = 27; i <= 33; ++i) map[i][60] = 2;
			for (int i = 23; i <= 27; ++i) map[i][61] = 2;
		}
		if (load[36] == 2) {
			for (int i = 27; i <= 33; ++i) map[i][60] = 2;
			for (int i = 60; i <= 67; ++i) map[27][i] = 2;
		}
	}
	if (num == 24) { // S1-7, case: 25, 37,
		if (load[25] == 2) {
			for (int i = 52; i <= 56; ++i) map[38][i] = 2;
			for (int i = 39; i <= 41; ++i) map[i][52] = 2;
		}
		if (load[37] == 2) {
			for (int i = 37; i <= 38; ++i) map[i][60] = 2;
		}
	}
	if (num == 25) { // S1-3, case: 37,38,39,  ex_case: 46
		if (load[37] == 2) {
			for (int i = 60; i <= 64; ++i) map[42][i] = 2;
			for (int i = 39; i <= 41; ++i) map[i][64] = 2;
		}
		if (load[38] == 2) {
			for (int i = 42; i <= 47; ++i) map[i][60] = 2;
			map[47][61] = 2;
		}
		if (load[39] == 2) {
			for (int i = 42; i <= 50; ++i) map[i][60] = 2;
			for (int i = 61; i <= 63; ++i) map[50][i] = 2;
		}
	}
	if (num == 26) { //도서관, case: 27,28,34,35,36,  ex_case: 40,47
		if (load[27] == 2) {
			for (int i = 20; i <= 24; ++i) map[i][60] = 2;
			for (int i = 54; i <= 60; ++i) map[20][i] = 2;
		}
		if (load[28] == 2) {
			for (int i = 20; i <= 24; ++i) map[i][60] = 2;
			for (int i = 61; i <= 64; ++i) map[20][i] = 2;
			for (int i = 16; i <= 19; ++i) map[i][64] = 2;
		}
		if (load[34] == 2) {
			map[23][60] = 2;
			map[23][61] = 2;
			map[24][60] = 2;
		}
		if (load[35] == 2) {
			for (int i = 20; i <= 24; ++i) map[i][60] = 2;
			for (int i = 61; i <= 67; ++i) map[20][i] = 2;
			for (int i = 21; i <= 23; ++i) map[i][67] = 2;
		}
		if (load[36] == 2) {
			for (int i = 24; i <= 27; ++i) map[i][60] = 2;
			for (int i = 61; i <= 67; ++i) map[27][i] = 2;
		}
	}
	if (num == 27) { // N15, case: 28,34,35, ex_case: 36,40,47
		if (load[28] == 2) {
			for (int i = 58; i <= 64; ++i) map[20][i] = 2;
			for (int i = 16; i <= 19; ++i) map[i][64] = 2;
		}
		if (load[34] == 2) {
			for (int i = 58; i <= 61; ++i) map[20][i] = 2;
			for (int i = 21; i <= 23; ++i) map[i][61] = 2;
		}
		if (load[35] == 2) {
			for (int i = 58; i <= 67; ++i) map[20][i] = 2;
			for (int i = 21; i <= 23; ++i) map[i][67] = 2;
		}
	}
	if (num == 28) { // E2, case: 29,30,31,34,35, ex_case: 36,40,47
		if (load[29] == 2) {
			for (int i = 12; i <= 16; ++i) map[i][64] = 2;
			for (int i = 59; i <= 63; ++i) map[12][i] = 2;
		}
		if (load[30] == 2) {
			for (int i = 9; i <= 16; ++i) map[i][64] = 2;
			for (int i = 64; i <= 67; ++i) map[9][i] = 2;
		}
		if (load[31] == 2) {
			for (int i = 6; i <= 16; ++i) map[i][64] = 2;
		}
		if (load[34] == 2) {
			for (int i = 16; i <= 20; ++i) map[i][64] = 2;
			for (int i = 61; i <= 63; ++i) map[20][i] = 2;
			for (int i = 21; i <= 23; ++i) map[i][61] = 2;
		}
		if (load[35] == 2) {
			for (int i = 16; i <= 20; ++i) map[i][64] = 2;
			for (int i = 65; i <= 67; ++i) map[20][i] = 2;
			for (int i = 21; i <= 23; ++i) map[i][67] = 2;
		}
		if (load[40] == 2) {
			for (int i = 16; i <= 20; ++i) map[i][64] = 2;
			for (int i = 65; i <= 73; ++i) map[20][i] = 2;
			for (int i = 21; i <= 27; ++i) map[i][73] = 2;
			for (int i = 27; i <= 33; ++i) map[i][74] = 2;
		}
	}
	if (num == 29) { // N16-1, case: 30,31
		if (load[30] == 2) {
			for (int i = 59; i <= 63; ++i) map[12][i] = 2;
			for (int i = 9; i <= 12; ++i) map[i][64] = 2;
			for (int i = 64; i <= 67; ++i) map[9][i] = 2;			
		}
		if (load[31] == 2) {
			for (int i = 59; i <= 63; ++i) map[12][i] = 2;
			for (int i = 6; i <= 12; ++i) map[i][64] = 2;
		}
	}
	if (num == 30) { // E1, case: 31
		if (load[31] == 2) {
			for (int i = 64; i <= 67; ++i) map[9][i] = 2;
			for (int i = 6; i <= 9; ++i) map[i][64] = 2;
		}
	}
	if (num == 31) { //N21, case: 32, 33
		if (load[32] == 2) {
			for (int i = 64; i <= 67; ++i) map[6][i] = 2;
		}
		if (load[33] == 2) {
			for (int i = 62; i <= 64; ++i) map[6][i] = 2;
		}
	}
	//num == 32 - N20, case: none
	//num == 33 - N19, case: none
	if (num == 34) { // 신학, case: 35, 36,40, 47
		if (load[35] == 2) {
			for (int i = 20; i <= 23; ++i) map[i][61] = 2;
			for (int i = 62; i <= 67; ++i) map[20][i] = 2;
			for (int i = 21; i <= 23; ++i) map[i][67] = 2;
		}
		if (load[36] == 2) {
			for (int i = 23; i <= 28; ++i) map[i][61] = 2;
			for (int i = 62; i <= 67; ++i) map[27][i] = 2;
		}
	}
	if (num == 35) { //NH관, case: 36, ex_case: 40,47
		if (load[36] == 2) {
			for (int i = 23; i <= 27; ++i) map[i][67] = 2;
		}
	}
	if (num == 36) { // E8-1, case: 40, 47
		if (load[40] == 2) {
			for (int i = 67; i <= 74; ++i) map[27][i] = 2;
			for (int i = 28; i <= 33; ++i) map[i][74] = 2;
		}
		if (load[47] == 2) {
			for (int i = 67; i <= 86; ++i) map[27][i] = 2;
		}
	}
	if (num == 37) { //E8-2, case: 40,41,42
		if (load[41] == 2) {
			for (int i = 35; i <= 37; ++i) map[i][74] = 2;
		}
		if (load[42] == 2) {
			for (int i = 37; i <= 42; ++i) map[i][74] = 2;
		}
	}
	if (num == 38) { // E8-7, case: 39,42,43,44
		if (load[39] == 2) {
			for (int i = 60; i <= 61; ++i) map[47][i] = 2;
			for (int i = 48; i <= 50; ++i) map[i][60] = 2;
			for (int i = 61; i <= 63; ++i) map[50][i] = 2;
		}
		if (load[42] == 2) {
			for (int i = 42; i <= 46; ++i) map[i][74] = 2;
		}
		if (load[43] == 2) {
			for (int i = 45; i <= 46; ++i) map[i][74] = 2;
			for (int i = 75; i <= 80; ++i) map[45][i] = 2;
		}
		if (load[44] == 2) {
			for (int i = 46; i <= 47; ++i) map[i][74] = 2;
		}
	}
	if (num == 39) {// E9, case: 45,  ex_case: 46
		if (load[45] == 2) {
			for (int i = 63; i <= 68; ++i) map[50][i] = 2;
		}
	}
	if (num == 40) { // E8-3, case: 41, 47
		if (load[41] == 2) {
			for (int i = 33; i <= 35; ++i) map[i][74] = 2;
		}
		if (load[47] == 2) {
			for (int i = 27; i <= 33; ++i) map[i][74] = 2;
			for (int i = 75; i <= 86; ++i) map[27][i] = 2;
		}
	}
	// num==41 - E8-4, case: none
	if (num == 42) { // E8-5, case: 43, 44
		if (load[43] == 2) {
			for (int i = 42; i <= 45; ++i) map[i][74] = 2;
			for (int i = 75; i <= 80; ++i) map[45][i] = 2;
		}
		if (load[44] == 2) {
			for (int i = 42; i <= 46; ++i) map[i][74] = 2;
		}
	}
	if (num == 43) { // E8-8, case: 44
		if (load[44] == 2) {
			map[46][80] = 2;
		}
	}
	if (num == 44) { // E8-6, case: 45
		if (load[45] == 2) {
			for (int i = 47; i <= 50; ++i) map[i][74] = 2;
		}
	}
	if (num == 45) { // E10, case: 46
		if (load[46] == 2) {
			for (int i = 50; i <= 53; ++i) map[i][74] = 2;
		}
	}
	if (num == 46) { // E8-10, case: 48
		if (load[48] == 2) {
			for (int i = 82; i <= 86; ++i) map[53][i] = 2;
		}
	}
	if (num == 47) { // 소운동장, case: 48,49
		if (load[48] == 2) {
			for (int i = 27; i <= 53; ++i) map[i][86] = 2;
		}
		if (load[49] == 2) {
			for (int i = 86; i <= 90; ++i) map[27][i] = 2;
		}
	}
	//num==48 - 양진재, case: none
	if (num == 49) { //E7-3, case: 51,52
		if (load[51] == 2) {
			for (int i = 90; i <= 99; ++i) map[27][i] = 2;
		}
		if (load[52] == 2) {
			for (int i = 91; i <= 96; ++i) map[27][i] = 2;
			for (int i = 28; i <= 32; ++i) map[i][96] = 2;
		}
	}
	if (num == 50) { // 대운동장, case: 51, 53
		if (load[51] == 2) {
			for (int i = 99; i <= 105; ++i) map[27][i] = 2;
		}
		if (load[53] == 2) {
			for (int i = 105; i <= 119; ++i) map[27][i] = 2;
		}
	}
	if (num == 51) { // E7-1, case: 52
		if (load[52] == 2) {
			for (int i = 106; i <= 109; ++i) map[27][i] = 2;
			for (int i = 28; i <= 32; ++i) map[i][106] = 2;
		}
	}
	// num == 52 - E7-2, case: none
	// num == 53 - 충북대학교 병원, case: none
}	

int pathfind::matching(string str) {
	if (str == "N2" || str == "N3" || str == "N4" || str == "N5" || str == "N6" || str == "N7" || str == "N8" || str == "N9" || str == "법학전문대학원" || str == "형설관" || str == "국제교류본부" || str == "CBNU STAR") return 1;
	else if (str == "S21" || str == "농업과학기술센터" || str == "건조실") return 2;
	else if (str == "N10" || str == "대학 본부" || str == "대학본부" || str == "국제교류본부" || str == "국제 교류 본부") return 3;
	else if (str == "S18" || str == "S19" || str == "승리관" || str == "종양연구소") return 4;
	else if (str == "S20" || str == "첨단바이오 연구센터") return 5;
	else if (str == "S17" || str == "양성재") return 6;
	else if (str == "S14" || str == "제2학생회관" || str == "동아리방") return 7;
	else if (str == "S8" || str == "야외공원장" || str == "공터") return 8;
	else if (str == "S9" || str == "박물관") return 9;
	else if (str == "S3" || str == "본부관리동 창고") return 10;
	else if (str == "S4-1" || str == "전자정보 3관") return 11;
	else if (str == "S4-2" || str == "나이팅게일관") return 12;
	else if (str == "S2" || str == "전산정보원") return 13;
	else if (str == "N11" || str == "공동실험실습관") return 14;
	else if (str == "솔못" || str == "SN") return 15;
	else if (str == "N13" || str == "경영학관") return 16;
	else if (str == "N14" || str == "인문사회관") return 17;
	else if (str == "N16-2" || str == "미술관") return 18;
	else if (str == "N17" || str == "개성재") return 19;
	else if (str == "N18" || str == "법학관") return 20;
	else if (str == "S1-5" || str == "자연과학대학 5호관") return 21;
	else if (str == "S1-4" || str == "자연과학대학 4호관") return 22;
	else if (str == "S1-1" || str == "자연과학대학 1호관") return 23;
	else if (str == "S1-2" || str == "자연과학대학 2호관") return 24;
	else if (str == "S1-7" || str == "과학기술도서관" || str == "과기도") return 25;
	else if (str == "S1-3" || str == "자연과학대학 3호관") return 26;
	else if (str == "N12" || str == "도서관" || str=="중앙 도서관" || str=="중앙도서관") return 27;
	else if (str == "N15" || str == "사회과학대학 본관") return 28;
	else if (str == "E2" || str == "개신중앙관" || str == "개신문화관" || str == "충북대 서점" || str == "서점") return 29;
	else if (str == "N16-1" || str == "인문대학 본관") return 30;
	else if (str == "E1" || str == "사범대학" || str == "사범대" || str == "사대") return 31;
	else if (str == "N21" || str == "은하수식당") return 32;
	else if (str == "N20" || str == "생활과학관" || str == "어린이집" || str == "직장 어린이집") return 33;
	else if (str == "N19" || str == "제2본관") return 34;
	else if (str == "E3" || str == "제1학생회관" || str == "신학생회관" || str == "신학") return 35;
	else if (str == "E3-1" || str == "NH관" || str == "헬스장") return 36;
	else if (str == "E8-1" || str == "공과대학 1호관") return 37;
	else if (str == "E8-2" || str == " 공대 합동강의동") return 38;
	else if (str == "E8-7" || str == "전자정보 1관") return 39;
	else if (str == "E9" || str == "학연산" || str == "학연산공동기술연구원") return 40;
	else if (str == "E8-3" || str == "공과대학 2호관") return 41;
	else if (str == "E8-4" || str == "제1공장동" || str == "1공장") return 42;
	else if (str == "E8-5" || str == "제2공장동" || str == "2공장") return 43;
	else if (str == "E8-8" || str == "공과대학 4호관") return 44;
	else if (str == "E8-6" || str == "공과대학 3호관") return 45;
	else if (str == "E10" || str == "전자정보 2관") return 46;
	else if (str == "E8-10" || str == "공과대학 5호관") return 47;
	else if (str == "소운동장" || str == "E4-1") return 48;
	else if (str == "양진재" || str == "E8-11") return 49;
	else if (str == "E7-3" || str == "의과대학 2호관") return 50;
	else if (str == "대운동장" || str == "E4-2") return 51;
	else if (str == "E7-1" || str == "의과대학 1호관") return 52;
	else if (str == "E7-2") return 53;
	else if (str == "충북대학교 병원" || str == "충대 병원" || str == "병원" || str == "E7-4" || str == "학교 병원") return 54;
	else return 0;
}