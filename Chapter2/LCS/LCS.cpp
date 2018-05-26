#include <iostream>
#include <string>
#include <fstream>

#define FILE_NAME "subsequence.txt"

using namespace std;

enum FROM {STR1, STR2, EQUAL};

void f(const string & str1, const string & str2);

int main(){
	// =================================== input
	ifstream fin;
	fin.open(FILE_NAME);

	string a, b, c, d;
	fin >> a >> a >> b >> b >> c >> c >> d >> d;
	fin.close();

	//cout << a << endl << b << endl << c << endl << d << endl;

	string LCS;

	// ==================================== A B
	cout << "a, b\n";
	f(a, b);

	// ==================================== C D
	cout << "c, d\n";
	f(c, d);

	// ==================================== A D
	cout << "a, d\n";
	f(a, d);

	// ==================================== C B
	cout << "c, b\n";
	f(c, b);

	system("pause");
	return 0;
}

void f(const string & str1, const string & str2){
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
	string LCS = "";
	int i = str1.length() - 1, j = str2.length() - 1;
	while (i >= 0 && j >= 0){
		if (from[i][j] == EQUAL){
			LCS.insert(LCS.begin(), str1[i]);
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

	cout << result << endl;
	cout << LCS << endl;
}
