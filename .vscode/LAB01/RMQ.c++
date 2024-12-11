#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

// Hàm tiền xử lý Sparse Table
void buildSparseTable(const vector<int>& a, vector<vector<int>>& M) {
    int n = a.size();
    int maxJ = log2(n); // j tối đa
    for (int i = 0; i < n; i++) {
        M[0][i] = i; // Đoạn 2^0 chỉ chứa 1 phần tử
    }
    for (int j = 1; (1 << j) <= n; j++) { // Với từng độ dài đoạn 2^j
        for (int i = 0; i + (1 << j) - 1 < n; i++) {
            // So sánh phần tử nhỏ nhất ở hai nửa đoạn
            if (a[M[j - 1][i]] < a[M[j - 1][i + (1 << (j - 1))]]) {
                M[j][i] = M[j - 1][i];
            } else {
                M[j][i] = M[j - 1][i + (1 << (j - 1))];
            }
        }
    }
}

// Hàm xử lý truy vấn RMQ(i, j) bằng Sparse Table
int queryRMQ(const vector<int>& a, const vector<vector<int>>& M, int i, int j) {
    int len = j - i + 1;
    int k = log2(len); // Tìm đoạn phủ lớn nhất
    if (a[M[k][i]] < a[M[k][j - (1 << k) + 1]]) {
        return a[M[k][i]];
    } else {
        return a[M[k][j - (1 << k) + 1]];
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    // Đọc input
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    
    // Tiền xử lý Sparse Table
    int maxJ = log2(n);
    vector<vector<int>> M(maxJ + 1, vector<int>(n)); // Sparse Table
    buildSparseTable(a, M);

    // Đọc số truy vấn
    int m;
    cin >> m;

    // Xử lý các truy vấn
    long long Q = 0; // Kết quả tổng
    for (int k = 0; k < m; k++) {
        int i, j;
        cin >> i >> j;
        Q += queryRMQ(a, M, i, j);
    }

    // Xuất kết quả
    cout << Q << endl;

    return 0;
}
