#include <iostream>
#include <vector>
#include <stack>
using namespace std;

const int MAX_N = 100005; // Giới hạn tối đa số đỉnh
vector<int> graph[MAX_N];
int disc[MAX_N], low[MAX_N]; // Thời gian phát hiện và giá trị low-link
bool inStack[MAX_N];         // Đánh dấu đỉnh có trong stack hay không
stack<int> st;               // Stack để lưu các đỉnh trong DFS
int timer = 0, sccCount = 0; // Biến đếm thời gian và số SCC

// Hàm Tarjan DFS
void tarjanDFS(int u) {
    disc[u] = low[u] = ++timer; // Gán thời gian phát hiện ban đầu
    st.push(u);                 // Đưa đỉnh vào stack
    inStack[u] = true;

    // Duyệt qua tất cả các đỉnh kề của u
    for (int v : graph[u]) {
        if (disc[v] == 0) { // Nếu v chưa được thăm
            tarjanDFS(v);
            low[u] = min(low[u], low[v]);
        } else if (inStack[v]) { // Nếu v nằm trong stack
            low[u] = min(low[u], disc[v]);
        }
    }

    // Kiểm tra xem u có phải là đầu tiên của một SCC hay không
    if (low[u] == disc[u]) {
        sccCount++; // Phát hiện một SCC mới
        while (true) {
            int v = st.top();
            st.pop();
            inStack[v] = false;
            if (v == u) break;
        }
    }
}

int main() {
    int N, M; // Số đỉnh và số cạnh
    cin >> N >> M;

    // Nhập dữ liệu đồ thị
    for (int i = 0; i < M; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
    }

    // Khởi tạo các giá trị
    for (int i = 1; i <= N; i++) {
        disc[i] = low[i] = 0;
        inStack[i] = false;
    }

    // Chạy Tarjan trên tất cả các đỉnh chưa được thăm
    for (int i = 1; i <= N; i++) {
        if (disc[i] == 0) {
            tarjanDFS(i);
        }
    }

    // In ra số lượng SCC
    cout  << sccCount << endl;

    return 0;
}
