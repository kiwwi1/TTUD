#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct Point {
    int x, y, dist;
};

int n, m, r, c;
vector<vector<int>> A;
vector<vector<bool>> visited;
int dx[4] = {-1, 1, 0, 0}; // Lên, xuống, trái, phải
int dy[4] = {0, 0, -1, 1};

bool isValid(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < m && A[x][y] == 0 && !visited[x][y];
}

int bfs(int startX, int startY) {
    queue<Point> q;
    q.push({startX, startY, 0});
    visited[startX][startY] = true;
    
    while (!q.empty()) {
        Point current = q.front();
        q.pop();
        
        // Kiểm tra xem có thoát ra ngoài biên không
        if (current.x == 0 || current.x == n-1 || current.y == 0 || current.y == m-1) {
            return current.dist+1;
        }

        // Kiểm tra 4 hướng
        for (int i = 0; i < 4; i++) {
            int newX = current.x + dx[i];
            int newY = current.y + dy[i];
            if (isValid(newX, newY)) {
                visited[newX][newY] = true;
                q.push({newX, newY, current.dist + 1});
            }
        }
    }
    
    // Nếu không tìm được đường thoát
    return -1;
}

int main() {
    cin >> n >> m >> r >> c;
    A.resize(n, vector<int>(m));
    visited.resize(n, vector<bool>(m, false));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> A[i][j];
        }
    }

    // Bắt đầu BFS từ vị trí r, c (chuyển thành chỉ số 0-based)
    int result = bfs(r - 1, c - 1);
    cout << result << endl;

    return 0;
}
