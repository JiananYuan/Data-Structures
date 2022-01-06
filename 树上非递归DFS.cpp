//前序遍历
void NonRecursoinPreOrder(BinTree t) {
    if(t==NULL) return ;
    stack<BinTree> tmp;
    while(t!=NULL) {
        if(t->right!=NULL) tmp.push(t->right);
        cout<<t->data;
        t = t->left;
    }
    node* p = NULL;
    while(!tmp.empty()) {
        p = tmp.top();
        tmp.pop();
        while(p!=NULL) {
            if(p->right!=NULL) tmp.push(p->right);
            cout<<p->data;
            p  = p->left;
        }
    }
}

//中序遍历
void NonRecursionInOrder(BinTree t) {
    if(t==NULL) return ;
    stack<BinTree> s;
    while(t) {
        s.push(t);
        t = t->left;
    }
    node* p = NULL;
    while(!s.empty()) {
        p = s.top();
        s.pop();
        cout<< p->data ;
        if(p->right) {
            p = p->right;
            while(p) {
                s.push(p);
                p = p->left;
            }
        }
    }
}

//后序遍历
void NonRecursionPostOrder(BinTree t) {
    if(!t) return ;
    stack<BinTree> v;
    stack<BinTree> book;
    book.push(NULL);
    while(t) {
        v.push(t);
        t = t->left;
    }
    node* p = NULL;
    while(!v.empty()) {
        p = v.top();
        if((p->right==NULL&&p->left==NULL)||p->right==NULL) {
            cout<<p->data;
            v.pop();
            continue;
        }
        if(p->right==book.top()) {
            cout<<p->data;
            v.pop();
            book.pop();
            continue;
        }
        if(p->right) {
            p = p->right;
            book.push(p);
            while(p) {
                v.push(p);
                p = p->left;
            }
        }
    }
}
