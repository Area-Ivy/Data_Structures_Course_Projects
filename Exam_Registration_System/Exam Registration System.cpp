#include <iostream>
#include <iomanip>
using namespace std;

// ����ѧ����Ϣ�ṹ��
struct Student {
    char id[20];        // ѧ����׼��֤��
    char name[50];      // ѧ��������
    char gender[10];    // ѧ�����Ա�
    int age;            // ѧ��������
    char category[50];  // ѧ���ı������
    Student* next;      // ָ����һ��ѧ���ڵ��ָ�루��������

    // ���캯�������ڳ�ʼ��ѧ����Ϣ
    Student(const char* id, const char* name, const char* gender, int age, const char* category) {
        int i = 0;
        while (id[i] != '\0') {
            this->id[i] = id[i];
            i++;
        }
        this->id[i] = '\0';  // ������

        i = 0;
        while (name[i] != '\0') {
            this->name[i] = name[i];
            i++;
        }
        this->name[i] = '\0';  // ������

        i = 0;
        while (gender[i] != '\0') {
            this->gender[i] = gender[i];
            i++;
        }
        this->gender[i] = '\0';  // ������

        this->age = age;

        i = 0;
        while (category[i] != '\0') {
            this->category[i] = category[i];
            i++;
        }
        this->category[i] = '\0';  // ������

        next = nullptr;
    }
};

// ����ѧ��������
class StudentManager {
private:
    Student* head;

public:
    // ���캯������ʼ������Ϊ��
    StudentManager() : head(nullptr) {}

    // �����������ͷ�������ڴ�
    ~StudentManager() {
        Student* current = head;
        while (current != nullptr) {
            Student* toDelete = current;
            current = current->next;
            delete toDelete;
        }
    }

    // ���ѧ��������β��
    void addStudent(const char* id, const char* name, const char* gender, int age, const char* category) {
        Student* newStudent = new Student(id, name, gender, age, category);
        
        if (head == nullptr) {
            head = newStudent;
        } else {
            Student* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newStudent;
        }
    }

    // ��ʾ����ѧ������Ϣ
    void displayStudents() const {
        if (!head) {
            cout << "û��ѧ����Ϣ����ʾ��" << endl;
            return;
        }
        cout << "����      ����      �Ա�      ����      ������� " << endl; 
        Student* temp = head;
        while (temp != nullptr) {
            cout << setiosflags(ios::left);
            cout << setw(10) << temp->id << setw(10) << temp->name << setw(10) << temp->gender
                 << setw(10) << temp->age << setw(10) << temp->category << endl;
            temp = temp->next;
        }
    }

    // �Ƚ������ַ����Ƿ����
    static int compareStrings(const char* str1, const char* str2) {
        int i = 0;
        while (str1[i] != '\0' && str2[i] != '\0') {
            if (str1[i] != str2[i]) {
                return 1;
            }
            i++;
        }
        return str1[i] == str2[i] ? 0 : 1;
    }

    // �޸�ָ������ѧ������Ϣ
    void modifyStudentInfo(const char* id) {
        Student* temp = head;
        while (temp != nullptr) {
            if (compareStrings(temp->id, id) == 0) {
                cout << "�����뿼��Ϊ " << id << " ��ѧ��������Ϣ��" << endl;
                cout << "����������Ŀ������������Ա����估�������" << endl;
                cin >> temp->name >> temp->gender >> temp->age >> temp->category;
                return;
            }
            temp = temp->next;
        }
        cout << "δ�ҵ���ѧ����" << endl;
    }

    // ɾ��ָ�����ŵ�ѧ��
    void deleteStudent(const char* id) {
        if (head == nullptr) {
            cout << "û��ѧ����Ϣ��ɾ����" << endl;
            return;
        }

        if (compareStrings(head->id, id) == 0) {
            Student* temp = head;
            head = head->next;
            delete temp;
            return;
        }

        Student* temp = head;
        while (temp->next != nullptr && compareStrings(temp->next->id, id) != 0) {
            temp = temp->next;
        }

        if (temp->next != nullptr) {
            Student* toDelete = temp->next;
            temp->next = temp->next->next;
            delete toDelete;
        } else {
            cout << "δ�ҵ���ѧ����" << endl;
        }
    }

