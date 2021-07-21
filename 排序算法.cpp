#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include "LinkList.h"
using namespace std;

// 冒泡排序 O(n^2) 将最大值一步步地交换到最后面。
// 数组
template<class T>
void bubbleSort(T arr[],int len) {
	
	for (int i = 0; i < len; i++) {
		bool flag = true;
		for (int j = 0; j < len - 1 - i; j++) {
			if (arr[j] > arr[j + 1]) {
				swap(arr[j], arr[j + 1]); 
				flag = false;
			}	
		}
		if (flag == true) break;
	}
}

// 选择排序 O(n^2) 比较的多，交换的少，每轮找出最小值，交换到最前面，形成有序区和无序区。
// 数组
template<typename T>
void selectionSort(vector<T>& arr) {
	for (int i = 0; i < arr.size(); i++) {
		int min = i;
		for (int j = i+1; j < arr.size(); j++) {
			if (arr[j] < arr[min]) min = j;
		}
		swap(arr[i], arr[min]);
	}
}

// 插入排序O(n^2) 有序区+无序区，每次将无序区第一个元素插入到有序区中去，
// 数组实现：比较得多，交换得也多；链表实现：比较得多，交换得少
template<typename T>
void insertionSort(vector<T>&arr) {
	for (int i = 1; i < arr.size(); i++) {
		for (int j = i; j > 0; j--) {
			if (arr[j] < arr[j - 1]) swap(arr[j], arr[j - 1]);
			else break;
		}
	}
}

//归并排序O(nlogn)把数据分为两段已排好的序列，从两端中选出最小的元素逐个添加到新数据段的末尾
/*
1申请空间，使其大小为两个已经排序序列之和，该空间用来存放合并后的序列；
2设定两个指针，最初位置分别为两个已经排序序列的起始位置；
3比较两个指针所指向的元素，选择相对小的元素放入到合并空间，并移动指针到下一位置；
4重复步骤 3 直到某一指针达到序列尾；
5将另一序列剩下的所有元素直接复制到合并序列尾。
*/

//数组实现，递归版,左右插入最大值numeric_limits<T>::max()，使得步骤5省略。
template<class T>
void merge1(vector<T>&array, int front, int mid, int end) {
	// preconditions:
	// array[front...mid] is sorted
	// array[mid+1 ... end] is sorted
	// Copy Array[front ... mid] to LeftSubArray
	// Copy Array[mid+1 ... end] to RightSubArray
	vector<T> LeftSubArray(array.begin() + front, array.begin() + mid + 1);
	vector<T> RightSubArray(array.begin() + mid + 1, array.begin() + end + 1);
	LeftSubArray.insert(LeftSubArray.end(), numeric_limits<T>::max());
	RightSubArray.insert(RightSubArray.end(), numeric_limits<T>::max());
	int idxLeft = 0, idxRight = 0;
	for (int i = front; i <= end; i++) {
		if (LeftSubArray[idxLeft] <= RightSubArray[idxRight]) {
			array[i] = LeftSubArray[idxLeft];
			idxLeft++;
		}
		else {
			array[i] = RightSubArray[idxRight];
			idxRight++; 
		}
	}
}

template <class T>
void merge2(vector<T> &Array, int front, int mid, int end) {
	//another implementation.
	//不在左右子数组最后插入最大值，而是如上述步骤5所述
	vector<T>LeftSubArray(Array.begin() + front, Array.begin() + mid + 1);
	vector<T>RightSubArray(Array.begin() + mid + 1, Array.begin() + end + 1);
	int idxLeft = 0, idxRight = 0;
	int i = front;
	while (idxLeft < (mid - front + 1) && idxRight < (end - mid)) {
		Array[i++] = LeftSubArray[idxLeft] < RightSubArray[idxRight] 
		  		   ? LeftSubArray[idxLeft++] : RightSubArray[idxRight++];
	}
	while (idxLeft < (mid - front + 1)) {
		Array[i++] = LeftSubArray[idxLeft++];
	}
	while (idxRight < (end - mid)) {
		Array[i++] = RightSubArray[idxRight++];
	}
}

template<class T>
void mergeSort(vector<T>&array, int front, int end) {
	if (front >= end) return;
	int mid = (front + end) / 2;
	mergeSort(array, front, mid);
	mergeSort(array, mid + 1, end);
	merge2(array, front, mid, end); //可选择上面两种方法
}


