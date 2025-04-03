#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

struct LinkNode {
	int id;
	int row;
	LinkNode *prev, *next, *right;
	LinkNode(int id, int row): id(id), row(row)
		,prev(nullptr), next(nullptr), right(nullptr) {}
};

struct LinkList {
	int id;
	LinkNode *l, *r;
	LinkNode* append(int row) {
		LinkNode *p = new LinkNode(id, row);
		if (l == nullptr)
			l = r = p;
		else {
			r -> next = p;
			p -> prev = r;
			r = p;
		}
		return p;
	}
	void remove(LinkNode *p) {
		if (p == l && p == r) {
			delete p;
			l = r = nullptr;
			return;
		}
		if (p == r) {
			r = r -> prev;
			r -> next = nullptr;
		}
		else if (p == l) {
			l = l -> next;
			l -> prev = nullptr;
		}
		else {
			p -> prev -> next = p -> next;
			p -> next -> prev = p -> prev;
		}
		delete p;
	}
	int highest() {
		return r == nullptr ? 0 : r -> row;
	}
} cols[30010];

int w, n;

struct RowManager {
	int l[120010], r[120010];
	LinkNode *head[120010];
	int rcnt;
	int sz[120010];
	int final_ans[30010];
	void init() {
		rcnt = 0;
		l[0] = 0;
		r[0] = 0;
		sz[0] = 0;
	}
	int new_row() {
		++ rcnt;
		r[rcnt] = 0;
		l[rcnt] = l[0];
		r[l[0]] = rcnt;
		l[0] = rcnt;
		head[rcnt] = 0;
		sz[rcnt] = 0;
		return rcnt;
	}
	int next_row(int x) {
		if (r[x] == 0)
			return new_row();
		return r[x];
	}
	int last_row(int x) {
		return x == 0 ? 0 : l[x];
	}
	int last_k_row(int x, int k) {
		while (k --)
			x = last_row(x);
		return x;
	}
	bool add_block(int row, int col) {
		LinkNode *ptr = cols[col].append(row);
		ptr -> right = head[row];
		head[row] = ptr;
		if (++ sz[row] == w) {
			ptr = head[row];
			while (ptr != nullptr) {
				LinkNode *temp = ptr -> right;
				cols[ptr -> id].remove(ptr);
				ptr = temp;
			}
			r[l[row]] = r[row];
			l[r[row]] = l[row];
			return true;
		}
		return false;
	}
	void calc_final() {
		for (int i = 0; i < w; i ++)
			final_ans[i] = 0;
		int num = 1, cur = r[0];
		while (cur != 0) {
			LinkNode *ptr = head[cur];
			while (ptr != nullptr) {
				LinkNode *temp = ptr -> right;
				final_ans[ptr -> id] = num;
				delete ptr;
				ptr = temp;
			}
			cur = r[cur];
			++ num;
		}
		for (int i = 0; i < w; i ++)
			printf("%d%c", final_ans[i], " \n"[i == w - 1]);
	}
} RM;

struct Block {
	int w, h;
	vector<int> wlow, whigh;
} b_info[7][4];

const int scores[5] = {0, 100, 250, 400, 1000};

int main() {
	// I
	b_info[0][0] = {4, 1, {0, 0, 0, 0}, {0, 0, 0, 0}};
	b_info[0][1] = {1, 4, {0}, {3}};
	// J
	b_info[1][0] = {3, 2, {0, 0, 0}, {1, 0, 0}};
	b_info[1][1] = {2, 3, {0, 2}, {2, 2}};
	// L
	b_info[2][0] = {3, 2, {0, 0, 0}, {0, 0, 1}};
	b_info[2][1] = {2, 3, {0, 0}, {2, 0}};
	// O
	b_info[3][0] = b_info[3][1] = {2, 2, {0, 0}, {1, 1}};
	// S
	b_info[4][0] = {3, 2, {0, 0, 1}, {0, 1, 1}};
	b_info[4][1] = {2, 3, {1, 0}, {2, 1}};
	// T
	b_info[5][0] = {3, 2, {0, 0, 0}, {0, 1, 0}};
	b_info[5][1] = {2, 3, {0, 1}, {2, 1}};
	// Z
	b_info[6][0] = {3, 2, {1, 0, 0}, {1, 1, 0}};
	b_info[6][1] = {2, 3, {0, 1}, {1, 2}};

	for (int i = 0; i < 7; i ++)
		for (int j : {2, 3}) {
			b_info[i][j].w = b_info[i][j - 2].w;
			b_info[i][j].h = b_info[i][j - 2].h;
			for (int k = 0; k < b_info[i][j].w; k ++) {
				b_info[i][j].wlow.push_back(b_info[i][j].h - 1 - b_info[i][j - 2].whigh[b_info[i][j].w - 1 - k]),
				b_info[i][j].whigh.push_back(b_info[i][j].h - 1 - b_info[i][j - 2].wlow[b_info[i][j].w - 1 - k]);
			}
		}

	int t; scanf("%d", &t);
	int curcase = 0;
	while (t --) {
		printf("Case #%d:\n", ++ curcase);
		scanf("%d%d", &w, &n);
		RM.init();
		for (int i = 0; i < w; i ++)
			cols[i].l = cols[i].r = nullptr, cols[i].id = i;

		int tot_score = 0;

		for (int i = 0; i < n; i ++) {
			char ch; int pos; int rot;
			scanf(" %c%d%d", &ch, &pos, &rot);
			int piece_id = 0;
			if (ch == 'I') piece_id = 0;
			else if (ch == 'J') piece_id = 1;
			else if (ch == 'L') piece_id = 2;
			else if (ch == 'O') piece_id = 3;
			else if (ch == 'S') piece_id = 4;
			else if (ch == 'T') piece_id = 5;
			else piece_id = 6;
			Block &blk = b_info[piece_id][rot / 90];

			int baseline = 0;
			for (int u = 0; u < blk.w; u ++)
				baseline = max(baseline, RM.last_k_row(cols[pos + u].highest(), blk.wlow[u]));
			vector<int> H(blk.h);
			for (int i = 0; i < blk.h; i ++)
				H[i] = (baseline = RM.next_row(baseline));
			int cnt = 0;
			for (int u = 0; u < blk.w; u ++)
				for (int v = blk.wlow[u]; v <= blk.whigh[u]; v ++)
					cnt += RM.add_block(H[v], pos + u);
			tot_score += scores[cnt];
		}
		printf("%d\n", tot_score);
		RM.calc_final();
	}
}