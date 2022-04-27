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

// Knn算法核心代码
void Knn()
{
	int count = 0;
	for (int k = 1; k <= KMAX; ++k)
	{
		for (int i = 0; i < text_Num; i++) // 遍历测试集
		{
			for (int j = 0; j < train_Num; j++) // 遍历训练集
			{
				// 把计算欧几里得距离依次存入distance结构体数组的value中 
				distance[j].value = EuclideanDistance(testSet[i], trainSet[j]);
				// 将训练集标签与计算好的距离绑定在一块 
				distance[j].clusterID = trainSet[j].clusterID;
			}
			// 用BubbleSort函数从小到大排序(距离,训练集标签)
			BubbleSort(train_Num, distance);
			// 统计与测试集标签距离最邻近的k个标签出现的频数 并返回频数最后高标签 即预测的标签
			forecastSet[i].clusterID = CountLabel(&count, k, testSet[i].clusterID);
		}
		// 打印结果 
		PrintResult(k, count);
		count = 0; //重置
	}
}

int main()
{
	if (InputAndInitialize() == 0) {      //判断数据样本读入是否成功
		return 0;
	}
	LoadData();
	PrintData();
	printf("\n\n测试集:%d组  训练集:%d组\n\n", text_Num, train_Num);
	Knn();
	system("pause");
	return 0;
}