#include<iostream>
using namespace std;
#define maxn 1000006
int const MOD = 1e9 + 7;
int n,a[maxn],temp[maxn];
int _merge(int left,int mid,int right){
    int i = left, j = mid+1,k= left,inv_count=0;
    while((i<=mid) && (j<=right)){
        if(a[i]<=a[j]){
            temp[k++] = a[i++];
        }
        else{
            temp[k++] = a[j++];
            inv_count = (inv_count + mid - i + 1) % MOD;
        }
    }
    while(i<=mid){
        temp[k++] = a[i++];
    }
    while(j<=right){
        temp[k++] = a[j++];
    }
    for(i=left;i<=right;i++){
        a[i] = temp[i];
    }
    return inv_count;
}
int _mergeSort(int left,int right){
    int inv_count = 0,mid;
    if(left<right){
        mid = (left+right)/2;
        inv_count = _mergeSort(left,mid);
        inv_count = (inv_count + _mergeSort(mid+1,right)) % MOD;
        inv_count = (inv_count + _merge(left,mid,right)) % MOD;
    }
    return inv_count;
}
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    cout<<_mergeSort(1,n);
    return 0;
}