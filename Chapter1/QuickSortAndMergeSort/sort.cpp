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
