#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

const int INF = INT_MAX;

int n, K, Q;                        // Số khách hàng, số xe tải, dung lượng tối đa mỗi xe
vector<int> d;                      // Yêu cầu số lượng hàng của mỗi khách hàng
vector<vector<int>> c;              // Ma trận khoảng cách
vector<int> load;                   // Tải trọng hiện tại của mỗi xe
vector<int> route;                  // Tuyến đường hiện tại của 1 xe
vector<bool> visited;               // Đánh dấu khách hàng đã được phục vụ
int min_distance = INF;             // Tổng khoảng cách tối thiểu

// Hàm tính khoảng cách của một lộ trình
int calculateRouteDistance(const vector<int>& route) {
    int distance = 0;
    for (int i = 1; i < route.size(); ++i) {
        distance += c[route[i - 1]][route[i]];
    }
    return distance;
}

// Hàm quay lui để tìm lời giải tối ưu
void backtrack(int truck, int total_distance) {
    if (truck == K) { // Nếu tất cả xe đã được thử
        for (int i = 1; i <= n; ++i) {
            if (!visited[i]) return; // Nếu có khách hàng chưa được phục vụ, bỏ qua
        }
        min_distance = min(min_distance, total_distance);
        return;
    }

    // Nếu xe tải hiện tại không phục vụ khách nào
    backtrack(truck + 1, total_distance);

    // Thử các lộ trình khả thi cho xe tải hiện tại
    for (int i = 1; i <= n; ++i) {
        if (!visited[i] && load[truck] + d[i] <= Q) { // Chỉ phục vụ nếu chưa đến thăm và còn tải trọng
            visited[i] = true;
            load[truck] += d[i];
            route.push_back(i); // Thêm khách hàng vào lộ trình

            // Tính khoảng cách từ điểm trước đó đến khách hàng hiện tại
            int last = route.size() > 1 ? route[route.size() - 2] : 0;
            int new_distance = total_distance + c[last][i];

            // Quay lui để tiếp tục thử các khách hàng khác
            backtrack(truck, new_distance);

            // Quay lui để hoàn tác
            visited[i] = false;
            load[truck] -= d[i];
            route.pop_back();
        }
    }
}

int main() {
    // Nhập dữ liệu
    cin >> n >> K >> Q;
    d.resize(n + 1);
    c.resize(n + 1, vector<int>(n + 1));
    visited.resize(n + 1, false);
    load.resize(K, 0);

    for (int i = 1; i <= n; ++i) cin >> d[i];
    for(int i = 0; i<=n ; i++){
        for (int j = 0; j <=n; j++) 
        cin >> c[i][j];
    }

    // Giải bài toán
    backtrack(0, 0);

    // Xuất kết quả
    cout << min_distance << endl;
    return 0;
}
