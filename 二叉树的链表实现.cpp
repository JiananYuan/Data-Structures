//*****************二叉树的数组实现********************
#include <iostream>
#include <cctype>
#include <math.h>
#include <stdlib.h>
#include <stack>
#include <queue>
#include <algorithm>
using namespace std;
typedef struct node* position;
typedef position BinTree;
typedef int Element;
struct node {
    Element data;
    BinTree left;
    BinTree right;
};

BinTree CreateBinTree() {
    Element data;
    cin>>data;
    BinTree BT,T;
    queue<BinTree> q;
    if(data!=0) {
        BT = new node;
        BT->data = data;
        BT->left = BT->right = NULL;
        q.push(BT);
    }
    else return NULL;
    while(!q.empty()) {
        T = q.front(); q.pop();
        cin>>data;
        if(data==0) T->left = NULL;
        else {
            T -> left = new node;
            T->left->data = data;
            T->left->left = T->left->right = NULL;
            q.push(T->left);
        }

        cin>>data;
        if(data==0) T->right = NULL;
        else {
            T -> right = new node;
            T->right->data = data;
            T->right->left = T->right->right = NULL;
            q.push(T->right);
        }
    }
    return BT;
}

bool IsEmpty(BinTree BT) {
    return BT == NULL;
}

void Pre_Order(BinTree BT) {
    if(BT) {
        cout<<BT->data<<" ";
        Pre_Order(BT->left);
        Pre_Order(BT->right);
    }
}

void In_Order(BinTree BT) {
    if(BT) {
        In_Order(BT->left);
        cout<<BT->data<<" ";
        In_Order(BT->right);
    }
}

void Post_Order(BinTree BT) {
    if(BT) {
        Post_Order(BT->left);
        Post_Order(BT->right);
        cout<<BT->data<<" ";
    }
}

void StackInOrder(BinTree BT) {
    BinTree T;
    stack<BinTree> s;
    T = BT;
    while(T || !s.empty()) {
        while(T) {
            s.push(T);
            T = T->left;
        }
        T = s.top();
        s.pop();
        cout<<T->data<<" ";
        T = T->right;
    }
}

void LevelOrder(BinTree BT) {
    if(!BT) return ;
    queue<BinTree> q;
    q.push(BT);
    while(!q.empty()) {
        BinTree t = q.front();
        q.pop();
        cout<<t->data<< " ";
        if(t->left) q.push(t->left);
        if(t->right) q.push(t->right);
    }
}

int getHeight(BinTree BT) {
    if(BT) {
        int HL = getHeight(BT->left);
        int HR = getHeight(BT->right);
        return max(HL,HR)+1;
    }
    return 0;
}

void destoryBinTree(BinTree BT) {
    if(BT) {
        destoryBinTree(BT->left);
        destoryBinTree(BT->right);
        delete BT;
    }
}
//*****************************************************

//********************测试代码*************************

int main() {
    string op;
    BinTree t;
    while(cin>>op) {
        if(op=="create") {
            t = CreateBinTree();
        }
        if(op=="pre") {
            Pre_Order(t);
        }
        if(op=="in") {
            In_Order(t);
        }
        if(op=="post") {
            Post_Order(t);
        }
        if(op=="stackin") {
            StackInOrder(t);
        }
        if(op=="geth") {
            cout<<getHeight(t)<<endl;
        }
        if(op=="level") {
            LevelOrder(t);
        }
        if(op=="stop") {
            destoryBinTree(t);
        }
    }
    return 0;
}