    // ���Ҳ���ʾָ�����ŵ�ѧ����Ϣ
    void searchStudent(const char* id) const {
        Student* temp = head;
        while (temp != nullptr) {
            if (compareStrings(temp->id, id) == 0) {
                cout << setiosflags(ios::left);
                cout << setw(10) << temp->id << setw(10) << temp->name << setw(10) << temp->gender
                     << setw(10) << temp->age << setw(10) << temp->category << endl;
                return;
            }
            temp = temp->next;
        }
        cout << "δ�ҵ���ѧ����" << endl;
    }

    // ��ָ��λ�ò���ѧ����Ϣ
    void insertStudentAtPosition(int position, const char* id, const char* name, const char* gender, int age, const char* category) {
        if (position < 1) {
            cout << "����λ����Ч!" << endl;
            return;
        }

        Student* newStudent = new Student(id, name, gender, age, category);

        if (position == 1) {
            newStudent->next = head;
            head = newStudent;
            return;
        }

        Student* temp = head;
        int currentPosition = 1;
        while (temp != nullptr && currentPosition < position - 1) {
            temp = temp->next;
            currentPosition++;
        }

        if (temp == nullptr) {
            cout << "λ�ó���������Χ��" << endl;
            delete newStudent;
        } else {
            newStudent->next = temp->next;
            temp->next = newStudent;
        }
    }
};

// ���������ṩ�û�����
int main() {
    StudentManager manager;
    int n;
    cout << "�����뽨��������Ϣϵͳ" << endl;
    cout << "�����뿼��������";
    cin >> n;
    cout << "����������Ҫ����Ŀ����Ŀ��ţ��������Ա����估�������" << endl;     
    for (int i = 0; i < n; i++) {
        char id[20], name[50], gender[10], category[50];
        int age;
        cin >> id >> name >> gender >> age >> category;
        manager.addStudent(id, name, gender, age, category);
    }  
    cout << endl;
    manager.displayStudents();
    cout << "��ѡ����Ҫ���еĲ�����1Ϊ���룬2Ϊɾ����3Ϊ���ң�4Ϊ�޸ģ�5Ϊͳ�ƣ�0Ϊȡ��������" << endl;
    cout << endl;
    
    int choice;
    while (true) {
        cout << "��ѡ����Ҫ���еĲ���: ";
        cin >> choice;

        switch (choice) {
            case 1: {  // ����ѧ����Ϣ
                int position;
                char id[20], name[50], gender[10], category[50];
                int age;
                cout << "��������Ҫ����Ŀ�����λ��: ";
                cin >> position;
                cout << "����������Ҫ����Ŀ����Ŀ��ţ��������Ա����估�������" << endl;
                cin >> id >> name >> gender >> age >> category;
                manager.insertStudentAtPosition(position, id, name, gender, age, category);
                cout << endl; 
				manager.displayStudents();
                break;
            }
            case 2: {  // ɾ��ѧ����Ϣ
                char id[20];
                cout << "������Ҫɾ����ѧ��׼��֤��: ";
                cin >> id;
                cout << "��ɾ���Ŀ�����Ϣ�ǣ�";
                manager.searchStudent(id);
                manager.deleteStudent(id);
                cout << endl; 
                manager.displayStudents();
                break;
            }
            case 3: {  // ����ѧ����Ϣ
                char id[20];
                cout << "������Ҫ���ҵ�ѧ���Ŀ���: ";
                cin >> id;
                cout << endl; 
				manager.searchStudent(id);
				cout << endl; 
                manager.displayStudents();
                break;
            }
            case 4: {  // �޸�ѧ����Ϣ
                char id[20];
                cout << "������Ҫ�޸ĵ�ѧ��׼��֤��: ";
                cin >> id;
                manager.modifyStudentInfo(id);
                cout << endl; 
				manager.displayStudents();
                break;
            }
            case 5: {  // ��ʾѧ����Ϣ
                cout << endl; 
				manager.displayStudents();
                break;
            }
            case 0:  // �˳�ϵͳ
                cout << "�˳�ϵͳ" << endl;
                return 0;
            default:
                cout << "��Чѡ������������" << endl;
        }
    }

    return 0;
}

/*
1 stu1 Ů 20 ������ʦ
2 stu2 �� 21 �������ʦ
3 stu3 �� 20 ������ʦ

4 stu4 Ů 21 �������ʦ


*/
