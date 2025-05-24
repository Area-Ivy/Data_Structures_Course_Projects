#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <climits>

using namespace std;
using namespace std::chrono;

// 生成随机数数组
void generateRandomNumbers(int nums[], int n) {
    srand((unsigned)time(0));
    for (int i = 0; i < n; ++i) {
        nums[i] = rand() % 100000;  // 生成0到99999之间的随机数
    }
}

class Sort{
public:
	
// 冒泡排序
void bubbleSort(int nums[], int n, long long& swaps, long long& comparisons) {
    bool swapped;
    for (int i = 0; i < n - 1; i++) {
        swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            comparisons++;
            if (nums[j] > nums[j + 1]) {
                int temp = nums[j];
                nums[j] = nums[j + 1];
                nums[j + 1] = temp;
                swaps++;
                swapped = true;
            }
        }
        if (!swapped)
            break;
    }
}

// 选择排序
void selectionSort(int nums[], int n, long long& swaps, long long& comparisons) {
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            comparisons++;
            if (nums[j] < nums[minIndex]) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            int temp = nums[i];
            nums[i] = nums[minIndex];
            nums[minIndex] = temp;
            swaps++;
        }
    }
}

// 插入排序
void insertionSort(int nums[], int n, long long& swaps, long long& comparisons) {
    for (int i = 1; i < n; i++) {
        int key = nums[i];
        int j = i - 1;
        while (j >= 0 && nums[j] > key) {
            comparisons++;
            nums[j + 1] = nums[j];
            swaps++;
            j--;
        }
        comparisons++;
        nums[j + 1] = key;
    }
}

// 希尔排序
void shellSort(int nums[], int n, long long& swaps, long long& comparisons) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int temp = nums[i];
            int j;
            for (j = i; j >= gap && nums[j - gap] > temp; j -= gap) {
                comparisons++;
                nums[j] = nums[j - gap];
                swaps++;
            }
            nums[j] = temp;
        }
    }
}

// 快速排序辅助函数
int partition(int nums[], int low, int high, long long& swaps, long long& comparisons) {
    int pivot = nums[high];
    int i = low - 1;
    for (int j = low; j <= high - 1; j++) {
        comparisons++;
        if (nums[j] < pivot) {
            i++;
            int temp = nums[i];
            nums[i] = nums[j];
            nums[j] = temp;
            swaps++;
        }
    }
    int temp = nums[i + 1];
    nums[i + 1] = nums[high];
    nums[high] = temp;
    swaps++;
    return (i + 1);
}

// 快速排序
void quickSort(int nums[], int low, int high, long long& swaps, long long& comparisons) {
    if (low < high) {
        int pi = partition(nums, low, high, swaps, comparisons);
        quickSort(nums, low, pi - 1, swaps, comparisons);
        quickSort(nums, pi + 1, high, swaps, comparisons);
    }
}

// 堆排序辅助函数
void heapify(int nums[], int n, int i, long long& swaps, long long& comparisons) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && nums[left] > nums[largest]) {
        comparisons++;
        largest = left;
    }
    if (right < n && nums[right] > nums[largest]) {
        comparisons++;
        largest = right;
    }

    if (largest != i) {
        int temp = nums[i];
        nums[i] = nums[largest];
        nums[largest] = temp;
        swaps++;
        heapify(nums, n, largest, swaps, comparisons);
    }
}

// 堆排序
void heapSort(int nums[], int n, long long& swaps, long long& comparisons) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(nums, n, i, swaps, comparisons);
    }
    for (int i = n - 1; i > 0; i--) {
        int temp = nums[0];
        nums[0] = nums[i];
        nums[i] = temp;
        swaps++;
        heapify(nums, i, 0, swaps, comparisons);
    }
}

