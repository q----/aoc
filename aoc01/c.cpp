#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

int add2(vector<int>& a){
	for(int i = 0; i < a.size()-1; i++){
		for(int j = i + 1; j < a.size(); j++){
			if(a[i] + a[j] == 2020){
				return a[i] * a[j];
			}
		}
	}
	return 0;
}

int add3(vector<int>& a){
	for(int i = 0; i < a.size()-2; i++){
		for(int j = i + 1; j < a.size()-1; j++){
			for(int k = j + 1; k < a.size(); k++){
				if(a[i] + a[j] + a[k] == 2020){
					return a[i] * a[j] * a[k];
				}
			}
		}
	}
	return 0;
}

int main(){
	string line;
	vector<int> input;
	
	ifstream myfile ("input");
	while (getline (myfile,line)){
		stringstream s(line);
		int x = 0;
		s >> x;
		input.push_back(x);
	}

	cout << add2(input) << endl;
	cout << add3(input) << endl;
	
	return 0;
}
