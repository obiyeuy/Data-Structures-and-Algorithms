/*creatgraph-ADJLIST.CPP  邻接表建图 */
#include <iostream>
using namespace std;
#define N 100
typedef struct edgenode
{
    int vnum;
    struct edgenode *next;
    int w;
} edgenode;
typedef struct vnode
{
    char v;
    edgenode *first;
} vnode;
typedef struct
{
    vnode VLIST[N];
    int n,m;
    int kind;
} GraphADj;

bool CreatADJG(GraphADj &g)
{
    cout <<"input num of V:";
    cin >>g.n;
    cout <<"input every V of g by char "<<endl;
    for(int i=1; i<=g.n; i++)
    {
        cin >>g.VLIST[i].v;
        g.VLIST[i].first=NULL;
    }

    cout <<"input every edge g"<<endl;
    for(int i=1; i<=g.n; i++)
    {
        cout <<"input every adjnode of "<<g.VLIST[i].v<<"  by int,finish with 0"<<endl;

        for(int flag=1; flag;)
        {
            edgenode *edge=new edgenode;
            cin >>edge->vnum;
            flag=edge->vnum;//输入0时候结束
            if(flag)
            {
                edge->w=1;
                edge->next=g.VLIST[i].first;
                g.VLIST[i].first=edge;
            }
            else delete edge;

        }

    }
    return 1;
}
bool OuptGraph(GraphADj g)
{
    cout << "the ADJLIST of g is"<<endl;
    for(int i=1; i<=g.n; i++)
    {
        cout<<g.VLIST[i].v;
        edgenode *etemp=g.VLIST[i].first;
        while(etemp)
        {
            cout<< "->(" << etemp->vnum  <<","<<etemp->w<<")";
            etemp=etemp->next;
        }
        cout<<endl;
    }
    return 1;
}
int main()
{
    GraphADj g;
    CreatADJG(g);
    OuptGraph(g);
    return 0;
}
