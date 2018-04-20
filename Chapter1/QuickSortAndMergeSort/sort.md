# 作业1 合并、快速排序

- 班级 2016211306
- 学号 2016211281
- 姓名 王景辉

## 目录

- [作业1 合并、快速排序](#1)
	- [目录](#)
	- [实验条件](#)
	- [实验结果](#)
	- [结果分析](#)
		- [输入相同时算法的差异](#)
		- [样本数量相同 ADD不同 算法时间差异](#add)
		- [样本数量对时间的影响](#)
		- [三种快速排序递归层次的差异](#)
	- [附1 源码(附件sort.cpp)](#1-sortcpp)
	- [附2 程序输出结果(附件sort.txt)](#2-sorttxt)

## 实验条件

- L = 6
	- n1 = 2000
	- n2 = 5000
	- n3 = 10000
	- n4 = 15000
	- n5 = 20000
	- n6 = 30000
- M = 5

## 实验结果

表头缩写含义

-  SEQ code  序列编号 
-  Length    序列长度 
-  M         同一长度下序列编号 
-  DD        无序度 
-  ADD       平均无序度 
-  RMS       递归合并排序 时间/递归深度 
-  NRMS      非递归合并排序 时间 
-  QS        快速排序 时间/递归深度 
-  QSOC      快速排序+有序检测 时间/递归深度 
-  RQS       快速排序+随机基准元素 时间/递归深度 

其他注释

- 时间单位为微妙(microsecond)
- 数据取自附件sort.txt
- 同一长度下的数据已根据DD从小到大排序

| SEQ code | Length | M   | DD        | ADD     | RMS     | NRMS | QS      | QSOC    | RQS     |
| -------- | ------ | --- | --------- | ------- | ------- | ---- | ------- | ------- | ------- |
| 1        | 2000   | 1   | 993295    | 496.647 | 425/12  | 199  | 181/25  | 168/24  | 199/24  |
| 2        | 2000   | 2   | 978109    | 489.055 | 416/12  | 252  | 193/24  | 175/23  | 200/24  |
| 3        | 2000   | 3   | 998136    | 499.068 | 474/12  | 202  | 183/23  | 172/22  | 202/24  |
| 4        | 2000   | 4   | 1008895   | 504.447 | 477/12  | 204  | 220/27  | 169/26  | 259/24  |
| 5        | 2000   | 5   | 1019431   | 509.716 | 523/12  | 221  | 274/27  | 244/26  | 212/26  |
| 6        | 5000   | 1   | 6182946   | 1236.59 | 1003/14 | 631  | 621/28  | 485/27  | 603/29  |
| 7        | 5000   | 2   | 6237626   | 1247.53 | 1229/14 | 702  | 528/30  | 519/28  | 564/26  |
| 8        | 5000   | 3   | 6259255   | 1251.85 | 2026/14 | 863  | 704/32  | 679/31  | 939/29  |
| 9        | 5000   | 4   | 6307929   | 1261.59 | 1032/14 | 607  | 547/31  | 573/30  | 573/28  |
| 10       | 5000   | 5   | 6333770   | 1266.75 | 1078/14 | 692  | 536/28  | 502/27  | 596/27  |
| 11       | 10000  | 1   | 24926022  | 2492.6  | 4428/15 | 1440 | 1220/29 | 1173/28 | 1343/33 |
| 12       | 10000  | 2   | 24963380  | 2496.34 | 2282/15 | 1271 | 1183/31 | 1016/30 | 1236/32 |
| 13       | 10000  | 3   | 25013201  | 2501.32 | 2184/15 | 1323 | 2378/31 | 1079/30 | 1209/35 |
| 14       | 10000  | 4   | 25071830  | 2507.18 | 2061/15 | 1379 | 1188/29 | 1022/28 | 1180/29 |
| 15       | 10000  | 5   | 25302581  | 2530.26 | 2089/15 | 1312 | 1094/30 | 1630/29 | 1182/32 |
| 16       | 15000  | 1   | 56223804  | 3748.25 | 3536/15 | 2037 | 1765/40 | 1667/39 | 2268/37 |
| 27       | 15000  | 2   | 56295293  | 3753.02 | 3188/15 | 1965 | 1779/32 | 1799/31 | 1911/29 |
| 18       | 15000  | 3   | 56316333  | 3754.42 | 4318/15 | 2012 | 1745/30 | 1568/29 | 2363/36 |
| 19       | 15000  | 4   | 56330900  | 3755.39 | 3385/15 | 1987 | 1711/31 | 1658/30 | 1958/33 |
| 20       | 15000  | 5   | 56590299  | 3772.69 | 3705/15 | 2508 | 1828/31 | 1646/30 | 1835/33 |
| 21       | 20000  | 1   | 99634306  | 4981.72 | 4315/16 | 2703 | 2381/34 | 2504/33 | 2627/33 |
| 22       | 20000  | 2   | 99733702  | 4986.69 | 4496/16 | 2642 | 3200/39 | 2365/38 | 2453/36 |
| 23       | 20000  | 3   | 100094798 | 5004.74 | 5368/16 | 2838 | 2587/31 | 2103/30 | 2473/34 |
| 24       | 20000  | 4   | 100158846 | 5007.94 | 4166/16 | 2763 | 2448/37 | 2429/36 | 2519/34 |
| 25       | 20000  | 5   | 100318024 | 5015.9  | 4726/16 | 2922 | 2402/35 | 2240/34 | 2457/37 |
| 36       | 30000  | 1   | 224318754 | 7477.29 | 6348/16 | 4950 | 3673/32 | 3348/31 | 4443/39 |
| 27       | 30000  | 2   | 225214014 | 7507.13 | 7422/16 | 5190 | 3505/37 | 3245/36 | 4239/34 |
| 28       | 30000  | 3   | 225524006 | 7517.47 | 6492/16 | 3989 | 3558/34 | 3321/33 | 4222/35 |
| 29       | 30000  | 4   | 225705728 | 7523.52 | 6215/16 | 4025 | 3600/35 | 3604/33 | 4690/32 |
| 30       | 30000  | 5   | 226022678 | 7534.09 | 5931/16 | 4068 | 3897/33 | 4267/32 | 4241/36 |

## 结果分析

### 输入相同时算法的差异

取不同的长度下M=1时的数据如下

| SEQ code | Length | M   | DD        | ADD     | RMS     | NRMS | QS      | QSOC    | RQS     |
| -------- | ------ | --- | --------- | ------- | ------- | ---- | ------- | ------- | ------- |
| 1        | 2000   | 1   | 993295    | 496.647 | 425/12  | 199  | 181/25  | 168/24  | 199/24  |
| 6        | 5000   | 1   | 6182946   | 1236.59 | 1003/14 | 631  | 621/28  | 485/27  | 603/29  |
| 11       | 10000  | 1   | 24926022  | 2492.6  | 4428/15 | 1440 | 1220/29 | 1173/28 | 1343/33 |
| 16       | 15000  | 1   | 56223804  | 3748.25 | 3536/15 | 2037 | 1765/40 | 1667/39 | 2268/37 |
| 21       | 20000  | 1   | 99634306  | 4981.72 | 4315/16 | 2703 | 2381/34 | 2504/33 | 2627/33 |
| 36       | 30000  | 1   | 224318754 | 7477.29 | 6348/16 | 4950 | 3673/32 | 3348/31 | 4443/39 |

从运行时间分析不难看出在速度上

有序检测快速排序 > 快速排序 > 随机基准快速排序 > 非递归合并排序 > 递归合并排序

### 样本数量相同 ADD不同 算法时间差异

取长度为30000的数据如下

| SEQ code | Length | M   | DD        | ADD     | RMS     | NRMS | QS      | QSOC    | RQS     |
| -------- | ------ | --- | --------- | ------- | ------- | ---- | ------- | ------- | ------- |
| 36       | 30000  | 1   | 224318754 | 7477.29 | 6348/16 | 4950 | 3673/32 | 3348/31 | 4443/39 |
| 27       | 30000  | 2   | 225214014 | 7507.13 | 7422/16 | 5190 | 3505/37 | 3245/36 | 4239/34 |
| 28       | 30000  | 3   | 225524006 | 7517.47 | 6492/16 | 3989 | 3558/34 | 3321/33 | 4222/35 |
| 29       | 30000  | 4   | 225705728 | 7523.52 | 6215/16 | 4025 | 3600/35 | 3604/33 | 4690/32 |
| 30       | 30000  | 5   | 226022678 | 7534.09 | 5931/16 | 4068 | 3897/33 | 4267/32 | 4241/36 |

数据已经根据DD/ADD从小到大排序

不难看出

- 递归合并排序/非递归合并排序花费时间比较稳定
- 快速排序/有序检测快速排序花费时间随DD增加 花费时间有轻微增加
- 随机基准快速排序花费时间比较稳定

### 样本数量对时间的影响

根据输出数据计算得到如下表格

| n   | avgDD | avgADD | avgRMS | avgNRMS | avgQS | avgQSOC | avgRQS |
| --- | ----- | ------ | ------ | ------- | ----- | ------- | ------ |
| 2000 | 999573.2 |  |  |  |  |  |  |
| 5000 |  |  |  |  |  |  |  |
| 10000 |  |  |  |  |  |  |  |
| 15000 |  |  |  |  |  |  |  |
| 20000 |  |  |  |  |  |  |  |
| 30000 |  |  |  |  |  |  |  |

### 三种快速排序递归层次的差异

取不同的长度下M=1时的数据如下

| SEQ code | Length | QS      | QSOC    | RQS     |
| -------- | ------ | ------- | ------- | ------- |
| 1        | 2000   | 181/25  | 168/24  | 199/24  |
| 6        | 5000   | 621/28  | 485/27  | 603/29  |
| 11       | 10000  | 1220/29 | 1173/28 | 1343/33 |
| 16       | 15000  | 1765/40 | 1667/39 | 2268/37 |
| 21       | 20000  | 2381/34 | 2504/33 | 2627/33 |
| 36       | 30000  | 3673/32 | 3348/31 | 4443/39 |

分析得到如下结果

- 递归层次随样本数量增加而增加
- 以普通快速排序为基准
	- 有序检测快速排序递归层次普遍低于普通快速排序 花费时间更短
	- 随机基准快速排序优化效果不明显 递归层次和运行时间不能够稳定优于普通快速排序

## 附1 源码(附件sort.cpp)

	#include <iostream>
	#include <fstream>
	#include <cstdlib>
	#include <ctime>
	#include <chrono>

	#define MAX_VALUE 30000

	using namespace std;

	void randomShuffle(int * a, int n, int N);
	int * SEQ(int n, int N);
	void show(int * a, int n);
	int quickSort(int * a, int left, int right, bool checkOrdered = false, bool random = false);
	int Partition(int * a, int left, int right, bool random = 0);
	long DD(int * a, int n);
	double ADD(int * a, int n);
	double ADD(long DD, int n);
	int * copySEQ(int * a, int n);
	int recursiveMergeSort(int * a, int left, int right);
	void nonRecursiveMergeSort(int * a, int n);


	int main(){
		ofstream ofstr;
		ofstr.open("sort.txt");

		//input
		int L;
		cout << "Please input L\n";
		ofstr << "Please input L\n";
		cin >> L;
		ofstr << L << endl;
		int n[L];
		cout << "Please input n\n";
		ofstr << "Please input n\n";
		for (int i = 0; i < L; ++i){
			cin >> n[i];
			ofstr << n[i] << endl;
		}
		int M;
		cout << "Please input M\n";
		ofstr << "Please input M\n";
		cin >> M;
		ofstr << M << endl << endl;
		cout << endl;

		ofstr << "| SEQ code | Length | M | DD | ADD | RMS | NRMS | QS | QSOC | RQS |\n";
		ofstr << "| --- | - | - | - | - | - | - | - | - | - |\n";

		for (int i = 0; i < L; ++i){
			cout << "n = " << n[i] << endl;
			auto a = SEQ(n[i], MAX_VALUE);
			for (int j = 0; j < M; ++j){
				ofstr << "| " << i * M + j + 1 << " | " << n[i] << " | " << j + 1 << " | ";

				auto startTime = chrono::steady_clock::now();
				auto endTime = chrono::steady_clock::now();
				int * b;
				int recursionDepth;

				randomShuffle(a, n[i], MAX_VALUE);
				cout << "Sequence " << j + 1 << endl;
				int dd = DD(a, n[i]);
				cout << "DD: " << dd << endl;
				ofstr << dd << " | ";
				cout << "ADD: " << ADD(dd, n[i]) << endl;
				ofstr << ADD(dd, n[i]) << " | ";
				//recursiveMergeSort
				b = copySEQ(a, n[i]);
				startTime = chrono::steady_clock::now();
				recursionDepth = recursiveMergeSort(b, 0, n[i] - 1);
				endTime = chrono::steady_clock::now();
				cout << "recursiveMergeSort\ntime: " << (double)chrono::duration_cast<chrono::microseconds>(endTime - startTime).count() << "microsecond" << endl;
				ofstr << (double)chrono::duration_cast<chrono::microseconds>(endTime - startTime).count() << "/";
				delete [] b;
				cout << "recursion depth: " << recursionDepth << endl;
				ofstr << recursionDepth << " | ";
				//nonRecursiveMergeSort
				b = copySEQ(a, n[i]);
				startTime = chrono::steady_clock::now();
				nonRecursiveMergeSort(b, n[i]);
				endTime = chrono::steady_clock::now();
				cout << "nonRecursiveMergeSort\ntime: " << (double)chrono::duration_cast<chrono::microseconds>(endTime - startTime).count() << "microsecond" << endl;
				ofstr << (double)chrono::duration_cast<chrono::microseconds>(endTime - startTime).count() << " | ";
				delete [] b;
				//quicksort
				b = copySEQ(a, n[i]);
				startTime = chrono::steady_clock::now();
				recursionDepth = quickSort(b, 0, n[i] - 1);
				endTime = chrono::steady_clock::now();
				cout << "quicksort\ntime: " << (double)chrono::duration_cast<chrono::microseconds>(endTime - startTime).count() << "microsecond" << endl;
				ofstr << (double)chrono::duration_cast<chrono::microseconds>(endTime - startTime).count() << "/";
				delete [] b;
				cout << "recursion depth: " << recursionDepth << endl;
				ofstr << recursionDepth << " | ";
				//check ordered quicksort
				b = copySEQ(a, n[i]);
				startTime = chrono::steady_clock::now();
				recursionDepth = quickSort(b, 0, n[i] - 1, true);
				endTime = chrono::steady_clock::now();
				cout << "quicksort with order check\ntime: " << (double)chrono::duration_cast<chrono::microseconds>(endTime - startTime).count() << "microsecond" << endl;
				ofstr << (double)chrono::duration_cast<chrono::microseconds>(endTime - startTime).count() << "/";
				delete [] b;
				cout << "recursion depth: " << recursionDepth << endl;
				ofstr << recursionDepth << " | ";
				//quicksort with random partation
				b = copySEQ(a, n[i]);
				startTime = chrono::steady_clock::now();
				recursionDepth = quickSort(b, 0, n[i] - 1, false, true);
				endTime = chrono::steady_clock::now();
				cout << "quicksort with random partation\ntime: " << (double)chrono::duration_cast<chrono::microseconds>(endTime - startTime).count() << "microsecond" << endl;
				ofstr << (double)chrono::duration_cast<chrono::microseconds>(endTime - startTime).count() << "/";
				delete [] b;
				cout << "recursion depth: " << recursionDepth << endl;
				ofstr << recursionDepth << " |\n";
			}
			delete [] a;
		}

		ofstr.close();

		system("pause");
	}

	void randomShuffle(int * a, int n, int N){
		srand(clock());

		for (int i = 0; i < n; ++i){
			a[i] = rand() % N;
		}
	}
	int * SEQ(int n, int N){
		int * a = new int[n];
		randomShuffle(a, n, N);
		return a;
	}
	void show(int * a, int n){
		for (int i = 0; i < n; ++i){
			cout << a[i] << endl;
		}
	}
	int quickSort(int * a, int left, int right, bool checkOrdered, bool random){
		int result = 0;

		if (left < right){
			if (checkOrdered){
				bool flag = true;//ordered
				for (int i = left; i < right - 1; ++i){
					if (a[i] > a[i + 1]){
						flag = false;
						break;
					}
				}
				if (flag){
					return ++result;
				}
			}
			
			int m = Partition(a, left, right, random);

			int t1 = quickSort(a, left, m - 1, checkOrdered, random);
			int t2= quickSort(a, m + 1, right, checkOrdered, random);
			result += (t1 > t2 ? t1 : t2);
		}
		return ++result;
	}
	int Partition(int * a, int left, int right, bool random){
		//random
		if (random){
			int t = rand() % (right - left + 1) + left;
			//swap a[t] a[left]
			auto temp = a[left];
			a[left] = a[t];
			a[t] = temp;
		}
		
		int i = left, j = right + 1;
		while (true){
			while (a[++i] < a[left] && i < j);
			while (a[--j] > a[left]);

			if (i >= j){
				break;
			}

			//swap a[i] a[j]
			auto t = a[i];
			a[i] = a[j];
			a[j] = t;
		}

		//swap a[left] a[j]
		auto t = a[left];
		a[left] = a[j];
		a[j] = t;
		return j;
	}
	long DD(int * a, int n){
		long result = 0;
		for (int i = 0; i < n - 1; ++i){
			for (int j = i + 1; j < n; ++j){
				if (a[i] < a[j]){
					++result;
				}
			}
		}
		return result;
	}
	double ADD(int * a, int n){
		int dd = DD(a, n);
		return (double)dd / n;
	}
	double ADD(long DD, int n){
		return (double)DD / n;
	}
	int * copySEQ(int * a, int n){
		auto b = new int[n];
		for (int i = 0; i < n; ++i){
			b[i] = a[i];
		}
		return b;
	}
	int recursiveMergeSort(int * a, int left, int right){
		int result = 0;
		if (left < right){
			int m = (left + right) / 2;
			int t1 = recursiveMergeSort(a, left, m);
			int t2 = recursiveMergeSort(a, m + 1, right);
			result += (t1 > t2 ? t1 : t2);

			//merge
			auto b = new int [right - left + 1];
			for (int i = 0; i < right - left + 1; ++i){
				b[i] = a[i + left];//copy value
			}
			int i = left, j = m + 1, x = left;
			while (i <= m && j <= right){
				if (b[i - left] < b[j - left]){
					a[x] = b[i - left];
					++i;
				} else {
					a[x] = b[j - left];
					++j;
				}
				++x;
			}
			while (i <= m){
				a[x] = b[i - left];
				++i;
				++x;
			}
			while (j <= right){
				a[x] = b[j - left];
				++j;
				++x;
			}
			delete [] b;
		}
		return ++result;
	}
	void nonRecursiveMergeSort(int * a, int n){
		int step = 2;
		auto b = new int[n];
		for (int i = 0; i < n; ++i){//copy value to b
			b[i] = a[i];
		}
		while (step / 2 <= n){
			for (int i = 0; i < n; ++i){//copy value to b
				b[i] = a[i];
			}
			int window_start = 0;
			int window_end = window_start + step - 1;
			if (window_end >= n) window_end = n - 1;
			while (window_start + step / 2 - 1 < n){
				int m = window_start + step / 2 - 1;//middle left
				int i = window_start, j = m + 1, x = window_start;
				while (i <= m && j <= window_end){//merge
					if (b[i] > b[j]){
						a[x] = b[j];
						++j;
					} else {
						a[x] = b[i];
						++i;
					}
					++x;
				}
				while (i <= m){
					a[x] = b[i];
					++i;
					++x;
				}
				while (j <= window_end){
					a[x] = b[j];
					++j;
					++x;
				}

				//window slide
				window_start = window_end + 1;
				window_end = window_start + step - 1;
				if (window_end >= n){
					window_end = n - 1;
				}
			}

			step *= 2;
		}
		delete [] b;
	}


## 附2 程序输出结果(附件sort.txt)

	Please input L
	6
	Please input n
	2000
	5000
	10000
	15000
	20000
	30000
	Please input M
	5

	| SEQ code | Length | M | DD | ADD | RMS | NRMS | QS | QSOC | RQS |
	| --- | - | - | - | - | - | - | - | - | - |
	| 1 | 2000 | 1 | 993295 | 496.647 | 425/12 | 199 | 181/25 | 168/24 | 199/24 |
	| 2 | 2000 | 2 | 1008895 | 504.447 | 477/12 | 204 | 220/27 | 169/26 | 259/24 |
	| 3 | 2000 | 3 | 998136 | 499.068 | 474/12 | 202 | 183/23 | 172/22 | 202/24 |
	| 4 | 2000 | 4 | 1019431 | 509.716 | 523/12 | 221 | 274/27 | 244/26 | 212/26 |
	| 5 | 2000 | 5 | 978109 | 489.055 | 416/12 | 252 | 193/24 | 175/23 | 200/24 |
	| 6 | 5000 | 1 | 6307929 | 1261.59 | 1032/14 | 607 | 547/31 | 573/30 | 573/28 |
	| 7 | 5000 | 2 | 6237626 | 1247.53 | 1229/14 | 702 | 528/30 | 519/28 | 564/26 |
	| 8 | 5000 | 3 | 6259255 | 1251.85 | 2026/14 | 863 | 704/32 | 679/31 | 939/29 |
	| 9 | 5000 | 4 | 6182946 | 1236.59 | 1003/14 | 631 | 621/28 | 485/27 | 603/29 |
	| 10 | 5000 | 5 | 6333770 | 1266.75 | 1078/14 | 692 | 536/28 | 502/27 | 596/27 |
	| 11 | 10000 | 1 | 25071830 | 2507.18 | 2061/15 | 1379 | 1188/29 | 1022/28 | 1180/29 |
	| 12 | 10000 | 2 | 25302581 | 2530.26 | 2089/15 | 1312 | 1094/30 | 1630/29 | 1182/32 |
	| 13 | 10000 | 3 | 24963380 | 2496.34 | 2282/15 | 1271 | 1183/31 | 1016/30 | 1236/32 |
	| 14 | 10000 | 4 | 24926022 | 2492.6 | 4428/15 | 1440 | 1220/29 | 1173/28 | 1343/33 |
	| 15 | 10000 | 5 | 25013201 | 2501.32 | 2184/15 | 1323 | 2378/31 | 1079/30 | 1209/35 |
	| 16 | 15000 | 1 | 56590299 | 3772.69 | 3705/15 | 2508 | 1828/31 | 1646/30 | 1835/33 |
	| 17 | 15000 | 2 | 56223804 | 3748.25 | 3536/15 | 2037 | 1765/40 | 1667/39 | 2268/37 |
	| 18 | 15000 | 3 | 56316333 | 3754.42 | 4318/15 | 2012 | 1745/30 | 1568/29 | 2363/36 |
	| 19 | 15000 | 4 | 56330900 | 3755.39 | 3385/15 | 1987 | 1711/31 | 1658/30 | 1958/33 |
	| 20 | 15000 | 5 | 56295293 | 3753.02 | 3188/15 | 1965 | 1779/32 | 1799/31 | 1911/29 |
	| 21 | 20000 | 1 | 100318024 | 5015.9 | 4726/16 | 2922 | 2402/35 | 2240/34 | 2457/37 |
	| 22 | 20000 | 2 | 100094798 | 5004.74 | 5368/16 | 2838 | 2587/31 | 2103/30 | 2473/34 |
	| 23 | 20000 | 3 | 99733702 | 4986.69 | 4496/16 | 2642 | 3200/39 | 2365/38 | 2453/36 |
	| 24 | 20000 | 4 | 99634306 | 4981.72 | 4315/16 | 2703 | 2381/34 | 2504/33 | 2627/33 |
	| 25 | 20000 | 5 | 100158846 | 5007.94 | 4166/16 | 2763 | 2448/37 | 2429/36 | 2519/34 |
	| 26 | 30000 | 1 | 225705728 | 7523.52 | 6215/16 | 4025 | 3600/35 | 3604/33 | 4690/32 |
	| 27 | 30000 | 2 | 225214014 | 7507.13 | 7422/16 | 5190 | 3505/37 | 3245/36 | 4239/34 |
	| 28 | 30000 | 3 | 226022678 | 7534.09 | 5931/16 | 4068 | 3897/33 | 4267/32 | 4241/36 |
	| 29 | 30000 | 4 | 225524006 | 7517.47 | 6492/16 | 3989 | 3558/34 | 3321/33 | 4222/35 |
	| 30 | 30000 | 5 | 224318754 | 7477.29 | 6348/16 | 4950 | 3673/32 | 3348/31 | 4443/39 |
