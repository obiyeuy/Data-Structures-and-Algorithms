#include<iostream>
#include<string>
#include<sstream>
#include<set>
#include<cstdio>
#include<iomanip>
#define MAX 100

using namespace std;
int n;
set<string>s[MAX];

void store(){
    for (int i = 1; i <= n; ++i){
        string str = "";
        while (true){
            char c = getchar();
            if (c == '#') break;
            else if (isalpha(c)){
                if (c >= 'A' && c <= 'Z')
                    c = c + 32;
                str += c;
            }
            else{
            //不是字符一个单词就结束了，要考虑是否要进入set了
                if (str.size() >= 3){
                    if (str.size() > 10)
                      str = str.substr(0, 10);  // 截取前十个
                    s[i].insert(str);
                }
                str ="";              
//不管进不进set，都必须清空，开始记录下一个单词s
            }
        }
    }
}

int main()
{
    cin >> n;   //总文件数
    scanf("\n");
    store();
    int m;    //指令数
    cin >> m;
    double ans[10] = { 0 };
    for (int i = 1; i <= m; ++i)
    {
        int a, b;
        int sa, sb;
        cin >> a >> b;
        sa = s[a].size();
        sb = s[b].size();
        set<string>::iterator ita;
        set<string>::iterator itb;
        int same = 0;
        for(ita=s[a].begin();ita!=s[a].end();
++ita){   //使用迭代器遍历set中元素
            for (itb = s[b].begin(); itb != s[b].end(); ++itb){
                if(*ita == *itb){
                    same++;
                }
            }
            ans[i] = 100.0 * same / (sa + sb - same);
        }
    }
    for (int i = 1; i <= m; ++i) {
        printf("%.1f%%\n", ans[i]);
    }
    return 0;
}
