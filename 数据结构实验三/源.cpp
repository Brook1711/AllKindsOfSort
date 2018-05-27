#include<iostream>
#include<time.h>
#include <iomanip>  
#include<Windows.h>
const int MaxSize = 100;
using namespace std;
template<class T>
class AllKindsOfSort
{
private:
	T arr[MaxSize];//源数据
	T temp;//哨兵
	int N;
public:
	void Print()
	{
		for (int i = 0; i < N; i++)
		{
			cout << arr[i] << " ";
		}
		cout << endl;
	}
	void InsertSort(int &movements, int &comparing);
	void ShellInsert(int &movements, int &comparing);
	void BubbleSort(int &movements, int &comparing);
	int Partion(int &movements, int &comparing,int first, int end);
	void QueckSort(int &movements, int &comparing, int i,int j);
	void SelectSort(int &movements, int &comparing);
	void Sifit(int &movements, int &comparing, int k, int m);
	void HeapSort(int &movements, int &comparing);

	void Creat(T a[], int n)//初始化数组
	{
		if (n > MaxSize)
		{
			throw "out of range!!!!!!!!!!!input something small!!!!!!!!!o(*≧▽≦)ツ┏━┓";
		}
		N = n;//初始化数组个数
		for (int i = 0; i < n; i++)
			arr[i] = a[i];
	}
	AllKindsOfSort()
	{
		N = 0;
	}
};

template<class T>
void AllKindsOfSort<T>::InsertSort(int &movements, int &comparing)
{
	for (int i = 1; i < N; i++)//i从1-(n-1)循环，共n-1趟排序
	{
		if (arr[i] < arr[i - 1])
		{
			temp = arr[i];//将待插入的值储存到哨兵中
			movements++;
			int j = i - 1;//确定向前寻找的第一个数的下标
			for (; temp < arr[j]; j--)//从j处向前查找并不断将大于r[j]的元素向后覆盖
			{
				comparing++;//比较一次
				movements++;//移动一次
				arr[j + 1] = arr[j];//直到找到比哨兵的值更小的值前一直将“空位”前移
			}
			arr[j + 1] = temp;//最终将两个相同的数中的一个变为哨兵的值
			movements++;
		}
		comparing++;//每进行一趟循环比较次数增加一
	}
}

template<class T>
void AllKindsOfSort<T>::ShellInsert(int & movements, int & comparing)
{
	for (int d = N / 2; d >= 1; d = d / 2)//以d为增量，不停“分割”数组，对分离出来的数组进行插入排序
	{
		for (int i = d; i < N; i++)//对“分割”出来的以d为增量的数组进行一次插入排序并且为一趟希尔排序
		{
			if (arr[i] < arr[i - d])//发现插入的新数小于队列中的最大数
			{
				temp = arr[i];//暂存到哨兵中
				movements++;
				int j = i - d;//确定开始向前寻找的第一个数的下标
				for (; j >= 0 && temp < arr[j]; j -= d)
				{
					arr[j + d] = arr[j];//只要哨兵一直小于j处元素的值，就将j处的数值向后移动
					comparing++;//每移动一个数比较一次
					movements++;//移动一次
				}
				arr[j + d] = temp;//用哨兵填补空位
				movements++;
			}
			comparing++;//每插入一个数比较一次
		}
		//至此一趟希尔排序完成
	}
}

template<class T>
void AllKindsOfSort<T>::BubbleSort(int & movements, int & comparing)
{
	int pos = N - 1;//初始化无序元素的范围
	while (pos != 0)//若无序边界到了起点则停止冒泡
	{
		int bound = pos;//提供冒泡边界
		pos = 0;//初始化边界为0
		for (int i = 0; i < bound; i++)
		{
			if (arr[i] > arr[i + 1])//若紧邻的后面的元素大于i处元素则不进行操作且比较次数加一
			{
				temp = arr[i];
				arr[i] = arr[i + 1];
				arr[i + 1] = temp;//以上为利用哨兵进行元素交换
				pos = i;//交换过的下界为有序边界，并在每一次循环中更新
				movements += 3;//完成一次交换操作后移动次数加一
			}
			comparing++;
		}
	}
}

