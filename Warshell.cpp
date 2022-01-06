#include <iostream>
#define N 105
using namespace std;
int a[N][N];

int main() {
    int n; cin >> n;
    for(int i=1;i<=n;i++) {
        for(int j=1;j<=n;j++) {
            cin >> a[i][j];
        }
    }
    for(int k=1;k<=n;k++) {
        for(int i=1;i<=n;i++) {
            for(int j=1;j<=n;j++) {
                a[i][j] = a[i][j] | (a[i][k] & a[k][j]);
            }
        }
    }
    for(int i=1;i<=n;i++) {
        cout << a[i][1];
        for(int j=2;j<=n;j++) {
            cout << " " <<a[i][j];
        }
        cout << endl;
    }
    return 0;
}
