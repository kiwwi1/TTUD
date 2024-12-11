#include <iostream>
#include <vector>
using namespace std;

const int MAXN = 100005;

vector<pair<int, int>> tree[MAXN]; // Danh sách kề (đỉnh, trọng số)
long long subtreeSize[MAXN];       // Kích thước cây con
long long fRoot = 0;               // Giá trị f(root)
long long fValue[MAXN];            // Lưu giá trị f(v) cho từng nút
int n;                             // Số lượng nút trong cây

// DFS lần 1: Tính f(root) và kích thước cây con
void dfs1(int node, int parent) {
    subtreeSize[node] = 1; // Bản thân nút node
    for (auto [neighbor, weight] : tree[node]) {
        if (neighbor != parent) {
            dfs1(neighbor, node);
            subtreeSize[node] += subtreeSize[neighbor];
            fRoot += weight * subtreeSize[neighbor];
        }
    }
}

// DFS lần 2: Tính f(v) cho tất cả các nút
void dfs2(int node, int parent) {
    for (auto [neighbor, weight] : tree[node]) {
        if (neighbor != parent) {
            // Tính f(neighbor) dựa trên f(node)
            fValue[neighbor] = fValue[node] + weight * (n - 2 * subtreeSize[neighbor]);
            dfs2(neighbor, node);
        }
    }
}

int main() {
    cin >> n;

    // Nhập các cạnh của cây
    for (int i = 0; i < n - 1; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        tree[u].emplace_back(v, w);
        tree[v].emplace_back(u, w);
    }

    // DFS lần 1: Tính f(root) và kích thước cây con
    dfs1(1, -1);
    fValue[1] = fRoot;

    // DFS lần 2: Tính f(v) cho tất cả các nút
    dfs2(1, -1);

    // Tìm giá trị lớn nhất của f(v)
    long long maxF = 0;
    for (int i = 1; i <= n; i++) {
        maxF = max(maxF, fValue[i]);
    }

    cout << maxF << endl;
    return 0;
}
