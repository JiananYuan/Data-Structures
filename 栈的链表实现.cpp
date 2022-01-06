#include <iostream>
#define NIL NULL
using namespace std;
template<class T>
struct node {
    T data;
    node* next;
};
//所有下标均从1开始计数
template<class T>
class MyList {
protected:
    int n;
    node<T>* head;
    node<T>* tail;
public:
    MyList(){init();}  //构造函数, 结点数初始化为0
    void init() {  //初始化链表
        n = 0;
        head = new node<T>;
        head->next = NIL;
        tail = head;
    }
    void push(T val) {  //相当于push_back()
        node<T>* p = new node<T>;
        p->data = val;
        p->next = NIL;
        tail->next = p;
        tail = p;
        n++;
    }
    bool Insert(int pos,T val) {  //插在指定位置处
        if(pos>n)  return false;
        node<T>* p=new node<T>;
        p->data=val;
        node<T>* pr=prve(pos);
        p->next=pr->next;
        pr->next=p;
        n++;
        return true;
    }
    node<T>* prve(int pos) {  //寻找前驱结点
        pos--;
        node<T>* p=head;
        while(pos--) p=p->next;
        return p;
    }
    bool Delete(int pos) {  //删除结点
        if(pos>n)  return false;
        node<T>* pr=prve(pos);
        node<T>* p=head;
        while(pos--)  p=p->next;
        pr->next=p->next;
        delete p;
        n--;
        //下一句为stack专用语句
        tail = pr;
        return true;
    }
    bool Modify(int pos,T val) {  //修改结点值
        if(pos>n)  return false;
        node<T>* p=head;
        while(pos--)  p=p->next;
        p->data=val;
        return true;
    }
    int Find(T val) {  //按值查找
        int cnt=0;
        node<T>* p=head->next;
        while(p!=NIL) {
            cnt++;
            if( p->data==val ) {
                return cnt;
            }
            p=p->next;
        }
        return -1;
    }
    T At(int pos) {  //查询pos位置上的值
        node<T>* p=head;
        while(pos--)  p=p->next;
        return p->data;
    }
    void Display() {  //展示链表内容
        node<T>* p = head->next;
        while(p!=NIL) {
            cout<<p->data<<" ";
            p=p->next;
        }
        cout<<endl;
    }
    int how_many() {return n;} //查询结点数
    ~MyList() {  //析构函数
        node<T>* p=head;
        node<T>* q;
        while(p != NIL) {
            q=p->next;
            delete p;
            p=q;
        }
        n = 0;
    }
};

//不继承，而是组合
template<class T>
//栈顶指针比栈顶多1
class MyStack {
protected:
    int MAXN;
    MyList<T> v;
public:
    MyStack():MAXN(10000){}
    bool Push(T val) {
        if(Size()==MAXN)  return false;
        v.push(val);
        return true;
    }
    bool Pop() {
        if(Size()==0)  return false;
        v.Delete(v.how_many());
        return true;
    }
    T Top() {
        return v.At(v.how_many());
    }
    bool is_Empty() {
        return v.how_many() == 0;
    }
    bool is_Full() {
        return v.how_many() == MAXN;
    }
    void make_Empty() {
        v.~MyList();
        v.init();
    }
    int Size(){return v.how_many();}
    ~MyStack(){}
};

int main() {
    MyStack<int> v;
    string op;
    while(cin>>op) {
        if(op=="pop") {
            if(v.Pop()) {
                cout<<"pop successfully"<<endl;
            } else {
                cout<<"error"<<endl;
            }
        } else if(op=="push") {
            int x;
            cin>>x;
            if(v.Push(x)) {
                cout<<"push successfully"<<endl;
            } else {
                cout<<"error"<<endl;
            }
        } else if(op=="top") {
            cout<<v.Top()<<endl;
        } else if(op=="empty?") {
            if(v.is_Empty()) {
                cout<<"empty"<<endl;
            } else {
                cout<<"not"<<endl;
            }
        } else if(op=="full?") {
            if(v.is_Full()) {
                cout<<"full"<<endl;
            } else {
                cout<<"not"<<endl;
            }
        }
    }
    v.make_Empty();
    return 0;
}
