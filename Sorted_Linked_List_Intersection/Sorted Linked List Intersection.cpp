#include <iostream>
using namespace std;

// ����ڵ�ṹ
struct Node {
    int data;        // �����򣬴洢�ڵ��ֵ
    Node* next;      // ָ����ָ����һ���ڵ�
    Node(int val) : data(val), next(nullptr) {} // ���캯������ʼ���ڵ�
};

// ������
class LinkedList {
private:
    Node* head; // ָ������ͷ����ָ��
public:
    
    // ���캯������ʼ������Ϊ��
    LinkedList() : head(nullptr) {}

    // ����ڵ㵽����β��
    void insert(int val) {
        Node* newNode = new Node(val); // �����½ڵ�
        if (!head) { // �������Ϊ�գ��½ڵ���Ϊͷ�ڵ�
            head = newNode;
        } else { // �����ҵ�����β�������½ڵ����ӵ�β��
            Node* temp = head;
            while (temp->next) { // ���������һ���ڵ�
                temp = temp->next;
            }
            temp->next = newNode; // �½ڵ��Ϊβ�ڵ�
        }
    }

    // ��ӡ����
    void print() {
        if (!head) { // �������Ϊ�գ���ӡNULL
            cout << "NULL" << endl;
            return;
        }
        Node* temp = head; // ��ͷ�ڵ㿪ʼ����
        while (temp) { // ��������ֱ��β�ڵ�
            cout << temp->data << " "; // ��ӡ��ǰ�ڵ�����
            temp = temp->next; // �ƶ�����һ���ڵ�
        }
        cout << endl;
    }

    // ��̬����������������������Ľ��������ؽ�������
    static LinkedList* intersection(LinkedList* list1, LinkedList* list2) {
        LinkedList* result = new LinkedList(); // ���ڴ洢����������
        Node* p1 = list1->head; // ָ���һ�������ͷ�ڵ�
        Node* p2 = list2->head; // ָ��ڶ��������ͷ�ڵ�

        // �������������ҵ���ͬ�Ľڵ�ֵ
        while (p1 && p2) {
            if (p1->data < p2->data) { // ���p1��ֵС���ƶ�p1
                p1 = p1->next;
            } else if (p1->data > p2->data) { // ���p2��ֵС���ƶ�p2
                p2 = p2->next;
            } else { // ���p1��p2��ֵ��ȣ����뽻������
                result->insert(p1->data);
                p1 = p1->next; // ͬʱ�ƶ�p1��p2
                p2 = p2->next;
            }
        }
        return result; // ���ؽ�������
    }
};

// �ӱ�׼�����ȡ����ֱ������-1����
LinkedList* readList() {
    LinkedList* list = new LinkedList(); // ����һ���µ�����
    int value;
    while (cin >> value && value != -1) { // ����-1ʱ����
        list->insert(value); // ��ֵ��������
    }
    return list; // ���ش���������
}

// ������
int main() {
    cout << "�������һ���ǽ������У���-1������" << endl;
    LinkedList* list1 = readList(); // �����һ������

    cout << "������ڶ����ǽ������У���-1������" << endl;
    LinkedList* list2 = readList(); // ����ڶ�������

    // ������������Ľ���
    LinkedList* intersectionList = LinkedList::intersection(list1, list2);
    cout << "�������еĽ���Ϊ��" << endl;
    intersectionList->print(); // ��ӡ��������

    // �ͷ��ڴ棬��ֹ�ڴ�й©
    delete list1;
    delete list2;
    delete intersectionList;

    return 0;
}
