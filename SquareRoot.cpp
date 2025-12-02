#include <bits/stdc++.h>
using namespace std;

#define MAXN 10000
#define SQRSIZE 100

int arr[MAXN];      // original array
int block[SQRSIZE]; // each block stores MIN value
int blk_sz;         // block size

// O(1) update
void update(int idx, int val) {
    int blockNumber = idx / blk_sz;
    arr[idx] = val;

    // recompute the entire block’s minimum 
    int start = blockNumber * blk_sz;
    int end = min(start + blk_sz, MAXN);

    int mn = INT_MAX;
    for (int i = start; i < end; i++) {
        mn = min(mn, arr[i]);
    }
    block[blockNumber] = mn;
}

// O(sqrt(n)) RMQ query
int query(int l, int r) {
    int mn = INT_MAX;

    // đi đến khi tròn block
    while (l <= r && l % blk_sz != 0) {
        mn = min(mn, arr[l]);
        l++;
    }

    // đi qua các block tròn
    while (l + blk_sz - 1 <= r) {
        mn = min(mn, block[l / blk_sz]);
        l += blk_sz;
    }

    // phần cuối không tròn block
    while (l <= r) {
        mn = min(mn, arr[l]);
        l++;
    }

    return mn;
}

// preprocess
void preprocess(int input[], int n) {
    blk_sz = sqrt(n);
    int blk_idx = -1;
    int mn;

    for (int i = 0; i < n; i++) {
        arr[i] = input[i];

        if (i % blk_sz == 0) {
            blk_idx++;
            block[blk_idx] = INT_MAX;
        }

        block[blk_idx] = min(block[blk_idx], arr[i]);
    }
}

int main() {
    int input[] = { 1, 5, 2, 4, 6, 1, 3, 5, 7, 10 };
    int n = sizeof(input) / sizeof(input[0]);

    preprocess(input, n);

    cout << "min(3,8) = " << query(3, 8) << endl;
    cout << "min(1,6) = " << query(1, 6) << endl;

    update(8, 0);    // set arr[8] = 0
    cout << "min(8,8) = " << query(8, 8) << endl;

    return 0;
}
