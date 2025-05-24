#include <iostream>
using namespace std;

class Queue {
public:
    int data[1000]; // ���ڴ洢����Ԫ��
    int front;      // ����ͷ
    int rear;       // ����β

    Queue() { front = rear = 0; } // ��ʼ������

    // �ж϶����Ƿ�Ϊ��
    bool empty() {
        return front == rear;
    }

    // ��Ӳ���
    void push(int value) {
        data[rear++] = value;
    }

    // ���Ӳ���
    int pop() {
        if (!empty()) {
            return data[front++];
        }
        return -1; // �������Ϊ�գ�����-1�����ᴥ����������
    }
};

int main() {
    int N;
    
    cout<<"������˿�����: ";
    
    cin >> N;  // ��ȡ�˿�����

    if(N>1000||N<1||cin.fail()){
    	cout<<"�������"<<endl;
    	return 0;
	}
    
    Queue A_queue, B_queue;  // �ֱ��ʾA���ں�B���ڵĶ���

    // ��ȡ�˿ͱ�ţ�������Ž���A���ڣ�ż����Ž���B����
    cout<<"������˿ͱ��: ";
    for (int i = 0; i < N; i++) {
        int customer;
        cin >> customer;
        
        if(cin.fail()){
        	cout<<"�������"<<endl;
        	return 0;
		}
		
        if (customer % 2 == 1) {
            A_queue.push(customer);  // ������Ž���A����
        } else {
            B_queue.push(customer);  // ż����Ž���B����
        }
    }
    bool first = true;  // ���ڿ��������ʽ
    cout<<"ҵ������ɵ�˳����: ";
    while (!A_queue.empty() || !B_queue.empty()) {
        // A���ڴ���2���˿�
        for (int i = 0; i < 2 && !A_queue.empty(); i++) {
            if (!first) {
                cout << " ";  // ���ƿո�
            }
            cout << A_queue.pop();
            first = false;
        }
        // B���ڴ���1���˿�
        if (!B_queue.empty()) {
            if (!first) {
                cout << " ";  // ���ƿո�
            }
            cout << B_queue.pop();
            first = false;
        }
    }

    cout << endl;  // �����������
    return 0;
}
