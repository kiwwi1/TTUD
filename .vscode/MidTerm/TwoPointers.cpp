#include<iostream>
#include <vector>
using namespace std;
int exec(const vector<int>& arr,int Q){
    int res = 0;
    int n = arr.size();
    int i = 1 , j = n;
    while(i<j){
        if(arr[i]+arr[j] == Q){
            res = res+1;
            i = i+1;
            j= j-1;
        }
        else if(arr[i]+arr[j]<Q){
            i = i+1;
        }
        else{
            j = j-1;    
        }
    }
    return res;

}
int main(){
    vector <int> arr;
    for(int i =0;i<arr.size();i++){
        arr.push_back(i);
    }
    int Q;
    cin >> Q;
    cout << exec(arr,Q) << endl;

}