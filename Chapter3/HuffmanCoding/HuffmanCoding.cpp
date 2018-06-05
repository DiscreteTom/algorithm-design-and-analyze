#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>

using namespace std;

#define FILE_NAME "huffman.txt"

//================================================= class Node
class Node{
public:
	char c;
	int w;
	Node * lChild;
	Node * rChild;

	Node(char ch, int weight);//leaf constructor
	Node(int weight, Node * leftChild = NULL, Node * rightChild = NULL);//middle node ctor
	Node * operator+(Node & another);//get middle node
};
Node::Node(int weight, Node * leftChild, Node * rightChild){
	c = 0;
	w = weight;
	lChild = leftChild;
	rChild = rightChild;
}
Node::Node(char ch, int weight){
	c = ch;
	w = weight;
	lChild = rChild = NULL;
}
Node * Node::operator+(Node & another){
	return new Node(w + another.w, this, &another);
}

//================================================ struct Code
struct Code{
	char c;
	string code;
};

//=================================================== function declaration
Node * popMinNode(vector<Node *> & nodes);


//================================================= main
int main(){
	//-------------------------------- init
	int num[53];
	for (int i = 0; i < 53; ++i){
		num[i] = 0;
	}

	/*
	format:
	num[0] ~ num[25] = a ~ z
	num[26] ~ num[51] = A ~ Z
	num[52] = #
	*/

	//----------------------------------- input
	ifstream fin;
	fin.open(FILE_NAME);
	string str[5];
	for (int i = 0; i < 5; ++i){
		fin >> str[i];
		for (int j = 0; j < str[i].length(); ++j){
			if (str[i][j] >= 'a' && str[i][j] <= 'z'){
				++num[str[i][j] - 'a'];
			} else if (str[i][j] >= 'A' && str[i][j] <= 'Z'){
				++num[str[i][j] - 'A' + 26];
			} else if (str[i][j] == '#'){
				++num[52];
			}
		}
	}
	fin.close();

	vector<Node *> tree;
	ofstream fout;
	fout.open("output.txt");

	//---------------------------- output char count and construct tree
	{
		cout << "char count:\n";
		fout << "char count:\n";
		for (int i = 0; i < 26; ++i){
			cout << (char)(i + 'a') << ": " << num[i] << endl;
			fout << (char)(i + 'a') << ": " << num[i] << endl;
			if (num[i]){
				tree.push_back(new Node(i + 'a', num[i]));
			}
		}
		for (int i = 26; i < 52; ++i){
			cout << (char)(i + 'A' - 26) << ": " << num[i] << endl;
			fout << (char)(i + 'A' - 26) << ": " << num[i] << endl;
			if (num[i]){
				tree.push_back(new Node(i + 'A' - 26, num[i]));
			}
		}
		cout << "#: " << num[52] << endl;
		fout << "#: " << num[52] << endl;
		if (num[52]){
			tree.push_back(new Node('#', num[52]));
		}
	}

	//----------------------------------------------- merge node
	while (tree.size() != 1){
		//get two Node with min weight
		Node * node1 = popMinNode(tree);
		Node * node2 = popMinNode(tree);
		Node * result = *node1 + *node2;
		tree.push_back(result);
	}

	//now we get a tree, tree[0] is the pointer to the root

	//----------------------- construct huffman code, use stack instead of recursion
	stack<Node *> nodeStack;//save next Node to be deal with
	stack<string> codeStack;
	vector<Code> codes;
	nodeStack.push(tree[0]);
	codeStack.push(string());
	while (nodeStack.size()){
		Node * currentNode = nodeStack.top();
		nodeStack.pop();
		string code = codeStack.top();
		codeStack.pop();
		if (currentNode->lChild){
			nodeStack.push(currentNode->lChild);
			codeStack.push(code + '0');
		}
		if (currentNode->rChild){
			nodeStack.push(currentNode->rChild);
			codeStack.push(code + '1');
		}
		if (!currentNode->lChild && !currentNode->rChild){
			codes.push_back({currentNode->c, code});
		}
	}

	//-------------------------------------------- output huffman code
	cout << "\nHuffman Code:\n";
	fout << "\nHuffman Code:\n";
	for (int i = 0; i < codes.size(); ++i){
		cout << codes[i].c << ": " << codes[i].code << endl;
		fout << codes[i].c << ": " << codes[i].code << endl;
	}

	//---------------------------------------------- count bits
	cout << "\nbit length:\n";
	fout << "\nbit length:\n";
	cout << "Using Fixed Length Coding: ";
	fout << "Using Fixed Length Coding: ";
	int charNum = 0;
	for (int i = 0; i < 5; ++i){
		charNum += str[i].length();
	}
	cout << charNum * 8 << endl;//8 bit per char
	fout << charNum * 8 << endl;//8 bit per char
	int bitNum = 0;
	for (int i = 0; i < codes.size(); ++i){
		if (codes[i].c >= 'a' && codes[i].c <= 'z'){
			bitNum += num[codes[i].c - 'a'] * codes[i].code.length();
		} else if (codes[i].c >= 'A' && codes[i].c <= 'Z'){
			bitNum += num[codes[i].c - 'A' + 26] * codes[i].code.length();
		} else {
			bitNum += num[52] * codes[i].code.length();//'#'
		}
	}
	cout << "Using Huffman Coding: " << bitNum << endl;
	fout << "Using Huffman Coding: " << bitNum << endl;

	//-------------------------------- free memory, use stack instead of recursion
	stack<Node *> freeStack;
	freeStack.push(tree[0]);
	while (freeStack.size()){
		Node * t = freeStack.top();
		freeStack.pop();
		if (t->lChild){
			freeStack.push(t->lChild);
		}
		if (t->rChild){
			freeStack.push(t->rChild);
		}
		delete t;
	}

	fout.close();
	system("pause");
	return 0;
}

Node * popMinNode(vector<Node *> & nodes){
	int min = nodes[0]->w;
	int index = 0;

	//find min weight node
	for (int i = 1; i < nodes.size(); ++i){
		if (nodes[i]->w < min){
			min = nodes[i]->w;
			index = i;
		}
	}

	//delete element and return
	Node * result = nodes[index];
	nodes.erase(nodes.begin() + index);
	return result;
}