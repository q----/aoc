#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

struct cond{
	string n;
	int l;
	int lm;
	int hm;
	int h;
};

cond pcond(string line){
	for(int i = 0; i < line.size(); i++) if(line[i] == '-') line[i] = ' ';
	string str;
	string str2;
	stringstream s(line);

	cond out;

	s >> str;
	if(str[str.size()-1] != ':') s >> str2;
	out.n = str + " " + str2;
	s >> out.l;
	s >> out.lm;
	s >> str;
	s >> out.hm;
	s >> out.h;

	return out;
}

vector<int> ptix(string line, int num){
	for(int i = 0; i < line.size(); i++) if(line[i] == ',') line[i] = ' ';
	stringstream s(line);
	vector<int> out;

	for(int x = 0; x < num; x++){
		int i;
		s >> i;
		out.push_back(i);
	}

	return out;
}

bool test(cond a, int v){
	if((a.l <= v && a.lm >= v) || (a.hm <= v && a.h >= v)){
		return true;
	}
	return false;
}

int inv(vector<int> ticket, vector<cond> conds){
	int out = 0;
	for(int a : ticket){
		bool flag = false;
		for(cond b : conds){
			if(test(b, a)){
			       flag = true;
			}
		}
		if(!flag){
		       out += a;
		}
	}
	return out;
}
bool invc(vector<int> ticket, vector<cond> conds){
	int out = 0;
	for(int a : ticket){
		bool flag = false;
		for(cond b : conds){
			if(test(b, a)){
			       flag = true;
			}
		}
		if(!flag){
			return false;
		}
	}
	return true;
}

void validate(vector<int> ticket, map<string, vector<int>>& valid, vector<cond> c){
	for(int a = 0; a < ticket.size(); a++){
		for(cond b : c){
			if(!test(b,ticket[a])){
				valid.find(b.n)->second.erase(find(valid.find(b.n)->second.begin(),valid.find(b.n)->second.end(), a));
			}
		}
	}
}

int notin(vector<int> a, vector<int> b){
	for(int c : a) if(find(b.begin(), b.end(), c) == b.end()) return c;
	return -1;
}

int main(){
	string line;
	ifstream myfile ("input");

	vector<cond> conditions;
	vector<int> mticket;
	vector<vector<int>> otickets;
	map<string, vector<int>> valid;
	
	while(getline(myfile, line)){
		if(line == "") break;
		conditions.push_back(pcond(line));
	}

	getline(myfile,line);
	getline(myfile,line);

	mticket = ptix(line, conditions.size());

	getline(myfile,line);
	getline(myfile,line);

	while(getline(myfile, line)) otickets.push_back(ptix(line, conditions.size()));

	int total = 0;	
	for(vector<int> a : otickets) total += inv(a,conditions);
	cout << total << endl;

	vector<int> seed;
	
	for(int i = 0; i < conditions.size(); i++){
		seed.push_back(i);
	}
	for(cond a : conditions){
		valid.insert(pair<string, vector<int>>(a.n, seed));
	}

	for(vector<int> a : otickets){
		if(!invc(a, conditions)) continue;
		validate(a, valid, conditions);
	}

	map<string, int> aaaa;

	for(int x = conditions.size(); x > 1; x--){
		vector<int> first;
		vector<int> second;
		string str;
		for(auto a: valid){
			if(a.second.size() == x){
				first = a.second;
				str = a.first;
				break;
			}
		}	
		for(auto a: valid){
			if(a.second.size() == x-1){
				second = a.second;
				break;
			}
		}	
		aaaa.insert(pair<string, int>(str, notin(first,second)));
	}
	for(auto a: valid){
		if(a.second.size() == 1){
			aaaa.insert(pair<string, int>(a.first, a.second[0]));
		}
	}

	long long done = 1;
	for(auto a: aaaa){
		if(a.first[0] == 'd' && a.first[1] == 'e'){
			done *= mticket[a.second];
		}
	}
	cout << done << endl;
	return 0;
}
