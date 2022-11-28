#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#define ll long long
#define ull unsigned long long
#define ed '\n'
#define pb push_back
#define ii pair<int,int>
#define o_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>
#define fi first
#define se second

using namespace __gnu_pbds;
using namespace std;

const int N = 5005, inf = INT_MAX;
vector<ii> g[N];
int b[N * 15], cnt, n, m, s, t, dis[N], cur[N];
array<int, 3> e[N * 15];

inline bool comp(array<int, 3> &a, array<int, 3> &b) {return a[2] > b[2];}

inline void add_edge(int u, int v, int c) {
    b[cnt] = c;
    g[u].pb({v, cnt++});
    cnt++;
}

int dfs(int u, int flow) {
    if (u == t) return flow;

    int sf = 0;
    for(int &i = cur[u]; i < g[u].size(); ++i) {
        int v = g[u][i].fi;
        int id = g[u][i].se;
        if (dis[v] == dis[u] + 1 && b[id]) {
            int neck = dfs(v, min(flow, b[id]));

            b[id]-= neck;
            b[id ^ 1] += neck;
            flow -= neck;
            sf += neck;

            if (!flow) break;
        }
    }
    return sf;
}

inline bool bfs() {
    queue<int> q;
    q.push(s);
    memset(dis, -1, sizeof dis);
    dis[s] = 0;

    while(q.size()) {
        int u = q.front();
        q.pop();

        for(ii &e: g[u]) {
            int v = e.fi;
            int id = e.se;
            if (dis[v] == -1 && b[id]) {
                dis[v] = dis[u] + 1;
                q.push(v);
            }
        }
    }
    return dis[t] != -1;
}

void solve() {
    cin >> n >> m;
    s = 1, t = n;
    for(int i = 1; i <= 2 * m; i += 2) {
        cin >> e[i][0] >> e[i][1] >> e[i][2];
        e[i + 1] = {e[i][1], e[i][0], e[i][2]};
    }

    sort(e + 1, e + m + 1, comp);

    ll ans = 0;
    for(bool flag: {0, 1}) {
        int i = 1;
        for(int delta = (1 << 10); delta; delta >>= 1) {
            while(i <= 2 * m && e[i][2] >= delta) {
                if (flag == 0) add_edge(e[i][0], e[i][1], e[i][2]);
                else g[e[i][1]].pb({e[i][0], i * 2 - 1});
                ++i;
            }
            while(bfs()) {
                memset(cur, 0, sizeof cur);
                ans += dfs(s, inf);
            }
        }
    }
    cout << ans;
}

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    if (fopen("cf.inp", "r")) {
//        freopen("cf.inp", "r", stdin);
        //freopen("cf.inp", "w", stdout);
    }
    solve();
    return 0;
}