template<class T>
int AllKindsOfSort<T>::Partion(int & movements, int & comparing, int first, int end)
{
	int i = first; //确定左区分界
	int j = end; //确定右区分界
	temp = arr[i];//暂存第一个数为基准元素
	movements++;
	while (i < j)
	{
		while ((i < j) && (arr[j] >= temp))
		{
			j--;//直到在基准元素右侧找到小于基准元素的元素之前右边界不断缩紧，每一次比较次数加一
			comparing++;
		}
		arr[i] = arr[j];//若找到某数小于基准元素则赋值为左界的值，可以看作“空穴”从i处交换到j处。移动数加一
		movements++;
		while ((i < j) && ((arr[j] <= temp)))
		{
			i++;//直到在基准元素左侧找到大于基准元素的元素之前左界边界不断缩紧，每一次比较次数加一
			comparing++;
		}
		arr[j] = arr[i];//若找到某数大于基准元素则赋值为右界的值，可以看作“空穴”从i处交换到j处。移动数加一
	}
	arr[i] = temp;//可看作是哨兵最终将空穴填满
	movements++;
	return i;//将找到的哨兵的在有序列中的位置下标返回
}

template<class T>
void AllKindsOfSort<T>::QueckSort(int &movements, int &comparing, int i, int j)
{
	if (i < j)
	{
		int pivotloc = Partion(movements, comparing, i, j);//记录该次基准元素的位置
		QueckSort(movements, comparing, i, pivotloc - 1);//左分区快速排序
		QueckSort(movements, comparing, pivotloc + 1, j);//右分区快速排序
	}
}

template<class T>
void AllKindsOfSort<T>::SelectSort(int & movements, int & comparing)
{
	for (int i = 0; i < N - 1; i++)
	{
		int index = i;//n-1趟排序，假设index为最小值的下标，通过之后的不断判断、更新确定最小值
		for (int j = i + 1; j < N; j++)
		{
			if (arr[j] < arr[index])
			{
				index = j;
			}
			comparing++;
		}
		if (index != i)//若index==i、说明无序部分第一个数就是最小的不用操作
		{
			temp = arr[i];
			arr[i] = arr[index];
			arr[index] = temp;
			movements+=3;//以上为以哨兵作为中间量交换无序区第一个与无序区最小值
		}
	}
}

template<class T>
void AllKindsOfSort<T>::Sifit(int & movements, int & comparing, int k, int m)
{
	int i = k, j = 2 * i;//k是被筛选的节点，m是最后一个节点编号
	while (j <= m)//当j节点存在
	{
		if (j < m&&arr[j - 1] < arr[j])//找到i的左右孩子的最大值
		{
			j++;
		}
		comparing++;
		if (arr[i - 1] >= arr[j - 1])break;//符合大根堆的条件
		else//根节点和孩子节点交换
		{
			temp = arr[i - 1];
			arr[i - 1] = arr[j - 1];
			arr[j - 1] = temp;
			movements += 3;
			i = j;
			j = 2 * i;//带比较节点下移，为下一个循环做准备
		}
	}

}

template<class T>
void AllKindsOfSort<T>::HeapSort(int & movements, int & comparing)
{
	for (int i = N / 2; i >= 1; i--)//此步骤是将整个数列假象成一棵二叉树并进行建堆过程
		Sifit(movements, comparing, i, N);
	for (int i = N; i > 1; i--)
	{
		temp = arr[0]; arr[0] = arr[i - 1]; arr[i - 1] = temp;//堆顶元素为范围内数列最大值，将它与最后一个值交换并不再管它
		movements += 3;
		Sifit(movements, comparing, 1, i - 1);//重新建堆
	}
}

