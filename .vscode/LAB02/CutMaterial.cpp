#include <iostream>
using namespace std;
#define MAX 100

int H, W, n;
int h[MAX], w[MAX];
int mark[MAX][MAX];

void input() {
    cin >> H >> W;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> h[i] >> w[i];
    }
}

bool check(int vo, int vx, int vy, int k) {
    int wk = w[k];
    int hk = h[k];
    if (vo == 1) {
        wk = h[k];
        hk = w[k];
    }
    if (vx + wk > W) return false;
    if (vy + hk > H) return false;
    for (int i = vx; i < vx + wk; i++) {
        for (int j = vy; j < vy + hk; j++) {
            if (mark[i][j]) return false;
        }
    }
    return true;
}

void doMark(int vx, int vy, int vo, int k, int mark_value) {
    int wk = w[k];
    int hk = h[k];
    if (vo == 1) {
        wk = h[k];
        hk = w[k];
    }
    for (int i = vx; i < vx + wk; i++) {
        for (int j = vy; j < vy + hk; j++) {
            mark[i][j] = mark_value;
        }
    }
}

int Try(int k) {
    if (k == n) {
        return 1; // All rectangles placed successfully
    }
    for (int vo = 0; vo <= 1; vo++) {
        int wk = w[k];
        int hk = h[k];
        if (vo == 1) {
            wk = h[k];
            hk = w[k];
        }
        for (int vx = 0; vx <= W - wk; vx++) {
            for (int vy = 0; vy <= H - hk; vy++) {
                if (check(vo, vx, vy, k)) {
                    doMark(vx, vy, vo, k, 1);
                    if (Try(k + 1)) {
                        return 1; // Found a valid configuration
                    }
                    doMark(vx, vy, vo, k, 0);
                }
            }
        }
    }
    return 0; // No valid configuration found
}

int main() {
    input();
    cout << Try(0);
    return 0;
}
