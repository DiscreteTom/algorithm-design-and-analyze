#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

#define MAX_VALUE 2000 // just for test
#define FILE_NAME "1033.txt"
#define K_NUM 1033

using namespace std;

template <class T>
int linearTimeSelect(T * a, int left, int right, int aim, T & receiver, bool triple = false);
template <class T>
void bubble(T * a, int left, int right);
template <class T>
int Partition(T * a, int left, int right, int middle);
template <class T>
void show(T * a, int n);
template <class T>
T * copySEQ(T * a, int n);
template <class T>
int QuickSortPartition(T * a, int left, int right);
template <class T>
int quickSort(T * a, int left, int right);

int main(){
	double k_dist[K_NUM];
	ifstream fin;
	fin.open(FILE_NAME);
	for (int i = 0; i < K_NUM; ++i){
		fin >> k_dist[i];
	}
	fin.close();

	ofstream fout;
	fout.open("selete.txt");

	//virables
	double receiver;
	int recursionDepth;
	double * a;
	//=====================================================================
	cout << "devide into 2 parts\n";
	fout << "devide into 2 parts\n";
	//minimum
	receiver = 0;
	a = copySEQ<double>(k_dist, K_NUM);
	recursionDepth = linearTimeSelect<double>(a, 0, K_NUM - 1, K_NUM, receiver);
	cout << "minimum k_dist is " << receiver << endl;
	fout << "minimum k_dist is " << receiver << endl;
	cout << "recursionDepth = " << recursionDepth << endl;
	fout << "recursionDepth = " << recursionDepth << endl;
	delete [] a;

	//5th minimum
	receiver = 0;
	a = copySEQ<double>(k_dist, K_NUM);
	recursionDepth = linearTimeSelect<double>(a, 0, K_NUM - 1, K_NUM - 4, receiver);
	cout << "5th minimum k_dist is " << receiver << endl;
	fout << "5th minimum k_dist is " << receiver << endl;
	cout << "recursionDepth = " << recursionDepth << endl;
	fout << "recursionDepth = " << recursionDepth << endl;
	delete [] a;
	
	//50th minimum
	receiver = 0;
	a = copySEQ<double>(k_dist, K_NUM);
	recursionDepth = linearTimeSelect<double>(a, 0, K_NUM - 1, K_NUM - 49, receiver);
	cout << "50th minimum k_dist is " << receiver << endl;
	fout << "50th minimum k_dist is " << receiver << endl;
	cout << "recursionDepth = " << recursionDepth << endl;
	fout << "recursionDepth = " << recursionDepth << endl;
	delete [] a;

	//maximum
	receiver = 0;
	a = copySEQ<double>(k_dist, K_NUM);
	recursionDepth = linearTimeSelect<double>(a, 0, K_NUM - 1, 1, receiver);
	cout << "maximum k_dist is " << receiver << endl;
	fout << "maximum k_dist is " << receiver << endl;
	cout << "recursionDepth = " << recursionDepth << endl;
	fout << "recursionDepth = " << recursionDepth << endl;
	delete [] a;

	fout << endl;

	//===========================================================================
	cout << "devide into 3 parts\n";
	fout << "devide into 3 parts\n";
	//minimum
	receiver = 0;
	a = copySEQ<double>(k_dist, K_NUM);
	recursionDepth = linearTimeSelect<double>(a, 0, K_NUM - 1, K_NUM, receiver, true);
	cout << "minimum k_dist is " << receiver << endl;
	fout << "minimum k_dist is " << receiver << endl;
	cout << "recursionDepth = " << recursionDepth << endl;
	fout << "recursionDepth = " << recursionDepth << endl;
	delete [] a;

	//5th minimum
	receiver = 0;
	a = copySEQ<double>(k_dist, K_NUM);
	recursionDepth = linearTimeSelect<double>(a, 0, K_NUM - 1, K_NUM - 4, receiver, true);
	cout << "5th minimum k_dist is " << receiver << endl;
	fout << "5th minimum k_dist is " << receiver << endl;
	cout << "recursionDepth = " << recursionDepth << endl;
	fout << "recursionDepth = " << recursionDepth << endl;
	delete [] a;
	
	//50th minimum
	receiver = 0;
	a = copySEQ<double>(k_dist, K_NUM);
	recursionDepth = linearTimeSelect<double>(a, 0, K_NUM - 1, K_NUM - 49, receiver, true);
	cout << "50th minimum k_dist is " << receiver << endl;
	fout << "50th minimum k_dist is " << receiver << endl;
	cout << "recursionDepth = " << recursionDepth << endl;
	fout << "recursionDepth = " << recursionDepth << endl;
	delete [] a;

	//maximum
	receiver = 0;
	a = copySEQ<double>(k_dist, K_NUM);
	recursionDepth = linearTimeSelect<double>(a, 0, K_NUM - 1, 1, receiver, true);
	cout << "maximum k_dist is " << receiver << endl;
	fout << "maximum k_dist is " << receiver << endl;
	cout << "recursionDepth = " << recursionDepth << endl;
	fout << "recursionDepth = " << recursionDepth << endl;
	delete [] a;

	fout << endl;

	//=========================================================================
	//quick sort to check correction
	quickSort<double>(k_dist, 0, K_NUM - 1);
	for (int i = 0; i < K_NUM; ++i){
		fout << i + 1 << " " << k_dist[i] << endl;
	}

	fout.close();

	system("pause");
}

