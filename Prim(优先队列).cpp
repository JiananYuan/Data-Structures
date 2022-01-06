#include <iostream>
#include <algorithm>
#include <queue>
#include <string.h>
#define N 5005
using namespace std;
int n,m;
int G[N][N];
bool visited[N];

struct Pair {
    int v;
    int w;
    Pair(int a,int b):v(a),w(b){}
};

struct cmp {
    bool operator()(const Pair& a,const Pair& b) {
        return a.w > b.w;
    }
};

priority_queue<Pair,vector<Pair>,cmp > q;


int prim() {
    q.push(Pair(1,0));
    int ans = 0, cnt = -1;
    while(cnt != n-1) {
        Pair t = q.top();
        q.pop();
        if (visited[t.v]) continue;
        for (int i = 1; i <= n; ++i) {
            if (!visited[i] && G[t.v][i] != 0x7f7f7f7f) {
                q.push(Pair(i,G[t.v][i]));
            }
        }
        visited[t.v] = true;
        ans += t.w;
        ++cnt;
    }
    return ans;
}

int main() {
    memset(G,0x7f,sizeof(G));
    cin >> n >> m;
    for (int i = 1; i <= m; ++i) {
        int x,y,z;
        cin >> x >> y >> z;
        G[x][y] = min(G[x][y],z);
        G[y][x] = min(G[y][x],z);
    }
    cout << prim() << endl;
    return 0;
}
