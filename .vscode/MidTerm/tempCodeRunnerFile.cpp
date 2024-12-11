#include<iostream>
using namespace std;
#define MAX 11
int n,K,visited[2*MAX+1],load,cmin,f,f_best;
int c[2*MAX+1][2*MAX+1],x[2*MAX+1],x_best[2*MAX+1];
void input(){
    cin >> n >> K;
    cmin = 1000000; 
    for(int i = 0; i<2*n;i++){
        for(int j =0 ;j <2*n;j++){
            cin >> c[i][j];
            if(i != j && c[i][j] < cmin) cmin = c[i][j];
        }
    }
}
bool check(int v){
    if(visited[v]==1) return false;
    if(v > n){
        if(visited[v-n]==0) return false;
    }
    else{
        if(load +1 > K) return false;
    }
    return true;
}
void updateBest(){
    if(f+c[2*n][0]<f_best)
        f_best = f+c[2*n][0];
    for(int i = 1 ; i <= 2*n ; i++){
            x_best[i] = x[i];
        }
}
void Try(int k){
    for(int v = 1; v<=2*n;v++){
        if(check(v)){
            x[k]=v;
            f+=c[x[k-1]][k];
            if(v <= n) load += 1;
            else load -= 1;
            visited[v]=1;
            if(k==2*n) updateBest();
            else{
                if(f+cmin*(2*n+1-k)<f_best){
                    Try(k+1);
                }
                else{
                    if(v<=n) load -=1; else load +=1;
                    visited[v]=0;
                    f -= c[x[k-1]][k];  
                }
            }
        }
    }
}
int main(){
    load = 0;
    f = 0;
    f_best = 1000000;
    input();
    for(int i = 0 ; i<=2*n;i++){
        visited[i] = 0;
    }
    x[0] = 0;
    Try(1);
    cout << f_best;
}