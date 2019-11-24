#include <iostream>
#include <stdio.h>
#include <algorithm>
#define MAX 105
#define INF 0x3fffffff
using namespace std;

int main() {
    int u[MAX],v[MAX],w[MAX];
    int n,m; cin>>n>>m;
    for(int i=1;i<=m;i++) cin>>u[i]>>v[i]>>w[i];
    int dis[MAX];
    for(int i=1;i<=n;i++) dis[i] = INF;
    dis[1] = 0;
    int t = n-1;
    while(t--) {
        for(int i=1;i<=m;i++) {
            dis[ v[i] ] = min(dis[ v[i] ],dis[ u[i] ] + w[i]);
        }
    }
    for(int i=1;i<=m;i++) cout<<dis[i]<<" ";
    return 0;
}
