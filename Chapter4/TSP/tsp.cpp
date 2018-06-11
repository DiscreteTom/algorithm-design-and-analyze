#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <ctime>

using namespace std;

#define DEBUG//for debug

//======================================== use this to control input
#define STATION_NUM 15
// #define STATION_NUM 20
//=================================================================

//--------------------------DO NOT CHANGE THIS
#if STATION_NUM == 15
#define FILE_NAME "tsp15.txt"
#elif STATION_NUM == 20
#define FILE_NAME "tsp20.txt"
#endif
//--------------------------------------------

void f(int stationCode[], double dis[][STATION_NUM], int startCode);
bool back(double dis[][STATION_NUM], bool inStationStack[], stack<int> & stationStack, stack<double> & disStack);
int main(){
	//--------------------------------------- declaration
	int stationCode[STATION_NUM];
	double dis[STATION_NUM][STATION_NUM];

	//------------------------------------------ input
	ifstream fin;
	fin.open(FILE_NAME);
	for (int i = 0; i < STATION_NUM; ++i){
		fin >> stationCode[i];
	}
	for (int i = 0; i < STATION_NUM; ++i){
		fin >> dis[i][i];//read station code
		for (int j = 0; j < STATION_NUM; ++j){
			fin >> dis[i][j];//read distance
		}
	}
	fin.close();

#ifdef DEBUG
	for (int i = 0; i < STATION_NUM; ++i){
		cout << "station code: " << stationCode[i] << endl;
		for (int j = 0; j < STATION_NUM; ++j){
			cout << "\tdistence to " << stationCode[j] << " is " << dis[i][j] << endl;
		}
	}
	for (int i = 0; i < STATION_NUM; ++i){
		cout << "station index: " << i << endl;
		for (int j = 0; j < STATION_NUM; ++j){
			cout << "\tdistence to station" << j << " is " << dis[i][j] << endl;
		}
	}
#endif

	f(stationCode, dis, 567443);

	system("pause");
	return 0;
}

void f(int stationCode[], double dis[][STATION_NUM], int startCode){
	//find start index
	int startIndex;
	for (int i = 0; i < STATION_NUM; ++i){
		if (stationCode[i] == startCode){
			startIndex = i;
			break;
		}
	}

	//======================================================== get min weight path
	double minDis = -1;//min distance
	bool inStationStack[STATION_NUM];
	for (int i = 0; i < STATION_NUM; ++i){
		inStationStack[i] = false;
	}
	stack<int> stationStack;
	stack<double> disStack;
	stack<int> resultStack;
	stationStack.push(startIndex);
	disStack.push(0);
	inStationStack[startIndex] = true;
	bool flag = true;
	long count = 0;
	auto startTime = clock();

	while (flag){
#ifdef DEBUG
		cout << "Progress: " << stationStack.size() << "/" << STATION_NUM << endl;
#endif
		++count;
		int currentStation = stationStack.top();
		int currentDis = disStack.top();

		//if currentDis > minDis, cut
		if (minDis != -1 && currentDis > minDis){
			flag = back(dis, inStationStack, stationStack, disStack);
			continue;
		}

		//get a complete path?
		if (stationStack.size() == STATION_NUM){
			if (dis[stationStack.top()][startIndex] < 99998){
				//now get a complete path
				if (minDis == -1 ||  minDis > disStack.top() + dis[stationStack.top()][startIndex]){
					//new min path
					minDis = disStack.top() + dis[stationStack.top()][startIndex];
					resultStack = stationStack;
					//need pop
					flag = back(dis, inStationStack, stationStack, disStack);
					continue;
				}
			} else {
				//can not build a circle, need pop
				flag = back(dis, inStationStack, stationStack, disStack);
				continue;
			}
		}

		//get one more station
		bool getNewStation = false;
		for (int i = 0; i < STATION_NUM; ++i){
			if (!inStationStack[i] && dis[i][currentStation] < 99999){
				//feasible
				inStationStack[i] = true;
				stationStack.push(i);
				disStack.push(disStack.top() + dis[i][currentStation]);
				getNewStation = true;
				break;
			}
		}
		if (!getNewStation){
			//can not get new station, need pop
			flag = back(dis, inStationStack, stationStack, disStack);
		}
	}
	auto endTime = clock();

	//====================================== output
	if (resultStack.size() != STATION_NUM){
		cout << "Error\n";
		return;
	}

#ifndef DEBUG
	cout << "Path: " << endl << stationCode[startIndex] << endl;
	for (int i = 0; i < STATION_NUM; ++i){
		cout << stationCode[resultStack.top()] << endl;
		resultStack.pop();
	}
#else
	cout << "Path: " << endl << startIndex << endl;
	for (int i = 0; i < STATION_NUM; ++i){
		cout << resultStack.top() << endl;
		resultStack.pop();
	}
#endif
	cout << "\nMin weight path distance: " << minDis << endl;
	cout << "Count station " << count << "times\n";
	cout << "Time cost: " << (endTime - startTime) / 1000 << "s\n";
}

bool back(double dis[][STATION_NUM], bool inStationStack[], stack<int> & stationStack, stack<double> & disStack){
	while (1){
		int popStation = stationStack.top();
		stationStack.pop();
		disStack.pop();
		inStationStack[popStation] = false;
		if (!stationStack.size()){
			return false;
		}
		int currentStation = stationStack.top();
		for (int i = popStation + 1; i < STATION_NUM; ++i){
			if (!inStationStack[i] && dis[i][currentStation] < 99998){
				//now we get a new station
				stationStack.push(i);
				disStack.push(disStack.top() + dis[i][currentStation]);
				inStationStack[i] = true;
				return true;
			}
		}
	}
}
