#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <set>

using namespace std;

struct inst{
	string op;
	int arg;
};

inst parse(string& line){
	inst curr;
	stringstream s(line);
	s >> curr.op;
	s >> curr.arg;
	return curr;
}

bool change(vector<inst>& prog, int chg){
	if(chg == -1) return true;
	if(prog[chg].op == "acc") return false;
	prog[chg].op = (prog[chg].op == "nop")?"jmp":"nop";
	return true;
}

bool test(vector<inst> prog, int chg){
	int acc = 0;
	int i = 0;
	set<int> ran;
	if(!change(prog, chg)) return false;
	while(i < prog.size()){
		if (ran.find(i) != ran.end()){
		       if(chg == -1) cout << acc << endl;
	       	       return false;
		}
		ran.insert(i);
		if(prog[i].op == "jmp"){
			i += prog[i].arg;
			continue;
		}
		if(prog[i].op == "acc"){
			acc += prog[i].arg;
		}
		i++;
	}	
	cout << acc << endl;
	return true;
}

int main(){
	string line;
	ifstream myfile ("input");
	vector<inst> prog;

	while (getline (myfile,line)) prog.push_back(parse(line));

	int chg = -1;
	while(!test(prog,chg)) chg++;

	return 0;
}
