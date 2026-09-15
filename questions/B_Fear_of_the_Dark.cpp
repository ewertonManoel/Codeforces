#include <bits/stdc++.h>

using namespace std;
int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin >> t;
    while(t--) {
        int px, py, ax, ay, bx, by; cin >> px >> py >> ax >> ay >> bx >> by;
        double d0a, d0b, dap, dbp, dab, dir, undir, w;
        d0a = sqrt(ax * ax + ay * ay); d0b = sqrt(bx * bx + by * by);
        dap = sqrt((px - ax) * (px - ax) + (py - ay) * (py - ay));
        dbp = sqrt((px - bx) * (px - bx) + (py - by) * (py - by));
        dab = sqrt((ax - bx) * (ax - bx) + (ay - by) * (ay - by));
        dir = min(max(d0a, dap), max(d0b, dbp));
        undir = min(max(d0a, max(dab / 2, dbp)), max(d0b, max(dab / 2, dap)));
        w = min(dir, undir);
        cout << fixed << setprecision(10) << w << '\n';
    }
}