int main()
{
	int n;
	cout << "Input the number of the sample for all kinds of sort:";
	cin >> n;
	int mov(0);//分别为插入排序的有序、逆序、随机移动次数
	int com(0);//分别为插入排序的有序、逆序、随机比较次数
	srand((int)time(0));//设置随机数种子
	int sorted_arr[MaxSize], resorted_arr[MaxSize], random_arr[MaxSize];
	for (int i = 1; i <= n; i++)//初始化正序、逆序、随机数组
	{
		sorted_arr[i - 1] = i;
		resorted_arr[i - 1] = n + 1 - i;

		random_arr[i - 1] = rand() % n;
	}
	AllKindsOfSort<int> test_for_sort;
	AllKindsOfSort<int> test_for_resort;
	AllKindsOfSort<int> test_for_radom;
	try {
		test_for_sort.Creat(sorted_arr, n);
		test_for_resort.Creat(resorted_arr, n);
		test_for_radom.Creat(random_arr, n);
	}
	catch (const char * msg)
	{
		cerr << msg;
	}
	cout << "before insert_sort:" << endl;
	cout << "sorted_arr:" << endl;
	test_for_sort.Print();
	cout << "resorted_arr:" << endl;
	test_for_resort.Print();
	cout << "random_arr:" << endl;
	test_for_radom.Print();
	cout << "以上为生成数组在没有被排序时的初始状态**********"<<endl;
	//**************华丽的分割线***************
	//以下测试插入排序
	LARGE_INTEGER  nFreq, t1, t2;
	double cost;
	cout << "after insert_sort:" << endl;
	cout << "sorted arr:" << endl;
	QueryPerformanceFrequency(&nFreq);
	QueryPerformanceCounter(&t1);
	test_for_sort.InsertSort(mov, com);
	QueryPerformanceCounter(&t2);
	cost= (t2.QuadPart - t1.QuadPart) / (double)nFreq.QuadPart;
	test_for_sort.Print();
	cout << "Move:" << mov << " Compare:" << com << " time cost: " <<setiosflags(ios::fixed)<< setprecision(9) << cost << endl;
	mov = 0; com = 0;
	cout << "resorted_arr:" << endl;
	QueryPerformanceFrequency(&nFreq);
	QueryPerformanceCounter(&t1);
	test_for_resort.InsertSort(mov, com);
	QueryPerformanceCounter(&t2);
	cost = (t2.QuadPart - t1.QuadPart) / (double)nFreq.QuadPart;
	test_for_resort.Print();
	cout << "Move:" << mov << " Compare:" << com << " time cost: " << setiosflags(ios::fixed) << setprecision(9) << cost << endl;
	mov = 0; com = 0;
	cout << "random_arr:" << endl;
	QueryPerformanceFrequency(&nFreq);
	QueryPerformanceCounter(&t1);
	test_for_radom.InsertSort(mov, com);
	QueryPerformanceCounter(&t2);
	cost = (t2.QuadPart - t1.QuadPart) / (double)nFreq.QuadPart;
	test_for_radom.Print();
	cout << "Move:" << mov << " Compare:" << com << " time cost: " << setiosflags(ios::fixed) << setprecision(9) << cost << endl;
	mov = 0; com = 0;
	cout << "以上是插入排序在正序、逆序、随机时的表现************" << endl;
	//**************华丽的分割线***************
	//以下测试希尔排序
	test_for_sort.Creat(sorted_arr, n);//重新初始化
	test_for_resort.Creat(resorted_arr, n);
	test_for_radom.Creat(random_arr, n);
	cout << "*****************华丽的分割线*******************" << endl;
	cout << "after ShellInsert:" << endl;
	cout << "sorted arr:" << endl;
	QueryPerformanceFrequency(&nFreq);
	QueryPerformanceCounter(&t1);
	test_for_sort.ShellInsert(mov, com);
	QueryPerformanceCounter(&t2);
	cost = (t2.QuadPart - t1.QuadPart) / (double)nFreq.QuadPart;
	test_for_sort.Print();
	cout << "Move:" << mov << " Compare:" << com << " time cost: " << setiosflags(ios::fixed) << setprecision(9) << cost << endl;
	mov = 0; com = 0;
	cout << "resorted_arr:" << endl;
	QueryPerformanceFrequency(&nFreq);
	QueryPerformanceCounter(&t1);
	test_for_resort.ShellInsert(mov, com);
	QueryPerformanceCounter(&t2);
	cost = (t2.QuadPart - t1.QuadPart) / (double)nFreq.QuadPart;
	test_for_resort.Print();
	cout << "Move:" << mov << " Compare:" << com << " time cost: " << setiosflags(ios::fixed) << setprecision(9) << cost << endl;
	mov = 0; com = 0;
	cout << "random_arr:" << endl;
	QueryPerformanceFrequency(&nFreq);
	QueryPerformanceCounter(&t1);
	test_for_radom.ShellInsert(mov, com);
	QueryPerformanceCounter(&t2);
	cost = (t2.QuadPart - t1.QuadPart) / (double)nFreq.QuadPart;
	test_for_radom.Print();
	cout << "Move:" << mov << " Compare:" << com << " time cost: " << setiosflags(ios::fixed) << setprecision(9) << cost << endl;
	mov = 0; com = 0;
	cout << "以上是希尔排序在正序、逆序、随机时的表现************" << endl;
	//**************华丽的分割线***************
	//以下测试冒泡排序
	cout << "*****************华丽的分割线*******************" << endl;
	test_for_sort.Creat(sorted_arr, n);//重新初始化
	test_for_resort.Creat(resorted_arr, n);
	test_for_radom.Creat(random_arr, n);
	cout << "after BublbleSort:" << endl;
	cout << "sorted arr:" << endl;
	QueryPerformanceFrequency(&nFreq);
	QueryPerformanceCounter(&t1);
	test_for_sort.BubbleSort(mov, com);
	QueryPerformanceCounter(&t2);
	cost = (t2.QuadPart - t1.QuadPart) / (double)nFreq.QuadPart;
	test_for_sort.Print();
	cout << "Move:" << mov << " Compare:" << com << " time cost: " << setiosflags(ios::fixed) << setprecision(9) << cost << endl;
	mov = 0; com = 0;
	cout << "resorted_arr:" << endl;
	QueryPerformanceFrequency(&nFreq);
	QueryPerformanceCounter(&t1);
	test_for_resort.BubbleSort(mov, com);
	QueryPerformanceCounter(&t2);
	cost = (t2.QuadPart - t1.QuadPart) / (double)nFreq.QuadPart;
	test_for_resort.Print();
	cout << "Move:" << mov << " Compare:" << com << " time cost: " << setiosflags(ios::fixed) << setprecision(9) << cost << endl;
	mov = 0; com = 0;
	cout << "random_arr:" << endl;
	QueryPerformanceFrequency(&nFreq);
	QueryPerformanceCounter(&t1);
	test_for_radom.BubbleSort(mov, com);
	QueryPerformanceCounter(&t2);
	cost = (t2.QuadPart - t1.QuadPart) / (double)nFreq.QuadPart;
	test_for_radom.Print();
	cout << "Move:" << mov << " Compare:" << com << " time cost: " << setiosflags(ios::fixed) << setprecision(9) << cost << endl;
	mov = 0; com = 0;
	cout << "以上是冒泡排序在正序、逆序、随机时的表现************" << endl;
	//**************华丽的分割线***************
	//以下测试快速排序
	cout << "*****************华丽的分割线*******************" << endl;
	test_for_sort.Creat(sorted_arr, n);//重新初始化
	test_for_resort.Creat(resorted_arr, n);
	test_for_radom.Creat(random_arr, n);
	cout << "after QueckSort:" << endl;
	cout << "sorted arr:" << endl;
	QueryPerformanceFrequency(&nFreq);
	QueryPerformanceCounter(&t1);
	test_for_sort.QueckSort(mov, com, 0, n - 1);
	QueryPerformanceCounter(&t2);
	cost = (t2.QuadPart - t1.QuadPart) / (double)nFreq.QuadPart;
	test_for_sort.Print();
	cout << "Move:" << mov << " Compare:" << com << " time cost: " << setiosflags(ios::fixed) << setprecision(9) << cost << endl;
	mov = 0; com = 0;
	cout << "resorted_arr:" << endl;
	QueryPerformanceFrequency(&nFreq);
	QueryPerformanceCounter(&t1);
	test_for_resort.QueckSort(mov, com, 0, n - 1);
	QueryPerformanceCounter(&t2);
	cost = (t2.QuadPart - t1.QuadPart) / (double)nFreq.QuadPart;
	test_for_resort.Print();
	cout << "Move:" << mov << " Compare:" << com << " time cost: " << setiosflags(ios::fixed) << setprecision(9) << cost << endl;
	mov = 0; com = 0;
	cout << "random_arr:" << endl;
	QueryPerformanceFrequency(&nFreq);
	QueryPerformanceCounter(&t1);
	test_for_radom.QueckSort(mov, com, 0, n - 1);
	QueryPerformanceCounter(&t2);
	cost = (t2.QuadPart - t1.QuadPart) / (double)nFreq.QuadPart;
	test_for_radom.Print();
	cout << "Move:" << mov << " Compare:" << com << " time cost: " << setiosflags(ios::fixed) << setprecision(9) << cost << endl;
	mov = 0; com = 0;
	cout << "以上是快速排序在正序、逆序、随机时的表现************" << endl;
	//**************华丽的分割线***************
	//以下测试选择排序
	cout << "*****************华丽的分割线*******************" << endl;
	test_for_sort.Creat(sorted_arr, n);//重新初始化
	test_for_resort.Creat(resorted_arr, n);
	test_for_radom.Creat(random_arr, n);
	cout << "after QueckSort:" << endl;
	cout << "sorted arr:" << endl;
	QueryPerformanceFrequency(&nFreq);
	QueryPerformanceCounter(&t1);
	test_for_sort.SelectSort(mov, com);
	QueryPerformanceCounter(&t2);
	cost = (t2.QuadPart - t1.QuadPart) / (double)nFreq.QuadPart;
	test_for_sort.Print();
	cout << "Move:" << mov << " Compare:" << com << " time cost: " << setiosflags(ios::fixed) << setprecision(9) << cost << endl;
	mov = 0; com = 0;
	cout << "resorted_arr:" << endl;
	QueryPerformanceFrequency(&nFreq);
	QueryPerformanceCounter(&t1);
	test_for_resort.SelectSort(mov, com);
	QueryPerformanceCounter(&t2);
	cost = (t2.QuadPart - t1.QuadPart) / (double)nFreq.QuadPart;
	test_for_resort.Print();
	cout << "Move:" << mov << " Compare:" << com << " time cost: " << setiosflags(ios::fixed) << setprecision(9) << cost << endl;
	mov = 0; com = 0;
	cout << "random_arr:" << endl;
	QueryPerformanceFrequency(&nFreq);
	QueryPerformanceCounter(&t1);
	test_for_radom.SelectSort(mov, com);
	QueryPerformanceCounter(&t2);
	cost = (t2.QuadPart - t1.QuadPart) / (double)nFreq.QuadPart;
	test_for_radom.Print();
	cout << "Move:" << mov << " Compare:" << com << " time cost: " << setiosflags(ios::fixed) << setprecision(9) << cost << endl;
	mov = 0; com = 0;
	cout << "以上是选择排序在正序、逆序、随机时的表现************" << endl;
	//**************华丽的分割线***************
	//以下测试堆排序
	cout << "*****************华丽的分割线*******************" << endl;
	test_for_sort.Creat(sorted_arr, n);//重新初始化
	test_for_resort.Creat(resorted_arr, n);
	test_for_radom.Creat(random_arr, n);
	cout << "after HeapSort:" << endl;
	cout << "sorted arr:" << endl;
	QueryPerformanceFrequency(&nFreq);
	QueryPerformanceCounter(&t1);
	test_for_sort.HeapSort(mov, com);
	QueryPerformanceCounter(&t2);
	cost = (t2.QuadPart - t1.QuadPart) / (double)nFreq.QuadPart;
	test_for_sort.Print();
	cout << "Move:" << mov << " Compare:" << com << " time cost: " << setiosflags(ios::fixed) << setprecision(9) << cost << endl;
	mov = 0; com = 0;
	cout << "resorted_arr:" << endl;
	QueryPerformanceFrequency(&nFreq);
	QueryPerformanceCounter(&t1);
	test_for_resort.HeapSort(mov, com);
	QueryPerformanceCounter(&t2);
	cost = (t2.QuadPart - t1.QuadPart) / (double)nFreq.QuadPart;
	test_for_resort.Print();
	cout << "Move:" << mov << " Compare:" << com << " time cost: " << setiosflags(ios::fixed) << setprecision(9) << cost << endl;
	mov = 0; com = 0;
	cout << "random_arr:" << endl;
	QueryPerformanceFrequency(&nFreq);
	QueryPerformanceCounter(&t1);
	test_for_radom.HeapSort(mov, com);
	QueryPerformanceCounter(&t2);
	cost = (t2.QuadPart - t1.QuadPart) / (double)nFreq.QuadPart;
	test_for_radom.Print();
	cout << "Move:" << mov << " Compare:" << com << " time cost: " << setiosflags(ios::fixed) << setprecision(9) << cost << endl;
	mov = 0; com = 0;
	cout << "以上是堆排序在正序、逆序、随机时的表现************" << endl;
	cout << "φ(≧ω≦*)φ" << endl;
	system("pause");
	return 0;
}