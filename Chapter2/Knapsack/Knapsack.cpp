#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

struct Item{
	int weight;
	int value;
};

void f(const int capacity, const vector<Item> & items);

int main(){
	vector<Item> items1, items2;
	//------------------------------------- input
	{
		vector<int>weight_buf;
		ifstream fin;
		fin.open("knapsack.txt");
		string t;
		fin >> t >> t >> t;
		for (int i = 0; i < 50; ++i){
			int weight;
			fin >> weight;
			weight_buf.push_back(weight);
		}
		fin >> t;
		for (int i = 0; i < 50; ++i){
			int value;
			fin >> value;
			items1.push_back({weight_buf[i], value});
		}
		weight_buf.clear();
		fin >> t >> t >> t >> t;
		for (int i = 0; i < 99; ++i){
			int weight;
			fin >> weight;
			weight_buf.push_back(weight);
		}
		fin >> t;
		for (int i = 0; i < 99; ++i){
			int value;
			fin >> value;
			items2.push_back({weight_buf[i], value});
		}
		fin.close();
	}

	//output for debug
	// {
	// 	cout << "Items1:\n";
	// 	for (int i = 0; i < items1.size(); ++i){
	// 		cout << i << " weight: " << items1[i].weight << " value: " << items1[i].value << endl;
	// 	}
	// 	cout << "Items2:\n";
	// 	for (int i = 0; i < items2.size(); ++i){
	// 		cout << i << " weight: " << items2[i].weight << " value: " << items2[i].value << endl;
	// 	}
	// }

	cout << "Data1:\n";
	f(300, items1);
	cout << "Data2:\n";
	f(600, items2);

	system("pause");
	return 0;
}

void f(const int capacity, const vector<Item> & items){
	//choice
	enum Choice{NOT_FIT, IN, NOT_IN};

	//----------------------------------- get memory & init
	int ** result = new int*[items.size() + 1];//result[0] will be filled with 0
	Choice ** choice = new Choice*[items.size() + 1];

	for (int i = 0; i <= items.size(); ++i){
		result[i] = new int[capacity + 1];
		choice[i] = new Choice[capacity + 1];
		for (int j = 0; j < capacity; ++j){
			result[i][j] = 0;
		}
	}
	bool * chosen = new bool[items.size()];
	for (int i = 0; i < items.size(); ++i){
		chosen[i] = false;
	}

	/*
	result[i][j] means the result value
	i means items[i - 1] to items[items.size() - 1] can be choose
		while items[0] to items[i - 2] has been decided
	j means the remain capacity of the knapsack
	*/

	//----------------------------------------- get max value
	for (int i = 1; i <= items.size(); ++i){
		for (int j = 1; j <= capacity; ++j){
			if (j < items[i - 1].weight){
				//can NOT fit this item
				result[i][j]  = result[i - 1][j];
				choice[i][j] = NOT_FIT;
			} else {//can fit this item
				//if we DO put this item in
				result[i][j] = items[i - 1].value + result[i - 1][j - items[i - 1].weight];
				choice[i][j] = IN;
				//if we DO NOT put this item in
				int t = result[i - 1][j];
				//compare
				if (t > result[i][j]){
					result[i][j] = t;
					choice[i][j] = NOT_IN;
				}
			}
		}
	}

	//------------------------------------ get items in this knapsack and total weight
	int ii = items.size(), jj = capacity;
	while (ii){
		if (choice[ii][jj] == IN){
			chosen[ii - 1] = true;
			jj -= items[ii - 1].weight;
		}
		--ii;
	}
	int totalWeight = capacity - jj;

	//output
	cout << "Max value in this knapsack is " << result[items.size()][capacity] << endl;
	cout << "Total weight of this knapsack is " << totalWeight << endl;
	cout << "The following items are in this knapsack\n";
	for (int i = 0; i < items.size(); ++i){
		if (chosen[i]){
			cout << i + 1 << " weight: " << items[i].weight << " value: " << items[i].value << endl;
		}
	}
	cout << endl;


	//--------------------------------------- free memory
	for (int i = 0; i <= items.size(); ++i){
		delete [] result[i];
	}
	delete [] result;
}