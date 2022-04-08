#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<assert.h>
#define N 1000000

struct datas {
    int key;
};
typedef struct datas ElemType;

ElemType A[N], Aux[N], B[N];
int C[N], iCountA[N];

//冒泡排序
void BubbleSort(ElemType A[], int n);
//简单选择排序
void SelectSort(ElemType A[], int n);
//直接插入排序
void InsertionSort(ElemType A[], int n);
//归并排序
void MergeSoft(ElemType A[], int low, int high, ElemType Aux[]);
void Merge(ElemType A[], int low, int m, int high, ElemType Aux[]);
//快速排序
void QuickSort(ElemType A[], int low, int high);
int QuickPass(ElemType A[], int low, int high);
//计数排序
void CounterSort(ElemType A[], int n, int iCountA[], int maxKey, ElemType sortedA[]);
//桶排序
void BucketSort(ElemType A[], int n);

void Copy(ElemType A[], ElemType B[]);//复制数组A到数组B
void CreateRandom(ElemType A[]);//产生N个随机数
void PrintData(ElemType A[]);//打印数据
void Check(ElemType A[]);//排序结果检测函数

int main()
{
    printf("   N=%d时：\n", N);
    int start1, finish1, start2, finish2;
    int low = 0, high = N - 1;
    CreateRandom(A);
    Copy(A, B);//B数组用来记录原数组
    //桶排序
    start1 = clock();
    BucketSort(A, N);
    finish1 = clock();
    //PrintData(Aux);
    Check(Aux);
    start2 = clock();
    BucketSort(A, N);
    finish2 = clock();
    printf("   桶排序所花时间：%dms", finish1 - start1);
    printf("   有序数组桶排序所花时间：%dms\n", finish2 - start2);
    //计数排序
    Copy(B, A);//将A数组中数据复原
    int maxKey = N - 1;
    start1 = clock();
    CounterSort(A, N, iCountA, maxKey, Aux);//结果在Aux中
    finish1 = clock();
    //PrintData(Aux);
    Check(Aux);
    start2 = clock();
    CounterSort(A, N, iCountA, maxKey, Aux);
    finish2 = clock();
    printf("   计数排序所花时间：%dms", finish1 - start1);
    printf("   有序数组计数排序所花时间：%dms\n", finish2 - start2);
    //归并排序
    Copy(B, A);//将A数组中数据复原
    start1 = clock();
    MergeSoft(A, low, high, Aux);
    finish1 = clock();
    //PrintData(A);
    Check(A);
    start2 = clock();
    MergeSoft(A, low, high, Aux);
    finish2 = clock();
    printf("   归并排序所花时间：%dms", finish1 - start1);
    printf("   有序数组归并排序所花时间：%dms\n", finish2 - start2);
    //快速排序
    Copy(B, A);//将A数组中数据复原
    start1 = clock();
    QuickSort(A, low, high);
    finish1 = clock();
    //PrintData(A);
    Check(A);
    start2 = clock();
    QuickSort(A, low, high);
    finish2 = clock();
    printf("   快速排序所花时间：%dms", finish1 - start1);
    printf("   有序数组快速排序所花时间：%dms\n", finish2 - start2);
    //直接插入排序
    Copy(B, A);//将A数组中数据复原
    start1 = clock();
    InsertionSort(A, N);
    finish1 = clock();
    //PrintData(A);
    Check(A);
    start2 = clock();
    InsertionSort(A, N);
    finish2 = clock();
    printf("   直接插入排序所花时间：%dms", finish1 - start1);
    printf("   有序数组直接插入排序所花时间：%dms\n", finish2 - start2);
    //简单选择排序
    Copy(B, A);//将A数组中数据复原
    start1 = clock();
    SelectSort(A, N);
    finish1 = clock();
    //PrintData(A);
    Check(A);
    start2 = clock();
    SelectSort(A, N);
    finish2 = clock();
    printf("   简单选择排序所花时间：%dms", finish1 - start1);
    printf("   有序数组简单选择排序所花时间：%dms\n", finish2 - start2);
    //冒泡排序
    Copy(B, A);//将A数组中数据复原
    start1 = clock();
    BubbleSort(A, N);
    finish1 = clock();
    //PrintData(A);
    Check(A);
    start2 = clock();
    BubbleSort(A, N);
    finish2 = clock();
    printf("   冒泡排序所花时间：%dms", finish1 - start1);
    printf("   有序数组冒泡排序所花时间：%dms\n", finish2 - start2);

    return 0;
}

