#include <iostream>
using namespace std;

const int MAX_N = 10000; // 最大的木头段数

// 最小堆结构，用于维护木头段的长度
class MinHeap {
private:
    int heap[MAX_N]; // 数组表示的堆
    int size;        // 堆中的元素数量

public:
    // 构造函数，初始化堆大小为0
    MinHeap() : size(0) {}

    // 插入一个新元素到最小堆中
    void insert(int value) {
        heap[size++] = value; // 将新元素放到堆的末尾
        int i = size - 1;
        // 上浮操作，保持最小堆的性质
        while (i > 0 && heap[(i - 1) / 2] > heap[i]) {
            swap(heap[i], heap[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
    }

    // 取出堆中最小的元素
    int extractMin() {
        if (size == 0) return 0; // 堆为空时返回0
        int minVal = heap[0]; // 根节点即为最小值
        heap[0] = heap[--size]; // 将最后一个元素移到根节点位置
        heapify(0); // 调整堆以恢复最小堆性质
        return minVal;
    }

    // 获取堆中元素的数量
    int getSize() const {
        return size;
    }

private:
    // 下沉操作，从索引i开始调整堆以保持最小堆性质
    void heapify(int i) {
        int smallest = i;
        int left = 2 * i + 1;  // 左子节点索引
        int right = 2 * i + 2; // 右子节点索引

        // 找出当前节点与其子节点中的最小值
        if (left < size && heap[left] < heap[smallest])
            smallest = left;

        if (right < size && heap[right] < heap[smallest])
            smallest = right;

        // 如果最小值不是当前节点，交换并递归调用
        if (smallest != i) {
            swap(heap[i], heap[smallest]);
            heapify(smallest);
        }
    }
};

int main() {
    int N; 
    cout << "请输入要将木头锯成的块数："; 
    cin >> N;

    MinHeap minHeap; // 创建最小堆，用于存储每块木头的长度
    int length;
    
    cout << "请依次输入每块木头的长度：";
    for (int i = 0; i < N; i++) {
        cin >> length;
        minHeap.insert(length);
    }

    int totalCost = 0; // 记录总花费

    // 每次合并两个最小长度的木头段，直到只剩下一段
    while (minHeap.getSize() > 1) {
        int first = minHeap.extractMin();  // 取出最短的木头段
        int second = minHeap.extractMin(); // 取出次短的木头段
        int cost = first + second;         // 合并后的花费为这两段的总长度
        totalCost += cost;                 // 累加花费
        minHeap.insert(cost);              // 将合并后的木头段长度重新插入堆中
    }
    
    cout << "将木头锯成" << N << "块的最小花费为：" << totalCost << endl;
    return 0;
}
