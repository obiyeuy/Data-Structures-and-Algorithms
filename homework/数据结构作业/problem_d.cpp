#include <iostream>
using namespace std;
#include <string.h>
#include <vector>

typedef struct {
    int p;//最佳匹配的位置
    int num;//最佳匹配的基因数量
    int seq;//发生最佳匹配基因库中的供体序号
} Match;//匹配结果类

//void get_next(string T, int next[]) { //next值的计算
//    // 求模式串T的next函数值并存入数组next
//    int i = 1;
//    next[1] = 0;
//    int j = 0;
//    while (i < T[0]) {
//        if (j == 0 || T[i] == T[j]) {
//            ++i;
//            ++j;
//            next[i] = j;
//        }
//        else  j = next[j];
//    }
//} // get_next
//
//Match Index_KMP(string S, string T, int pos) { //KMP匹配
//    //  1≤pos≤StrLength(S)
//    int next[256];//定义next,0号空间不用
//    get_next(T, next);//next值计算
//    int i = pos;
//    int j = 1;
//    Match m, mtemp; //m存放最优匹配结果，mtemp存放当前的匹配结果
//    m.p = mtemp.p = pos;
//    m.num = mtemp.num = 0;
//    while (i <= S[0] && j <= T[0])
//    {
//        if (j == 0 || S[i] == T[j])
//        {
//            ++i;
//            ++j;
//            if (j == 1)
//            {
//                //如果当前的匹配结果优于之前的最优结果，则修正最优结果为当前值
//                if (mtemp.num >= m.num) {
//                    m.num = mtemp.num;
//                    m.p = mtemp.p;
//                }
//                mtemp.num = 0;
//                mtemp.p = i;
//            }
//            else//S[i]=T[j]
//                ++mtemp.num;//当前匹配上的基因数量++
//        }
//        else { //j≠0&&S[i] ≠ T[j]
//            j = next[j];         // 模式串向右移动
//            if (mtemp.num >= m.num)//如果当前的匹配结果优于之前的最优结果，则修正最优结果为当前值
//            {
//                m.num = mtemp.num;
//                m.p = mtemp.p;
//            }
//            mtemp.num = j - 1;
//            mtemp.p = i - j;
//        }
//    }
//    if (mtemp.num >= m.num)//如果当前的匹配结果优于之前的最优结果，则修正最优结果为当前值
//    {
//        m.num = mtemp.num;
//        m.p = mtemp.p;
//    }
//    m.seq = 0;
//    return m;
//} // Index_KMP

//void InsertStr(string& S, string P) { //从S的1号位置开始插入P，S的第0个空间存放长度
//    S = "0";//此处必须有个初始化，否则insert将失败
//    S.insert(1, P);//从S的1号位置开始插入P
//    S[0] = P.length();//S[0]用于存放长度
//}

Match Index(string S,string T, int position)
{
    int s = S.length();
    int t = T.length();
    Match m;
    m.p = 0;
    m.num = 0;

    int i = 0, j = 0;
    int maxj = 0;
    int maxi = 0;
    int index = position;
    while (index < s ) {
        for (j = 0, i = index; j < t; j++) {
            if (S[i] == T[j]) {
                i++;
            }
            else {
                break;
            }
        }
        if (j > maxj) {
            maxj = j;
            maxi = index;
        }
        if (j == t) {
            maxj = j;
            maxi = index;
            break;
        }
        if (j < t) { //not match
            j = 0;
            index++;

        }
        else {    //matched
            m.num = T.length() - 1;
            m.p = index;
        }
    } 
    if (maxj > m.num) {
        m.num = maxj;
        m.p = maxi;
    }
    m.seq = 0;
    return m;
}


int main() {
    int n;/***基因库规模：基因串数量***/
    cin >> n;
    vector<string> supply(n);/**n个人的基因库**/
    string ge;//临时量
    for (int i = 0; i < n; i++) {
        cin >> ge;
        supply[i] = ge;//串插入
    }
    string accept;/**受体基因串**/
    cin >> accept;//串插入
    Match m, mt;
    m.p = 0;
    m.num = 0;
    m.seq = 0;

    mt.p = 0;
    mt.num = 0;
    mt.seq = 0;
    for (int i = 0; i < n; i++) {
        mt = Index(supply[i], accept, 0);
        if (mt.num > m.num) {
            m.p = mt.p;
            m.num = mt.num;
            m.seq = i + 1;
        }if (m.num == (int)accept.length()) {
            break;
        }
    }
    if (m.num == 0) {
        printf("0 0 0.00%%");
    }
    else if (m.num == (int)accept.length()) {
        printf("%d %d 100.00%%", m.seq, m.p + 1);
    }
    else {
        printf("%d %d %.2f%%", m.seq, m.p + 1, 100.0 * m.num / accept.length());
    }
    
    return 0;
}
