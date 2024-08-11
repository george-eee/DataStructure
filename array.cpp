// 数组是一种线性数据结构 它将同类型元素存储在连续的内存空间中
// 我们将元素在数组中的位置称为索引 从本质上看 索引就是元素的偏移量 如果乘上元素长度 就得到了元素的地址偏移量
// 数组的优点：空间效率高 随机存取 缓存局部性 缺点：插入和删除效率低 长度固定 易造成空间浪费
// 下面给出数组常用操作的代码实现：

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

/*初始化数组*/
void initArray(int*& array, int size) {
	// 使用new开辟内存空间 自动初始化为0
	array = new int[size]();
	// 检查
	if (!array) {
		cerr << "memory allocation failed" << endl;
		exit(1);
	}
}

/*遍历数组*/
int traverse(const int* array, int size) {
	int count = 0;
	for (int i = 0; i < size; ++i) {
		count += array[i];
	}
	return count;
}

/*打印数组*/
void printArray(const int* array, int size) {
	cout << "array: ";
	for (int i = 0; i < size; ++i) {
		cout << array[i] << " ";
	}
	cout << endl;
}

/*随机访问数组元素*/
int randomAccess(const int* array, int size) {
	// 设置随机数种子
	srand((unsigned int)time(NULL));
	// 获取随机索引
	int randomIndex = rand() % size;
	return array[randomIndex];
}

/*插入元素*/
void insertItem(int*& array, int& size, int insertIndex, int insertNum) {
	// 将插入索引位置(包含)以后的元素全部向后移动一位
	if (insertIndex >= 0 && insertIndex <= size) {
		for (int i = size - 1; i > insertIndex; --i) {
			array[i] = array[i - 1];// 为了不使用中间变量 采用倒序方式
		}
		// 插入元素
		array[insertIndex] = insertNum;
	}
}

/*删除元素*/
void removeItem(int*& array, int& size, int removeIndex) {
	if (removeIndex >= 0 && removeIndex < size) {
		// 将删除索引位置以后的元素全部向前移动一位
		for (int i = removeIndex; i < size - 1; ++i) {
			array[i] = array[i + 1];
		}
		// 将最后一个元素设置为0
		array[size - 1] = 0;
		// 数组大小-1
		--size;
	}
}

/*查找指定元素(线性查找)*/
int find(const int* array, int size, int target) {
	for (int i = 0; i < size; ++i) {
		if (array[i] == target) {
			return i;// 返回元素索引
		}
	}
	return -1;// 未找到 返回负数
}

/*扩容数组*/
void extend(int*& array, int& size, int extension) {
	// 开辟新数组的内存空间(默认初始化为0)
	int* newArray = new int[size + extension]();
	// 检查是否开辟失败
	if (!newArray) {
		cerr << "memory allocation failed" << endl;
		exit(1);
	}
	// 将原数组的元素复制到新数组
	for (int i = 0; i < size; ++i) {
		newArray[i] = array[i];
	}
	// 释放原数组空间
	delete[] array;
	// 更新数组信息
	array = newArray;
	size += extension;
}

/*检验*/
int main() {
	// 初始化数组
	int size = 5;
	int* myarray = nullptr;
	initArray(myarray, size);
	for (int i = 0; i < size; ++i) {
		myarray[i] = i;
	}
	// 遍历数组
	int count = traverse(myarray, size);
	cout << "数组元素之和: " << count << endl;
	// 打印数组
	printArray(myarray, size);
	// 随机访问数组元素
	int randomaccess = randomAccess(myarray, size);
	cout << "随机访问数组元素: " << randomaccess << endl;
	// 插入元素
	int insertindex = 3;
	int insertnum = 5;
	insertItem(myarray, size, insertindex, insertnum);
	cout << "在索引为3处插入元素5后的数组:\n";
	printArray(myarray, size);
	// 删除元素
	int removeindex = 1;
	removeItem(myarray, size, removeindex);
	cout << "删除索引为1的元素后的数组:\n";
	printArray(myarray, size);
	// 查找指定元素
	int targetNum = 5;
	int targetIndex = find(myarray, size, targetNum);
	cout << "数组中元素5的索引为: " << targetIndex << endl;
	// 扩充数组
	int extension = 3;
	extend(myarray, size, extension);
	cout << "扩充3个元素空间后的数组:\n";
	printArray(myarray, size);
	// 释放内存
	delete[] myarray;
	return 0;
}