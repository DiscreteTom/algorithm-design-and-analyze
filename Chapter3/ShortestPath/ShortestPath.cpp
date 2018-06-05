#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

// #define FILE_NAME "matrix22.txt"
// #define STATION_NUM 22
#define FILE_NAME "matrix42.txt"
#define STATION_NUM 42

void f(double dis[][STATION_NUM], int stationCode[], int sourceCode, int sinkCode = -1);

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
			fin >> dis[i][j];
		}
	}
	fin.close();

	//------------------------------------ output for debug
	// for (int i = 0; i < STATION_NUM; ++i){
	// 	cout << "station code: " << stationCode[i] << endl;
	// 	for (int j = 0; j < STATION_NUM; ++j){
	// 		cout << "\t" << dis[i][j] << endl;
	// 	}
	// }

	// f(dis, stationCode, 567443);
	// f(dis, stationCode, 567443, 33109);
	f(dis, stationCode, 565845);
	// f(dis, stationCode, 565845, 565667);
	

	system("pause");
	return 0;
}

//! if sinkCode == -1 then calculate all path
void f(double dis[][STATION_NUM], int stationCode[], int sourceCode, int sinkCode){
	//--------------------------------------- get sourceIndex and sinkIndex
	int sourceIndex = -1;
	int sinkIndex = -1;
	for (int i = 0; i < STATION_NUM; ++i){
		if (stationCode[i] == sourceCode){
			sourceIndex = i;
			break;
		}
	}
	if (sinkCode != -1){
		for (int i = 0; i < STATION_NUM; ++i){
			if (stationCode[i] == sinkCode){
				sinkIndex = i;
				break;
			}
		}
	}

	if (sourceIndex == -1) return;//error

	bool set[STATION_NUM];//if station[i] is in the set, set[i] = true
	for (int i = 0; i < STATION_NUM; ++i){
		set[i] = false;
	}
	set[sourceIndex] = true;
	bool flag = true;//if set[i] = true for all i, flag = false
	vector<int> path[STATION_NUM];
	
	while (flag){
		//------------------ add one more station in set
		//get closest station which is not in set
		int closestIndex = -1;
		double closestDis = -1;
		for (int i = 0; i < STATION_NUM; ++i){
			if (!set[i] && dis[i][sourceIndex] != -1){//not in set & reachable point
				if (closestDis == -1 || dis[i][sourceIndex] < closestDis){
					closestDis = dis[i][sourceIndex];
					closestIndex = i;
				}
			}
		}

		//put closest station in set
		set[closestIndex] = true;

		//refresh distance
		for (int i = 0; i < STATION_NUM; ++i){
			if (i != sourceIndex){
				if (dis[i][closestIndex] != -1){
					if (dis[sourceIndex][i] == -1 || dis[sourceIndex][i] > dis[sourceIndex][closestIndex] + dis[closestIndex][i]){
						dis[sourceIndex][i] = dis[sourceIndex][closestIndex] + dis[closestIndex][i];
						dis[i][sourceIndex] = dis[sourceIndex][i];
						path[i] = path[closestIndex];
						path[i].push_back(closestIndex);
					}
				}
			}
		}

		//judge flag
		flag = false;
		for (int i = 0; i < STATION_NUM; ++i){
			if (!set[i]){
				flag = true;
				break;
			}
		}

		//one-to-one situation, break loop
		if (sinkIndex != -1){
			if (set[sinkIndex]){
				flag = false;
			}
		}
	}

	//------------------------------- output
	ofstream fout;
	fout.open("output.txt");
	if (sinkIndex == -1){
		cout << "All path from " << sourceCode << ":\n";
		fout << "All path from " << sourceCode << ":\n";
		for (int i = 0; i < STATION_NUM; ++i){
			if (i != sourceIndex){
				cout << "To " << stationCode[i] << ": " << dis[sourceIndex][i] << endl;
				fout << "To " << stationCode[i] << ": " << dis[sourceIndex][i] << endl;
				cout << "\tPath:\n";
				fout << "\tPath:\n";
				for (int i = 0; i < path[i].size(); ++i){
					cout << "\t" << stationCode[i] << endl;
					fout << "\t" << stationCode[i] << endl;
				}
			}
		}
	} else {
		cout << "Distance from " << sourceCode << " to " << sinkCode << " is ";
		fout << "Distance from " << sourceCode << " to " << sinkCode << " is ";
		cout << dis[sourceIndex][sinkIndex] << endl;
		fout << dis[sourceIndex][sinkIndex] << endl;
		cout << "\tPath:\n";
		fout << "\tPath:\n";
		for (int i = 0; i < path[sinkIndex].size(); ++i){
			cout << "\t" << stationCode[sinkIndex] << endl;
			fout << "\t" << stationCode[sinkIndex] << endl;
		}
	}
}
