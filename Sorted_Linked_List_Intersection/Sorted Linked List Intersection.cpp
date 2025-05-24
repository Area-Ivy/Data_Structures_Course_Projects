#include <iostream>
using namespace std;

// 链表节点结构
struct Node {
    int data;        // 数据域，存储节点的值
    Node* next;      // 指针域，指向下一个节点
    Node(int val) : data(val), next(nullptr) {} // 构造函数，初始化节点
};

// 链表类
class LinkedList {
private:
    Node* head; // 指向链表头部的指针
public:
    
    // 构造函数，初始化链表为空
    LinkedList() : head(nullptr) {}

    // 插入节点到链表尾部
    void insert(int val) {
        Node* newNode = new Node(val); // 创建新节点
        if (!head) { // 如果链表为空，新节点作为头节点
            head = newNode;
        } else { // 否则找到链表尾部，将新节点连接到尾部
            Node* temp = head;
            while (temp->next) { // 遍历到最后一个节点
                temp = temp->next;
            }
            temp->next = newNode; // 新节点成为尾节点
        }
    }

    // 打印链表
    void print() {
        if (!head) { // 如果链表为空，打印NULL
            cout << "NULL" << endl;
            return;
        }
        Node* temp = head; // 从头节点开始遍历
        while (temp) { // 遍历链表直到尾节点
            cout << temp->data << " "; // 打印当前节点数据
            temp = temp->next; // 移动到下一个节点
        }
        cout << endl;
    }

    // 静态函数：计算两个有序链表的交集，返回交集链表
    static LinkedList* intersection(LinkedList* list1, LinkedList* list2) {
        LinkedList* result = new LinkedList(); // 用于存储交集的链表
        Node* p1 = list1->head; // 指向第一个链表的头节点
        Node* p2 = list2->head; // 指向第二个链表的头节点

        // 遍历两个链表，找到相同的节点值
        while (p1 && p2) {
            if (p1->data < p2->data) { // 如果p1的值小，移动p1
                p1 = p1->next;
            } else if (p1->data > p2->data) { // 如果p2的值小，移动p2
                p2 = p2->next;
            } else { // 如果p1和p2的值相等，加入交集链表
                result->insert(p1->data);
                p1 = p1->next; // 同时移动p1和p2
                p2 = p2->next;
            }
        }
        return result; // 返回交集链表
    }
};

// 从标准输入读取链表，直到输入-1结束
LinkedList* readList() {
    LinkedList* list = new LinkedList(); // 创建一个新的链表
    int value;
    while (cin >> value && value != -1) { // 输入-1时结束
        list->insert(value); // 将值插入链表
    }
    return list; // 返回创建的链表
}

// 主函数
int main() {
    cout << "请输入第一个非降序序列，以-1结束：" << endl;
    LinkedList* list1 = readList(); // 输入第一个链表

    cout << "请输入第二个非降序序列，以-1结束：" << endl;
    LinkedList* list2 = readList(); // 输入第二个链表

    // 计算两个链表的交集
    LinkedList* intersectionList = LinkedList::intersection(list1, list2);
    cout << "两个序列的交集为：" << endl;
    intersectionList->print(); // 打印交集链表

    // 释放内存，防止内存泄漏
    delete list1;
    delete list2;
    delete intersectionList;

    return 0;
}
