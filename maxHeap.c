#include"maxHeap.h"

//typedef int HPDataType;
//typedef struct Heap
//{
//	HPDataType* _data;
//	int _size;
//	int _capacity;
//}Heap;


void Swap(HPDataType* x1, HPDataType* x2)
{
	HPDataType temp = *x1;
	*x1 = *x2;
	*x2 = temp;
}

//���������max heap
void AdjustDown(HPDataType* a, int n, int root)
{
	int child = root * 2 + 1;
	int parent = root;

	while (child < n)
	{
		// ѡ���Һ����д��һ��
		if (child + 1 < n && a[child + 1] > a[child])
		{
			child++;
		}
		//������Ӵ��ڸ��ף����е������� 
		if (a[child] > a[parent])
		{
			Swap(&a[child], &a[parent]);
			parent = child;
			child = parent * 2 + 1;
		}
		//�������֤�����Ӳ����ڸ��ף����Բ���Ҫ���������ˣ�ֱ������ѭ��
		else
		{
			break;
		}
	}
}

//���ϵ���
void AdjustUp(HPDataType* a, int n, int child)
{
	assert(a);
	int parent = (child - 1) / 2;
	while (parent >= 0)
	{
	
		//������Ӵ��ڸ��ף����н���
		if (a[parent] < a[child])
		{
			Swap(&a[child], &a[parent]);
			child = parent;
			parent = (child - 1) / 2;
		}
		else
		{
			break;
		}
	}
}

// �ѵĹ���
void HeapCreate(Heap* hp, HPDataType* a, int n)
{
	assert(hp && a);
	hp->_data = (HPDataType*)malloc(sizeof(HPDataType) * (n));
	if (!hp->_data)
	{
		exit(-1);
	}
	for (int i = 0; i < n; i++)
	{
		hp->_data[i] = a[i];
	}
	hp->_capacity = n;
	hp->_size = n;
	// ���ѣ� �����һ����Ҷ�ӽڵ㿪ʼ���е���
	// ���һ����Ҷ�ӽڵ㣬���չ��� �����һ��λ���±� - 1�� / 2
	for (int i = (n - 1 - 1) / 2; i >= 0; --i)
	{
		AdjustDown(hp->_data, hp->_size, i);
	}

}

// �ѵ�����
void HeapDestory(Heap* hp)
{
	assert(hp);
	free(hp->_data);
	hp->_data = NULL;
	hp->_capacity = 0;
	hp->_data = 0;
}

// �ѵĲ���
void HeapPush(Heap* hp, HPDataType x)
{
	assert(hp);
	//������������˾�����
	if (hp->_capacity == hp->_size)
	{
		HPDataType* temp = (HPDataType*)realloc(hp->_data, sizeof(HPDataType) * hp->_capacity * 2);
		if (!temp)
		{
			exit(-1);
		}
		hp->_data = temp;
		hp->_capacity *= 2;
	}
	//β��
	hp->_data[hp->_size] = x;
	hp->_size++;
	AdjustUp(hp->_data, hp->_size, hp->_size - 1);
}

// �ѵ�ɾ����ɾ���Ѷ�������
void HeapPop(Heap* hp)
{
	assert(hp);
	if (HeapEmpty(hp))
	{
		return;
	}
	Swap(&hp->_data[0], &hp->_data[hp->_size - 1]);
	hp->_size--;
	AdjustDown(hp->_data, hp->_size, 0);
}

// ȡ�Ѷ�������
HPDataType HeapTop(Heap* hp)
{
	assert(hp);
	return hp->_data[0];
}

// �ѵ����ݸ���
int HeapSize(Heap* hp)
{
	assert(hp);
	return hp->_size;
}

// �ѵ��п�
int HeapEmpty(Heap* hp)
{
	assert(hp);
	return hp->_size == 0;
}

// TopK���⣺�ҳ�N�����������/��С��ǰK�����⡣
// ���磺δ��������ǰ10�����ɣ�������ͨ��ѧ������ҫ����ǰ10�ĺ��ţ�ȫ������ǰ10����ס��ȵ����ⶼ��Topk���⣬
// ��Ҫע�⣺
// ������ǰK��������K������С��

// ����С��ǰK��������K�����Ĵ��
void PrintTopK(int* a, int n, int k)
{
	Heap hp;
	HeapCreate(&hp, a, k);
	for(int i = k; i < n; i++)
	{
		if (a[i] < HeapTop(&hp))
		{
			HeapPop(&hp);
			HeapPush(&hp, a[i]);
		}
	}
	for (int i = 0; i < k; i++)
	{
		printf("%d ", HeapTop(&hp));
		HeapPop(&hp);
	}
}
void TestTopk()
{

	int n = 1000;
	int* a = (int*)malloc(sizeof(int) * n);
	if (!a)
	{
		exit(-1);
	}
	srand(time(0));
	//�������1000�����������飬��֤Ԫ�ض�С��1000
	for (size_t i = 0; i < n; ++i)
	{
		a[i] = rand() % 1000;
	}
	//ȷ��10��������
	a[5] = -1;
	a[121] = -2;
	a[531] = -3;
	a[521] = -4;
	a[115] = -5;
	a[235] = -6;
	a[99] = -7;
	a[76] = -8;
	a[423] = -9;
	a[44] = -10;
	PrintTopK(a, n, 10);
}