//find number aim maximum element
//return recursionDepth
//aim item will be send by receiver
//if triple == true, devide array to 3 parts
template <class T>
int linearTimeSelect(T * a, int left, int right, int aim, T & receiver, bool triple){
	if (left > right){
		return 1;
	} else if (right - left < 20){
		//use a simple sort to find aim
		bubble<T>(a, left, right);
		if (aim <= right - left + 1){
			receiver = a[right - (aim - 1)];
		}
		return 1;
	} else {
		int recursionDepth = 0;

		//find middle
		int bn;//number of items in array b
		bn = (right - left + 1) / 5;
		if ((right - left + 1) % 5){
			++bn;
		}
		T b[bn];//to store the middle item in every 5 items
		for (int i = 0; i < bn; ++i){
			int this_left = left + 5 * i;
			int this_right = this_left + 4;
			this_right = (this_right > right ? right : this_right);
			bubble<T>(a, this_left, this_right);
			b[i] = a[(this_right - this_left + 1) / 2 + this_left];
		}
		T middle;
		recursionDepth += linearTimeSelect<T>(b, 0, bn - 1, bn / 2, middle, triple);
		int locate = Partition<T>(a, left, right, middle);

		if (triple){
			if (locate == right - (aim - 1)){
				receiver = a[locate];
			} else if (locate < right - (aim - 1)){//search right
				recursionDepth += linearTimeSelect<T>(a, locate + 1, right, aim, receiver, triple);
			} else {//search left
				recursionDepth += linearTimeSelect<T>(a, left, locate - 1, aim - (right - locate + 1), receiver, triple);
			}
		} else {
			if (locate > right - (aim - 1)){//search left
				recursionDepth += linearTimeSelect<T>(a, left, locate, aim - (right - locate), receiver, triple);
			} else {
				recursionDepth += linearTimeSelect<T>(a, locate + 1, right, aim, receiver, triple);
			}
		}
		return ++recursionDepth;
	}
}

template <class T>
void bubble(T * a, int left, int right){
	for (int i = left; i < right; ++i){
		for (int j = left; j < right; ++j){
			if (a[j] > a[j + 1]){
				//swap
				auto t = a[j + 1];
				a[j + 1] = a[j];
				a[j] = t;
			}
		}
	}
}
template <class T>
int Partition(T * a, int left, int right, int middle){
	//find middle
	int locate = left;
	for (int i = left; i <= right; ++i){
		if (a[i] == middle){
			locate = i;
			break;
		}
	}
	//swap a[locate] a[left]
	auto item = a[locate];
	a[locate] = a[left];
	a[left] = item;

	//partition
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
template <class T>
void show(T * a, int n){
	for (int i = 0; i < n; ++i){
		cout << a[i];
	}
}
template <class T>
T * copySEQ(T * a, int n){
	auto b = new T[n];
	for (int i = 0; i < n; ++i){
		b[i] = a[i];
	}
	return b;
}
template <class T>
int quickSort(T * a, int left, int right){
	int result = 0;

	if (left < right){
		int m = QuickSortPartition<T>(a, left, right);

		int t1 = quickSort<T>(a, left, m - 1);
		int t2= quickSort<T>(a, m + 1, right);
		result += (t1 > t2 ? t1 : t2);
	}
	return ++result;
}
template <class T>
int QuickSortPartition(T * a, int left, int right){
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