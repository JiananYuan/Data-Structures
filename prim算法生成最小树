#include <iostream>
#include <algorithm>
#define MAX 5005
#define inf 0x7fffffff
#define ERROR -1
using namespace std;
int Graph[MAX][MAX];

void initGraph(int n) {
    for(int i=1;i<=n;i++) {
        for(int j=1;j<=n;j++) {
            Graph[i][j] = inf;
        }
    }
}

void buildGraph(int m) {
    int x,y,c;
    while(m--) {
        cin>>x>>y>>c;
        Graph[x][y] = Graph[y][x] = min(c,Graph[x][y]);
    }
}

int prim(int n) {
    int dis[MAX],MST[MAX];
    MST[1] = 0;
    dis[1] = 0;
    for(int i=2;i<=n;i++) {
        dis[i] = Graph[1][i];
        MST[i] = 1;
    }
    int sum = 0;
    for(int i=2;i<=n;i++) {
        int minx = inf;
        int id = 0;
        for(int j=1;j<=n;j++) {
            if(dis[j] != 0 && dis[j] < minx) {
                minx = dis[j];
                id = j;
            }
        }
        if(id == 0) return ERROR;
        cout << "V" << MST[id] << "-V" << id << "=" << minx << endl;
        sum += minx;
        dis[id] = 0;
        for(int j=1;j<=n;j++) {
            if(Graph[id][j] < dis[j]) {
                dis[j] = Graph[id][j];
                MST[j] = id;
            }
        }
    }
    return sum;
}

int main() {
    int n,m; cin>>n>>m;
    initGraph(n);
    buildGraph(m);
    int cost = prim(n);
    cout<<cost<<endl;
    return 0;
}
