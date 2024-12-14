#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main(){
    int n,Q;
    cin >> n  >> Q;
    int a[100];

    for(int i=0;i<n;i++){
        cin >> a[i];
    }
    int r =0 ;int l =0;
    int sum =0;
    int count= 0;
    int res = 1e9;
    for( r= 0; r< n; r++){
        sum += a[r];
        while(sum >= Q){
            count += n-r;
            sum -= a[l];
            l++;
        }       
}
cout << count;
    return 0;
}