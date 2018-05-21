#include <iostream>
#include <string>
#include <fstream>

#define FILE_NAME "subsequence.txt"

using namespace std;

enum FROM {STR1, STR2, EQUAL};

int f(const string & str1, const string & str2, string & receiver);

int main(){
	// =================================== input
	ifstream fin;
	fin.open(FILE_NAME);

	string a, b, c, d;
	fin >> a >> a >> b >> b >> c >> c >> d >> d;
	fin.close();

	//cout << a << endl << b << endl << c << endl << d << endl;

	string receiver;

	// ==================================== A B
	cout << f(a, b, receiver) << endl << receiver << endl;

	// ==================================== C D
	cout << f(c, d, receiver) << endl << receiver << endl;

	// ==================================== A D
	cout << f(a, d, receiver) << endl << receiver << endl;

	// ==================================== C B
	cout << f(c, b, receiver) << endl << receiver << endl;

	system("pause");
	return 0;
}

int f(const string & str1, const string & str2, string & receiver){
	// ==================================== get memory
	int ** length = new int*[str1.length()];
	FROM ** from = new FROM*[str1.length()];
	for (int i = 0; i < str1.length(); ++i){
		length[i] = new int[str2.length()];
		from[i] = new FROM[str2.length()];
	}

	// ================================= init
	for (int i = 0; i < str1.length(); ++i){
		for (int j = 0; j < str2.length(); ++j){
			length[i][j] = 0;
		}
	}
	int result;

	// ============================== LCSLength
	for (int i = 0; i < str1.length(); ++i){
		for (int j = 0; j < str2.length(); ++j){
			if (str1[i] == str2[j]){
				if (i > 1 && j > 1)
					length[i][j] = length[i - 1][j - 1] + 1;
				else
					length[i][j] = 1;
				from[i][j] = EQUAL;
			} else {
				if (i > 1 && j > 1){
					if (length[i - 1][j] >= length[i][j - 1]){
						length[i][j] = length[i - 1][j];
						from[i][j] = STR1;
					} else {
						length[i][j] = length[i][j - 1];
						from[i][j] = STR2;
					}
				} else {
					length[i][j] = 0;
				}
			}
		}
	}

	result = length[str1.length() - 1][str2.length() - 1];

	// =============================== LCS
	receiver = "";
	int i = str1.length() - 1, j = str2.length() - 1;
	while (i >= 0 && j >= 0){
		if (from[i][j] == EQUAL){
			receiver.insert(receiver.begin(), str1[i]);
			--i;
			--j;
		} else if (from[i][j] == STR1){
			--i;
		} else {
			--j;
		}
	}

	// =============================== free memory
	for (int i = 0; i < str1.length(); ++i){
		delete [] length[i];
		delete [] from[i];
	}
	delete [] length;
	delete [] from;

	return result;
}
