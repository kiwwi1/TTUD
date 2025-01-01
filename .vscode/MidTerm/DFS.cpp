#include<bits/stdc++.h>
using namespace std;
int n,m;
vector<int> adj[1005];
bool visited[1005];
void input(){
    cin >>n >> m;
    for(int i = 0;i<m;i++){
        int x,y;
        cin >> x >> y;

        adj[x].push_back(y);
    }
    memset(visited,false,sizeof(visited));
}
void dfs(int u){
    cout << u << " ";
    visited[u] = true;
    for(int v : adj[u]){
        if(!visited[v]){
            dfs(v);
        }
    }

}
int main(){
    input();
    dfs(1);
    return 0;
}