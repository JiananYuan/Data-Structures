/***************************循环链表**************************

template<class T>
struct node {
    T data;
    node* next;
    node* last;
};
//所有下标均从1开始计数
template<class T>
class CircleList {
protected:
    int n;
    node<T>* head;
    node<T>* tail;
public:
    CircleList():n(0) {init();}  //构造函数, 结点数初始化为0
    void init() {  //初始化链表
        head = new node<T>;
        head->next = head;
        head->last = head;
        tail = head;
    }
    void push(T x) {  //相当于push_back()
        node<T>* p = new node<T>;
        p->data = x;
        p->next = head;
        head->last = p;
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
        while(pos--) p=p->next;
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
        while(p!=head) {
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
        while(p!=head) {
            cout<<p->data<<" ";
            p=p->next;
        }
        cout<<endl;
    }
    int how_many() {return n;} //查询结点数
    bool is_Empty() {return n == 0;}
    ~CircleList() {  //析构函数
        node<T>* p=head->next;
        node<T>* q;
        while(p != head) {
            q=p->next;
            delete p;
            p=q;
        }
        delete head;
        n = 0;
    }
};
//*******************************************************
