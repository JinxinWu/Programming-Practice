#pragma once

#ifndef __LYSCLASSIFICATION_H
#define __LYSCLASSIFICATION_H
#define dimNum 4                   	// 维数
#define total 150                   // 总数据的数量
#define text_Num 50                 // 测试集数量
#define train_Num 100               // 训练集数量
#define KMAX 15                     // K的最大值

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

//存储鸢尾花数据的结构体
typedef struct {
	double sepalLength;             	// 花萼长度
	double sepalWidth;              	// 花萼宽度
	double petalLength;             	// 花瓣长度
	double petalWidth;              	// 花瓣宽度
	char type[20];                      // 存放花的种类
	int clusterID;                  	// 用于存放该点所属的簇群编号012
} Iris;

//存储距离的结构体
typedef struct {
	double value; // 距离数据
	int clusterID;    // 用于绑定训练集标签
} Distance;

Iris testSet[text_Num];	      // 测试集结构体数组
Iris forecastSet[text_Num];   // 保存预测标签的结果
Iris trainSet[train_Num];	  // 训练集结构体数组
Iris temp[total];			  // 临时存放数据结构体数组
Distance distance[train_Num]; // 存放距离结构体数组

/**
 * @brief 把不同种类的花分别转化成 0 1 2 标签
 * @param type  输入花的种类
 * @param label 输出转化的标签（指针实现）
 */
void Label012(char* type, int* label)
{
	if (strcmp(type, "Iris-setosa") == 0)
		*label = 0;
	if (strcmp(type, "Iris-versicolor") == 0)
		*label = 1;
	if (strcmp(type, "Iris-virginica") == 0)
		*label = 2;
}

/**
 * @brief 利用伪随机数打乱数据
 * @param iris
 * @param n
 */
void MakeRand(Iris iris[], int n)
{
	Iris t;
	int n1, n2;
	srand((unsigned int)time(NULL)); //获取随机数的种子
	for (int i = 0; i < n; ++i)
	{
		n1 = (rand() % n); //产生n以内的随机数  n是数组元素个数
		n2 = (rand() % n);
		// 若两随机数不相等，则下标为这两随机数的数组进行交换
		if (n1 != n2)
		{
			t = iris[n1];
			iris[n1] = iris[n2];
			iris[n2] = t;
		}
	}
}

/**
 * @brief 打开数据文件并预处理数据
 * @param path 数据文件的路径
 */
int InputAndInitialize()
{
	char fname[256];//文件名
	printf("请输入存放数据的文件名：");
	scanf("%s", fname);
	// 用于先存放150个数据后再打乱
	FILE* fp = fopen(fname, "rb");
	if (fp == NULL) {
		printf("不能打开输入的文件\n");
		return 0;
	}
	for (int i = 0; i < total; ++i)
	{
		fscanf(fp, "%lf,%lf,%lf,%lf,%s", &temp[i].sepalLength, &temp[i].sepalWidth, 
			                             &temp[i].petalLength, &temp[i].petalWidth, &temp[i].type);
		Label012(temp[i].type, &temp[i].clusterID);
	}
	MakeRand(temp, total); //打乱所有数据
	fclose(fp);
	fp = NULL;
	return 1; // 1表示数据读入成功
}

/**
 * @brief 把分割后的数据都打印出来  便于观察是否已经打乱
 */
void PrintData()
{
	printf("\n设置标签 -> 打乱 -> 按%d/%d分割\n", text_Num, train_Num);
	printf("数据如下:\n\n");
	printf("%d组测试集:\n", text_Num);
	for (int i = 0; i < text_Num; ++i)
		printf("%.2lf,%.2lf,%.2f,%.2lf,%d\n", testSet[i].sepalLength, testSet[i].sepalWidth,
			        testSet[i].petalLength, testSet[i].petalWidth, testSet[i].clusterID);
	printf("\n\n%d组训练集:\n", train_Num);
	for (int i = 0; i < train_Num; ++i)
		printf("%.2lf,%.2lf,%.2f,%.2lf,%d\n", trainSet[i].sepalLength, trainSet[i].sepalWidth, 
			       trainSet[i].petalLength, trainSet[i].petalWidth, trainSet[i].clusterID);
}

/**
 * @brief 加载数据  分割：测试text_Num组   训练train_Num组
 */
