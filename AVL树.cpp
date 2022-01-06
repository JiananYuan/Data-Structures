#include <iostream>
#include <algorithm>
#define NIL NULL
using namespace std;
typedef int Element;
struct node {
    Element data;
    node* l;
    node* r;
    int h;
    node(Element d = 0,node* a = NIL,node* b = NIL,int he = 0):data(d),l(a),r(b),h(he) {}
};

typedef node* AVLTree;

int getHeight(AVLTree t) {
    if(t) {
        int lmax = getHeight(t->l);
        int rmax = getHeight(t->r);
        return max(lmax,rmax)+1;
    }
    return 0;
}

AVLTree LeftRotate(AVLTree t) { //顺时针
    AVLTree root = t -> l;
    t -> l = root -> r;
    root -> r = t;
    t -> h = max(getHeight(t->l),getHeight(t->r))+1;
    root -> h = max(getHeight(root->l),getHeight(t))+1;
    return root;
}

AVLTree RightRotate(AVLTree t) { //逆时针
    AVLTree root = t -> r;
    t -> r = root -> l;
    root -> l = t;
    t -> h = max(getHeight(t->l),getHeight(t->r))+1;
    root -> h = max(getHeight(root->r),getHeight(t))+1;
    return root;
}

AVLTree LeftRightRotate(AVLTree t) {
    t->l = RightRotate(t->l);
    return LeftRotate(t);
}

AVLTree RightLeftRotate(AVLTree t) {
    t->r = LeftRotate(t->r);
    return RightRotate(t);
}


AVLTree Insert(AVLTree T,Element c) {
    if(!T)  T = new node(c,NIL,NIL,1);
    else if(c < T->data) {
        T -> l = Insert(T -> l,c);
        if(getHeight(T->l) - getHeight(T->r) == 2) {
            if(c < T->l->data)  T = LeftRotate(T);
            else  T = LeftRightRotate(T);
        }
    }
    else if(c > T->data) {
        T -> r = Insert(T -> r,c);
        if(getHeight(T->r) - getHeight(T->l) == 2) {
            if(c > T->r->data)  T = RightRotate(T);
            else  T = RightLeftRotate(T);
        }
    }
    T -> h = max(getHeight(T->l),getHeight(T->r))+1;
    return T;
}

void preOrder(AVLTree t) {
    if(t) {
        cout<<t->data<<" ";
        preOrder(t->l);
        preOrder(t->r);
    }
}

void inOrder(AVLTree t) {
    if(t) {
        inOrder(t->l);
        cout<<t->data<<" ";
        inOrder(t->r);
    }
}

void postOrder(AVLTree t) {
    if(t) {
        postOrder(t->l);
        postOrder(t->r);
        cout<<t->data<<" ";
    }
}

bool Find(AVLTree t,Element x) {
    if(t) {
        if(t->data == x) return true;
        if(t->data > x)
            return Find(t->l,x);
        else
            return Find(t->r,x);
    }
    return false;
}

int main() {
    AVLTree tr = NIL;
    string op;
    while(cin>>op) {
        if(op == "insert") {
            int x; cin>>x;
            tr = Insert(tr,x);
        }
        if(op == "pre") {
            preOrder(tr);
            cout<<endl;
        }
        if(op == "in") {
            inOrder(tr);
            cout<<endl;
        }
        if(op == "post") {
            postOrder(tr);
            cout<<endl;
        }
        if(op == "find") {
            int x; cin>>x;
            if(Find(tr,x)) cout<<"exist!"<<endl;
            else           cout<<"not exist!"<<endl;
        }
    }
    return 0;
}
