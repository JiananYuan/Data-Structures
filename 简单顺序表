//*******************顺序表**********************
//!注意：下标从1计起
template<class T>
class MyArray{
protected:
    T data[10001];
    int MAXN;
    int Size;
public:
    MyArray(): Size(0), MAXN(10001){}
    bool Push(T val) {
    	if(Size>10000)  return false;
    	Size++;
        data[Size]=val;
        return true;
	}
    bool Modify(int pos, T val) {
        if(pos>Size) return false;
        data[pos]=val;
        return true;
    }
    bool Insert(int pos,T val) {
        if(pos>Size)  return false;
        Size++;
        for(int i=Size;i>pos;i--)
            data[i]=data[i-1];
        data[pos]=val;
        return true;
    }
    bool Delete(int pos) {
        if(pos>Size)  return false;
        for(int i=pos;i<=Size-1;i++)
            data[i]=data[i+1];
        Size--;
        return true;
    }
    T At(int pos) {
        return data[pos];
    }
    int Find(T val) {
        for(int i=1;i<=Size;i++)
            if(val==data[i])  return i;
        return -1;
    }
    void Display() {
        for(int i=1;i<=Size;i++)  cout<<data[i]<<" ";
        cout<<endl;
    }
    int getSize(){return Size;}
    ~MyArray(){}
};
//********************************************************

//********************************************************
int main() {
    int n;
    cin>>n;
    MyArray<int> v;
    while(n--) {
        int x;
        cin>>x;
        v.Push(x);
    }
    v.Display();
    int pos,val;
    cin>>pos>>val;
    if(pos<1||pos>v.getSize())  cout<<"error"<<endl;
    else {v.Insert(pos,val);v.Display();}
    cin>>pos>>val;
    if(pos<1||pos>v.getSize())  cout<<"error"<<endl;
    else {v.Insert(pos,val);v.Display();}
    cin>>pos;
    if(pos<1||pos>v.getSize())  cout<<"error"<<endl;
    else {v.Delete(pos);v.Display();}
    cin>>pos;
    if(pos<1||pos>v.getSize())  cout<<"error"<<endl;
    else {v.Delete(pos);v.Display();}
    cin>>pos;
    if(pos<1||pos>v.getSize())  cout<<"error"<<endl;
    else                        cout<<v.At(pos)<<endl;
    cin>>pos;
    if(pos<1||pos>v.getSize())  cout<<"error"<<endl;
    else                        cout<<v.At(pos)<<endl;
    return 0;
}
//*********************************************************
