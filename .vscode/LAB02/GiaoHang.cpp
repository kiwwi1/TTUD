#include<bits/stdc++.h>
using namespace std;
int N, K, Q, Key;
int d[15];
int c[31][31];
int x[15], y[15];
int visited[30] = {0};
int load[30] = {0};
int segments = 0, cur_min = 0, nbr = 0, c_min = 10e5, res = 10e5;

bool checkX(int v, int k){
    if (v > 0 && visited[v] == 1) return false;
    if (load[k] + d[v] > Q) return false;
    return true;
}

void updateRes(){
    if (res > cur_min) res = cur_min;
}

void TryX(int s, int k){
    if (s == 0){    
        if (k < K){
            TryX(y[k + 1], k + 1);
            return;
        }
    }
    for (int v = 0; v <= N; v++){
        if (checkX(v, k)){
            x[s] = v;
            visited[v] = 1;
            load[k] += d[v];
            segments += 1;
            cur_min += c[s][v];
            if (v > 0){
                if(cur_min + (N + nbr - segments) * c_min < res) TryX(v, k);
            } else{
                if (k == K){
                    if (segments == N + nbr) updateRes();
                }
                else{
                    if(cur_min + (N + nbr - segments) * c_min < res) TryX(y[k + 1], k + 1);
                }
            }
            visited[v] = 0;
            segments -= 1;
            cur_min -= c[s][v];
            load[k] -= d[v];
        }
    }
}

bool checkY(int v, int k){
    if(v == 0) return false;
    if(load[k] + d[v] > Q) return false;
    if (visited[v]) return false;
    return true;
}

void TryY(int k){
    int s = 0;
    if(y[k - 1] > 0) s = y[k - 1] + 1;  
    for (int v = s; v <= N; v++){
        if (checkY(v, k)){
            y[k] = v;
            if (v > 0) segments += 1;
            visited[v] = 1; 
            cur_min += c[0][v];
            load[k] = load[k] + d[v];
            if (k < K) TryY(k + 1);
            else{
                nbr = segments;
                TryX(y[1], 1);
            }
            load[k] -= d[v];
            cur_min -= c[0][v];
            visited[v] = 0;
            if(v > 0) segments -= 1;
        }
    }
}

int main(){
    cin >> N >> Key >> Q;
    for (int i = 1; i <= N; i++){
        cin >> d[i];
    }
    for (int i = 0; i < N + 1; i++)
        for (int j = 0; j < N + 1; j++){
            cin >> c[i][j];
            if (i != j){
                if (c[i][j] < c_min) c_min = c[i][j];
            }
        }
    y[0] = 0;
    for(K = 1; K <= Key; K++){
    TryY(1);
    }
    cout << res;
}