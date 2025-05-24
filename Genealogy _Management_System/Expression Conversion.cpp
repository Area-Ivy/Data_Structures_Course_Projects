#include <iostream>
#include <cstring>
using namespace std;

bool flag; 

// �����Ա�ṹ��
struct FamilyMember {
    char name[20];               // ��Ա����
    FamilyMember* parent;         // ָ�򸸽ڵ��ָ��
    FamilyMember* firstChild;     // ָ���һ���ӽڵ��ָ��
    FamilyMember* nextSibling;    // ָ����һ���ֵܽڵ��ָ��

    // ���캯�������ڳ�ʼ����Ա��Ϣ
    FamilyMember(const char* memberName) {
        strcpy(name, memberName); // ���ƴ�������ֵ�name
        parent = nullptr;
        firstChild = nullptr;
        nextSibling = nullptr;
    }
};

// �������࣬��������Ա����ӡ�ɾ�����޸�
class FamilyTree {
private:
    FamilyMember* root; // ָ����׵ĸ��ڵ㣨���ȣ�

public:
    // ���캯������ʼ�����ڵ�Ϊ��
    FamilyTree() {
        root = nullptr;
    }

    // ��������ĸ��ڵ㣨���ȣ�
    void createFamily(const char* ancestorName) {
        if (root == nullptr) { // ������ڵ㲻���ڣ������µ����Ƚڵ�
            root = new FamilyMember(ancestorName);
            cout << "�˼��׵�������" << ancestorName; 
        } else {
            cout << "�����Ѵ���!" << endl;
        }
    }

    // ����ָ�������ĳ�Ա�ڵ�
    FamilyMember* findMember(FamilyMember* node, const char* memberName) {
        if (node == nullptr) return nullptr; // ����ڵ�Ϊ�գ�����nullptr
        if (strcmp(node->name, memberName) == 0) return node; // ����ҵ�ƥ��Ľڵ㣬���ظýڵ�

        // �ݹ���ҵ�һ���ӽڵ���ֵܽڵ�
        FamilyMember* found = findMember(node->firstChild, memberName);
        if (found) return found;
        return findMember(node->nextSibling, memberName);
    }

    // ��ָ����Ա������ӽڵ�
    void addMember(const char* parentName, const char* childName) {
        // ����ָ���ĸ��ڵ�
        FamilyMember* parentNode = findMember(root, parentName);
        if (parentNode == nullptr) { // ���ڵ㲻���ڵ����
            cout << "δ�ҵ�ָ���ĸ��ڵ�: " << parentName;
            flag = 1;
            return;
        }

        // �����µ��ӽڵ㲢���ø��ڵ�ָ��
        FamilyMember* newChild = new FamilyMember(childName);
        newChild->parent = parentNode;

        // �����ӽڵ����Ϊ���ڵ�ĵ�һ���ӽڵ���ֵܽڵ�
        if (parentNode->firstChild == nullptr) {
            parentNode->firstChild = newChild; // ���û���ӽڵ㣬ֱ�����Ϊ��һ���ӽڵ�
        } else {
            FamilyMember* sibling = parentNode->firstChild;
            while (sibling->nextSibling != nullptr) { // ���������һ���ֵܽڵ�
                sibling = sibling->nextSibling;
            }
            sibling->nextSibling = newChild; // ���Ϊ���һ���ֵܽڵ�
        }
        
    }

     // ɾ��ָ����Ա��ȫ���ӽڵ�
    void deleteChildren(const char* parentName) {
        // ���Ҹ��ڵ�
        FamilyMember* parentNode = findMember(root, parentName);
        if (parentNode == nullptr) { // ����Ҳ������ڵ�
            cout << "δ�ҵ�ָ���ĸ��ڵ�: " << parentName;
            return;
        }
        
        displayChildren(parentName);
        
        if (parentNode->firstChild == nullptr) { // ������ڵ�û���ӽڵ�
			return;
        }
        
        // �ݹ�ɾ���ӽڵ�����
        deleteSubTree(parentNode->firstChild);

        // �����ڵ�ĵ�һ���ӽڵ�ָ���ÿ�
        parentNode->firstChild = nullptr;
    }

