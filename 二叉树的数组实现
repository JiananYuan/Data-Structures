//*****************二叉树的数组实现********************
#include <iostream>
#include <cctype>
#include <math.h>
#include <stdlib.h>
using namespace std;
template <class T>
struct node {
    T data;
};
//*****************************************************
template <class T>
class BinTree {
    protected:
        const static int MAX = 1002;
        node<T> arr[MAX];
        int N;
    public:
        BinTree():N(0) {}
        void Insert() {
            int n; cin>>n;
            for(int i=N+1;i<=N+n;i++) {
                cin>>arr[i].data;
            }
            N += n;
        }
        int Find(T val) {
            for(int i=1;i<=N;i++) {
                if(arr[i].data==val) return i;
            }
            return -1;
        }
        bool is_leaf(int i) {
            return (2*i > N && 2*i+1 > N );
        }
        bool is_root(int i) {
            return i==1;
        }
        T left_child(int i) {
            return arr[2*i].data;
        }
        T right_child(int i) {
            return arr[2*i+1].data;
        }
        int Size() {return N;}
        void make_Empty() {N=0;}
        ~BinTree() {}
};

//********************测试代码*************************

int main() {
    BinTree<int> t;
    string op;
    while(cin>>op) {
        if(op=="insert") {
            t.Insert();
        }
        if(op=="find") {
            int x; cin>>x;
            cout<<t.Find(x)<<endl;
        }
        if(isdigit(op[0])) {
            string opp; cin>>opp;
            int x = atoi(op.c_str());
            if(opp=="is_leaf") {
                cout<<t.is_leaf(x)<<endl;
            }
            if(opp=="is_root") {
                cout<<t.is_root(x)<<endl;
            }
            if(opp=="leftchi") {
                cout<<t.left_child(x)<<endl;
            }
            if(opp=="rightchi") {
                cout<<t.right_child(x)<<endl;
            }
        }
    }

    return 0;
}
