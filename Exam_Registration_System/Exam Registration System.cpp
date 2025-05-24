#include <iostream>
#include <iomanip>
using namespace std;

// 定义学生信息结构体
struct Student {
    char id[20];        // 学生的准考证号
    char name[50];      // 学生的姓名
    char gender[10];    // 学生的性别
    int age;            // 学生的年龄
    char category[50];  // 学生的报考类别
    Student* next;      // 指向下一个学生节点的指针（用于链表）

    // 构造函数，用于初始化学生信息
    Student(const char* id, const char* name, const char* gender, int age, const char* category) {
        int i = 0;
        while (id[i] != '\0') {
            this->id[i] = id[i];
            i++;
        }
        this->id[i] = '\0';  // 结束符

        i = 0;
        while (name[i] != '\0') {
            this->name[i] = name[i];
            i++;
        }
        this->name[i] = '\0';  // 结束符

        i = 0;
        while (gender[i] != '\0') {
            this->gender[i] = gender[i];
            i++;
        }
        this->gender[i] = '\0';  // 结束符

        this->age = age;

        i = 0;
        while (category[i] != '\0') {
            this->category[i] = category[i];
            i++;
        }
        this->category[i] = '\0';  // 结束符

        next = nullptr;
    }
};

// 创建学生管理类
class StudentManager {
private:
    Student* head;

public:
    // 构造函数，初始化链表为空
    StudentManager() : head(nullptr) {}

    // 析构函数，释放链表的内存
    ~StudentManager() {
        Student* current = head;
        while (current != nullptr) {
            Student* toDelete = current;
            current = current->next;
            delete toDelete;
        }
    }

    // 添加学生到链表尾部
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

    // 显示所有学生的信息
    void displayStudents() const {
        if (!head) {
            cout << "没有学生信息可显示。" << endl;
            return;
        }
        cout << "考号      姓名      性别      年龄      报考类别 " << endl; 
        Student* temp = head;
        while (temp != nullptr) {
            cout << setiosflags(ios::left);
            cout << setw(10) << temp->id << setw(10) << temp->name << setw(10) << temp->gender
                 << setw(10) << temp->age << setw(10) << temp->category << endl;
            temp = temp->next;
        }
    }

    // 比较两个字符串是否相等
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

    // 修改指定考号学生的信息
    void modifyStudentInfo(const char* id) {
        Student* temp = head;
        while (temp != nullptr) {
            if (compareStrings(temp->id, id) == 0) {
                cout << "请输入考号为 " << id << " 的学生的新信息：" << endl;
                cout << "请依次输入的考生的姓名，性别，年龄及报考类别！" << endl;
                cin >> temp->name >> temp->gender >> temp->age >> temp->category;
                return;
            }
            temp = temp->next;
        }
        cout << "未找到该学生！" << endl;
    }

    // 删除指定考号的学生
    void deleteStudent(const char* id) {
        if (head == nullptr) {
            cout << "没有学生信息可删除。" << endl;
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
            cout << "未找到该学生！" << endl;
        }
    }

    // 查找并显示指定考号的学生信息
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
        cout << "未找到该学生！" << endl;
    }

    // 在指定位置插入学生信息
    void insertStudentAtPosition(int position, const char* id, const char* name, const char* gender, int age, const char* category) {
        if (position < 1) {
            cout << "插入位置无效!" << endl;
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
            cout << "位置超出了链表范围！" << endl;
            delete newStudent;
        } else {
            newStudent->next = temp->next;
            temp->next = newStudent;
        }
    }
};

// 主函数，提供用户交互
int main() {
    StudentManager manager;
    int n;
    cout << "首先请建立考生信息系统" << endl;
    cout << "请输入考生人数：";
    cin >> n;
    cout << "请依次输入要插入的考生的考号，姓名，性别，年龄及报考类别！" << endl;     
    for (int i = 0; i < n; i++) {
        char id[20], name[50], gender[10], category[50];
        int age;
        cin >> id >> name >> gender >> age >> category;
        manager.addStudent(id, name, gender, age, category);
    }  
    cout << endl;
    manager.displayStudents();
    cout << "请选择您要进行的操作（1为插入，2为删除，3为查找，4为修改，5为统计，0为取消操作）" << endl;
    cout << endl;
    
    int choice;
    while (true) {
        cout << "请选择您要进行的操作: ";
        cin >> choice;

        switch (choice) {
            case 1: {  // 插入学生信息
                int position;
                char id[20], name[50], gender[10], category[50];
                int age;
                cout << "请输入你要插入的考生的位置: ";
                cin >> position;
                cout << "请依次输入要插入的考生的考号，姓名，性别，年龄及报考类别！" << endl;
                cin >> id >> name >> gender >> age >> category;
                manager.insertStudentAtPosition(position, id, name, gender, age, category);
                cout << endl; 
				manager.displayStudents();
                break;
            }
            case 2: {  // 删除学生信息
                char id[20];
                cout << "请输入要删除的学生准考证号: ";
                cin >> id;
                cout << "你删除的考生信息是：";
                manager.searchStudent(id);
                manager.deleteStudent(id);
                cout << endl; 
                manager.displayStudents();
                break;
            }
            case 3: {  // 查找学生信息
                char id[20];
                cout << "请输入要查找的学生的考号: ";
                cin >> id;
                cout << endl; 
				manager.searchStudent(id);
				cout << endl; 
                manager.displayStudents();
                break;
            }
            case 4: {  // 修改学生信息
                char id[20];
                cout << "请输入要修改的学生准考证号: ";
                cin >> id;
                manager.modifyStudentInfo(id);
                cout << endl; 
				manager.displayStudents();
                break;
            }
            case 5: {  // 显示学生信息
                cout << endl; 
				manager.displayStudents();
                break;
            }
            case 0:  // 退出系统
                cout << "退出系统" << endl;
                return 0;
            default:
                cout << "无效选择，请重新输入" << endl;
        }
    }

    return 0;
}

/*
1 stu1 女 20 软件设计师
2 stu2 男 21 软件开发师
3 stu3 男 20 软件设计师

4 stu4 女 21 软件测试师


*/
