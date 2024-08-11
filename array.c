// 数组是一种线性数据结构 它将同类型元素存储在连续的内存空间中
// 我们将元素在数组中的位置称为索引 从本质上看 索引就是元素的偏移量 如果乘上元素长度 就得到了元素的地址偏移量
// 数组的优点：空间效率高 随机存取 缓存局部性 缺点：插入和删除效率低 长度固定 易造成空间浪费
// 下面给出数组常用操作的代码实现：

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>

/*初始化数组*/
void initArray(int** array, int size)
{
	// 使用二级指针存储数组名 再让数组名指向开辟出的数组的首地址
	*array = (int*)malloc(sizeof(int) * size);
	// 检查
	if (!*array)
	{
		perror("memory allocation failed");
		exit(1);
	}
	// 将开辟出的数组进行初始化
	for (int i = 0; i < size; ++i)
	{
		(*array)[i] = 0;
	}
}

/*遍历数组*/
int traverse(const int* array, int size)
{
	int count = 0;
	for (int i = 0; i < size; ++i)
	{
		count += array[i];
	}
	return count;
}

/*打印数组*/
void printArray(const int* array, int size)
{
	printf("array: ");
	for (int i = 0; i < size; ++i)
	{
		printf("%d ", array[i]);
	}
	printf("\n");
}

/*随机访问数组元素*/
int randomAccess(const int* array, int size)
{
	// 设置随机数种子
	srand((unsigned int)time(NULL));
	// 获取随机索引
	int randomIndex = rand() % size; // 注意：rand()%size的范围是[0,size) 左闭右开 刚好是符合数组索引范围的
	return array[randomIndex];
}

/*插入元素*/
void insertItem(int* array, int size, int insertIndex, int insertNum)
{
	// 将插入索引位置(包含)以后的元素全部向后移动一位
	if (insertIndex >= 0 && insertIndex <= size)
	{
		for (int i = size - 1; i > insertIndex; --i)
		{
			array[i] = array[i - 1]; // 为了不使用中间变量 采用倒序方式
		}
		// 插入元素
		array[insertIndex] = insertNum;
	}
}

/*删除元素*/
void removeItem(int* array, int size, int removeIndex)
{
	if (removeIndex >= 0 && removeIndex < size)
	{
		// 将删除索引位置以后的元素全部向前移动一位
		for (int i = removeIndex; i < size - 1; ++i)
		{
			array[i] = array[i + 1];
		}
		array[size - 1] = 0; // 将最后一个元素置为0
	}
}

/*查找指定元素(线性查找)*/
int find(const int* array, int size, int target)
{
	for (int i = 0; i < size; ++i)
	{
		if (array[i] == target)
		{
			return i; // 返回该元素的索引
		}
	}
	return -1; // 未找到 返回负数
}

/*扩容数组*/
int* extend(int* array, int size, int extension)
{
	// 计算新的数组大小
	int newSize = size + extension;
	// 开辟新数组的内存空间
	int* newArray = (int*)malloc(sizeof(int) * newSize);
	// 检查 若开辟失败 newArray指向一个空地址 即newArray变为一个空指针
	if (!newArray)
	{
		perror("memory allocation failed");
		exit(1);
	}
	// 将原数组元素复制到新数组
	for (int i = 0; i < size; ++i)
	{
		newArray[i] = array[i];
	}
	// 初始化扩展后的空间
	for (int i = size; i < newSize; ++i)
	{
		newArray[i] = 0;
	}
	// 释放原数组空间
	free(array);
	return newArray;
}

/*检验*/
int main()
{
	// 初始化数组
	int size = 5;
	int* myarray;
	initArray(&myarray, size);
	for (int i = 0; i < size; ++i)
	{
		myarray[i] = i;
	}
	// 遍历数组
	int count = traverse(myarray, size);
	printf("数组元素之和: %d\n", count);
	// 打印数组
	printArray(myarray, size);
	// 随机访问数组元素
	int randomaccess = randomAccess(myarray, size);
	printf("随机访问数组元素: %d\n", randomaccess);
	// 插入元素
	int insertindex = 3;
	int insertnum = 5;
	insertItem(myarray, size, insertindex, insertnum);
	printf("在索引为3处插入元素5后的数组:\n");
	printArray(myarray, size);
	// 删除元素
	int removeindex = 1;
	removeItem(myarray, size--, removeindex);
	printf("删除索引为1的元素后的数组:\n");
	printArray(myarray, size);
	// 查找指定元素
	int targetNum = 5;
	int targetIndex = find(myarray, size, targetNum);
	printf("数组中元素5的索引为: %d\n", targetIndex);
	// 扩充数组
	int extension = 3;
	myarray = extend(myarray, size, extension);
	size += extension;
	printf("扩充3个元素空间后的数组:\n");
	printArray(myarray, size);
	// 释放内存
	free(myarray);
	return 0;
}