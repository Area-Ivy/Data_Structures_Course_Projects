#include <iostream>
#include <climits>
using namespace std;

#define MAX_N 26  // ����С����������26��a-z��

// �����
const int INF = INT_MAX;
class MST{
public:
// ��С��������Prim�㷨
void prim(int n, int graph[MAX_N][MAX_N], char nodeNames[MAX_N], int startNode, int parent[MAX_N], int minEdge[MAX_N]) {
    bool inMST[MAX_N] = {false};  // ��¼С���Ƿ��Ѿ�����������
    // ��ʼ��
    for (int i = 0; i < n; ++i) {
        minEdge[i] = INF;  // ���ó�ʼ��ȨΪ�����
        parent[i] = -1;    // �޸��ڵ�
    }
    minEdge[startNode] = 0;  // ������С��Ϊ0

    // ��ʼ��չ��С������
    for (int count = 0; count < n; ++count) {
        // �ҵ���С�ߵĽڵ�
        int u = -1;
        for (int v = 0; v < n; ++v) {
            if (!inMST[v] && (u == -1 || minEdge[v] < minEdge[u])) {
                u = v;
            }
        }

        // ��u�ڵ���뵽��������
        inMST[u] = true;

        // ������u�����������ڵ����С��
        for (int v = 0; v < n; ++v) {
            if (graph[u][v] != INF && !inMST[v] && graph[u][v] < minEdge[v]) {
                minEdge[v] = graph[u][v];
                parent[v] = u;
            }
        }
    }
}

// �����С�������Ĺ���
void printMST(int n, int parent[MAX_N], int minEdge[MAX_N], char nodeNames[MAX_N]) {
    int totalCost = 0;
    cout << "��С�������Ķ��㼰��Ϊ: "<<endl;
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
	
	cout << "**             �������ģ��ϵͳ                **" << endl;
    cout << "=================================================" << endl;
    cout << "**             A --- ������������              **" << endl;
    cout << "**             B --- ��ӵ����ı�              **" << endl;
    cout << "**             C --- ������С������            **" << endl;
    cout << "**             D --- ��ʾ��С������            **" << endl;
    cout << "**             E --- �˳�����                  **" << endl;
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
	   
    int parent[MAX_N]; // �洢��С�������ĸ��ڵ�
    int minEdge[MAX_N];// �洢��С����������С��Ȩ 
	
	
	while(true){
		
		cout<<endl;
		cout<<"��ѡ����� : ";
		cin>>command;
		
		if(command=='A'){
			cout<<"�����붥��ĸ���(������26��): ";
			cin>>n;
			cout<<"��������������������(�õ���Сд��ĸ��ʾ): "<<endl;
			for (int i = 0; i < n; i++) {
                cin >> nodeNames[i];
                nodeNum[nodeNames[i]-'a'] = i;
            }
            
            // ��ʼ��ͼ
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (i != j) {
                        graph[i][j] = INF;  // �����ӵı�ȨΪ�����
                    } else {
                        graph[i][j] = 0;  // �Լ����Լ��ı�ȨΪ0
                   }
                }
            }
		}
		
		else if(command=='B'){
			while(true){	
				cout<<"�������������㼰��(�� ? ? 0 �����������): "; 
                cin >> u_char >> v_char >> cost;
                
                if(u_char=='?'&&v_char=='?'){
                	break;
				}
                // ��С����תΪ���
                u = nodeNum[u_char - 'a'];
                v = nodeNum[v_char - 'a'];

                // ����ͼ������������
                graph[u][v] = cost;
                graph[v][u] = cost;
			}
		}
		
		else if(command=='C'){
            cout << "��������ʼ����: ";
            cin >> start;
            startNode = nodeNum[start - 'a'];  // ������ַ�ת��Ϊ���
            
            cout << "����Prim��С������!"<<endl;

            // ʹ��Prim�㷨������С������
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
			cout << "��Чѡ��!" << endl;
		}
	}
	
    return 0;
}
