#include <iostream>
using namespace std;

// �����Թ������ߴ�
#define MAX_N 20

int Step; 

// �Թ���
class Maze {
private:
    char maze[MAX_N][MAX_N];    // �Թ��Ĳ���
    bool visited[MAX_N][MAX_N]; // ����ѷ��ʵĸ���
    int path[MAX_N * MAX_N][2]; // �洢·��
    int n, m; // �Թ���������
    int presetN = 6; // Ԥ���Թ��� 
    int presetM = 6; // Ԥ���Թ���
    int startX, startY; // �������
    int endX, endY; // ��������
    const int direction[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}; // �ĸ������ϡ��¡�����

public:
    // ���캯������ʼ���Թ�������������ڡ���������
    Maze(int rows, int cols, int sx, int sy, int ex, int ey) {
        if(rows==-1&&cols==-1){
        	n = presetN + 1;
	        m = presetM + 1;
		}
		else{
			n = rows + 1;
	        m = cols + 1;	
		}
		
        startX = sx;
        startY = sy;
        endX = ex;
        endY = ey;
    }

    // �����Թ�����
    void inputMaze() {
        cout << "�������Թ��Ĳ��֣�#Ϊ�ϰ���0Ϊ���ߣ�:" << endl;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                char cell;
                cin >> cell;
                if (cell == '#') {
                    maze[i][j] = '#';  // �ϰ�
                } else if (cell == '0') {
                    maze[i][j] = '0';  // ����
                } else {
                    maze[i][j] = '#';  // �Ƿ�����Ĭ����Ϊ�ϰ�
                }
            }
        }
    }
    
    // Ԥ���Թ�����
    void presetMaze() {
        // Ԥ��һ���Թ�������ʹ�� # �� 0
        char preset[MAX_N][MAX_N] = {
            {'#', '#', '#', '#', '#', '#', '#'},
            {'#', '0', '#', '0', '0', '0', '#'},
            {'#', '0', '#', '0', '#', '#', '#'},
            {'#', '0', '0', '0', '#', '0', '#'},
            {'#', '0', '#', '0', '0', '0', '#'},
            {'#', '0', '#', '0', '#', '0', '#'},
            {'#', '#', '#', '#', '#', '#', '#'}
        };
        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                maze[i][j] = preset[i][j];
            }
        }
    }

    // ��ӡ�Թ�
    void printMaze(bool printPath = false) {
    	cout<<"     ";
    	for (int k = 0; k < m; k++) {
    		cout<<k<<"��   "; 
		}
		cout<<endl;
        for (int i = 0; i < n; i++) {
        	cout<<i<<"��   ";
            for (int j = 0; j < m; j++) {
                if (maze[i][j] == '#') {
                    cout << "#     ";  // �ϰ�
                } else if (printPath && visited[i][j]) {
                    cout << "x     ";  // ·��
                } else {
                    cout << "0     ";  // ���ߵ�·��
                }
            }
            cout << endl;
        }
    }

    // ���·��
    void printPath(int step) {
        cout << "�Թ�·��: " << endl;
        for (int i = 0; i <= step; i++) {
            cout << "<" << path[i][0] << ", " << path[i][1] << ">";
            if (i < step) cout << " ---> ";
        }
        cout << endl;
    }

    // ���ݷ�Ѱ��·��
    bool solveMaze(int x, int y, int step) {
        // �������
        if (x == endX && y == endY) {
            path[step][0] = x;
            path[step][1] = y;
            visited[x][y] = true;
            Step = step;
            return true;
        }

        // ��ǵ�ǰλ���ѷ���
        visited[x][y] = true;
        path[step][0] = x;
        path[step][1] = y;

        // ��̽�ĸ�����
        for (int i = 0; i < 4; i++) {
            int newX = x + direction[i][0];
            int newY = y + direction[i][1];

            // �����λ���Ƿ���Ч��δ���ʹ�
            if (newX >= 0 && newX < n && newY >= 0 && newY < m && maze[newX][newY] == '0' && !visited[newX][newY]) {
                if (solveMaze(newX, newY, step + 1)) {
                    return true;  // �ҵ�����
                }
            }
        }

        // ������з����޷�ǰ��������
        visited[x][y] = false;
        return false;
    }

    // �����ܺ�������ʼѰ��·��
    void findPath() {
        // ��ʼ������״̬
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                visited[i][j] = false;
            }
        }

        // ʹ�û��ݷ�����ڿ�ʼѰ��·��
        if (solveMaze(startX, startY, 0)) {
            cout << "�Թ���ͼ��" << endl;
            printMaze(true);  // ����Թ���·��
            printPath(Step);  // ���·��
        } else {
            cout << "û��·���������!" << endl;
        }
    }
};

int main() {
    int n, m, sx, sy, ex, ey;
    	
    n = -1;
    m = -1;
        
    // ������ںͳ�������
	cout << "��������ڵ����� (x y): ";
	cin >> sx >> sy;
	cout << "��������ڵ����� (x y): ";
	cin >> ex >> ey;
	    
	// �����Թ�����
    Maze maze(n, m, sx, sy, ex, ey);
        
    maze.presetMaze();
    
    // ��ӡ��ʼ�Թ�
    cout << "��ʼ�Թ���" << endl;
    maze.printMaze();

    // ����·��
    maze.findPath();

    return 0;
}
