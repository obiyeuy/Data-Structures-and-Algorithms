#include<iostream>
#include<string.h>
using namespace std;
// typedef char SString[255];//定义字符串类型SString

/******
next的计算思想和教材一样，只不过是我们字符串数组下标从0开始计算
教材中是从1开始的，所以本代码的next公式为：
next[j]=
         max{k|j之前最长的相同的真前缀和真后缀串的长度} //教材中公式取的是最长的长度+1，因为我们是从0开始算，直接取最长的长度即可
        -1，j=0时候   表示j=0时候，j之前肯定是空串，更谈不上最长的相同前后缀串了。
        0，其他情况  就是j>0时候，j之前不存在最长的相同前后缀子串

注意：另外j之前相同的前后缀子串可能有多个，我们取最长的那个k
*/
void get_next(string T,int next[]){//计算next值
    int j=0,k=-1;//注意初值含义，j=0时k=-1，表示j之前不存在最长的前后缀串，即next[0]=-1
    next[0]=-1;//这种情况下表示一开始就匹配不上，使用KMP算法时候将同时把i，j后移
    while(j<T.length()){
        if(k==-1||T[j]==T[k]){
            //j++,k++,next[j]=k;
            next[++j]=++k;
            //上述代码的含义就是在next[j]=k的情况下,如果T[j]==T[k],则next[j+1]=k+1
            //或者k=-1条件下，让next[j+1]=0，表示j>0时候不存在相同的最长前后缀串即++k后k=0
        }
        else k=next[k];//如果T[j]≠T[k]，k跳转到next[k]继续循环匹配
    }
}
void get_next2(string T,int next[]){//计算next值的优化算法
    int j=0,k=-1;//注意初值含义，j=0时k=-1，表示j之前不存在最长的前后缀串，即next[0]=-1
    next[0]=-1;//这种情况下表示一开始就匹配不上，是迭代计算next值的基础。使用KMP算法时候将同时把i，j后移
    while(j<T.length()){
        if(k==-1||T[j]==T[k]){
            j++,k++;
            if(T[j]!=T[k])next[j]=k;
            else next[j]=next[k];

        }
        else k=next[k];//如果T[j]≠T[k]，k跳转到next[k]继续循环匹配
    }
}
/****
    S = aaabaaabaaabaaabaaab
    T = aaaab
    改进前：next[j]=-1 0 1 2 3
    优化后：nextval[j]=-1 -1 -1 -1 3
***/
int KMP(string A,string B,int Pos){//KMP算法
    int i=Pos,j=0;
    int next[B.length()];//定义next数组
    get_next2(B,next);//计算next数组的值
    for(int m=0;m<B.length();m++)
        cout<<next[m]<<" ";
    while(i<A.length()&&j<B.length()){
        if(j==-1||A[i]==B[j]){
            i++,j++;
        }
        else
            j=next[j];
    }
    if(j==B.length())
        return i-j;
    else
        return -1;
}

int main(){
    string S,T;
    cout<<"input mainstring  S:";
    cin>>S;
    cout<<" intput substring T:";
    cin>>T;
    cout<<"the match pos ="<<KMP(S,T,0)<<endl;
    return 0;
}


