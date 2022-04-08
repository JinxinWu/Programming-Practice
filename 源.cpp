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

//ð������
void BubbleSort(ElemType A[], int n);
//��ѡ������
void SelectSort(ElemType A[], int n);
//ֱ�Ӳ�������
void InsertionSort(ElemType A[], int n);
//�鲢����
void MergeSoft(ElemType A[], int low, int high, ElemType Aux[]);
void Merge(ElemType A[], int low, int m, int high, ElemType Aux[]);
//��������
void QuickSort(ElemType A[], int low, int high);
int QuickPass(ElemType A[], int low, int high);
//��������
void CounterSort(ElemType A[], int n, int iCountA[], int maxKey, ElemType sortedA[]);
//Ͱ����
void BucketSort(ElemType A[], int n);

void Copy(ElemType A[], ElemType B[]);//��������A������B
void CreateRandom(ElemType A[]);//����N�������
void PrintData(ElemType A[]);//��ӡ����
void Check(ElemType A[]);//��������⺯��

int main()
{
    printf("   N=%dʱ��\n", N);
    int start1, finish1, start2, finish2;
    int low = 0, high = N - 1;
    CreateRandom(A);
    Copy(A, B);//B����������¼ԭ����
    //Ͱ����
    start1 = clock();
    BucketSort(A, N);
    finish1 = clock();
    //PrintData(Aux);
    Check(Aux);
    start2 = clock();
    BucketSort(A, N);
    finish2 = clock();
    printf("   Ͱ��������ʱ�䣺%dms", finish1 - start1);
    printf("   ��������Ͱ��������ʱ�䣺%dms\n", finish2 - start2);
    //��������
    Copy(B, A);//��A���������ݸ�ԭ
    int maxKey = N - 1;
    start1 = clock();
    CounterSort(A, N, iCountA, maxKey, Aux);//�����Aux��
    finish1 = clock();
    //PrintData(Aux);
    Check(Aux);
    start2 = clock();
    CounterSort(A, N, iCountA, maxKey, Aux);
    finish2 = clock();
    printf("   ������������ʱ�䣺%dms", finish1 - start1);
    printf("   �������������������ʱ�䣺%dms\n", finish2 - start2);
    //�鲢����
    Copy(B, A);//��A���������ݸ�ԭ
    start1 = clock();
    MergeSoft(A, low, high, Aux);
    finish1 = clock();
    //PrintData(A);
    Check(A);
    start2 = clock();
    MergeSoft(A, low, high, Aux);
    finish2 = clock();
    printf("   �鲢��������ʱ�䣺%dms", finish1 - start1);
    printf("   ��������鲢��������ʱ�䣺%dms\n", finish2 - start2);
    //��������
    Copy(B, A);//��A���������ݸ�ԭ
    start1 = clock();
    QuickSort(A, low, high);
    finish1 = clock();
    //PrintData(A);
    Check(A);
    start2 = clock();
    QuickSort(A, low, high);
    finish2 = clock();
    printf("   ������������ʱ�䣺%dms", finish1 - start1);
    printf("   �������������������ʱ�䣺%dms\n", finish2 - start2);
    //ֱ�Ӳ�������
    Copy(B, A);//��A���������ݸ�ԭ
    start1 = clock();
    InsertionSort(A, N);
    finish1 = clock();
    //PrintData(A);
    Check(A);
    start2 = clock();
    InsertionSort(A, N);
    finish2 = clock();
    printf("   ֱ�Ӳ�����������ʱ�䣺%dms", finish1 - start1);
    printf("   ��������ֱ�Ӳ�����������ʱ�䣺%dms\n", finish2 - start2);
    //��ѡ������
    Copy(B, A);//��A���������ݸ�ԭ
    start1 = clock();
    SelectSort(A, N);
    finish1 = clock();
    //PrintData(A);
    Check(A);
    start2 = clock();
    SelectSort(A, N);
    finish2 = clock();
    printf("   ��ѡ����������ʱ�䣺%dms", finish1 - start1);
    printf("   ���������ѡ����������ʱ�䣺%dms\n", finish2 - start2);
    //ð������
    Copy(B, A);//��A���������ݸ�ԭ
    start1 = clock();
    BubbleSort(A, N);
    finish1 = clock();
    //PrintData(A);
    Check(A);
    start2 = clock();
    BubbleSort(A, N);
    finish2 = clock();
    printf("   ð����������ʱ�䣺%dms", finish1 - start1);
    printf("   ��������ð����������ʱ�䣺%dms\n", finish2 - start2);

    return 0;
}

//ð������
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
//��ѡ������
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
//ֱ�Ӳ�������
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
//�鲢����
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
//��������
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
//��������
void CounterSort(ElemType A[], int n, int iCountA[], int maxKey, ElemType sortedA[])
{
    for (int key = 0; key <= maxKey; ++key)
        iCountA[key] = 0;//���������������
    for (int i = 0; i < n; ++i)
        ++iCountA[A[i].key];
    int iStartPos = 0;
    for (int key = 0; key <= maxKey; ++key)
    {
        int iNextPos = iStartPos + iCountA[key];
        iCountA[key] = iStartPos;
        iStartPos = iNextPos;
    }
    //assert(iStartPos == n);����
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


//��������A������B
void Copy(ElemType A[], ElemType B[])
{
    for (int i = 0; i < N; i++)
        B[i] = A[i];
}
//����N�������
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
//��ӡ����
void PrintData(ElemType A[])
{
    for (int i = 0; i < N; i++)
    {
        printf("%8d ", A[i].key);
        if ((i + 1) % 10 == 0)
            printf("\n");
    }
}
//��������⺯��
void Check(ElemType A[])
{
    int flag = 1;
    for (int i = 0; i < N - 1; i++)
    {
        if (A[i].key > A[i + 1].key)
            flag = -1;
    }
    if (flag == 1)
        printf("   ��������ȷ\n");
    else
        printf("   ����������\n");
}