//冒泡排序
void BubbleSort(ElemType A[], int n)
{
    for (int i = 0; i < n - 1; ++i)
        for (int j = 0; j < n - i - 1; ++j)
        {
            if (A[j].key > A[j + 1].key)
            {
                ElemType B;
                B = A[j];
                A[j] = A[j + 1];
                A[j + 1] = B;
            }
        }
}
//简单选择排序
void SelectSort(ElemType A[], int n)
{
    for (int i = 0; i < n - 1; ++i)
    {
        int minI = i;
        for (int j = i + 1; j < n; ++j)
        {
            if (A[minI].key > A[j].key)
                minI = j;
        }
        ElemType B;
        B = A[i];
        A[i] = A[minI];
        A[minI] = B;
    }
}
//直接插入排序
void InsertionSort(ElemType A[], int n)
{
    for (int i = 1; i < n; ++i)
    {
        ElemType x = A[i];
        int j = i - 1;
        while (j >= 0 && x.key < A[j].key)
        {
            A[j + 1] = A[j];
            --j;
        }
        A[j + 1] = x;
    }
}
//归并排序
void MergeSoft(ElemType A[], int low, int high, ElemType Aux[])
{
    int m;
    if (low >= high)
        return;
    m = (low + high) / 2;
    MergeSoft(A, low, m, Aux);
    MergeSoft(A, m + 1, high, Aux);
    Merge(A, low, m, high, Aux);
    for (int i = low; i <= high; ++i)
        A[i] = Aux[i];
}
void Merge(ElemType A[], int low, int m, int high, ElemType Aux[])
{
    int i = low;
    int j = m + 1;
    int k = i;
    while (i <= m && j <= high)
    {
        if (A[i].key < A[j].key)
            Aux[k++] = A[i++];
        else
            Aux[k++] = A[j++];
    }
    while (i <= m)
        Aux[k++] = A[i++];
    while (j <= high)
        Aux[k++] = A[j++];
}
//快速排序
void QuickSort(ElemType A[], int low, int high)
{
    if (low >= high)
        return;
    int pivot = QuickPass(A, low, high);
    QuickSort(A, low, pivot - 1);
    QuickSort(A, pivot + 1, high);
}
int QuickPass(ElemType A[], int low, int high)
{
    ElemType x = A[low];
    while (low < high)
    {
        while (low < high && x.key <= A[high].key)
            --high;
        if (low == high)
            break;
        A[low++] = A[high];
        while (low < high && x.key >= A[low].key)
            ++low;
        if (low == high)
            break;
        A[high--] = A[low];
    }
    A[low] = x;
    return low;
}
//计数排序
void CounterSort(ElemType A[], int n, int iCountA[], int maxKey, ElemType sortedA[])
{
    for (int key = 0; key <= maxKey; ++key)
        iCountA[key] = 0;//辅助计数数组清空
    for (int i = 0; i < n; ++i)
        ++iCountA[A[i].key];
    int iStartPos = 0;
    for (int key = 0; key <= maxKey; ++key)
    {
        int iNextPos = iStartPos + iCountA[key];
        iCountA[key] = iStartPos;
        iStartPos = iNextPos;
    }
    //assert(iStartPos == n);断言
    for (int i = 0; i < n; ++i)
        sortedA[iCountA[A[i].key]++] = A[i];
}
void BucketSort(ElemType A[], int n)
{
    int m = 0;
    for (int i = 0; i < n; ++i)
    {
        int k = A[i].key;
        ++C[k];
    }
    for (int k = 1; k <= N; ++k)
    {
        for (int i = 1; i <= C[k]; ++i)
        {
            A[m++].key = k;
        }
    }
}


//复制数组A到数组B
void Copy(ElemType A[], ElemType B[])
{
    for (int i = 0; i < N; i++)
        B[i] = A[i];
}
//产生N个随机数
void CreateRandom(ElemType A[])
{
    int a;
    srand((unsigned int)time(NULL));
    for (int i = 0; i < N; i++)
    {
        a = (int)(1.0 * rand() / RAND_MAX * N);
        A[i].key = a;
    }
}
//打印数据
void PrintData(ElemType A[])
{
    for (int i = 0; i < N; i++)
    {
        printf("%8d ", A[i].key);
        if ((i + 1) % 10 == 0)
            printf("\n");
    }
}
//排序结果检测函数
void Check(ElemType A[])
{
    int flag = 1;
    for (int i = 0; i < N - 1; i++)
    {
        if (A[i].key > A[i + 1].key)
            flag = -1;
    }
    if (flag == 1)
        printf("   排序结果正确\n");
    else
        printf("   排序结果错误\n");
}
