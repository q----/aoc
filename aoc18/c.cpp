#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

long long ev(stringstream& s){
	vector<long long> num;
	vector<char> op;

	long long x;
	s >> x;
	num.push_back(x);

	while(true){
		char o;
		if(!(s >> o)) break;
		op.push_back(o);
		long long y;
		s >> y;
		num.push_back(y);
	}

	while(find(op.begin(), op.end(), '+') != op.end()){
		for(int f = 1; f < num.size(); f++){
			if(op[f-1] == '+'){
				num[f-1] += num[f];
				num.erase(num.begin() + f);
				op.erase(op.begin() + f - 1);
				break;
			}
		}
	}

	long long out = num[0];
	for(int f = 1; f < num.size(); f++) out *= num[f];	

	return out;	
}

long long reduce(string in){
	while(in.find("(") != string::npos){
		int start;
		for(int i = 0; i < in.size(); i++){
			if(in[i] == '(') start = i;
			if(in[i] == ')') {
				stringstream s(in.substr(start+1,i-start-1));
				string rep = to_string(ev(s));
				in.replace(start,i-start+1, rep);
				break;
			}
		}
	}
	stringstream q(in);
	return ev(q);
}

int main(){
	string line;
	long long total = 0;

	ifstream myfile ("input");
	while (getline (myfile,line)) total += reduce(line);

	cout << total << endl;

	return 0;
}
