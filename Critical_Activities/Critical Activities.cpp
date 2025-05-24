#include <iostream>
using namespace std;

// 定义任务结构体，包含开始节点、结束节点、时间及输入顺序
struct Task {
    int start;
    int end;
    int time;
    int order; // 输入顺序
};

// 定义边结构体，表示图的边，包含结束节点、时间及下一个边
struct Edge {
    int end;
    int time;
    Edge* next;
};

// 定义关键活动结构体，包含开始节点、结束节点及输入顺序
struct CriticalTask {
    int start;
    int end;
    int order;
};

// 定义队列结构体，用于拓扑排序
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
    cout << "请输入节点数N和任务数M: ";
    cin >> N >> M;
    Task tasks[M];
    cout << "请输入每个任务的开始节点、结束节点和时间:" << endl;
    for(int i = 0; i < M; i++) {
        cin >> tasks[i].start >> tasks[i].end >> tasks[i].time;
        tasks[i].order = i; // 记录输入顺序
    }
    
    // 构建邻接表
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
    
    // 拓扑排序
    Queue q;
    q.init();
    int early_finish[N+1] = {0};
    int early_start[N+1] = {0};
    int topo_order[100];
    int topo_cnt = 0;
    
    // 找到所有入度为0的节点，作为开始节点
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
        cout << "调度不可行" << endl;
        cout << 0 << endl;
        return 0;
    }
    
    // 计算最早完成时间和最早开始时间
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
    
    // 找到汇点（拓扑排序的最后一个节点）
    int sink = topo_order[topo_cnt - 1];
    
    // 计算最晚完成时间和最晚开始时间
    int late_finish[N+1];
    int late_start[N+1];
    for(int i = 1; i <= N; i++) {
        late_finish[i] = early_finish[sink];
        late_start[i] = early_finish[sink];
    }
    late_finish[sink] = early_finish[sink];
    late_start[sink] = late_finish[sink];
    
    // 逆拓扑顺序遍历，更新最晚完成时间和最晚开始时间
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
    
    // 找出关键活动
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
    
    // 按开始节点升序，结束节点降序排序关键活动
    for(int i = 0; i < crit_cnt - 1; i++) {
        for(int j = i + 1; j < crit_cnt; j++) {
            if(critical_tasks[i].start > critical_tasks[j].start ||
               (critical_tasks[i].start == critical_tasks[j].start && 
                critical_tasks[i].end < critical_tasks[j].end)) {
                // 交换
                CriticalTask temp = critical_tasks[i];
                critical_tasks[i] = critical_tasks[j];
                critical_tasks[j] = temp;
            }
        }
    }
    
    // 输出完成时间
    int finish_time = late_finish[sink];
    cout << "完成整个项目所需的时间为: " << endl;
	cout << finish_time << endl;
    
    // 输出关键活动
    cout << "所有的关键活动为:" << endl;
    for(int i = 0; i < crit_cnt; i++) {
        cout << critical_tasks[i].start << "->" << critical_tasks[i].end << endl;
    }
    
    return 0;
}
