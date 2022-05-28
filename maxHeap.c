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

//建立大根堆max heap
void AdjustDown(HPDataType* a, int n, int root)
{
	int child = root * 2 + 1;
	int parent = root;

	while (child < n)
	{
		// 选左右孩子中大的一个
		if (child + 1 < n && a[child + 1] > a[child])
		{
			child++;
		}
		//如果孩子大于父亲，进行调整交换 
		if (a[child] > a[parent])
		{
			Swap(&a[child], &a[parent]);
			parent = child;
			child = parent * 2 + 1;
		}
		//到这里就证明孩子不大于父亲，所以不需要继续调整了，直接跳出循环
		else
		{
			break;
		}
	}
}

//向上调整
void AdjustUp(HPDataType* a, int n, int child)
{
	assert(a);
	int parent = (child - 1) / 2;
	while (parent >= 0)
	{
	
		//如果孩子大于父亲，进行交换
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

// 堆的构建
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
	// 建堆： 从最后一个非叶子节点开始进行调整
	// 最后一个非叶子节点，按照规则： （最后一个位置下标 - 1） / 2
	for (int i = (n - 1 - 1) / 2; i >= 0; --i)
	{
		AdjustDown(hp->_data, hp->_size, i);
	}

}

// 堆的销毁
void HeapDestory(Heap* hp)
{
	assert(hp);
	free(hp->_data);
	hp->_data = NULL;
	hp->_capacity = 0;
	hp->_data = 0;
}

// 堆的插入
void HeapPush(Heap* hp, HPDataType x)
{
	assert(hp);
	//检查容量，满了就扩容
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
	//尾插
	hp->_data[hp->_size] = x;
	hp->_size++;
	AdjustUp(hp->_data, hp->_size, hp->_size - 1);
}

// 堆的删除，删除堆顶的数据
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

// 取堆顶的数据
HPDataType HeapTop(Heap* hp)
{
	assert(hp);
	return hp->_data[0];
}

// 堆的数据个数
int HeapSize(Heap* hp)
{
	assert(hp);
	return hp->_size;
}

// 堆的判空
int HeapEmpty(Heap* hp)
{
	assert(hp);
	return hp->_size == 0;
}

// TopK问题：找出N个数里面最大/最小的前K个问题。
// 比如：未央区排名前10的泡馍，西安交通大学王者荣耀排名前10的韩信，全国排名前10的李白。等等问题都是Topk问题，
// 需要注意：
// 找最大的前K个，建立K个数的小堆

// 找最小的前K个，建立K个数的大堆
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
	//随机生成1000个数存入数组，保证元素都小于1000
	for (size_t i = 0; i < n; ++i)
	{
		a[i] = rand() % 1000;
	}
	//确定10个最大的数
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