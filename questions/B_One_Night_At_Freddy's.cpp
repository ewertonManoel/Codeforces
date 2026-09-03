#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin >> t;
    while(t--) {
        int n, m, l; cin >> n >> m >> l;
        map<int, int> mp;
        mp[0] = m;
        int prev_time = 0, cur_time = 0;
        for(int i = 0; i < n; i++) { 
            prev_time = cur_time;
            cin >> cur_time;
            int target = n-i+1;
            int time = cur_time - prev_time;
            while(m > target) {
                auto itr = mp.begin();
                int res = min(m - target, itr->second);
                m -= res; itr->second -= res;
                if(itr->second == 0) mp.erase(itr);
            }
            while(time > 0) {
                auto itr = mp.begin();
                int num = time;
                int val = itr->first;
                int count = itr->second;
                if(next(itr) != mp.end()) num = min(num, (next(itr)->first - val) * count);
                mp.erase(itr);
                int r = num % count;
                mp[val + num / count] += count - r;
                if(r > 0) mp[val + num / count + 1] += r; 
                time -= num;
            }
            auto itr = mp.end(); itr--;
            itr->second--; if(itr->second == 0) mp.erase(itr);
            mp[0]++;
        }
        auto itr = mp.end(); itr--;
        int ans = itr->first + (l - cur_time);
        cout << ans << '\n';
    }
}