#include<bits/stdc++.h>
using namespace std;
const int MAX_N = 100005; // Giới hạn tối đa số đỉnh
vector<int> adj[MAX_N]; // danh sách kề của đồ thị
int in_degree[MAX_N]; 
int duration[MAX_N];
int time_earliest[MAX_N];
int n,m; // So cong viec va so rang buoc
void input(){
    cin >> n >> m;
    for(int i = 1 ; i <= n;i++){
        cin >>duration[i];
    }
    for(int i = 0 ; i < m; i++){
        int u,v;
        cin >> u >> v;
        adj[u].push_back(v);
        in_degree[v]++;
    }
}
int main(){
    input();
    queue<int> q;
    for(int i =1;i<=n;i++){
        if(in_degree[i]==0){
            q.push(i);
            time_earliest[i] = duration[i];        
        }
    }
    while(!q.empty()){
        int u = q.front();
        q.pop();
        for(int v : adj[u]){
            in_degree[v]--;
            if(in_degree[v]==0){
                q.push(v);
            }
            time_earliest[v] = max(time_earliest[v],time_earliest[u]+duration[v]);
        }
    }
    int result = 0;
    for(int i = 1; i <= n; i++){
        result = max(result,time_earliest[i]);
    }
    cout << result << endl;
    return 0;

}

