#include <iostream>
#include <stdio.h>
#include <cstring>
#define N 1005
#define INF (int)1e8
using namespace std;
int mp[N][N];
int dp[N][N];

int main() {
    int n,m,t; cin>>n>>m>>t;
    for(int i=1;i<=n;i++) {
        for(int j=1;j<=n;j++) {
            mp[i][j] = INF;
        }
    }

    while(m--) {
        int x,y,c; scanf("%d%d%d",&x,&y,&c);
        mp[x][y] = c;
    }

    for(int i=1;i<=n;i++) {
        for(int j=1;j<=n;j++) {
            dp[i][j] = mp[i][j];
        }
    }

    for(int k=1;k<=n;k++) {
        for(int i=1;i<=n;i++) {
            for(int j=1;j<=n;j++) {
                dp[i][j] = min(dp[i][j],dp[i][k] + dp[k][j]);
            }
        }
    }

    while(t--) {
        int from,to; scanf("%d%d",&from,&to);
        int ans = dp[from][to];
        if(ans == INF) ans = -1;
        printf("%d\n",ans);
    }
    return 0;
}
