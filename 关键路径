#include <iostream>
#include <stack>
#include <queue>
#include <algorithm>
#define MAX 35
using namespace std;
struct node {
    int to,val;
    node* nxt;
    node(int a=0,int b=0): to(a),val(b),nxt(NULL){}
}e[MAX];
int n,m;
int ve[MAX],vl[MAX];

void build() {
    for(int i=0;i<m;i++) {
        int u,v,w; cin >> u >> v >>w;
        node *p = &e[u];
        while(p->nxt)
            p = p->nxt;
        p->nxt = new node(v,w);
    }
}

void Tsort() {
    int ind[MAX] = {0};
    for(int i=0;i<n;i++) {
        node* p = e[i].nxt;
        while(p) {
            ind[ p->to ] ++;
            p = p->nxt;
        }
    }

    queue<int> q;
    for(int i=0;i<n;i++) {
        if(ind[i] == 0) {
            q.push(i);
            ind[i] = -1;
        }
    }

    stack<int> s;
    while(!q.empty()) {
        int pos = q.front(); q.pop(); s.push(pos);
        node* p = e[pos].nxt;
        while(p) {
            ind[ p->to ] --;
            ve[p->to] = max(ve[p->to],ve[pos] + p->val);
            p = p->nxt;
        }
        for(int i=0;i<n;i++) {
            if(ind[i] == 0) {
                q.push(i);
                ind[i]  = -1;
            }
        }
    }

    for(int i=0;i<n;i++) vl[i] = ve[s.top()];
    while(!s.empty()) {
        int id = s.top(); s.pop();
        node* p = e[id].nxt;
        while(p) {
            if(vl[id] + p->val > vl[p->to]) {
                vl[id] = vl[p->to] - p->val;
            }
            p = p->nxt;
        }
    }
}

void FindKeyPath() {
    Tsort();
//    for(int i=0;i<n;i++) {
//        if(ve[i] == vl[i]) cout<< i <<" ";
//    }
    for(int i=0;i<n;i++) cout<<ve[i]<<" ";
    cout<<endl;
    for(int i=0;i<n;i++) cout<<vl[i]<<" ";
    cout<<endl;
}

int main() {
    cin >> n >> m;
    build();
    FindKeyPath();
    return 0;
}
