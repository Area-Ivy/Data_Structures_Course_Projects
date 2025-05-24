#include <iostream>
using namespace std;

class Queue {
public:
    int data[1000]; // 用于存储队列元素
    int front;      // 队列头
    int rear;       // 队列尾

    Queue() { front = rear = 0; } // 初始化队列

    // 判断队列是否为空
    bool empty() {
        return front == rear;
    }

    // 入队操作
    void push(int value) {
        data[rear++] = value;
    }

    // 出队操作
    int pop() {
        if (!empty()) {
            return data[front++];
        }
        return -1; // 如果队列为空，返回-1（不会触发这个情况）
    }
};

int main() {
    int N;
    
    cout<<"请输入顾客总数: ";
    
    cin >> N;  // 读取顾客总数

    if(N>1000||N<1||cin.fail()){
    	cout<<"输入错误"<<endl;
    	return 0;
	}
    
    Queue A_queue, B_queue;  // 分别表示A窗口和B窗口的队列

    // 读取顾客编号，奇数编号进入A窗口，偶数编号进入B窗口
    cout<<"请输入顾客编号: ";
    for (int i = 0; i < N; i++) {
        int customer;
        cin >> customer;
        
        if(cin.fail()){
        	cout<<"输入错误"<<endl;
        	return 0;
		}
		
        if (customer % 2 == 1) {
            A_queue.push(customer);  // 奇数编号进入A窗口
        } else {
            B_queue.push(customer);  // 偶数编号进入B窗口
        }
    }
    bool first = true;  // 用于控制输出格式
    cout<<"业务处理完成的顺序是: ";
    while (!A_queue.empty() || !B_queue.empty()) {
        // A窗口处理2个顾客
        for (int i = 0; i < 2 && !A_queue.empty(); i++) {
            if (!first) {
                cout << " ";  // 控制空格
            }
            cout << A_queue.pop();
            first = false;
        }
        // B窗口处理1个顾客
        if (!B_queue.empty()) {
            if (!first) {
                cout << " ";  // 控制空格
            }
            cout << B_queue.pop();
            first = false;
        }
    }

    cout << endl;  // 输出结束后换行
    return 0;
}
