#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <ctime>

using namespace std;

// #define DEBUG//for debug

//======================================== use this to control input
#define STATION_NUM 22
// #define STATION_NUM 30
// #define STATION_NUM 42
//=================================================================

//--------------------------DO NOT CHANGE THIS
#if STATION_NUM == 22
#define FILE_NAME "station22.txt"
#elif STATION_NUM == 30
#define FILE_NAME "station30.txt"
#elif STATION_NUM == 42
#define FILE_NAME "station42.txt"
#endif
//--------------------------------------------

//number of color
#define COLOR_NUM 5

void f(int s[], bool b[][STATION_NUM]);

int main(){
	//--------------------------------------- declaration
	int stationCode[STATION_NUM];
	bool reachable[STATION_NUM][STATION_NUM];

	//------------------------------------------ input
	ifstream fin;
	fin.open(FILE_NAME);
	for (int i = 0; i < STATION_NUM; ++i){
		fin >> stationCode[i];
	}
	double buf;
	for (int i = 0; i < STATION_NUM; ++i){
		fin >> buf;//read station code
		for (int j = 0; j < STATION_NUM; ++j){
			fin >> buf;//read distance
			reachable[i][j] = (buf > 99998 ? false : true);
		}
	}
	fin.close();

#ifdef DEBUG
	// for (int i = 0; i < STATION_NUM; ++i){
	// 	cout << "station code: " << stationCode[i] << endl;
	// 	for (int j = 0; j < STATION_NUM; ++j){
	// 		if (reachable[i][j]){
	// 			cout << "\t" << stationCode[j] << " is reachable\n";
	// 		}
	// 	}
	// }
	for (int i = 0; i < STATION_NUM; ++i){
		cout << "station " << i << " is adjacent with" << endl;
		for (int j = 0; j < STATION_NUM; ++j){
			if (reachable[i][j]){
				cout << j << "\t";
			}
		}
		cout << endl;
	}
#endif

	f(stationCode, reachable);

	system("pause");
	return 0;
}

void f(int stationCode[], bool reachable[][STATION_NUM]){
	int color[STATION_NUM];//color, from 1 to COLOR_NUM, 0 for uncolored
	long count = 0;//how many nodes we scanned
	for (int i = 0; i < STATION_NUM; ++i){//init c[]
		color[i] = 0;
	}

	//use stack instead of recursion
	stack<int> stationStack;
	stack<int> colorStack;
	stationStack.push(0);
	colorStack.push(1);

	bool flag = true;
	auto startTime = clock();

	while (flag){
		int currentStation = stationStack.top();
		int currentColor = colorStack.top();
		++count;

		bool colorUsed = false;
		//judge whether color currentStation with currentColor is feasible
		for (int i = 0; i < STATION_NUM; ++i){//choose an adjacent node
			if (reachable[i][currentStation] && color[i] == currentColor){
				colorUsed = true;
				break;
			}
		}
		if (colorUsed){
			//this color has been used
			if (currentColor < COLOR_NUM){
				//try next color
				colorStack.pop();
				colorStack.push(currentColor + 1);
			} else {
				//all color tried, should pop
				while (colorStack.top() == COLOR_NUM){
					colorStack.pop();
					currentStation = stationStack.top();
					stationStack.pop();

					//cancel coloring
					color[currentStation] = 0;
#ifdef DEBUG
					cout << "Cancel coloring station[" << currentStation << "]\n";
#endif
				}
				currentColor = colorStack.top();
				colorStack.pop();
				colorStack.push(currentColor + 1);//try next color
			}
		} else {
			//this color has not been used
			color[currentStation] = currentColor;//color the station

#ifdef DEBUG
			cout << "Color station[" << currentStation << "] with color[" << currentColor << "]\n";
#endif

			//judge flag
			if (currentStation == STATION_NUM - 1){
				flag = false;//stop loop
			} else {
				//find next station
				stationStack.push(currentStation + 1);
				colorStack.push(1);
			}
		}

#ifndef DEBUG
		cout << "Progress: " << stationStack.size() << "/" << STATION_NUM << endl;
#endif
	}

#ifdef DEBUG
	cout << "\n\nFinal result:\n";
	for (int i = 0; i < STATION_NUM; ++i){
		cout << "Color station[" << i << "] with color[" << color[i] - 1 << "]\n";
	}
#endif

	auto endTime = clock();
	//output
	cout << "\nColor number : " << COLOR_NUM << endl;
	cout << "Search nodes : " << count << endl;
	cout << "Time : " << (endTime - startTime) / 1000 << "s\n";
}