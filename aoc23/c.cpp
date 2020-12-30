#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

const string input = "853192647";

//vector<int>::iterator operator+(const vector<int>::iterator lhs, const int &rhs){
//	auto it = lhs;
//	for(int i = 0; i < rhs; i++) ++it;
//	return it;
//}

string rotate(string in){
	return in.substr(1) + in[0];
}

vector<int> rotate(vector<int> in){
	in.push_back(in.front());
	in.erase(in.begin());
	return in;
}

char m1(char a){
	return (((a-58)%9)+57);
}

int m1(int a){
	return (((a-1000001)%1000000)+1000000);
}

string step(string in){
	string rem = in.substr(1,3);
	in.erase(1,3);
	char f = m1(in[0]);
	while(rem.find(f) != string::npos) f = m1(f);
	in.insert(in.find(f)+1, rem);
	return rotate(in);
}

vector<int> step(vector<int>& in){
	vector<int> rem;
	for(int i = 1; i < 4; i++){
		rem.push_back(in[i]);
	}
	in.erase(in.begin()+1, in.begin()+ 4);
	int f = m1(in.front());
	while(find(rem.begin(), rem.end(), f) != rem.end()) f = m1(f);
	in.insert(find(in.begin(),in.end(),f), rem.begin(), rem.end());
	return rotate(in);
}

int main(){
	string curr = input;

	for(int i = 0; i < 100; i++) curr = step(curr);

	while(curr[0] != '1') curr = rotate(curr);

	cout << curr.substr(1) << endl;

	vector<int> cups;
	
	for(char a: input){
	       cups.push_back(a-48);
	}
	for(int i = 10; i <= 1000000; i++){
	       cups.push_back(i);
	}

	for(int i = 0; i < 10000000; i++){
	       cups = step(cups);
	       cout << i << endl;
	}

	auto it = find(cups.begin(), cups.end(), 1);
	cout << *(++it) * *(++it) << endl;



	return 0;
}
