#include "LysClassification.h"

void Label012(char* type, int* label);
void MakeRand(Iris iris[], int n);
int InputAndInitialize();
void PrintData();
void LoadData();
double EuclideanDistance(Iris i1, Iris i2);
int CompareLabel(int a, int b, int c);
int CountLabel(int* count, int k, int clusterID);
void BubbleSort(int n, Distance* distance);
void PrintResult(int k, int count);

// Knn�㷨���Ĵ���
void Knn()
{
	int count = 0;
	for (int k = 1; k <= KMAX; ++k)
	{
		for (int i = 0; i < text_Num; i++) // �������Լ�
		{
			for (int j = 0; j < train_Num; j++) // ����ѵ����
			{
				// �Ѽ���ŷ����þ������δ���distance�ṹ�������value�� 
				distance[j].value = EuclideanDistance(testSet[i], trainSet[j]);
				// ��ѵ������ǩ�����õľ������һ�� 
				distance[j].clusterID = trainSet[j].clusterID;
			}
			// ��BubbleSort������С��������(����,ѵ������ǩ)
			BubbleSort(train_Num, distance);
			// ͳ������Լ���ǩ�������ڽ���k����ǩ���ֵ�Ƶ�� ������Ƶ�����߱�ǩ ��Ԥ��ı�ǩ
			forecastSet[i].clusterID = CountLabel(&count, k, testSet[i].clusterID);
		}
		// ��ӡ��� 
		PrintResult(k, count);
		count = 0; //����
	}
}

int main()
{
	if (InputAndInitialize() == 0) {      //�ж��������������Ƿ�ɹ�
		return 0;
	}
	LoadData();
	PrintData();
	printf("\n\n���Լ�:%d��  ѵ����:%d��\n\n", text_Num, train_Num);
	Knn();
	system("pause");
	return 0;
}