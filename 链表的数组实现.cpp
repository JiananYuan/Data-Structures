#include <iostream>
#define MAX 10005
using namespace std;

template <class T>
struct node {
    T data;
    int cur;
};

template <class T>
class CurList {
protected:
    node<T> a[MAX];
    int Size;
    int head,tail;
    /* alloc分配空间，不成功返回-1 */
    int alloc() {
        int pos = a[0].cur;  //从备用链表上取结点
        if(pos == 0)  return -1; //链表已满
        a[0].cur  = a[pos].cur; //更新备用链表的头节点下一个指向
        return pos;
    }
    bool free(int pos) {
        if(pos<1||pos>Size) return false;
        a[pos].cur = a[0].cur;
        a[0].cur = pos; //将pos位置上的结点加到备用链表中
        return true;
    }
public:
    /*初始化表 O(N) */
    CurList() {
        for(int i=0;i<MAX;i++) {
            a[i].cur = i+1;
        }
        a[MAX-1].cur = 0;
        Size=0;
        head = alloc();
        a[head].cur = 0;
        tail = head;
    }
    /*push将数据加到表尾 O(1)*/
    bool Push(T val) {
        int des = alloc();
        if(des == -1)  return false;
        a[des].data = val;
        a[des].cur = 0;
        a[tail].cur = des;
        tail = des;
        Size++;
        return true;
    }
    /*插入到指定位置的后一个位置*/
    bool Insert(int pos,T val) {
        int des=alloc();
        if(des==-1) return false;
        int pre=Find_previous(pos);
        a[des].data = val;
        a[des].cur = a[pre].cur;
        a[pre].cur = des;
        Size++;
        return true;
    }
    bool Delete(int pos) {
        if(pos<1||pos>Size) return false;
        int pre = Find_previous(pos);
        int i=head;
        while(pos--) i=a[i].cur;
        a[pre].cur = a[i].cur;
        free(i);
        return true;
    }
    bool Modify(int pos,T val) {
        if(pos<1||pos>Size)  return false;
        int i=head;
        while(pos--) i=a[i].cur;
        a[i].data = val;
        return true;
    }
    T At(int pos) {
        int i=head;
        while(pos--) i=a[i].cur;
        return a[i].data;
    }
    int Find(T val) {
        int cnt=1;
        for(int i=a[head].cur;i!=0;i=a[i].cur) {
            if(a[i].data == val) return cnt;
            cnt++;
        }
        return -1;
    }
    int Find_previous(int pos) {
        int i=head;
        pos--;
        while(pos--)  i=a[i].cur;
        return i;
    }
    bool is_Empty() {
        return a[head].cur == 0;
    }
    void Display() {
        for(int i = a[head].cur;i!=0;i = a[i].cur) {
            cout<<a[i].data<<" ";
        }
        cout<<endl;
    }
    ~CurList() {}
};



//***************************************************************
int main() {
    CurList<int> v;
    string op;
    while(cin>>op) {
        if(op=="push") {
            int x;
            cin>>x;
            v.Push(x);
        }
        if(op=="insert") {
            int a,b;
            cin>>a>>b;
            v.Insert(a,b);
        }
        if(op=="delete") {
            int pos;
            cin>>pos;
            if(v.Delete(pos)) cout<<"delete successfully"<<endl;
            else              cout<<"error"<<endl;
        }
        if(op=="modify") {
            int pos,val;
            cin>>pos>>val;
            if(v.Modify(pos,val)) cout<<"modify successfully"<<endl;
            else                  cout<<"error"<<endl;
        }
        if(op=="at") {
            int pos; cin>>pos;
            cout<<v.At(pos)<<endl;
        }
        if(op=="find") {
            int des;
            cin>>des;
            if(v.Find(des)!=-1)  cout<<v.Find(des)<<endl;
            else                 cout<<"not found"<<endl;
        }
        if(op=="em") {
            if(v.is_Empty())    cout<<"empty"<<endl;
            else                cout<<"not yet empty"<<endl;
        }
        v.Display();
    }
    return 0;
}
