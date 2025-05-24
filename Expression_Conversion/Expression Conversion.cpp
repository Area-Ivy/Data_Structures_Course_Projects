#include <iostream>
#include <cctype>

// ������������ȼ��ͱ��ʽת������
class InfixToPostfixHelper {
public:
    // ��������ȼ�
    int getPriority(char op) {
        if (op == '+' || op == '-') return 1;
        if (op == '*' || op == '/') return 2;
        return 0;
    }

    // �ж��Ƿ��ǲ�����
    bool isOperator(char c) {
        return (c == '+' || c == '-' || c == '*' || c == '/');
    }

    // �ж��ַ��Ƿ������ֻ�С����
    bool isNumber(char c) {
        return (isdigit(c) || c == '.');
    }

    // �жϸ����Ƿ�����Ϊ����
    bool isNegative(char c, const char* expr, int i) {
        return (c == '-' && (i == 0 || isOperator(expr[i - 1]) || expr[i - 1] == '('));
    }

    // ����׺���ʽת��Ϊ��׺���ʽ
    void convert(const char* expr) {
        char stack[100];  // ������ջ
        int stackTop = -1; // ջ��ָ��
        char result[200];  // �洢���
        int resultIndex = 0;  // �����������

        int i = 0;
        while (expr[i] != '\0') {
            if (expr[i] == ' ') {
                i++;
                continue;  // �����ո�
            }

            if (isNumber(expr[i]) || (expr[i] == '-' && isNegative(expr[i], expr, i))) {
                // �������֣����������͸�������
                int start = i;
                if (expr[i] == '-') i++; // �����ţ����ź��������

                // ��ȡ�������ֻ򸡵���
                while (isNumber(expr[i])) {
                    i++;
                }

                int len = i - start;
                for (int j = 0; j < len; j++) {
                    result[resultIndex++] = expr[start + j];
                }
                result[resultIndex++] = ' '; // ���ֺ�ӿո�
                continue;
            }

            if (expr[i] == '(') {
                // ������ֱ��ѹջ
                stack[++stackTop] = expr[i];
            } else if (expr[i] == ')') {
                // �����ţ�����ջֱ������������
                while (stackTop >= 0 && stack[stackTop] != '(') {
                    result[resultIndex++] = stack[stackTop--];
                    result[resultIndex++] = ' ';
                }
                stackTop--;  // ����������
            } else if (isOperator(expr[i])) {
                // ���������
                while (stackTop >= 0 && getPriority(stack[stackTop]) >= getPriority(expr[i])) {
                    result[resultIndex++] = stack[stackTop--];
                    result[resultIndex++] = ' ';
                }
                stack[++stackTop] = expr[i];  // ����ǰ�����ѹջ
            }

            i++;
        }

        // ����ջ�е����������
        while (stackTop >= 0) {
            result[resultIndex++] = stack[stackTop--];
            result[resultIndex++] = ' ';
        }

        result[resultIndex - 1] = '\0';  // ȥ�����һ���ո�
        std::cout << result << std::endl;
    }
};

int main() {
    // ��������
    InfixToPostfixHelper helper;

    // ��ʾ�û�������ʽ
    std::cout << "������һ����׺���ʽ:" << std::endl;

    // �ֶ���ȡһ����׺���ʽ
    char texpr[200];
    char expr[200];
    int i = 0;
    char ch;
    while (std::cin.get(ch) && ch != '\n') {
        texpr[i++] = ch;  // ��������ַ���������
    }
    texpr[i] = '\0';  // ȷ���ַ�������
    
    // Ԥ���� 
	int j = 0,tj=0;
    while (texpr[tj] != '\0') {
		if(texpr[tj]=='+'&&texpr[tj+1]!=' '){}
		else{
			expr[j] = texpr[tj];
            j++;	
		}
		tj++;
    }
    expr[j] = '\0';  // ȷ���ַ�������
    
	// ִ��ת��
    std::cout << "ת����ĺ�׺���ʽΪ:" << std::endl;
    helper.convert(expr);

    return 0;
}
