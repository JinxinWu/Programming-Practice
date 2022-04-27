#pragma once

#ifndef __LYSCLASSIFICATION_H
#define __LYSCLASSIFICATION_H
#define dimNum 4                   	// ά��
#define total 150                   // �����ݵ�����
#define text_Num 50                 // ���Լ�����
#define train_Num 100               // ѵ��������
#define KMAX 15                     // K�����ֵ

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

//�洢�β�����ݵĽṹ��
typedef struct {
	double sepalLength;             	// ���೤��
	double sepalWidth;              	// ������
	double petalLength;             	// ���곤��
	double petalWidth;              	// ������
	char type[20];                      // ��Ż�������
	int clusterID;                  	// ���ڴ�Ÿõ������Ĵ�Ⱥ���012
} Iris;

//�洢����Ľṹ��
typedef struct {
	double value; // ��������
	int clusterID;    // ���ڰ�ѵ������ǩ
} Distance;

Iris testSet[text_Num];	      // ���Լ��ṹ������
Iris forecastSet[text_Num];   // ����Ԥ���ǩ�Ľ��
Iris trainSet[train_Num];	  // ѵ�����ṹ������
Iris temp[total];			  // ��ʱ������ݽṹ������
Distance distance[train_Num]; // ��ž���ṹ������

/**
 * @brief �Ѳ�ͬ����Ļ��ֱ�ת���� 0 1 2 ��ǩ
 * @param type  ���뻨������
 * @param label ���ת���ı�ǩ��ָ��ʵ�֣�
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
 * @brief ����α�������������
 * @param iris
 * @param n
 */
void MakeRand(Iris iris[], int n)
{
	Iris t;
	int n1, n2;
	srand((unsigned int)time(NULL)); //��ȡ�����������
	for (int i = 0; i < n; ++i)
	{
		n1 = (rand() % n); //����n���ڵ������  n������Ԫ�ظ���
		n2 = (rand() % n);
		// �������������ȣ����±�Ϊ�����������������н���
		if (n1 != n2)
		{
			t = iris[n1];
			iris[n1] = iris[n2];
			iris[n2] = t;
		}
	}
}

/**
 * @brief �������ļ���Ԥ��������
 * @param path �����ļ���·��
 */
int InputAndInitialize()
{
	char fname[256];//�ļ���
	printf("�����������ݵ��ļ�����");
	scanf("%s", fname);
	// �����ȴ��150�����ݺ��ٴ���
	FILE* fp = fopen(fname, "rb");
	if (fp == NULL) {
		printf("���ܴ�������ļ�\n");
		return 0;
	}
	for (int i = 0; i < total; ++i)
	{
		fscanf(fp, "%lf,%lf,%lf,%lf,%s", &temp[i].sepalLength, &temp[i].sepalWidth, 
			                             &temp[i].petalLength, &temp[i].petalWidth, &temp[i].type);
		Label012(temp[i].type, &temp[i].clusterID);
	}
	MakeRand(temp, total); //������������
	fclose(fp);
	fp = NULL;
	return 1; // 1��ʾ���ݶ���ɹ�
}

/**
 * @brief �ѷָ������ݶ���ӡ����  ���ڹ۲��Ƿ��Ѿ�����
 */
void PrintData()
{
	printf("\n���ñ�ǩ -> ���� -> ��%d/%d�ָ�\n", text_Num, train_Num);
	printf("��������:\n\n");
	printf("%d����Լ�:\n", text_Num);
	for (int i = 0; i < text_Num; ++i)
		printf("%.2lf,%.2lf,%.2f,%.2lf,%d\n", testSet[i].sepalLength, testSet[i].sepalWidth,
			        testSet[i].petalLength, testSet[i].petalWidth, testSet[i].clusterID);
	printf("\n\n%d��ѵ����:\n", train_Num);
	for (int i = 0; i < train_Num; ++i)
		printf("%.2lf,%.2lf,%.2f,%.2lf,%d\n", trainSet[i].sepalLength, trainSet[i].sepalWidth, 
			       trainSet[i].petalLength, trainSet[i].petalWidth, trainSet[i].clusterID);
}

/**
 * @brief ��������  �ָ����text_Num��   ѵ��train_Num��
 */
void LoadData()
{
	int n = 0, m = 0;
	for (int i = 0; i < total; i++)
	{
		// �Ƚ�TEST_SIZE�����ݴ�����Լ�
		if (i < text_Num)
		{
			testSet[n].sepalLength = temp[i].sepalLength;
			testSet[n].sepalWidth = temp[i].sepalWidth;
			testSet[n].petalLength = temp[i].petalLength;
			testSet[n].petalWidth = temp[i].petalWidth;
			testSet[n].clusterID = temp[i].clusterID;
			n++;
		}
		else // ʣ�µ����ݴ���ѵ����
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
 * @brief ����ŷ����þ���
 * @param d1
 * @param d2
 * @param n ά��
 * @return double
 */
double EuclideanDistance(Iris i1, Iris i2)
{
	double result = 0.0;
	// ŷ����þ���
	result = pow(i1.sepalLength - i2.sepalLength, 2.0) + pow(i1.petalWidth - i2.petalWidth, 2.0)
		   + pow(i1.sepalLength - i2.sepalLength, 2.0) + pow(i1.petalWidth - i2.petalWidth, 2.0);
	result = sqrt(result);

	return result; //���ؾ���
}

/**
 * @brief �Ƚ�������ǩ���ֵ�Ƶ��
 * @param a
 * @param b
 * @param c
 * @return char ���س��ֵ�Ƶ�����ı�ǩ
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
 * @brief ͳ������Լ��������ڽ���k����ǩ���ֵ�Ƶ��
 * @param count ����ͳ��
 * @param k ǰKֵ
 * @param clusterID ѵ������Ԥ���ǩ
 * @return ����Ƶ����ߵı�ǩ
 */
int CountLabel(int* count, int k, int clusterID)
{
	int sum0 = 0, sum1 = 0, sum2 = 0; // �ֱ�ͳ�ƾ������ڽ��������ǩ���ֵ�Ƶ��
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
	// ������Ƶ����ߵı�ǩ����Լ���ǩ�Ƿ����
	char maxLabel = CompareLabel(sum0, sum1, sum2);
	// ͳ�Ʒ��ϵ�����
	if (maxLabel == clusterID)
		(*count)++;// ע�����Ǹ�ָ��
	return maxLabel;
}

/**
* @brief ð�������㷨��ѵ������������
* @param n �������
* @param ditance �����ָ��
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
				int m = distance[j].clusterID;    // �����˽����±�
				distance[j].clusterID = distance[j + 1].clusterID;
				distance[j + 1].clusterID = m;
			}
		}
	}
}

/**
 * @brief ��ӡ���
 * @param k Kֵ
 * @param count Ԥ����ȷ��������
 */
void PrintResult(int k, int count)
{
	printf("�ԱȽ��:\n");
	// ��ӡÿ��Kֵ��Ӧ�ĸ���
	printf("K = %d     P = %.2lf%%\n", k, (100.0 * count) / text_Num);
	printf("ԭ�б�ǩ:");
	printf("[%d", testSet[0].clusterID);
	for (int i = 1; i < text_Num; ++i)
		printf(",%d", testSet[i].clusterID);
	printf("]\n");
	printf("Ԥ���ǩ:");
	printf("[%d", forecastSet[0].clusterID);
	for (int i = 1; i < text_Num; ++i)
		printf(",%d", forecastSet[i].clusterID);
	printf("]\n\n");
}



#endif // !__LYSCLASSIFICATION_H
