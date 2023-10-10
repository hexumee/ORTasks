#include <iostream>
#include <vector>

using namespace std;

vector<int> tree;
vector<int> lazy;

void build_segment_tree(vector<int>& a, int v, int tl, int tr) {
    if (tl == tr) {
        tree[v] = a[tl];
    } else {
        int tm = (tl + tr) / 2;
        build_segment_tree(a, v*2, tl, tm);
        build_segment_tree(a, v*2+1, tm+1, tr);
        tree[v] = tree[v*2] + tree[v*2+1];
    }
}

void push(int v, int tl, int tr) {
    if (lazy[v] != 0) {
        tree[v] += lazy[v] * (tr-tl+1);

        if (tl != tr) {
            lazy[v*2] += lazy[v];
            lazy[v*2+1] += lazy[v];
        }

        lazy[v] = 0;
    }
}

void update(int v, int tl, int tr, int l, int r, int add) {
    push(v, tl, tr);

    if (l > r) {
        return;
    }

    if (l == tl && r == tr) {
        tree[v] += add * (tr-tl+1);

        if (tl != tr) {
            lazy[v*2] += add;
            lazy[v*2+1] += add;
        }
    } else {
        int tm = (tl + tr) / 2;

        update(v*2, tl, tm, l, min(r, tm), add);
        update(v*2+1, tm+1, tr, max(l, tm+1), r, add);
        
        tree[v] = tree[v*2] + tree[v*2+1];
    }
}

int get(int v, int tl, int tr, int pos) {
    push(v, tl, tr);

    if (tl == tr) {
        return tree[v];
    }

    int tm = (tl + tr) / 2;
    if (pos <= tm) {
        return get(v*2, tl, tm, pos);
    } else {
        return get(v*2+1, tm+1, tr, pos);
    }
}

int main() {
    int n, m;
    cin >> n;

    vector<int> data(n+1, 0);
    tree.resize(4*(n+1));
    lazy.resize(4*(n+1), 0);

    for (int i = 1; i <= n; i++) {
        cin >> data[i];
    }

    build_segment_tree(data, 1, 1, n);

    cin >> m;
    vector<int> result;

    for (int i = 0; i < m; i++) {
        char type;
        cin >> type;

        if (type == 'g') {
            int pos;
            cin >> pos;

            int res = get(1, 1, n, pos);
            result.push_back(res);
        } else if (type == 'a') {
            int l, r, add;
            cin >> l >> r >> add;

            update(1, 1, n, l, r, add);
        }
    }

    for (int res : result) {
        cout << res << "\n";
    }
}
