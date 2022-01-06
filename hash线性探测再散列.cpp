#include <iostream>
#define MAX 1002
#define INF 0x7fffffff
#define mod 11
using namespace std;
int main() {
    int t; cin>>t;
    int a[MAX];
    while(t--) {
        int len,n; cin>>len>>n;
        for(int i=0;i<len;i++) a[i] = INF;
        for(int i=0;i<n;i++) {
            int x; cin>>x;
            int tmp = x % mod;
            for(int j=0; ;j++) {
                if(a[(tmp+j+len)%len]==INF) {
                    a[(tmp+j+len)%len] = x;
                    break;
                }
            }
        }
        for(int i=0;i<len;i++) {
            if(a[i]==INF) cout<<"NULL ";
            else cout<<a[i]<<" ";
        }
        cout<<endl;
        int t; cin>>t;
        while(t--) {
            int x; cin>>x;
            int tmp = x % mod;
            int cnt = 0, ans = -1;
            for(int j=0; ;j++) {
                cnt++;
                if(a[(tmp+j+len)%len]==INF)  break;
                if(a[(tmp+j+len)%len]==x) {
                    ans = (tmp+j+len)%len;
                    break;
                }
            }
            if(ans != -1)  cout<<"found  times:"<<cnt<<"  position:"<<ans+1<<endl;
            else           cout<<"not found  times:"<<cnt<<endl;
        }
    }
    return 0;
}
