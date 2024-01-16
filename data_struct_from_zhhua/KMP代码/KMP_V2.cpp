#include "stdio.h"
#define  MAXSTRLEN  255   // 用户可在255以内定义最大串长
typedef unsigned char SString[MAXSTRLEN + 1];// 0号单元存放串的长度
int Index(SString S, SString T, int pos) {//简单匹配
   // 返回子串T在主串S中第pos个字符之后的位置。若不存在，
    // 则函数值为0。其中，T非空，1≤pos≤StrLength(S)。
    int i = pos;   int j = 1;
    while (i <= S[0] && j <= T[0]) {
      if (S[i] == T[j]) { ++i;  ++j; }   // 继续比较后继字符
      else { i = i-j+2;   j = 1; }     // 指针后退重新开始匹配
    }
   if (j > T[0])  return  i-T[0];
   else return 0;
} // Index
void get_next(SString T, int next[] ) {//next值的计算
     // 求模式串T的next函数值并存入数组next
    int i = 1;   next[1] = 0;  int j = 0;
      while (i < T[0]) {
           if (j == 0 || T[i] == T[j])
                 {++i;  ++j; next[i] = j; }
           else  j = next[j];
      }
    } // get_next
 void get_nextval(SString T, int nextval[]) {//改进的next值的计算
      int  i = 1;   nextval[1] = 0;  int j = 0;
      while (i < T[0]) {
          if (j ==0 || T[i] == T[j]) {
              ++i;  ++j;
              if (T[i] != T[j])  nextval[i] = j;
              else  nextval[i] = nextval[j];
         }
        else  j = nextval[j];
     }
  } // get_nextval
 int Index_KMP(SString S, SString T, int pos) {
     //  1≤pos≤StrLength(S)
	 int next[MAXSTRLEN + 1];//定义next
	 get_next(T,next);//next值计算
	 //int nextval[MAXSTRLEN + 1];//定义nextval
	 //get_nextval(T,nextval); //计算改进的next值

     int i = pos;   int j = 1;
     while (i <= S[0] && j <= T[0]) {
         if (j == 0 || S[i] == T[j]) { ++i;  ++j; }
                                               // 继续比较后继字符
       else  j = next[j];         // 模式串向右移动
     }
    if (j > T[0])  return  i-T[0];    // 匹配成功
    else return 0;
} // Index_KMP




void InitStr(SString S,char* p){
	int i=0;
	for(i=1;*p;p++,i++){//拷贝
		S[i]=*p;
	}
	S[0]=i-1;//长度值为i-1；
}

int main(){
SString S,T;
InitStr(S,"aaabbabbc");
InitStr(T,"abb");
//printf("the match pos is %d\n",Index(S,T,4));//¼òµ¥µÄÆ¥Åä
printf("the match pos is %d\n",Index_KMP(S,T,4));//KMP
return 0;
}
