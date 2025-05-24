#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <climits>

using namespace std;
using namespace std::chrono;

// �������������
void generateRandomNumbers(int nums[], int n) {
    srand((unsigned)time(0));
    for (int i = 0; i < n; ++i) {
        nums[i] = rand() % 100000;  // ����0��99999֮��������
    }
}

class Sort{
public:
	
// ð������
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

// ѡ������
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

// ��������
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

// ϣ������
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

// ��������������
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

// ��������
void quickSort(int nums[], int low, int high, long long& swaps, long long& comparisons) {
    if (low < high) {
        int pi = partition(nums, low, high, swaps, comparisons);
        quickSort(nums, low, pi - 1, swaps, comparisons);
        quickSort(nums, pi + 1, high, swaps, comparisons);
    }
}

// ������������
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

// ������
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

// �鲢����������
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

// �鲢����
void mergeSort(int nums[], int l, int r, long long& swaps, long long& comparisons) {
    if (l >= r) {
        return;
    }
    int m = l + (r - l) / 2;
    mergeSort(nums, l, m, swaps, comparisons);
    mergeSort(nums, m + 1, r, swaps, comparisons);
    merge(nums, l, m, r, swaps, comparisons);
}

// ��ȡ���������ֵ
int getMax(int nums[], int n) {
    int maxVal = nums[0];
    for (int i = 1; i < n; i++) {
        if (nums[i] > maxVal) {
            maxVal = nums[i];
        }
    }
    return maxVal;
}

// ��������ļ������򲿷�
void countingSortForRadix(int nums[], int n, int exp, long long& swaps, long long& comparisons) {
    const int RADIX = 10; // ����Ϊ10��ʮ�������֣�
    int output[n]; // �������
    int count[RADIX] = {0}; // �������飬��СΪ����

    // ���ݵ�ǰλ��ͳ��Ƶ��
    for (int i = 0; i < n; i++) {
        int digit = (nums[i] / exp) % RADIX;
        count[digit]++;
    }

    // �������������ۼӺ�
    for (int i = 1; i < RADIX; i++) {
        count[i] += count[i - 1];
    }

    // ���ݼ������飬��Ԫ�ط������������
    for (int i = n - 1; i >= 0; i--) {
        int digit = (nums[i] / exp) % RADIX;
        output[count[digit] - 1] = nums[i];
        count[digit]--;
    }

    // ��������鸴�ƻ�ԭ����
    for (int i = 0; i < n; i++) {
        nums[i] = output[i];
    }
}

// ��������������
void radixSort(int nums[], int n, long long& swaps, long long& comparisons) {
    int maxVal = getMax(nums, n);

    // ��λ���ӵ͵���������
    for (int exp = 1; maxVal / exp > 0; exp *= 10) {
        countingSortForRadix(nums, n, exp, swaps, comparisons);
    }
}

};

Sort s;

int main() {
    const int MAX_SIZE = 100000; // ������鳤��
    int nums[MAX_SIZE];
    
    cout << "=============================================" << endl;
    cout << "**             �����㷨�Ƚ�                **" << endl;
    cout << "=============================================" << endl;
    cout << "**             1---ð������                **" << endl;
    cout << "**             2---ѡ������                **" << endl;
    cout << "**             3---ֱ�Ӳ�������            **" << endl;
    cout << "**             4---ϣ������                **" << endl;
    cout << "**             5---��������                **" << endl;
    cout << "**             6---������                  **" << endl;
    cout << "**             7---�鲢����                **" << endl;
    cout << "**             8---��������                **" << endl;
    cout << "**             9---�˳�����                **" << endl;
    cout << "=============================================" << endl;

    cout << endl;

    int choice, n;
    cout << "������Ҫ������������ĸ���: ";
    cin >> n;
    
    string sortKinds[8]={"ð������","ѡ������","ֱ�Ӳ�������","ϣ������","��������","������","�鲢����","��������"}; 
    
    
    while (true) {
        cout << "��ѡ�������㷨��  ";
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
            cout << "�����������������!" << endl << endl;
            continue;
        }
        // ���������
        
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
                cout << "��Чѡ��!" << endl;
                break;
        }

        clock_t end = clock();
        double duration = double(end - start) / CLOCKS_PER_SEC;

        cout << sortKinds[choice-1] << "����ʱ��: " << duration<< endl;      
		cout << sortKinds[choice-1] << "�Ƚϴ���: " << comparisons << endl;
		cout << sortKinds[choice-1] << "��������: " << swaps << endl << endl;
		
    }

    return 0;
}


