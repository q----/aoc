#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int value(string& a){
	int out = 0;
	for(int i = 0; i < a.size(); i++){
		out *= 2;
		if(a[i] == 'B' || a[i] == 'R') out++;
	}
	return out;
}

int main(){
	string line;
	ifstream myfile ("input");
	vector<int> values;

	while (getline (myfile,line)) values.push_back(value(line));
	
	int min = *min_element(values.begin(), values.end());
	int max = *max_element(values.begin(), values.end());

	cout << max << endl;

	for(int i = min; i < max; i++) if(find(values.begin(), values.end(), i) == values.end()) cout << i << endl;

	return 0;
}
