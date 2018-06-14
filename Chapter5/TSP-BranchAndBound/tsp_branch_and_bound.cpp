#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <queue>
#include <ctime>

using namespace std;

// #define DEBUG//for debug

//======================================== use this to control input
// #define STATION_NUM 15
// #define STATION_NUM 20
#define STATION_NUM 22
//=================================================================

//--------------------------DO NOT CHANGE THIS
#if STATION_NUM == 15
#define FILE_NAME "tsp15.txt"
#elif STATION_NUM == 20
#define FILE_NAME "tsp20.txt"
#elif STATION_NUM == 22
#define FILE_NAME "tsp22.txt"
#endif
//--------------------------------------------

void f(const int stationCode[], const double dis[][STATION_NUM], int startCode);
double greedy(double bias, const vector<int> & path, int startIndex, const double dis[][STATION_NUM]);
double getMin(const double bias, const vector<int> & path, int startIndex, const double dis[][STATION_NUM]);

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
	// for (int i = 0; i < STATION_NUM; ++i){
	// 	cout << "station code: " << stationCode[i] << endl;
	// 	for (int j = 0; j < STATION_NUM; ++j){
	// 		cout << "\tdistence to " << stationCode[j] << " is " << dis[i][j] << endl;
	// 	}
	// }
	// for (int i = 0; i < STATION_NUM; ++i){
	// 	cout << "station index: " << i << endl;
	// 	for (int j = 0; j < STATION_NUM; ++j){
	// 		cout << "\tdistence to station" << j << " is " << dis[i][j] << endl;
	// 	}
	// }
#endif

	f(stationCode, dis, 567443);

	system("pause");
	return 0;
}

void f(const int stationCode[], const double dis[][STATION_NUM], int startCode){
	//find start index
	int startIndex;
	for (int i = 0; i < STATION_NUM; ++i){
		if (stationCode[i] == startCode){
			startIndex = i;
			break;
		}
	}

	long count = 0;//number of stations we search

	vector<int> toBeDealWith;//ANT
	vector<vector<int>> path;//not include startStation
	vector<double> bias;
	vector<double> lb;
	toBeDealWith.push_back(startIndex);
	path.push_back(vector<int>());//path[i][0] is not the startIndex
	bias.push_back(0);
	lb.push_back(99999);
	double max = greedy(bias[0], path[0], startIndex, dis);
	double min = getMin(bias[0], path[0], startIndex, dis);
	double result = -1;
	vector<int> resultPath;
	auto startTime = clock();
#ifdef DEBUG
	int preSize = -1;
#endif
	bool flag = true;
	while (flag){
#ifdef DEBUG
		// cout << "Number of nodes to be deal with: " << toBeDealWith.size() << endl;
		// cout << "Path[0] = \n";
		// for (int i = 0; i < path[0].size(); ++i){
		// 	cout << "\t" << path[0][i] << endl;
		// }
		if (preSize != path[0].size()){
			cout << "path[0].size() = " << path[0].size() << endl;
			preSize = path[0].size();
		}
#endif
		++count;
		int minIndex;
		{//get minIndex
			double min = -1;
			for (int i = 0; i < lb.size(); ++i){
				if (min < 0 || min > lb[i]){
					min = lb[i];
					minIndex = i;
				}
			}
		}
		//need to erase minIndex before judge result
		auto thisIndex = toBeDealWith[minIndex];
		auto thisPath = path[minIndex];
		auto thisBias = bias[minIndex];
		auto thisLb = lb[minIndex];
		toBeDealWith.erase(toBeDealWith.begin() + minIndex);
		path.erase(path.begin() + minIndex);
		bias.erase(bias.begin() + minIndex);
		lb.erase(lb.begin() + minIndex);
		//deal with toBeDealWith[minIndex]'s subnodes, get max and min
		bool inPath[STATION_NUM];
		for (int i = 0; i < STATION_NUM; ++i){
			inPath[i] = false;
		}
		for (int i = 0; i < thisPath.size(); ++i){
			inPath[thisPath[i]] = true;
		}
		for (int i = 0; i < STATION_NUM; ++i){
			if (i == startIndex && thisPath.size() != STATION_NUM - 1) continue;
			if (!inPath[i] && dis[thisIndex][i] < 99998){
				//push
				toBeDealWith.push_back(i);
				path.push_back(vector<int>(thisPath));
				path[path.size() - 1].push_back(i);
				bias.push_back(thisBias + dis[thisIndex][i]);
				double m_max = greedy(bias[bias.size() - 1], path[path.size() - 1], startIndex, dis);
				double m_min = getMin(bias[bias.size() - 1], path[path.size() - 1], startIndex, dis);
				lb.push_back(m_min);
				if (m_min <= max){
					if (m_max < max) max = m_max;//refresh max

					//judge result
					if (i == startIndex){
						double t_result = thisBias + dis[thisIndex][i];
						if (result < 0 || result > t_result){
							//get a new result, delete it from queue
							bias.pop_back();
							lb.pop_back();
							path.pop_back();
							toBeDealWith.pop_back();
							//refresh result
							result = t_result;
							resultPath = thisPath;
							resultPath.insert(resultPath.begin(), startIndex);
							max = result;
							//delete in toBeDealWith
							for (int i = 0; i < path.size(); ++i){
								if (lb[i] > max){
									toBeDealWith.erase(toBeDealWith.begin() + i);
									path.erase(path.begin() + i);
									lb.erase(lb.begin() + i);
									bias.erase(bias.begin() + i);
									--i;
								}
							}
						}
					}
				}
			}
		}
		if (!path.size()){
			flag = false;
		}
	}
	auto endTime = clock();
	//now we get result
	//======================================= output
	if (result < 0){
		cout << "error\n";
		cout << "result = " << result << endl;
		cout << "Count station " << count << " times\n";
	} else {
		cout << "=============== Using Branch and Bound Method ============\n";
		cout << "Shortest path:\n";
		cout << "   " << startCode << endl;
		for (int i = 1; i < resultPath.size(); ++i){
			cout << "-> " << stationCode[resultPath[i]] << endl;
		}
		cout << "Distance:\n";
		cout << "   " << dis[startIndex][resultPath[0]] << endl;
		for (int i = 1; i < resultPath.size(); ++i){
			cout << " + " << dis[resultPath[i - 1]][resultPath[i]] << endl;
		}
		cout << " = " << result << endl;
		cout << "Count station " << count << " times\n";
		if (endTime - startTime > 1000)
			cout << "Time: " << (endTime - startTime) / 1000 << "s\n";
		else
			cout << "Time: " << endTime - startTime << "ms\n"; 
	}
}

