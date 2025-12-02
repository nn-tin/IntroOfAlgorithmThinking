#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100000;
int segtree[4 * MAXN];
int arr[MAXN];

// build tree
void build(int idx, int l, int r) {
    if (l == r) {
        segtree[idx] = arr[l];
        return;
    }
    int mid = (l + r) / 2;
    build(idx * 2, l, mid);
    build(idx * 2 + 1, mid + 1, r);
    segtree[idx] = min(segtree[idx * 2], segtree[idx * 2 + 1]);
}

// point update
void update(int idx, int l, int r, int pos, int val) {
    if (l == r) {
        segtree[idx] = val;
        return;
    }
    int mid = (l + r) / 2;

    if (pos <= mid)
        update(idx * 2, l, mid, pos, val);
    else
        update(idx * 2 + 1, mid + 1, r, pos, val);

    segtree[idx] = min(segtree[idx * 2], segtree[idx * 2 + 1]);
}

// range query min
int query(int idx, int l, int r, int ql, int qr) {
    if (qr < l || r < ql) 
        return INT_MAX;         // outside range

    if (ql <= l && r <= qr)     
        return segtree[idx];    // fully covered

    int mid = (l + r) / 2;
    return min(
        query(idx * 2, l, mid, ql, qr),
        query(idx * 2 + 1, mid + 1, r, ql, qr)
    );
}

int main() {
    int n = 10;
    int input[] = {1, 5, 2, 4, 6, 1, 3, 5, 7, 10};

    for (int i = 0; i < n; i++)
        arr[i] = input[i];

    build(1, 0, n - 1);

    cout << "min(3,8) = " << query(1, 0, n - 1, 3, 8) << endl;
    cout << "min(1,6) = " << query(1, 0, n - 1, 1, 6) << endl;

    update(1, 0, n - 1, 8, 0);
    cout << "min(8,8) = " << query(1, 0, n - 1, 8, 8) << endl;

    return 0;
}
