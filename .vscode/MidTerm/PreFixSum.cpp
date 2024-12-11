#include<iostream>
#include <vector>
using namespace std;
void buildPreFixSum(const vector<int> &arr, vector<int>& prefixSum){
    int n = arr.size();
    prefixSum.resize(n+1,0);
    for(int i = 1; i <= n; i++){
        prefixSum[i] = prefixSum[i-1] + arr[i-1];
    }
}
int rangeSum(const vector<int> &prefixSum,int i,int j){
    return prefixSum[j+1] - prefixSum[i]; 
}
int main(){
    vector<int> arr ;
    for(int i = 0 ; i<arr.size(); i++){
        arr.push_back(i);
    }
    int i,j;
    cin >> i >> j;
    vector<int> prefixSum;
    buildPreFixSum(arr,prefixSum);
    cout << rangeSum(prefixSum,i,j) << endl;
}