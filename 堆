#include <iostream>
#define INF 0x7fffffff
#define Element int
using namespace std;
struct HNode {
    Element *data;
    int Size;
    int Capacity;
    HNode(int s) {
        data = new Element[s+1];
        Size = 0; Capacity = s; data[0] = INF;
    }
};
typedef HNode* Heap;
typedef Heap MaxHeap;
typedef Heap MinHeap;

bool isFull(MaxHeap h) {
    return h->Size == h->Capacity;
}

bool Insert(MaxHeap h, Element x) {
    if(isFull(h)) return false;
    int i = ++h->Size;
    for(;h->data[i/2] < x;i /= 2) h->data[i] = h->data[i/2];
    h->data[i] = x;
    return true;
}

bool isEmpty(MaxHeap h) {
    return h->Size == 0;
}

Element DeleteMax(MaxHeap h) {
    if(isEmpty(h)) return -1;
    Element maxx = h->data[1];
    Element x = h->data[h->Size--];
    int parent = 0,child = 0;
    for(int parent = 1;parent*2 <= h->Size; parent = child) {
        child = parent*2;
        if((child!=h->Size) && (h->data[child] < h->data[child+1])) {
            child++;
        }
        if(x >= h->data[child]) break;
        else {
            h->data[parent] = h->data[child];
        }
    }
    h->data[parent] = x;
    return maxx;
}

int main() {
    MaxHeap h = new HNode(10);

    return 0;
}
