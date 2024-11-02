#include <iostream>
using namespace std;

int n, M; 
int a[20]; 
int countSolutions = 0; 


void backtrack(int index, int currentSum) {
  
    if (index == n ) {
        if(currentSum == M){
            countSolutions++;
        }
        return;
    }


    for (int X = 1; X <= (M - currentSum) / a[index]; X++) {
        // Tính tổng mới khi chọn giá trị X cho biến thứ index
        int newSum = currentSum + X * a[index];
        // Nếu tổng hiện tại chưa vượt quá M, tiếp tục tìm cho các biến tiếp theo
        if (newSum <= M) {
            backtrack(index + 1, newSum);
        } else {
            break;
        }
    }
}

int main() {
    // Nhập n và M
    cin >> n >> M;
    
    // Nhập các hệ số a_1, a_2, ..., a_n
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    backtrack(0, 0);
    cout << countSolutions << endl;

    return 0;
}
