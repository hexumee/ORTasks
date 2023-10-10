#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> data(n);
    vector<long long> ps(n+1, 0);

    for (int i = 0; i < n; i++) {
        cin >> data[i];
        ps[i + 1] = ps[i] + data[i];
    }

    int k;
    cin >> k;

    vector<long long> result;
    for (int q = 0; q < k; q++) {
        int left, right;
        cin >> left >> right;

        result.push_back(ps[right] - ps[left-1]);
    }

    for (int i = 0; i < result.size(); i++) {
        cout << result[i] << " ";
    }

    cout << "\n";
}
