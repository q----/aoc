#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

long long check_trees(vector<vector<bool>>& field, int right, int down){
	long long tree = 0;
	for(int i = 0; i < field.size()/down; i++) {
		if(field[i*down][(right*i) % field[i].size()]) tree++;
	}
	return tree;
}

int main(){
	string line;
	ifstream myfile ("input");
	vector<vector<bool>> field;

	while (getline (myfile,line)){
		vector<bool> l;
		for(int i = 0; i < line.size(); i++) l.push_back((line[i] == '#')? true: false);
		field.push_back(l);
	}

	long long x = check_trees(field, 3, 1);

	cout << x << endl;

	x *= check_trees(field, 1, 1);
	x *= check_trees(field, 5, 1);
	x *= check_trees(field, 7, 1);
	x *= check_trees(field, 1, 2);

	cout << x << endl;

	return 0;
}
