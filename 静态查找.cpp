#include <iostream>
#include <stdio.h>
#include <cstring>
#include <algorithm>
#include <math.h>
#define MAX 10005
#define N 200
using namespace std;
typedef int Element;


//顺序查找----------------------------------------
int SearchInOrder(Element a[],int n,Element key) {
    a[0] = key;
    int i = n;
    while(a[i] != key) i--;
    return i;
}
//------------------------------------------------


//二分查找----------------------------------------
bool SearchInBinary(Element a[],int n,Element key) {
    int l = 1;
    int r = n;
    Element d[MAX];
    memcpy(d+1,a+1,n*sizeof(int));
    sort(d+1,d+1+n);
    while(l <= r) {
        int mid = (l+r)/2;
        if(d[mid] == key) return true;
        else if(d[mid] >  key) r = mid - 1;
        else if(d[mid] <  key) l = mid + 1;
    }
    return false;
}
//-------------------------------------------------


//分块查找-----------------------------------------
struct Index {
    int maxx;
    int start_id;
    int end_id;
}index[N];

void buildBlocks(Element a[],int n,int m) {
    int c = n/m;
    for(int i = 1;i <= m-1; i++) {
        index[i].maxx = a[i*c];
        index[i].start_id = (i-1)*c + 1;
        index[i].end_id = i*c;
        for(int j = index[i].start_id;j <= index[i].end_id ;j++) {
            index[i].maxx = max(a[j],index[i].maxx);
        }
    }
    index[m].maxx = a[m*c];
    index[m].start_id = (m-1)*c + 1;
    index[m].end_id = n;
    for(int j = index[m].start_id; j <= index[m].end_id ;j++) {
        index[m].maxx = max(a[j],index[m].maxx);
    }
}

int SearchInBlocks(Element a[],int n,int m,Element x) {
    int c = n/m;
    int l = 1,r = m, mid = 0;
    while(l <= r) {
        mid = (l+r)/2;
        if(index[mid].maxx == x)  break;
        else if(index[mid].maxx > x) r = mid - 1;
        else if(index[mid].maxx < x) l = mid + 1;
    }
    if(index[mid].maxx < x) mid++;
    for(int j = index[mid].start_id; j <= index[mid].end_id ;j++) {
        if(x == a[j]) return j;
    }
    return 0;
}
//-------------------------------------------------------


int main(){
    Element a[MAX];
    //freopen("1.txt","r",stdin);
    int n; cin>>n;
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
//    int m; cin>>m;
//    buildBlocks(a,n,m);
//    int x = 0;
//    while(cin>>x) {
//        cout<<SearchInBlocks(a,n,m,x)<<endl;
//    }
    return 0;
}