// 归并排序辅助函数
void merge(int nums[], int l, int m, int r, long long& swaps, long long& comparisons) {
    int n1 = m - l + 1;
    int n2 = r - m;
    int* L = new int[n1];
    int* R = new int[n2];

    for (int i = 0; i < n1; i++)
        L[i] = nums[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = nums[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        comparisons++;
        if (L[i] <= R[j]) {
            nums[k++] = L[i++];
        } else {
            nums[k++] = R[j++];
        }
        swaps++;
    }

    while (i < n1) {
        nums[k++] = L[i++];
        swaps++;
    }

    while (j < n2) {
        nums[k++] = R[j++];
        swaps++;
    }

    delete[] L;
    delete[] R;
}

// 归并排序
void mergeSort(int nums[], int l, int r, long long& swaps, long long& comparisons) {
    if (l >= r) {
        return;
    }
    int m = l + (r - l) / 2;
    mergeSort(nums, l, m, swaps, comparisons);
    mergeSort(nums, m + 1, r, swaps, comparisons);
    merge(nums, l, m, r, swaps, comparisons);
}

// 获取数组中最大值
int getMax(int nums[], int n) {
    int maxVal = nums[0];
    for (int i = 1; i < n; i++) {
        if (nums[i] > maxVal) {
            maxVal = nums[i];
        }
    }
    return maxVal;
}

// 基数排序的计数排序部分
void countingSortForRadix(int nums[], int n, int exp, long long& swaps, long long& comparisons) {
    const int RADIX = 10; // 基数为10（十进制数字）
    int output[n]; // 输出数组
    int count[RADIX] = {0}; // 计数数组，大小为基数

    // 根据当前位数统计频率
    for (int i = 0; i < n; i++) {
        int digit = (nums[i] / exp) % RADIX;
        count[digit]++;
    }

    // 计算计数数组的累加和
    for (int i = 1; i < RADIX; i++) {
        count[i] += count[i - 1];
    }

    // 根据计数数组，将元素放入输出数组中
    for (int i = n - 1; i >= 0; i--) {
        int digit = (nums[i] / exp) % RADIX;
        output[count[digit] - 1] = nums[i];
        count[digit]--;
    }

    // 将输出数组复制回原数组
    for (int i = 0; i < n; i++) {
        nums[i] = output[i];
    }
}

// 基数排序主函数
void radixSort(int nums[], int n, long long& swaps, long long& comparisons) {
    int maxVal = getMax(nums, n);

    // 按位数从低到高逐步排序
    for (int exp = 1; maxVal / exp > 0; exp *= 10) {
        countingSortForRadix(nums, n, exp, swaps, comparisons);
    }
}

};

Sort s;

int main() {
    const int MAX_SIZE = 100000; // 最大数组长度
    int nums[MAX_SIZE];
    
    cout << "=============================================" << endl;
    cout << "**             排序算法比较                **" << endl;
    cout << "=============================================" << endl;
    cout << "**             1---冒泡排序                **" << endl;
    cout << "**             2---选择排序                **" << endl;
    cout << "**             3---直接插入排序            **" << endl;
    cout << "**             4---希尔排序                **" << endl;
    cout << "**             5---快速排序                **" << endl;
    cout << "**             6---堆排序                  **" << endl;
    cout << "**             7---归并排序                **" << endl;
    cout << "**             8---基数排序                **" << endl;
    cout << "**             9---退出程序                **" << endl;
    cout << "=============================================" << endl;

    cout << endl;

    int choice, n;
    cout << "请输入要产生的随机数的个数: ";
    cin >> n;
    
    string sortKinds[8]={"冒泡排序","选择排序","直接插入排序","希尔排序","快速排序","堆排序","归并排序","基数排序"}; 
    
    
    while (true) {
        cout << "请选择排序算法：  ";
        cin >> choice;

        if (choice == 9) {
        	cout<<"press any key to continue"<<endl;
        	getchar();
        	break;
		}
        if (cin.fail() || choice < 1 || choice>9)
        {
            cin.clear();
            cin.ignore(1024, '\n');
            cout << "输入错误，请重新输入!" << endl << endl;
            continue;
        }
        // 生成随机数
        
        generateRandomNumbers(nums, n);

        long long swaps = 0;
        long long comparisons = 0;
        clock_t start = clock();

        switch (choice) {
            case 1:
                s.bubbleSort(nums, n, swaps, comparisons);
                break;
            case 2:
                s.selectionSort(nums, n, swaps, comparisons);
                break;
            case 3:
                s.insertionSort(nums, n, swaps, comparisons);
                break;
            case 4:
                s.shellSort(nums, n, swaps, comparisons);
                break;
            case 5:
                s.quickSort(nums, 0, n - 1, swaps, comparisons);
                break;
            case 6:
                s.heapSort(nums, n, swaps, comparisons);
                break;
            case 7:
                s.mergeSort(nums, 0, n - 1, swaps, comparisons);
                break;
            case 8:
                s.radixSort(nums, n, swaps, comparisons);
                break;
            default:
                cout << "无效选择!" << endl;
                break;
        }

        clock_t end = clock();
        double duration = double(end - start) / CLOCKS_PER_SEC;

        cout << sortKinds[choice-1] << "所用时间: " << duration<< endl;      
		cout << sortKinds[choice-1] << "比较次数: " << comparisons << endl;
		cout << sortKinds[choice-1] << "交换次数: " << swaps << endl << endl;
		
    }

    return 0;
}


