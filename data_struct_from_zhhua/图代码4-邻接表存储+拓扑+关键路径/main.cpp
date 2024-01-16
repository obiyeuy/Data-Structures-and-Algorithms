#include "ALGraph.h"
#include <iostream>
using namespace std;
int main(){
	ALGraph G;
	ALGraph InverseG;
	CreateGraph(G);//邻接表方式建图或网的
	if(G.kind==DG||G.kind==DN)//建立G的逆邻接表InverseG
		CreateInverseGraph(InverseG,G);
	cout<<"邻接表为G\n";
	Output(G);
	if(G.kind==DG||G.kind==DN){//输出逆邻接表,拓扑排序
		cout<<"逆邻接表为InverseG\n";
		Output(InverseG);

		printf("\n拓扑排序的结果为\n");
		if(TopologicalSort(G)==0){
			printf("\n有回路不符合要求，拓扑排序针对的是有向无环图或网\n");		
		}
		if(G.kind==DN){
			printf("\n有向网的关键路径为：\n");
			CriticalPath(G);
		}
	}
	return 0;
}