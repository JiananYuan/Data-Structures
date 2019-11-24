//***************************二叉搜索树(指针实现)*************************
#include <iostream>
using namespace std;
template <class T>
struct node {
    T element;
    node* left;
    node* right;
    node(T e,node* l,node* r):element(e),left(l),right(r){}
};

template <class T>
class BSTree {
protected:
    node<T>* root;
public:
    BSTree(){root = NULL;}

    node<T>* getRoot(){return root;}

    bool inside_Find(T val,node<T>* p) {
        if(p==NULL) return false;
        if(val < p->element) return inside_Find(val,p->left);
        else if(val > p->element) return inside_Find(val,p->right);
        else return true;
    }

    bool Find(T val) {
        return inside_Find(val,root);
    }

    node<T>* inside_FindMin(node<T>* p) {
        if(root==NULL) return NULL;
        else if(p->left==NULL) return p;
        else return inside_FindMin(p->left);
    }

    int FindMin() {return inside_FindMin(root)->element;}

    node<T>* inside_FindMax(node<T>* p) {
        if(root==NULL) return NULL;
        if(p!=NULL) {
            while(p->right != NULL) {
                p = p->right;
            }
        }
        return p;
    }

    int FindMax() {return inside_FindMax(root)->element;}

    void inside_Insert(int val,node<T>*& p) {
        if(p==NULL) {
            p = new node<T>(val,NULL,NULL);
        }
        else if(val < p->element) inside_Insert(val,p->left);
        else if(val > p->element) inside_Insert(val,p->right);
    }

    void Insert(int val) {
        inside_Insert(val,root);
    }

    node<T>* inside_Delete(int val,node<T>* p) {
        if(p==NULL) return NULL;
        else if(val < p->element) p->left = inside_Delete(val,p->left);
        else if(val > p->element) p->right = inside_Delete(val,p->right);
        // found and will be judged
        else if(p->left && p->right) {
            node<T>* tmp = inside_FindMin(p->right);
            p->element = tmp->element;
            p->right = inside_Delete(p->element,p->right);
        }
        else {
            node<T>* tmp = p;
            if(p->left==NULL) p=p->right;
            else if(p->right==NULL) p=p->left;
            delete tmp;
        }
        return p;
    }

    void Delete(int val) {
        inside_Delete(val,root);
    }

    void PreOrder(node<T>* p) {
        if(p==NULL) return ;
        cout<<p->element<<" ";
        PreOrder(p->left);
        PreOrder(p->right);
    }

    void InOrder(node<T>* p) {
        if(p==NULL) return ;
        InOrder(p->left);
        cout<<p->element<<" ";
        InOrder(p->right);
    }

    void PostOrder(node<T>* p) {
        if(p==NULL) return ;
        PostOrder(p->left);
        PostOrder(p->right);
        cout<<p->element<<" ";
    }

    ~BSTree(){makeEmpty(root);}

    void makeEmpty(node<T>* p) {
        if(p!=NULL) {
            makeEmpty(p->left);
            makeEmpty(p->right);
            delete p;
        }
    }
};
//************************************************************************

//*********************************测试代码********************************
int main()
{
    BSTree<int> a;
    string op;
    while(cin>>op) {
        if(op=="insert") {
            int x;
            cin>>x;
            a.Insert(x);
        }
        if(op=="find") {
            int x;
            cin>>x;
            cout<<a.Find(x)<<endl;
        }
        if(op=="delete") {
            int x;
            cin>>x;
            a.Delete(x);
        }
        if(op=="max") {
            cout<<a.FindMax()<<endl;
        }
        if(op=="min") {
            cout<<a.FindMin()<<endl;
        }
        if(op=="前序遍历") {
            a.PreOrder(a.getRoot());
            cout<<endl;
        }
        if(op=="中序遍历") {
            a.InOrder(a.getRoot());
            cout<<endl;
        }
        if(op=="后序遍历") {
            a.PostOrder(a.getRoot());
            cout<<endl;
        }
    }
    return 0;
}
