#include <iostream>
#include <vector>

using namespace std;

struct segment_tree_node {
    int left;
    int right;
    long long sum;
    long long lazy;
};

void build_segment_tree(vector<segment_tree_node>& tree, vector<int>& array, int node, int left, int right) {
    tree[node].left = left;
    tree[node].right = right;
    tree[node].lazy = 0;

    if (left == right) {
        tree[node].sum = array[left-1];
        return;
    }

    int mid = (left+right)/2;
    build_segment_tree(tree, array, 2*node, left, mid);
    build_segment_tree(tree, array, 2*node+1, mid+1, right);
    tree[node].sum = tree[2*node].sum + tree[2*node+1].sum;
}

long long query_segment_tree(vector<segment_tree_node>& tree, int node, int left, int right) {
    if (tree[node].left == left && tree[node].right == right) {
        return tree[node].sum;
    }

    int mid = (tree[node].left + tree[node].right) / 2;
    if (right <= mid) {
        return query_segment_tree(tree, 2*node, left, right);
    } else if (left > mid) {
        return query_segment_tree(tree, 2*node+1, left, right);
    } else {
        long long left_sum = query_segment_tree(tree, 2*node, left, mid);
        long long right_sum = query_segment_tree(tree, 2*node+1, mid+1, right);
        return left_sum + right_sum;
    }
}

void update_segment_tree(vector<segment_tree_node>& tree, int node, int index, int value) {
    if (tree[node].left == tree[node].right) {
        tree[node].sum = value;
        return;
    }

    int mid = (tree[node].left + tree[node].right) / 2;
    if (index <= mid) {
        update_segment_tree(tree, 2*node, index, value);
    } else {
        update_segment_tree(tree, 2*node+1, index, value);
    }

    tree[node].sum = tree[2*node].sum + tree[2*node+1].sum;
}

int main() {
    int n;
    cin >> n;

    vector<int> data(n);
    for (int i = 0; i < n; i++) {
        cin >> data[i];
    }

    int tree_size = 4*n;
    vector<segment_tree_node> tree(tree_size);
    build_segment_tree(tree, data, 1, 1, n);

    int m;
    cin >> m;

    vector<long long> result;
    for (int q = 0; q < m; q++) {
        char type;
        cin >> type;

        if (type == 's') {
            int left, right;
            cin >> left >> right;

            long long sum = query_segment_tree(tree, 1, left, right);
            result.push_back(sum);
        } else if (type == 'u') {
            int index, value;
            cin >> index >> value;

            update_segment_tree(tree, 1, index, value);
        }
    }

    for (int i = 0; i < result.size(); i++) {
        cout << result[i] << " ";
    }

    cout << "\n";
}
