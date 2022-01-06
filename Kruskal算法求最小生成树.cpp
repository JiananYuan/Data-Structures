#include <iostream>
#include <algorithm>
#include <stdio.h>
#define MAX 100005
#define N 1005
#define ERROR -1
using namespace std;
struct node {
    int from,to,dis;
}edge[MAX];
bool cmp(const node& a,const node& b) {
    return a.dis < b.dis;
}
int father[N];
void init(int n) {
    for(int i=1;i<=n;i++) father[i] = i;
}
int findFather(int x) {
    while(x != father[x]) x = father[x];
    return x;
}
void unionn(int x,int y) {
    int a = findFather(x);
    int b = findFather(y);
    if(a!=b) father[b] = a;
}
int kruskal(int n,int m) {
    int cnt = 0,sum = -1e9;
    for(int i=1;i<=m;i++) {
        if(cnt == n-1) break;
        int a = findFather(edge[i].from);
        int b = findFather(edge[i].to);
        if(a!=b) {
            unionn(edge[i].from,edge[i].to);
            sum += edge[i].dis);
            cnt++;
        }
    }
    if(cnt != n-1) return ERROR;
    return sum;
}

int main() {
    int n,m; cin>>n>>m;
    init(n);
    for(int i=1;i<=m;i++) {
        scanf("%d%d%d",&edge[i].from,&edge[i].to,&edge[i].dis);
    }
    sort(edge+1,edge+1+m,cmp);
    int ans = kruskal(n,m);
    cout<<ans<<endl;
    return 0;
}