//归并排序 迭代版实现，分而治之自底向上
template<class T>
void mergeSort(T arr[], int len) {
	T* a = arr;
	T* b = new T[len];
	for (int seg = 1; seg < len; seg += seg) {
		for (int start = 0; start < len; start += 2*seg) {
			int low = start, mid = min(start + seg, len), high = min(start + 2 * seg, len);
			int start1 = low, end1 = mid;//左闭右开区间，分两个部分
			int start2 = mid, end2 = high;
			int k = low;
			while (start1 < end1 && start2 < end2) {
				b[k++] = a[start1] < a[start2] ? a[start1++] : a[start2++];
			}
			while (start1 < end1) {
				b[k++] = a[start1++];
			}
			while (start2 < end2) {
				b[k++] = a[start2++];
			}
		}
		T* temp = a;
		a = b;
		b = temp;
	}
	if (a != arr) {
		for (int i = 0; i < len; i++)
			b[i] = a[i];
		b = a;
		delete[] b;

	}
}


//快速排序 QuickSort 平均时间复杂度O(nlogn)，最坏复杂度O(n^2)，但一般比归并排序快， 空间复杂度O(logn)；
/*
1选取数组中一个值为基准pivot;
2采用分区partition算法将小于等于pivot的数放在pivot前面，将大于pivot的数放在它后面；
3递归地对pivot前后两个区进行步骤1、2。
*/
template <class T>
void quickSort(T arr[], int front, int end) {
	if (front >= end) return;
	int idx_pivot = partition2(arr, front, end); //此处可选择采用哪种方法实现的分区；
	quickSort(arr, front, idx_pivot - 1);
	quickSort(arr, idx_pivot + 1,end);
}

template<class T> //分区的第一种实现，即只pivot与前面的区的大小相比较，前区不断向后移；
int partition1(T arr[], int front, int end) {
	T pivot = arr[end];
	int idx_pivot = end;
	while (front < end) {
		if (arr[front] <= pivot) front++;
		else swap(arr[front], arr[--end]);
	}
	swap(arr[end], arr[idx_pivot]);
	return end;
}
7
template<class T>//分区的第二种实现，pivot分别与前后两个区比较，前区后移，后区前移；
int partition2(T arr[], int front, int end) {
	T pivot = arr[end];//把end处的值赋给pivot，之后假设end处的值为空，或重复值，往后一直有一个空值，最终由pivot填补。
	while (front < end) {
		while (front<end && arr[front] <= pivot)front++;
		arr[end] = arr[front];
		while (front<end && arr[end] > pivot)end--;
		arr[front] = arr[end];
	}
	arr[front] = pivot;
	return front;
}

//第三种方法还存在问题，不对
template<class T>//分区的第三种实现，pivot分别与前后两个区比较，前区后移，后区前移；
int partition3(T arr[], int front, int end) {
	T pivot = arr[end];//
	while (front < end) {
		while (front<end && arr[front] <= pivot)front++;
		while (front<end && arr[end] > pivot)end--;
		swap(arr[front],arr[end]);
	}
	return end;
}


int main() {
	int arr[] = { 2,4,1,3 };
	//LinkList<int> L = LinkList<int>::LinkList();

	int len = (int) sizeof(arr) / sizeof(*arr);
	vector<int> v(arr,arr+len);
	quickSort(arr,0,len-1);
	for (int i = 0; i < len; i++)
		cout << arr[i] << ' ';
	cout << endl;
	float arrf[] = { 17.5, 19.1, 0.6, 1.9, 10.5, 12.4, 3.8, 19.7, 1.5, 25.4, 28.6, 4.4, 23.8, 5.4 };
	len = (float) sizeof(arrf) / sizeof(*arrf);
	vector<float> vf(arrf, arrf + len);
	quickSort(arrf,0,len-1);
	for (int i = 0; i < len; i++)
		cout << arrf[i] << ' ';
	cout << endl;

	vector<int>a(5, 1);
	a.insert(a.begin()+1,10);
	for(vector<int>::iterator t =  a.begin();t!=a.end();t++)cout << *t<<" ";
	return 0;
}