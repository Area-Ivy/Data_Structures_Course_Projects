#include <iostream>
using namespace std;

// 定义迷宫的最大尺寸
#define MAX_N 20

int Step; 

// 迷宫类
class Maze {
private:
    char maze[MAX_N][MAX_N];    // 迷宫的布局
    bool visited[MAX_N][MAX_N]; // 标记已访问的格子
    int path[MAX_N * MAX_N][2]; // 存储路径
    int n, m; // 迷宫的行列数
    int presetN = 6; // 预设迷宫行 
    int presetM = 6; // 预设迷宫列
    int startX, startY; // 入口坐标
    int endX, endY; // 出口坐标
    const int direction[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}; // 四个方向：上、下、左、右

public:
    // 构造函数：初始化迷宫的行列数和入口、出口坐标
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

    // 输入迷宫布局
    void inputMaze() {
        cout << "请输入迷宫的布局（#为障碍，0为可走）:" << endl;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                char cell;
                cin >> cell;
                if (cell == '#') {
                    maze[i][j] = '#';  // 障碍
                } else if (cell == '0') {
                    maze[i][j] = '0';  // 可走
                } else {
                    maze[i][j] = '#';  // 非法输入默认作为障碍
                }
            }
        }
    }
    
    // 预设迷宫布局
    void presetMaze() {
        // 预设一个迷宫样例，使用 # 和 0
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

    // 打印迷宫
    void printMaze(bool printPath = false) {
    	cout<<"     ";
    	for (int k = 0; k < m; k++) {
    		cout<<k<<"列   "; 
		}
		cout<<endl;
        for (int i = 0; i < n; i++) {
        	cout<<i<<"行   ";
            for (int j = 0; j < m; j++) {
                if (maze[i][j] == '#') {
                    cout << "#     ";  // 障碍
                } else if (printPath && visited[i][j]) {
                    cout << "x     ";  // 路径
                } else {
                    cout << "0     ";  // 可走的路径
                }
            }
            cout << endl;
        }
    }

    // 输出路径
    void printPath(int step) {
        cout << "迷宫路径: " << endl;
        for (int i = 0; i <= step; i++) {
            cout << "<" << path[i][0] << ", " << path[i][1] << ">";
            if (i < step) cout << " ---> ";
        }
        cout << endl;
    }

    // 回溯法寻找路径
    bool solveMaze(int x, int y, int step) {
        // 到达出口
        if (x == endX && y == endY) {
            path[step][0] = x;
            path[step][1] = y;
            visited[x][y] = true;
            Step = step;
            return true;
        }

        // 标记当前位置已访问
        visited[x][y] = true;
        path[step][0] = x;
        path[step][1] = y;

        // 试探四个方向
        for (int i = 0; i < 4; i++) {
            int newX = x + direction[i][0];
            int newY = y + direction[i][1];

            // 检查新位置是否有效且未访问过
            if (newX >= 0 && newX < n && newY >= 0 && newY < m && maze[newX][newY] == '0' && !visited[newX][newY]) {
                if (solveMaze(newX, newY, step + 1)) {
                    return true;  // 找到出口
                }
            }
        }

        // 如果所有方向都无法前进，回溯
        visited[x][y] = false;
        return false;
    }

    // 主功能函数：开始寻找路径
    void findPath() {
        // 初始化访问状态
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                visited[i][j] = false;
            }
        }

        // 使用回溯法从入口开始寻找路径
        if (solveMaze(startX, startY, 0)) {
            cout << "迷宫地图：" << endl;
            printMaze(true);  // 输出迷宫和路径
            printPath(Step);  // 输出路径
        } else {
            cout << "没有路径到达出口!" << endl;
        }
    }
};

int main() {
    int n, m, sx, sy, ex, ey;
    	
    n = -1;
    m = -1;
        
    // 输入入口和出口坐标
	cout << "请输入入口的坐标 (x y): ";
	cin >> sx >> sy;
	cout << "请输入出口的坐标 (x y): ";
	cin >> ex >> ey;
	    
	// 创建迷宫对象
    Maze maze(n, m, sx, sy, ex, ey);
        
    maze.presetMaze();
    
    // 打印初始迷宫
    cout << "初始迷宫：" << endl;
    maze.printMaze();

    // 查找路径
    maze.findPath();

    return 0;
}
