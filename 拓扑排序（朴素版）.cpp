#include <iostream>
#define MAX 1005
using namespace std;
int mp[MAX][MAX];

int main() {
    int n,m; //n: number of vertex, m: number of edge
    cin>>n>>m;
    int x,y;
    while(m--) {
        cin>>x>>y;
        mp[x][y] = 1; //stand: exist between x and y
    }
    int ind[MAX];
    for(int i=1;i<=n;i++) {
        int k = 0;
        for(int j=1;j<=n;j++) {
            if(mp[j][i] == 1) k++;
        }
        ind[i] = k;  //initialize ind array
    }
    int cnt = 0;
    while(true) {
        for(int i=1;i<=n;i++) {
            if(ind[i] == 0) {
                cout<<i<<" ";
                cnt++;
                ind[i] = -1;
                for(int j=1;j<=n;j++) {
                    if(mp[i][j] == 1) ind[j]--;
                }
            }
        }
        if(cnt == n) break;
    }
    return 0;
}
