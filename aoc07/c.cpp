#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <set>

using namespace std;

struct bags{
	string o;
	string i;
	int num;
};

vector<bags> parse(string& line){
	stringstream s(line);
	bags a;
	vector<bags> out;
	string b;
	string c;
	int num;
	s >> b;
	s >> c;
	a.o = b + " " + c;
	s >> b; //bags
	s >> b; //contain
	while(s >> num){
		s >> b;
		s >> c;
		a.i = b + " " + c;
		a.num = num;
		s >> b; //bags,
		out.push_back(a);
	}
	return out;
}

int contains(vector<bags>& rules, string bag){
	int total = 1;
	for(bags a : rules) if(a.o == bag) total += a.num * contains(rules, a.i);
	return total;
}


int main(){
	string line;
	ifstream myfile ("input");

	vector<bags> hey;
	set<string> target;
	target.insert("shiny gold");

	while (getline (myfile,line)) for(auto a : parse(line))	hey.push_back(a);

	bool done = false;
	while(!done){
		done = true;
		for(auto a : hey){
			if((target.find(a.i) != target.end()) && (target.find(a.o) == target.end())){
				done = false;
				target.insert(a.o);
			}
		}
	}

	cout << target.size() - 1 << endl;
	cout << contains(hey, "shiny gold") - 1 << endl;
	return 0;
}
