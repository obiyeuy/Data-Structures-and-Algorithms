/*creatgraph-GM.CPP  邻接矩阵建图 */
#include <iostream>
#define N 10
using namespace std;

typedef struct
{
    char V[N];
    int VR[N][N];
    int n,m;//n表示定点数量，m代表边的数量
    int kind;//图的种类
} Graph;

bool CreatG(Graph &g)
{
    cout << "input number of V:";
    cin >> g.n;
    cout << "n=" << g.n << endl;
    cout<< "input every V value"<<endl;
    for(int i=1; i<=g.n; i++)
        cin >> g.V[i];
    cout <<"input edge of g"<<endl;
    for(int i=1; i<=g.n; i++)
        for(int j=1; j<=g.n; j++)
            cin >>g.VR[i][j];
    return 1;
}

bool OutputG(Graph g)
{
    for(int i=1; i<=g.n; i++)
        cout <<g.V[i] << "    ";
        cout << endl;
    for(int i=1; i<=g.n; i++)
    {

        for(int j=1; j<=g.n; j++)
        {
            cout <<g.VR[i][j];
        }
        cout <<endl;
    }
return 1;
}

int  main ()
{
    Graph g;
    CreatG(g);
    OutputG(g);
    return 0;

}
