#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include "LinkList.h"
using namespace std;

// ð������ O(n^2) �����ֵһ�����ؽ���������档
// ����
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

// ѡ������ O(n^2) �ȽϵĶ࣬�������٣�ÿ���ҳ���Сֵ����������ǰ�棬�γ�����������������
// ����
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

// ��������O(n^2) ������+��������ÿ�ν���������һ��Ԫ�ز��뵽��������ȥ��
// ����ʵ�֣��Ƚϵö࣬������Ҳ�ࣻ����ʵ�֣��Ƚϵö࣬��������
template<typename T>
void insertionSort(vector<T>&arr) {
	for (int i = 1; i < arr.size(); i++) {
		for (int j = i; j > 0; j--) {
			if (arr[j] < arr[j - 1]) swap(arr[j], arr[j - 1]);
			else break;
		}
	}
}

//�鲢����O(nlogn)�����ݷ�Ϊ�������źõ����У���������ѡ����С��Ԫ�������ӵ������ݶε�ĩβ
/*
1����ռ䣬ʹ���СΪ�����Ѿ���������֮�ͣ��ÿռ�������źϲ�������У�
2�趨����ָ�룬���λ�÷ֱ�Ϊ�����Ѿ��������е���ʼλ�ã�
3�Ƚ�����ָ����ָ���Ԫ�أ�ѡ�����С��Ԫ�ط��뵽�ϲ��ռ䣬���ƶ�ָ�뵽��һλ�ã�
4�ظ����� 3 ֱ��ĳһָ��ﵽ����β��
5����һ����ʣ�µ�����Ԫ��ֱ�Ӹ��Ƶ��ϲ�����β��
*/

//����ʵ�֣��ݹ��,���Ҳ������ֵnumeric_limits<T>::max()��ʹ�ò���5ʡ�ԡ�
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
	//�����������������������ֵ����������������5����
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
	merge2(array, front, mid, end); //��ѡ���������ַ���
}


//�鲢���� ������ʵ�֣��ֶ���֮�Ե�����
template<class T>
void mergeSort(T arr[], int len) {
	T* a = arr;
	T* b = new T[len];
	for (int seg = 1; seg < len; seg += seg) {
		for (int start = 0; start < len; start += 2*seg) {
			int low = start, mid = min(start + seg, len), high = min(start + 2 * seg, len);
			int start1 = low, end1 = mid;//����ҿ����䣬����������
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


//�������� QuickSort ƽ��ʱ�临�Ӷ�O(nlogn)������Ӷ�O(n^2)����һ��ȹ鲢����죬 �ռ临�Ӷ�O(logn)��
/*
1ѡȡ������һ��ֵΪ��׼pivot;
2���÷���partition�㷨��С�ڵ���pivot��������pivotǰ�棬������pivot�������������棻
3�ݹ�ض�pivotǰ�����������в���1��2��
*/
template <class T>
void quickSort(T arr[], int front, int end) {
	if (front >= end) return;
	int idx_pivot = partition2(arr, front, end); //�˴���ѡ��������ַ���ʵ�ֵķ�����
	quickSort(arr, front, idx_pivot - 1);
	quickSort(arr, idx_pivot + 1,end);
}

template<class T> //�����ĵ�һ��ʵ�֣���ֻpivot��ǰ������Ĵ�С��Ƚϣ�ǰ����������ƣ�
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
template<class T>//�����ĵڶ���ʵ�֣�pivot�ֱ���ǰ���������Ƚϣ�ǰ�����ƣ�����ǰ�ƣ�
int partition2(T arr[], int front, int end) {
	T pivot = arr[end];//��end����ֵ����pivot��֮�����end����ֵΪ�գ����ظ�ֵ������һֱ��һ����ֵ��������pivot���
	while (front < end) {
		while (front<end && arr[front] <= pivot)front++;
		arr[end] = arr[front];
		while (front<end && arr[end] > pivot)end--;
		arr[front] = arr[end];
	}
	arr[front] = pivot;
	return front;
}

//�����ַ������������⣬����
template<class T>//�����ĵ�����ʵ�֣�pivot�ֱ���ǰ���������Ƚϣ�ǰ�����ƣ�����ǰ�ƣ�
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