    // ���ĳ�Ա����
    void modifyMemberName(const char* oldName, const char* newName) {
        // ������Ҫ���������ĳ�Ա
        FamilyMember* member = findMember(root, oldName);
        if (member) {
            strcpy(member->name, newName); // ���³�Ա������
            cout<< oldName <<"�Ѹ���Ϊ"<<newName;
        } else {
            cout << "δ�ҵ���Ա: " << oldName;
        }
    }

    void displayChildren(const char* parentName) {
        // ���Ҹ��ڵ�
    	FamilyMember* parentNode = findMember(root, parentName);
    	if (parentNode == nullptr) {
    	    cout << "δ�ҵ�ָ���ĸ��ڵ�: " << parentName;
    	    return;
    	}

    	// ���ø��ڵ��Ƿ����ӽڵ�
    	if (parentNode->firstChild == nullptr) {
        	cout << parentName << " û����Ů��";
        	return;
    	}

    	// ��������������ӽڵ�
    	cout << parentName << "�ĵ�һ��������: ";
    	FamilyMember* child = parentNode->firstChild;
    	while (child != nullptr) {
    	    cout << child->name << " "; // ����ӽڵ������
    	    child = child->nextSibling; // �ƶ�����һ���ֵܽڵ�
    	}
	}
	
    // �ݹ�ɾ������
    void deleteSubTree(FamilyMember* node) {
        if (node == nullptr) return;

        deleteSubTree(node->firstChild); // ɾ�������ӽڵ�
        deleteSubTree(node->nextSibling); // ɾ�������ֵܽڵ�

        delete node; // ɾ����ǰ�ڵ�
    }
};

int main() {
    FamilyTree family;

    char choice;
    char name[20], parentName[20];
    int childNum;
    
    cout << "**                ���׹���ϵͳ                 **" << endl;
    cout << "=================================================" << endl;
    cout << "**           ��ѡ��Ҫִ�еĲ��� :              **" << endl;
    cout << "**             A --- ���Ƽ���                  **" << endl;
    cout << "**             B --- ��Ӽ����Ա              **" << endl;
    cout << "**             C --- ��ɢ�ֲ���ͥ              **" << endl;
    cout << "**             D --- ���ļ�ͥ��Ա����          **" << endl;
    cout << "**             E --- �˳�����                  **" << endl;
    cout << "=================================================" << endl;
    
    cout << "���Ƚ���һ������!" << endl;
	cout << "���������ȵ�����: ";
    cin >> name;
    family.createFamily(name);
    
    while (true) {
    	cout << endl; 
    	cout << endl;
        cout << "��ѡ��Ҫִ�еĲ���:";
		cin >> choice;
        
        switch (choice) {
            case 'A':
                cout << "������Ҫ������ͥ���˵�����: ";
                cin >> parentName;
                cout << "������" << parentName << "�Ķ�Ů������"; 
                cin >> childNum;
                cout << "����������" << parentName << "�Ķ�Ů��������";
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
                cout << "������Ҫ��Ӷ��ӣ���Ů�������˵�����: ";
                cin >> parentName;
                cout << "������" << parentName << "����ӵĶ��ӣ���Ů����������: ";
				cin >> name;
				flag = 0;
				family.addMember(parentName, name);
				if(!flag) 
				family.displayChildren(parentName);
                break;
            case 'C':
                cout << "������Ҫ��ɢ��ͥ���˵�����: ";
                cin >> name;
                cout << "Ҫ��ɢ��ͥ������: " << name << endl;
                family.deleteChildren(name);
                break;
            case 'D':
                cout << "������Ҫ�����������˵�Ŀǰ����: ";
                cin >> name;
                cout << "��������ĺ������: ";
                char newName[20];
                cin >> newName;
                family.modifyMemberName(name, newName);
                break;
            case 'E':
                cout << "�˳�����" << endl;
                return 0;
            default:
                cout << "��Чѡ�����������롣" << endl;
        }
        cin.clear();
        cin.ignore(INT_MAX, '\n');
    }

    return 0;
}
