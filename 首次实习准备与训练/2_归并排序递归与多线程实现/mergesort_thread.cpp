#include <iostream>
#include <vector>
#include <thread>  // C++多线程核心头文件
#include <cstdlib> // malloc/free 或直接用C++ vector替代
using namespace std;

// 归并操作（兼容C语言逻辑，也可完全改用C++容器）
void merge(int a[], int l, int mid, int r) {
    int *temp = (int*)malloc((r - l + 1) * sizeof(int));
    int i = l, j = mid + 1, k = 0;

    while (i <= mid && j <= r) {
        if (a[i] <= a[j]) {
            temp[k++] = a[i++];
        } else {
            temp[k++] = a[j++];
        }
    }

    while (i <= mid)
        temp[k++] = a[i++];
    while (j <= r)
        temp[k++] = a[j++];

    for (i = l, k = 0; i <= r; i++, k++) {
        a[i] = temp[k];
    }

    free(temp);
}

// 归并排序核心函数（递归+多线程创建）
void mergesort(int a[], int l, int r) {
    if (l < r) {
        int mid = (l + r) / 2;

        // 方式1：创建两个子线程，分别排序左、右区间
        // 注意：std::thread 直接传递参数，无需手动封装结构体
        thread left_thread(mergesort, a, l, mid);
        thread right_thread(mergesort, a, mid + 1, r);

        // 等待左右子线程排序完成（必须等待，否则直接归并会出错）
        left_thread.join();
        right_thread.join();

        // 归并两个已排序的子区间
        merge(a, l, mid, r);

        // 方式2：（可选）小规模数据用单线程，避免线程创建开销
        // if (mid - l > 1000) { // 区间长度大于1000时才用多线程
        //     std::thread left_thread(mergesort, a, l, mid);
        //     mergesort(a, mid+1, r); // 右区间主线程执行
        //     left_thread.join();
        // } else {
        //     mergesort(a, l, mid);
        //     mergesort(a, mid+1, r);
        // }
        // merge(a, l, mid, r);
    }
}

// 打印数组
void printarray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << "  ";
    }
    cout << endl;
}

// 主函数（C++风格输入输出，兼容原逻辑）
int main() {
    int n;
    int arr[100]; // 保留原数组大小，也可改用 std::vector<int> arr(n); 更灵活

    cout << "要排序数组的规模大小是：";
    cin >> n;

    for (int i = 0; i < n; ++i) {
        cout << "输入第" << i << "个数据元素：";
        cin >> arr[i];
    }

    cout << "输入数组是：" << endl;
    printarray(arr, n);

    // 调用多线程归并排序
    mergesort(arr, 0, n - 1);

    cout << "升序排序之后得到数组为：" << endl;
    printarray(arr, n);

    return 0;
}


//g++ mergesort_thread.cpp -o mergesort -std=c++11 -lpthread
