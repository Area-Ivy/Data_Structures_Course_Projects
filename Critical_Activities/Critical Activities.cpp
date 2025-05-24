#include <iostream>
using namespace std;

// ��������ṹ�壬������ʼ�ڵ㡢�����ڵ㡢ʱ�估����˳��
struct Task {
    int start;
    int end;
    int time;
    int order; // ����˳��
};

// ����߽ṹ�壬��ʾͼ�ıߣ����������ڵ㡢ʱ�估��һ����
struct Edge {
    int end;
    int time;
    Edge* next;
};

// ����ؼ���ṹ�壬������ʼ�ڵ㡢�����ڵ㼰����˳��
struct CriticalTask {
    int start;
    int end;
    int order;
};

// ������нṹ�壬������������
struct Queue {
    int data[100];
    int front, rear;
    void init() { front = rear = 0; }
    bool empty() { return front == rear; }
    void enqueue(int x) { data[rear++] = x; }
    int dequeue() { return data[front++]; }
};

int main() {
    int N, M;
    cout << "������ڵ���N��������M: ";
    cin >> N >> M;
    Task tasks[M];
    cout << "������ÿ������Ŀ�ʼ�ڵ㡢�����ڵ��ʱ��:" << endl;
    for(int i = 0; i < M; i++) {
        cin >> tasks[i].start >> tasks[i].end >> tasks[i].time;
        tasks[i].order = i; // ��¼����˳��
    }
    
    // �����ڽӱ�
    Edge* adj[N+1];
    for(int i = 1; i <= N; i++) {
        adj[i] = NULL;
    }
    int indegree[N+1] = {0};
    for(int i = 0; i < M; i++) {
        Task t = tasks[i];
        Edge* e = new Edge();
        e->end = t.end;
        e->time = t.time;
        e->next = adj[t.start];
        adj[t.start] = e;
        indegree[t.end]++;
    }
    
    // ��������
    Queue q;
    q.init();
    int early_finish[N+1] = {0};
    int early_start[N+1] = {0};
    int topo_order[100];
    int topo_cnt = 0;
    
    // �ҵ��������Ϊ0�Ľڵ㣬��Ϊ��ʼ�ڵ�
    for(int i = 1; i <= N; i++) {
        if(indegree[i] == 0) {
            q.enqueue(i);
            topo_order[topo_cnt++] = i;
        }
    }
    int cnt = 0;
    while(!q.empty()) {
        int u = q.dequeue();
        cnt++;
        for(Edge* e = adj[u]; e != NULL; e = e->next) {
            int v = e->end;
            indegree[v]--;
            if(indegree[v] == 0) {
                q.enqueue(v);
                topo_order[topo_cnt++] = v;
            }
        }
    }
    if(cnt != N) {
        cout << "���Ȳ�����" << endl;
        cout << 0 << endl;
        return 0;
    }
    
    // �����������ʱ������翪ʼʱ��
    for(int i = 0; i < topo_cnt; i++) {
        int u = topo_order[i];
        for(Edge* e = adj[u]; e != NULL; e = e->next) {
            int v = e->end;
            if(early_finish[v] < early_finish[u] + e->time) {
                early_finish[v] = early_finish[u] + e->time;
                early_start[v] = early_finish[u];
            }
        }
    }
    
    // �ҵ���㣨������������һ���ڵ㣩
    int sink = topo_order[topo_cnt - 1];
    
    // �����������ʱ�������ʼʱ��
    int late_finish[N+1];
    int late_start[N+1];
    for(int i = 1; i <= N; i++) {
        late_finish[i] = early_finish[sink];
        late_start[i] = early_finish[sink];
    }
    late_finish[sink] = early_finish[sink];
    late_start[sink] = late_finish[sink];
    
    // ������˳������������������ʱ�������ʼʱ��
    for(int i = topo_cnt - 2; i >= 0; i--) {
        int u = topo_order[i];
        for(Edge* e = adj[u]; e != NULL; e = e->next) {
            int v = e->end;
            if(late_finish[u] > late_finish[v] - e->time) {
                late_finish[u] = late_finish[v] - e->time;
                late_start[u] = late_finish[u] - e->time;
            }
        }
    }
    
    // �ҳ��ؼ��
    CriticalTask critical_tasks[M];
    int crit_cnt = 0;
    for(int i = 0; i < M; i++) {
        Task t = tasks[i];
        if(early_finish[t.start] + t.time == late_finish[t.end]) {
            critical_tasks[crit_cnt].start = t.start;
            critical_tasks[crit_cnt].end = t.end;
            critical_tasks[crit_cnt].order = t.order;
            crit_cnt++;
        }
    }
    
    // ����ʼ�ڵ����򣬽����ڵ㽵������ؼ��
    for(int i = 0; i < crit_cnt - 1; i++) {
        for(int j = i + 1; j < crit_cnt; j++) {
            if(critical_tasks[i].start > critical_tasks[j].start ||
               (critical_tasks[i].start == critical_tasks[j].start && 
                critical_tasks[i].end < critical_tasks[j].end)) {
                // ����
                CriticalTask temp = critical_tasks[i];
                critical_tasks[i] = critical_tasks[j];
                critical_tasks[j] = temp;
            }
        }
    }
    
    // ������ʱ��
    int finish_time = late_finish[sink];
    cout << "���������Ŀ�����ʱ��Ϊ: " << endl;
	cout << finish_time << endl;
    
    // ����ؼ��
    cout << "���еĹؼ��Ϊ:" << endl;
    for(int i = 0; i < crit_cnt; i++) {
        cout << critical_tasks[i].start << "->" << critical_tasks[i].end << endl;
    }
    
    return 0;
}
