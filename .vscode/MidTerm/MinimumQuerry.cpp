#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

const int MAXN = 1000; // Kích thước tối đa của mảng
const int LOG = 10;    // log2(MAXN) + 1 (dành cho bảng sparse)

int sparseTable[MAXN][LOG]; // Sparse table lưu trữ chỉ số của phần tử nhỏ nhất
vector<int> arr;            // Dãy số đầu vào
int n;                      // Số lượng phần tử trong mảng

// Hàm xây dựng Sparse Table
void buildSparseTable() {
    for (int i = 0; i < n; i++) {
        sparseTable[i][0] = i; // Mỗi phần tử là nhỏ nhất trong đoạn chỉ chứa nó
    }

    // Xây dựng bảng theo độ dài 2^j
    for (int j = 1; (1 << j) <= n; j++) {
        for (int i = 0; i + (1 << j) - 1 < n; i++) {
            int leftIndex = sparseTable[i][j - 1];
            int rightIndex = sparseTable[i + (1 << (j - 1))][j - 1];
            sparseTable[i][j] = (arr[leftIndex] <= arr[rightIndex]) ? leftIndex : rightIndex;
        }
    }
}

// Hàm thực hiện RMQ(i, j) trả về chỉ số của phần tử nhỏ nhất
int query(int l, int r) {
    int len = r - l + 1;
    int k = log2(len); // log2 của độ dài đoạn
    int leftIndex = sparseTable[l][k];
    int rightIndex = sparseTable[r - (1 << k) + 1][k];
    return (arr[leftIndex] <= arr[rightIndex]) ? leftIndex : rightIndex;
}

int main() {
    int k; // Số lượng truy vấn

   
    cin >> n;
    arr.resize(n);

   
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    // Xây dựng Sparse Table
    buildSparseTable();

    
    cin >> k;
    for (int queryIndex = 0; queryIndex < k; queryIndex++) {
        int i, j;
        
        cin >> i >> j;

        int minIndex = query(i, j);
        cout 
             << minIndex <<  arr[minIndex] << endl;
    }

    return 0;
}
