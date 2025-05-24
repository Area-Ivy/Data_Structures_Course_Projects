#include <iostream>
#include <cctype>

// 处理运算符优先级和表达式转换的类
class InfixToPostfixHelper {
public:
    // 运算符优先级
    int getPriority(char op) {
        if (op == '+' || op == '-') return 1;
        if (op == '*' || op == '/') return 2;
        return 0;
    }

    // 判断是否是操作符
    bool isOperator(char c) {
        return (c == '+' || c == '-' || c == '*' || c == '/');
    }

    // 判断字符是否是数字或小数点
    bool isNumber(char c) {
        return (isdigit(c) || c == '.');
    }

    // 判断负号是否是作为负数
    bool isNegative(char c, const char* expr, int i) {
        return (c == '-' && (i == 0 || isOperator(expr[i - 1]) || expr[i - 1] == '('));
    }

    // 将中缀表达式转换为后缀表达式
    void convert(const char* expr) {
        char stack[100];  // 操作符栈
        int stackTop = -1; // 栈顶指针
        char result[200];  // 存储结果
        int resultIndex = 0;  // 结果数组索引

        int i = 0;
        while (expr[i] != '\0') {
            if (expr[i] == ' ') {
                i++;
                continue;  // 跳过空格
            }

            if (isNumber(expr[i]) || (expr[i] == '-' && isNegative(expr[i], expr, i))) {
                // 处理数字（包括负数和浮点数）
                int start = i;
                if (expr[i] == '-') i++; // 处理负号，负号后面接数字

                // 读取完整数字或浮点数
                while (isNumber(expr[i])) {
                    i++;
                }

                int len = i - start;
                for (int j = 0; j < len; j++) {
                    result[resultIndex++] = expr[start + j];
                }
                result[resultIndex++] = ' '; // 数字后加空格
                continue;
            }

            if (expr[i] == '(') {
                // 左括号直接压栈
                stack[++stackTop] = expr[i];
            } else if (expr[i] == ')') {
                // 右括号，弹出栈直到遇到左括号
                while (stackTop >= 0 && stack[stackTop] != '(') {
                    result[resultIndex++] = stack[stackTop--];
                    result[resultIndex++] = ' ';
                }
                stackTop--;  // 弹出左括号
            } else if (isOperator(expr[i])) {
                // 处理运算符
                while (stackTop >= 0 && getPriority(stack[stackTop]) >= getPriority(expr[i])) {
                    result[resultIndex++] = stack[stackTop--];
                    result[resultIndex++] = ' ';
                }
                stack[++stackTop] = expr[i];  // 将当前运算符压栈
            }

            i++;
        }

        // 弹出栈中的所有运算符
        while (stackTop >= 0) {
            result[resultIndex++] = stack[stackTop--];
            result[resultIndex++] = ' ';
        }

        result[resultIndex - 1] = '\0';  // 去掉最后一个空格
        std::cout << result << std::endl;
    }
};

int main() {
    // 创建对象
    InfixToPostfixHelper helper;

    // 提示用户输入表达式
    std::cout << "请输入一个中缀表达式:" << std::endl;

    // 手动读取一个中缀表达式
    char texpr[200];
    char expr[200];
    int i = 0;
    char ch;
    while (std::cin.get(ch) && ch != '\n') {
        texpr[i++] = ch;  // 将输入的字符存入数组
    }
    texpr[i] = '\0';  // 确保字符串结束
    
    // 预处理 
	int j = 0,tj=0;
    while (texpr[tj] != '\0') {
		if(texpr[tj]=='+'&&texpr[tj+1]!=' '){}
		else{
			expr[j] = texpr[tj];
            j++;	
		}
		tj++;
    }
    expr[j] = '\0';  // 确保字符串结束
    
	// 执行转换
    std::cout << "转换后的后缀表达式为:" << std::endl;
    helper.convert(expr);

    return 0;
}
