#include <iostream>
#include <climits>
using namespace std;

#define MAX_N 26  // 假设小区数不超过26（a-z）

// 无穷大
const int INF = INT_MAX;
class MST{
public:
// 最小生成树的Prim算法
void prim(int n, int graph[MAX_N][MAX_N], char nodeNames[MAX_N], int startNode, int parent[MAX_N], int minEdge[MAX_N]) {
    bool inMST[MAX_N] = {false};  // 记录小区是否已经在生成树中
    // 初始化
    for (int i = 0; i < n; ++i) {
        minEdge[i] = INF;  // 设置初始边权为无穷大
        parent[i] = -1;    // 无父节点
    }
    minEdge[startNode] = 0;  // 起点的最小边为0

    // 开始扩展最小生成树
    for (int count = 0; count < n; ++count) {
        // 找到最小边的节点
        int u = -1;
        for (int v = 0; v < n; ++v) {
            if (!inMST[v] && (u == -1 || minEdge[v] < minEdge[u])) {
                u = v;
            }
        }

        // 将u节点加入到生成树中
        inMST[u] = true;

        // 更新与u相连的其他节点的最小边
        for (int v = 0; v < n; ++v) {
            if (graph[u][v] != INF && !inMST[v] && graph[u][v] < minEdge[v]) {
                minEdge[v] = graph[u][v];
                parent[v] = u;
            }
        }
    }
}

// 输出最小生成树的过程
void printMST(int n, int parent[MAX_N], int minEdge[MAX_N], char nodeNames[MAX_N]) {
    int totalCost = 0;
    cout << "最小生成树的顶点及边为: "<<endl;
    cout << endl;

    for (int u = 0; u < n; ++u) {
        if (parent[u] != -1) {
            cout << nodeNames[parent[u]] << "-(" << minEdge[u] << ")->" << nodeNames[u] << endl;
        }
    }
}

};

MST m;

int main() {
	
	cout << "**             电网造价模拟系统                **" << endl;
    cout << "=================================================" << endl;
    cout << "**             A --- 创建电网顶点              **" << endl;
    cout << "**             B --- 添加电网的边              **" << endl;
    cout << "**             C --- 构造最小生成树            **" << endl;
    cout << "**             D --- 显示最小生成树            **" << endl;
    cout << "**             E --- 退出程序                  **" << endl;
    cout << "=================================================" << endl;
	
	char command;
	int n;
	char nodeNames[MAX_N];
	int nodeNum[MAX_N]; 
	int graph[MAX_N][MAX_N];
	char u_char, v_char;
    int cost;
    int u,v;
	char start;        
    int startNode; 
	   
    int parent[MAX_N]; // 存储最小生成树的父节点
    int minEdge[MAX_N];// 存储最小生成树的最小边权 
	
	
	while(true){
		
		cout<<endl;
		cout<<"请选择操作 : ";
		cin>>command;
		
		if(command=='A'){
			cout<<"请输入顶点的个数(不超过26个): ";
			cin>>n;
			cout<<"请依次输入各顶点的名称(用单个小写字母表示): "<<endl;
			for (int i = 0; i < n; i++) {
                cin >> nodeNames[i];
                nodeNum[nodeNames[i]-'a'] = i;
            }
            
            // 初始化图
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (i != j) {
                        graph[i][j] = INF;  // 无连接的边权为无穷大
                    } else {
                        graph[i][j] = 0;  // 自己到自己的边权为0
                   }
                }
            }
		}
		
		else if(command=='B'){
			while(true){	
				cout<<"请输入两个顶点及边(以 ? ? 0 代表结束输入): "; 
                cin >> u_char >> v_char >> cost;
                
                if(u_char=='?'&&v_char=='?'){
                	break;
				}
                // 将小区名转为编号
                u = nodeNum[u_char - 'a'];
                v = nodeNum[v_char - 'a'];

                // 无向图，设置两条边
                graph[u][v] = cost;
                graph[v][u] = cost;
			}
		}
		
		else if(command=='C'){
            cout << "请输入起始顶点: ";
            cin >> start;
            startNode = nodeNum[start - 'a'];  // 将起点字符转换为编号
            
            cout << "生成Prim最小生成树!"<<endl;

            // 使用Prim算法计算最小生成树
            m.prim(n, graph, nodeNames, startNode, parent, minEdge);
		}
		
		else if(command=='D'){
		    m.printMST(n, parent, minEdge, nodeNames);	
		}
		
		else if(command=='E'){
			cout<<"press any key to continue"<<endl;
        	getchar();
        	break;	
		}
		
		else{
			cout << "无效选择!" << endl;
		}
	}
	
    return 0;
}
