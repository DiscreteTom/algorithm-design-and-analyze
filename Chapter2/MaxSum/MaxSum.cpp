#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

#define FILE_NAME_1 "data1.txt"
#define FILE_NAME_2 "data2.txt"

void f(vector<int> a);

int main(){
	//declaraion
	vector<int> data1;
	vector<int> data2;
	
	//input
	fstream fin;
	fin.open(FILE_NAME_1);
	int t;
	while (!fin.eof()){
		fin >> t;
		data1.push_back(t);
		fin.get();//read \n
	}
	data1.erase(data1.end() - 1);
	fin.close();
	fin.open(FILE_NAME_2);
	while (!fin.eof()){
		fin >> t;
		data2.push_back(t);
		fin.get();
	}
	fin.close();

	//output for debug
	// cout << "data1:======================================================\n";
	// for (int i = 0; i < data1.size(); ++i){
	// 	cout << data1[i] << endl;
	// }
	// cout << "data2:======================================================\n";
	// for (int i = 0; i < data2.size(); ++i){
	// 	cout << data2[i] << endl;
	// }

	cout << "data1\n";
	f(data1);
	cout << "data2\n";
	f(data2);

	system("pause");
	return 0;
}

void f(vector<int> a){
	int * sum = new int[a.size()];
	int * from = new int[a.size()];
	for (int i = 0; i < a.size(); ++i){
		//init
		sum[i] = 0;

		if (i == 0){
			sum[i] = a[i];
			from[i] = 0;
		} else {
			auto t = sum[i - 1] + a[i];
			if (t > a[i]){
				sum[i] = t;
				from[i] = from[i - 1];
			} else {
				sum[i] = a[i];
				from[i] = i;
			}
		}
	}

	//get the max one
	int result = sum[0];
	int resultIndex = 0;
	for (int i = 1; i < a.size(); ++i){
		if (sum[i] > result){
			result = sum[i];
			resultIndex = i;
		}
	}

	cout << "MaxSum = " << result << endl;
	cout << "result from " << from[resultIndex] << " to " << resultIndex << endl;
}