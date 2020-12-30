#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

struct grp{
	int num = 0;
	string answers = "";
};

int corr(grp& a){
	int out = 0;
	for(char b : a.answers)	if(count(a.answers.begin(), a.answers.end(), b) == a.num) out++;
	return out / a.num;
}

int tot(grp& a){
	set<char> x;
	for(char b : a.answers) x.insert(b);
	return x.size();
}

int main(){
	string line;
	ifstream myfile ("input");

	vector<grp> answers;
	grp curr;

	while (getline (myfile,line)){
		if(line == ""){
			answers.push_back(curr);
			curr.answers = "";
			curr.num = 0;
			continue;
		}
		curr.answers += line;
		curr.num++;
	}
	answers.push_back(curr);

	int total = 0;
	int total2 = 0;
 	for(grp x : answers){
		total += tot(x);
	       	total2 += corr(x);
	}

	cout << total << endl;
	cout << total2 << endl;

	return 0;
}
