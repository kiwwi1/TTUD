#include<bits/stdc++.h>
using namespace std;

const int MAX_N = 100005; // Giới hạn tối đa số đỉnh
vector<int> graph[MAX_N]; // danh sách kề của đồ thị
int disc[MAX_N], low[MAX_N]; // Thời gian phát hiện và giá trị low-link
bool visited[MAX_N];         // Đánh dấu đỉnh có trong stack hay không
set<int> articulationPoints; // Lưu các điểm khớp
vector<pair<int, int>> bridges; // Lưu các cầu
int timer = 0; // Biến đếm thời gian

void dfs(int u, int parent){
    visited[u] = true;
    disc[u] = low[u] = ++timer;
    int children = 0;
    for(int v : graph[u]){
        if(v == parent) continue;
        if(!visited[v]){
            children++;
            dfs(v, u);
            low[u]= min(low[u], low[v]);
            if(low[v] >= disc[u] && parent != -1){
                articulationPoints.insert(u);
            }
            if(low[v]>disc[u]){
                bridges.push_back({u, v});
            }
        } else{
            low[u] = min(low[u], disc[v]);
        }
    }
    if(parent == -1 && children > 1){
        articulationPoints.insert(u);
    }

}
int main(){
    int N,M;
    cin >> N >> M;
    for(int i = 0; i < M; i++){
        int u,v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
     for (int i = 1; i <= N; i++) {
        visited[i] = false;
        disc[i] = low[i] = 0;
    }
    for(int i = 1; i <= N; i++){
        if(!visited[i]){
            dfs(i, -1);
        }
    }

    cout << articulationPoints.size() << " " << bridges.size() << endl;
}