void LoadData()
{
	int n = 0, m = 0;
	for (int i = 0; i < total; i++)
	{
		// 先将TEST_SIZE个数据存入测试集
		if (i < text_Num)
		{
			testSet[n].sepalLength = temp[i].sepalLength;
			testSet[n].sepalWidth = temp[i].sepalWidth;
			testSet[n].petalLength = temp[i].petalLength;
			testSet[n].petalWidth = temp[i].petalWidth;
			testSet[n].clusterID = temp[i].clusterID;
			n++;
		}
		else // 剩下的数据存入训练集
		{
			trainSet[m].sepalLength = temp[i].sepalLength;
			trainSet[m].sepalWidth = temp[i].sepalWidth;
			trainSet[m].petalLength = temp[i].petalLength;
			trainSet[m].petalWidth = temp[i].petalWidth;
			trainSet[m].clusterID = temp[i].clusterID;
			m++;
		}
	}
}

/**
 * @brief 计算欧几里得距离
 * @param d1
 * @param d2
 * @param n 维数
 * @return double
 */
double EuclideanDistance(Iris i1, Iris i2)
{
	double result = 0.0;
	// 欧几里得距离
	result = pow(i1.sepalLength - i2.sepalLength, 2.0) + pow(i1.petalWidth - i2.petalWidth, 2.0)
		   + pow(i1.sepalLength - i2.sepalLength, 2.0) + pow(i1.petalWidth - i2.petalWidth, 2.0);
	result = sqrt(result);

	return result; //返回距离
}

/**
 * @brief 比较三个标签出现的频数
 * @param a
 * @param b
 * @param c
 * @return char 返回出现的频数最多的标签
 */
int CompareLabel(int a, int b, int c)
{
	if (a > b && a > c)
		return 0;
	if (b > a && b > c)
		return 1;
	if (c > a && c > b)
		return 2;
	return 0;
}

/**
 * @brief 统计与测试集距离最邻近的k个标签出现的频数
 * @param count 用于统计
 * @param k 前K值
 * @param clusterID 训练集的预测标签
 * @return 返回频数最高的标签
 */
int CountLabel(int* count, int k, int clusterID)
{
	int sum0 = 0, sum1 = 0, sum2 = 0; // 分别统计距离最邻近的三类标签出现的频数
	for (int i = 0; i < k; i++)
	{
		switch (distance[i].clusterID)
		{
		case 0:
			sum0++;
			break;
		case 1:
			sum1++;
			break;
		case 2:
			sum2++;
			break;
		}
	}
	// 检测出现频数最高的标签与测试集标签是否相等
	char maxLabel = CompareLabel(sum0, sum1, sum2);
	// 统计符合的数量
	if (maxLabel == clusterID)
		(*count)++;// 注意这是个指针
	return maxLabel;
}

/**
* @brief 冒泡排序算法给训练集距离排序
* @param n 排序个数
* @param ditance 距离的指针
*/
void BubbleSort(int n, Distance* distance)
{
	for (int i = 0; i < n - 1; ++i)
	{
		for (int j = 0; j < n - 1 - j; ++j)
		{
			if (distance[j].value > distance[j + 1].value)
			{
				double temp = distance[j].value;
				distance[j].value = distance[j + 1].value;
				distance[j + 1].value = temp;
				int m = distance[j].clusterID;    // 别忘了交换下标
				distance[j].clusterID = distance[j + 1].clusterID;
				distance[j + 1].clusterID = m;
			}
		}
	}
}

/**
 * @brief 打印结果
 * @param k K值
 * @param count 预测正确的总数量
 */
void PrintResult(int k, int count)
{
	printf("对比结果:\n");
	// 打印每个K值对应的概率
	printf("K = %d     P = %.2lf%%\n", k, (100.0 * count) / text_Num);
	printf("原有标签:");
	printf("[%d", testSet[0].clusterID);
	for (int i = 1; i < text_Num; ++i)
		printf(",%d", testSet[i].clusterID);
	printf("]\n");
	printf("预测标签:");
	printf("[%d", forecastSet[0].clusterID);
	for (int i = 1; i < text_Num; ++i)
		printf(",%d", forecastSet[i].clusterID);
	printf("]\n\n");
}



#endif // !__LYSCLASSIFICATION_H
