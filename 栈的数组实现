//***************************栈实现*****************************

template<class T>
//栈顶指针比栈顶多1
class MyStack {
protected:
    int MAXN;
    int ptr;
    T data[10000];
public:
    MyStack():MAXN(10000),ptr(0){}
    bool Push(T val) {
        if(ptr==MAXN)  return false;
        data[ptr]=val;
        ptr++;
        return true;
    }
    bool Pop() {
        if(ptr==0)  return false;
        ptr--;
        return true;
    }
    T Top() {
        return data[ptr-1];
    }
    bool is_Empty() {
        return ptr == 0;
    }
    bool is_Full() {
        return ptr==MAXN;
    }
    void make_Empty() {
        ptr = 0;
    }
    int Size(){return ptr;}
    ~MyStack(){}
};
//*********************************************************

//*************************测试代码*************************
int main() {
    MyStack<int> v(5);
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
//*********************************************************
