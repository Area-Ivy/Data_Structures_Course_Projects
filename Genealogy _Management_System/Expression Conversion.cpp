#include <iostream>
#include <cstring>
using namespace std;

bool flag; 

// 家族成员结构体
struct FamilyMember {
    char name[20];               // 成员姓名
    FamilyMember* parent;         // 指向父节点的指针
    FamilyMember* firstChild;     // 指向第一个子节点的指针
    FamilyMember* nextSibling;    // 指向下一个兄弟节点的指针

    // 构造函数，用于初始化成员信息
    FamilyMember(const char* memberName) {
        strcpy(name, memberName); // 复制传入的名字到name
        parent = nullptr;
        firstChild = nullptr;
        nextSibling = nullptr;
    }
};

// 家谱树类，管理家族成员的添加、删除和修改
class FamilyTree {
private:
    FamilyMember* root; // 指向家谱的根节点（祖先）

public:
    // 构造函数，初始化根节点为空
    FamilyTree() {
        root = nullptr;
    }

    // 创建家族的根节点（祖先）
    void createFamily(const char* ancestorName) {
        if (root == nullptr) { // 如果根节点不存在，创建新的祖先节点
            root = new FamilyMember(ancestorName);
            cout << "此家谱的祖先是" << ancestorName; 
        } else {
            cout << "家族已存在!" << endl;
        }
    }

    // 查找指定姓名的成员节点
    FamilyMember* findMember(FamilyMember* node, const char* memberName) {
        if (node == nullptr) return nullptr; // 如果节点为空，返回nullptr
        if (strcmp(node->name, memberName) == 0) return node; // 如果找到匹配的节点，返回该节点

        // 递归查找第一个子节点和兄弟节点
        FamilyMember* found = findMember(node->firstChild, memberName);
        if (found) return found;
        return findMember(node->nextSibling, memberName);
    }

    // 在指定成员下添加子节点
    void addMember(const char* parentName, const char* childName) {
        // 查找指定的父节点
        FamilyMember* parentNode = findMember(root, parentName);
        if (parentNode == nullptr) { // 父节点不存在的情况
            cout << "未找到指定的父节点: " << parentName;
            flag = 1;
            return;
        }

        // 创建新的子节点并设置父节点指针
        FamilyMember* newChild = new FamilyMember(childName);
        newChild->parent = parentNode;

        // 将新子节点添加为父节点的第一个子节点或兄弟节点
        if (parentNode->firstChild == nullptr) {
            parentNode->firstChild = newChild; // 如果没有子节点，直接添加为第一个子节点
        } else {
            FamilyMember* sibling = parentNode->firstChild;
            while (sibling->nextSibling != nullptr) { // 遍历到最后一个兄弟节点
                sibling = sibling->nextSibling;
            }
            sibling->nextSibling = newChild; // 添加为最后一个兄弟节点
        }
        
    }

     // 删除指定成员的全部子节点
    void deleteChildren(const char* parentName) {
        // 查找父节点
        FamilyMember* parentNode = findMember(root, parentName);
        if (parentNode == nullptr) { // 如果找不到父节点
            cout << "未找到指定的父节点: " << parentName;
            return;
        }
        
        displayChildren(parentName);
        
        if (parentNode->firstChild == nullptr) { // 如果父节点没有子节点
			return;
        }
        
        // 递归删除子节点链表
        deleteSubTree(parentNode->firstChild);

        // 将父节点的第一个子节点指针置空
        parentNode->firstChild = nullptr;
    }

    // 更改成员姓名
    void modifyMemberName(const char* oldName, const char* newName) {
        // 查找需要更改姓名的成员
        FamilyMember* member = findMember(root, oldName);
        if (member) {
            strcpy(member->name, newName); // 更新成员的名字
            cout<< oldName <<"已更名为"<<newName;
        } else {
            cout << "未找到成员: " << oldName;
        }
    }

    void displayChildren(const char* parentName) {
        // 查找父节点
    	FamilyMember* parentNode = findMember(root, parentName);
    	if (parentNode == nullptr) {
    	    cout << "未找到指定的父节点: " << parentName;
    	    return;
    	}

    	// 检查该父节点是否有子节点
    	if (parentNode->firstChild == nullptr) {
        	cout << parentName << " 没有子女。";
        	return;
    	}

    	// 遍历并输出所有子节点
    	cout << parentName << "的第一代子孙是: ";
    	FamilyMember* child = parentNode->firstChild;
    	while (child != nullptr) {
    	    cout << child->name << " "; // 输出子节点的姓名
    	    child = child->nextSibling; // 移动到下一个兄弟节点
    	}
	}
	
    // 递归删除子树
    void deleteSubTree(FamilyMember* node) {
        if (node == nullptr) return;

        deleteSubTree(node->firstChild); // 删除所有子节点
        deleteSubTree(node->nextSibling); // 删除所有兄弟节点

        delete node; // 删除当前节点
    }
};

int main() {
    FamilyTree family;

    char choice;
    char name[20], parentName[20];
    int childNum;
    
    cout << "**                家谱管理系统                 **" << endl;
    cout << "=================================================" << endl;
    cout << "**           请选择要执行的操作 :              **" << endl;
    cout << "**             A --- 完善家谱                  **" << endl;
    cout << "**             B --- 添加家族成员              **" << endl;
    cout << "**             C --- 解散局部家庭              **" << endl;
    cout << "**             D --- 更改家庭成员姓名          **" << endl;
    cout << "**             E --- 退出程序                  **" << endl;
    cout << "=================================================" << endl;
    
    cout << "首先建立一个家谱!" << endl;
	cout << "请输入祖先的姓名: ";
    cin >> name;
    family.createFamily(name);
    
    while (true) {
    	cout << endl; 
    	cout << endl;
        cout << "请选择要执行的操作:";
		cin >> choice;
        
        switch (choice) {
            case 'A':
                cout << "请输入要建立家庭的人的姓名: ";
                cin >> parentName;
                cout << "请输入" << parentName << "的儿女人数："; 
                cin >> childNum;
                cout << "请依次输入" << parentName << "的儿女的姓名：";
                flag = 0;
				for(int i=0; i<childNum; i++){
				    cin >> name;
				    family.addMember(parentName, name);
				    if(flag == 1) break;
				} 
				if(!flag)
				family.displayChildren(parentName); 
                break;
            case 'B':
                cout << "请输入要添加儿子（或女儿）的人的姓名: ";
                cin >> parentName;
                cout << "请输入" << parentName << "新添加的儿子（或女儿）的姓名: ";
				cin >> name;
				flag = 0;
				family.addMember(parentName, name);
				if(!flag) 
				family.displayChildren(parentName);
                break;
            case 'C':
                cout << "请输入要解散家庭的人的姓名: ";
                cin >> name;
                cout << "要解散家庭的人是: " << name << endl;
                family.deleteChildren(name);
                break;
            case 'D':
                cout << "请输入要更改姓名的人的目前姓名: ";
                cin >> name;
                cout << "请输入更改后的姓名: ";
                char newName[20];
                cin >> newName;
                family.modifyMemberName(name, newName);
                break;
            case 'E':
                cout << "退出程序。" << endl;
                return 0;
            default:
                cout << "无效选择，请重新输入。" << endl;
        }
        cin.clear();
        cin.ignore(INT_MAX, '\n');
    }

    return 0;
}
