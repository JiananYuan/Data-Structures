//*****************************双向链表*****************************

#define NIL NULL
using namespace std;
template<class T>
struct node {
    T data;
    node* next;
    node* last;
};
//所有下标均从1开始计数
template<class T>
class DoubleList {
protected:
    int n;
    node<T>* head;
    node<T>* tail;
public:
    DoubleList():n(0) {init();}  //构造函数, 结点数初始化为0
    void init() {  //初始化链表
        head = new node<T>;
        head->next = NIL;
        head->last = NIL;
        tail = head;
    }
    void push() {  //相当于push_back()
        T x;
        cin>>x;
        node<T>* p = new node<T>;
        p->data = x;
        p->next = NIL;
        p->last = tail;
        tail->next = p;
        tail = p;
        n++;
    }
    bool Insert(int pos,T val) {  //插在指定位置处
        if(pos>n)  return false;
        node<T>* p=new node<T>;
        p->data=val;
        node<T>* q=head;
        while(pos--)  q=q->next;
        q->last->next=p;
        p->next=q;
        p->last=q->last;
        q->last=p;
        n++;
        return true;
    }
    bool Delete(int pos) {  //删除结点
        if(pos>n)  return false;
        node<T>* p=head;
        while(pos--)  p=p->next;
        p->last->next=p->next;
        p->next->last=p->last;
        delete p;
        n--;
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
    ~DoubleList() {  //析构函数
        node<T>* p=head;
        node<T>* q=NIL;
        while(p != NIL) {
            q=p->next;
            delete p;
            p=q;
        }
        n = 0;
    }
};

//*******************************************************************


int main() {
    //下面为测试
    DoubleList<string> v;
    for(int i=0;i<5;i++) {
        v.push();
        v.Display();
    }
    for(int i=0;i<5;i++) {
        int pos;
        string s;
        cin>>pos>>s;
        if(v.Insert(pos,s))  cout<<"successfully insert"<<endl;
        else  cout<<"error"<<endl;
        v.Display();
    }
    cout<<endl;
    for(int i=0;i<5;i++) {
        int pos;
        cin>>pos;
        if(v.Delete(pos))  cout<<"delete successfully"<<endl;
        else  cout<<"error"<<endl;
        v.Display();
    }
    cout<<endl;
    for(int i=0;i<5;i++) {
        int pos;
        string s;
        cin>>pos>>s;
        if(v.Modify(pos,s))  cout<<"modify successfully"<<endl;
        else  cout<<"error"<<endl;
        v.Display();
    }
    cout<<endl;
    for(int i=0;i<5;i++) {
        string val;
        cin>>val;
        if(v.Find(val)==-1)  cout<<"not found"<<endl;
        else  cout<<"found! "<<v.Find(val)<<endl;
    }
    for(int i=0;i<5;i++) {
        int pos;
        cin>>pos;
        cout<<v.At(pos)<<endl;
    }
    cout<<endl;
    v.Display();
    return 0;
}
