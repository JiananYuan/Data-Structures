#include <iostream>
#include <stdio.h>
#include <algorithm>
#define INF 0x7fffffff
#define N 1005
#define ERROR -1
using namespace std;
typedef long long ll;
int n,m;
int mp[N][N];
int dis[N];
bool collected[N];
int findShortPath() {
    int minx = INF;
    int id = 0;
    for(int i=1;i<=n;i++) {
        if(!collected[i] && minx > dis[i]) {
            minx = dis[i];
            id = i;
        }
    }
    if(id == 0) return ERROR;
    return id;
}

void djikstra() {
    for(int i=1;i<=n;i++)  dis[i] = mp[1][i];
    collected[1] = true;
    dis[1] = 0;
    while(true) {
        int id = findShortPath();
        if(id == ERROR) break;
        collected[id] = true;
        for(int i=1;i<=n;i++) {
            if(!collected[i] && mp[id][i]<INF) {
                dis[i] = min(dis[i],dis[id] + mp[id][i]);
            }
        }
    }
}
int main() {
    cin>>n>>m;
    while(m--) {
        int x,y,c; scanf("%d%d%d",&x,&y,&c);
        mp[x][y] = c;
    }
    for(int i=1;i<=n;i++) {
        for(int j=1;j<=n;j++) {
            if(i == j)  continue;
            if(!mp[i][j]) mp[i][j] = INF;
        }
    }
    djikstra();
    for(int i=1;i<=n;i++) cout<<dis[i]<<" ";
    return 0;
}
