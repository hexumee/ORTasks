#include <iostream>
#include <vector>

using namespace std;

vector<int> tree;

void build(vector<int>& a, int v, int tl, int tr) {
    if (tl == tr) {
        tree[v] = (a[tl] == 0) ? 1 : 0;
    } else {
        int tm = (tl + tr) / 2;
        build(a, v*2, tl, tm);
        build(a, v*2+1, tm+1, tr);
        tree[v] = tree[v*2] + tree[v*2+1];
    }
}

void update(vector<int>& a, int v, int tl, int tr, int pos, int new_val) {
    if (tl == tr) {
        a[tl] = new_val;
        tree[v] = (new_val == 0) ? 1 : 0;
    } else {
        int tm = (tl + tr) / 2;
        if (pos <= tm) {
            update(a, v*2, tl, tm, pos, new_val);
        }
        else {
            update(a, v*2+1, tm+1, tr, pos, new_val);
        }
        tree[v] = tree[v*2] + tree[v*2+1];
    }
}

int find_kth_zero(int v, int tl, int tr, int k) {
    if (k > tree[v]) {
        return -1;
    }

    if (tl == tr) {
        return tl;
    }
    
    int tm = (tl + tr) / 2;
    if (tree[v*2] >= k) {
        return find_kth_zero(v*2, tl, tm, k);
    } else {
        return find_kth_zero(v*2+1, tm+1, tr, k-tree[v*2]);
    }
}

int main() {
    int n, m;
    cin >> n;

    vector<int> data(n+1, 0);
    tree.resize(4*(n+1));

    for (int i = 1; i <= n; i++) {
        cin >> data[i];
    }

    build(data, 1, 1, n);

    cin >> m;
    vector<int> answers;
    for (int i = 0; i < m; i++) {
        char type;
        cin >> type;

        if (type == 'u') {
            int pos, new_val;
            cin >> pos >> new_val;

            update(data, 1, 1, n, pos, new_val);
        } else if (type == 's') {
            int k;
            cin >> k;

            int res = find_kth_zero(1, 1, n, k);
            answers.push_back(res);
        }
    }

    for (int ans : answers) {
        cout << ans << " ";
    }

    cout << "\n";
}