double greedy(double bias, const vector<int> & path, int startIndex, const double dis[][STATION_NUM]){
	bool inPath[STATION_NUM];
	for (int i = 0; i < STATION_NUM; ++i){
		inPath[i] = false;
	}
	for (int i = 0; i < path.size(); ++i){
		inPath[path[i]] = true;
	}
	inPath[startIndex] = true;
	//---------------------------------- init inPath done.
	int start = startIndex;
	if (path.size()) start = path[path.size() - 1];
	double result = bias;
	bool flag = true;
	while (flag){
		//find closest point
		double min = -1;
		int minIndex;
		for (int i = 0; i < STATION_NUM; ++i){
			if (!inPath[i] && dis[start][i] < 99998){//not in path and reachable
				if (min < 0 || min > dis[start][i]){
					min = dis[start][i];
					minIndex = i;
				}
			}
		}
		//now we get the closest point
		if (min < 0){
			return 99999;//can not reach every point
		}
		inPath[minIndex] = true;
		result += dis[start][minIndex];
		start = minIndex;

		//judge flag
		flag = false;
		for (int i = 0; i < STATION_NUM; ++i){
			if (!inPath[i]){
				flag = true;
				break;
			}
		}
	}
	return result + dis[start][startIndex];
}

double getMin(const double bias, const vector<int> & path, int startIndex, const double dis[][STATION_NUM]){
	double result = 2 * bias;
	bool inPath[STATION_NUM];
	for (int i = 0; i < STATION_NUM; ++i){
		inPath[i] = false;
	}
	for (int i = 0; i < path.size(); ++i){
		inPath[path[i]] = true;
	}
	double minOfStart = -1;
	double minOfEnd = -1;
	int endIndex = startIndex;
	if (path.size()) endIndex = path[path.size() - 1];
	for (int i = 0; i < STATION_NUM; ++i){//deal with startOfPath and EndOfPath
		if (!inPath[i] && dis[i][startIndex] < 99998){
			if (minOfStart < 0 || minOfStart > dis[i][startIndex]){
				minOfStart = dis[i][startIndex];
			}
		}
		if (!inPath[i] && dis[i][endIndex] < 99998){
			if (minOfEnd < 0 || minOfStart > dis[i][endIndex]){
				minOfEnd = dis[i][endIndex];
			}
		}
	}
	result += minOfStart + minOfEnd;
	for (int i = 0; i < STATION_NUM; ++i){
		if (inPath[i] || i == startIndex) continue;
		//find two closest point
		double min1 = -1;
		double min2 = -1;//make sure that min1 < min2
		for (int j = 0; j < STATION_NUM; ++j){
			if (dis[i][j] < 99998){
				if (min1 < 0) min1 = dis[i][j];
				else if (min2 < 0) min2 = dis[i][j];
				else if (min1 > dis[i][j]){
					min2 = min1;
					min1 = dis[i][j];
				} else if (min2 > dis[i][j]) min2 = dis[i][j];
			}
		}
		if (min1 < 0 || min2 < 0) return 99999;
		result += min1 + min2;
	}
	return result / 2;
}