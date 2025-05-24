#include <iostream>
using namespace std;

const int MAX_N = 10000; // ����ľͷ����

// ��С�ѽṹ������ά��ľͷ�εĳ���
class MinHeap {
private:
    int heap[MAX_N]; // �����ʾ�Ķ�
    int size;        // ���е�Ԫ������

public:
    // ���캯������ʼ���Ѵ�СΪ0
    MinHeap() : size(0) {}

    // ����һ����Ԫ�ص���С����
    void insert(int value) {
        heap[size++] = value; // ����Ԫ�طŵ��ѵ�ĩβ
        int i = size - 1;
        // �ϸ�������������С�ѵ�����
        while (i > 0 && heap[(i - 1) / 2] > heap[i]) {
            swap(heap[i], heap[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
    }

    // ȡ��������С��Ԫ��
    int extractMin() {
        if (size == 0) return 0; // ��Ϊ��ʱ����0
        int minVal = heap[0]; // ���ڵ㼴Ϊ��Сֵ
        heap[0] = heap[--size]; // �����һ��Ԫ���Ƶ����ڵ�λ��
        heapify(0); // �������Իָ���С������
        return minVal;
    }

    // ��ȡ����Ԫ�ص�����
    int getSize() const {
        return size;
    }

private:
    // �³�������������i��ʼ�������Ա�����С������
    void heapify(int i) {
        int smallest = i;
        int left = 2 * i + 1;  // ���ӽڵ�����
        int right = 2 * i + 2; // ���ӽڵ�����

        // �ҳ���ǰ�ڵ������ӽڵ��е���Сֵ
        if (left < size && heap[left] < heap[smallest])
            smallest = left;

        if (right < size && heap[right] < heap[smallest])
            smallest = right;

        // �����Сֵ���ǵ�ǰ�ڵ㣬�������ݹ����
        if (smallest != i) {
            swap(heap[i], heap[smallest]);
            heapify(smallest);
        }
    }
};

int main() {
    int N; 
    cout << "������Ҫ��ľͷ��ɵĿ�����"; 
    cin >> N;

    MinHeap minHeap; // ������С�ѣ����ڴ洢ÿ��ľͷ�ĳ���
    int length;
    
    cout << "����������ÿ��ľͷ�ĳ��ȣ�";
    for (int i = 0; i < N; i++) {
        cin >> length;
        minHeap.insert(length);
    }

    int totalCost = 0; // ��¼�ܻ���

    // ÿ�κϲ�������С���ȵ�ľͷ�Σ�ֱ��ֻʣ��һ��
    while (minHeap.getSize() > 1) {
        int first = minHeap.extractMin();  // ȡ����̵�ľͷ��
        int second = minHeap.extractMin(); // ȡ���ζ̵�ľͷ��
        int cost = first + second;         // �ϲ���Ļ���Ϊ�����ε��ܳ���
        totalCost += cost;                 // �ۼӻ���
        minHeap.insert(cost);              // ���ϲ����ľͷ�γ������²������
    }
    
    cout << "��ľͷ���" << N << "�����С����Ϊ��" << totalCost << endl;
    return 0;
}
