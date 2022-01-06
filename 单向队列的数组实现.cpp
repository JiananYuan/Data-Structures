//************************单向队列***************************
#include <iostream>
using namespace std;
template <class T>
class MyQueue {
protected:
    const static int MAX = 1001;
    int head;
    int tail;
    int Size;
    T arr[MAX];
public:
    MyQueue() {
        head=tail=0;//the queue is empty
    }
    bool Push(T val) {
        if(isFull()) return false;
        arr[tail]=val;
        tail = (tail+1)% MAX;
        Size++;
        return true;
    }
    bool Pop() {
        if(isEmpty()) return false;
        head=(head+1)% MAX;
        Size--;
        return true;
    }
    T Front() {
        return arr[head];
    }
    int getSize() {return Size;}
    bool isEmpty() {return head==tail;}
    bool isFull() {return (tail+1) % MAX == head;}
    ~MyQueue(){}
};
//*************************************************

//*****************测试代码*************************
int main() {
    MyQueue<string> v;
    string op;
    while(cin>>op) {
        if(op=="push") {
            string x;
            cin>>x;
            v.Push(x);
        } else if(op=="pop") {
            if(v.Pop()) cout<<"pop successfully"<<endl;
            else		cout<<"error"<<endl;
        } else if(op=="top") {
            cout<<v.Front()<<endl;
        } else if(op=="empty?") {
            if(v.isEmpty())  cout<<"empty"<<endl;
            else  cout<<"not yet"<<endl;
        } else if(op=="size") {
            cout<<v.getSize()<<endl;
        } else if(op=="full?") {
            if(v.isFull()) cout<<"full"<<endl;
            else           cout<<"no yet"<<endl;
        }
     }
    return 0;
}
//*****************************************************
