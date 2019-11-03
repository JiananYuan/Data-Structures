#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
using namespace std;
typedef struct node {
    unsigned weight;
    char data;
    unsigned parent,lchild,rchild;
    void setConfig(int w=0,char d='\0',int p=0,int l=0,int r=0){
        weight=w,data=d,parent=p,lchild=l,rchild=r;
    }
}HTNode,*HuffmanTree;
typedef char** HuffmanCode;

void selectFunction(HuffmanTree& HT,int range,int& s1,int& s2) {
    unsigned tmp = 0x7fffffff;
    for(int i=1;i<=range;i++) {
        if((HT+i)->parent==0&&(HT+i)->weight<tmp) {
            s1 = i;
            tmp = (HT+i)->weight;
        }
    }
    tmp = 0x7fffffff;
    for(int i=1;i<=range;i++) {
        if((HT+i)->parent==0&&i!=s1&&(HT+i)->weight<tmp) {
            s2 = i;
            tmp = (HT+i)->weight;
        }
    }
}

void BuildHuffmanTree(HuffmanTree& HT,int* w,char* e,int n) {
    if(n<=1) return ;
    int m = 2*n - 1;
    HT = (HuffmanTree)malloc((m+1)*sizeof(HTNode));
    for(int i=1;i<=n;i++)   (HT+i)->setConfig(*(w+i),*(e+i),0,0,0);
    for(int i=n+1;i<=m;i++) (HT+i)->setConfig(0,'\0',0,0,0);
    for(int i=n+1;i<=m;i++) {
        int s1 = 0,s2 = 0;
        selectFunction(HT,i-1,s1,s2);
        HT[s1].parent = i; HT[s2].parent = i;
        HT[i].lchild = s1; HT[i].rchild = s2;
        HT[i].weight = HT[s1].weight + HT[s2].weight;
    }
}

void BuildHuffmanCode(HuffmanTree& HT,HuffmanCode& HC,int n) {
    HC = (HuffmanCode)malloc((n+1)*sizeof(char*));
    char *tmp  = (char*)malloc(n*sizeof(char));
    tmp[n-1] = '\0';
    for(int i=1;i<=n;i++) {
        int start = n-1;
        for(int c=i,f=HT[i].parent;f!=0;c=f,f=HT[f].parent) {
            if(HT[f].lchild==c) tmp[--start]='0';
            else                tmp[--start]='1';
        }
        HC[i] = (char*)malloc((n-start)*sizeof(char));
        strcpy(HC[i],&tmp[start]);
    }
    //for(int i=1;i<=n;i++) cout<<ch[i]<<" :"<<HC[i]<<endl;（如果照题意输出，这句补上，且在函数接口处补全参数）
    free(tmp);
}

void HuffmanCoding(char* str,char* e,HuffmanTree& HT,HuffmanCode& HC,int n) {
    int len = strlen(str);
    for(int i=0;i<len;i++) {
        for(int j=1;j<=n;j++) {
            if(str[i] == (HT+j)->data) {
                cout<<HC[j];
                break;
            }
        }
    }
    cout<<endl;
}

void HuffmanDecoding(char* str,HuffmanTree& HT,int n) {
    int root = 2*n-1;
    char* ptr = str;
    int p = root;
    char* ans = (char*)malloc(100*sizeof(char));
    int u = 0;
    while(*ptr!='\0') {
        if(*ptr=='0')  p = (HT+p)->lchild;
        if(*ptr=='1')  p = (HT+p)->rchild;
        ptr++;
        if( (HT+p)->lchild==0 && (HT+p)->rchild==0 ) {
            ans[u++] = (HT+p)->data;
            p = root;
        }
    }
    a[u]='\0';
    if(p==root) cout<<ans<<endl;
    else        cout<<"error!"<<endl;
}

int main() {
    int t; cin>>t;
    while(t--) {
        HuffmanTree tr = NULL;
        int n; cin>>n;
        char ch[15];
        int weight[15];
        for(int i=1;i<=n;i++) cin>>ch[i];
        for(int i=1;i<=n;i++) cin>>weight[i];
        BuildHuffmanTree(tr,weight,ch,n);
        HuffmanCode Code = NULL;
        BuildHuffmanCode(tr,Code,n);
        char str[100];
        cin>>str;
        HuffmanCoding(str,ch,tr,Code,n);
        cin>>str;
        HuffmanDecoding(str,tr,n);
    }
    return 0;
}
