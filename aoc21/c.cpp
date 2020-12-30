#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

const vector<string> operator&(const vector<string>& lhs, const vector<string>& rhs){
	vector<string> out;
	for(string a : lhs) for(string b : rhs) if(a==b) out.push_back(a);
	return out;
}

const vector<string> operator^(const vector<string>& lhs, const vector<string>& rhs){
	vector<string> out;
	for(string a : lhs) if(count(rhs.begin(), rhs.end(), a) == 0) out.push_back(a);
	return out;
}

ostream& operator<<(ostream& os, vector<string> const& in){
	for(string a: in) os << a << ",";
	return os;
}

pair<vector<string>, vector<string>> parse (string line){
	stringstream s(line);
	vector<string> ing;
	vector<string> all;
	while(true){
		string ingr;
		s >> ingr;
		if(ingr[0] == '(') break;
		ing.push_back(ingr);
	}

	while(true){
		string alle;	       
		if(!(s >> alle)) break;
		alle.pop_back();
		all.push_back(alle);
	}
	return pair<vector<string>, vector<string>> (all, ing);
}

bool test(map<string, vector<string>>& m){
	for(auto a: m) if(a.second.size() != 1) return false;
	return true;
}

int main(){
	string line;
	ifstream f("input");

	map<string, vector<string>> m;
	vector<string> alling;

	while(getline(f,line)){
		pair<vector<string>, vector<string>> curr = parse(line);
		for(string a : curr.second) alling.push_back(a);
	       	for(string a : curr.first){
			if(m.count(a) == 0){
				m.insert(pair<string, vector<string>>(a, curr.second));
			} else {
				m[a] = curr.second & m[a];
			}
		}
	}

	set<string> allall;
	for(auto a : m) for(string b: a.second) allall.insert(b);

	int total = 0;
	for(string a : alling) if(allall.count(a) == 0) total++;
	cout << total << endl;

	//should refactor the while loop with a function to make it better (allowing a return instead of having to break)
	bool flag;
	while(!test(m)){
		flag = false;
		for(auto a: m){
			if(a.second.size() == 1) continue;
			for(auto b: m){
				if(a==b) continue;
				if(b.second.size() != 1) continue;
				int g = a.second.size();
				m[a.first] = (a.second ^ b.second);
				if(m[a.first].size() < g){
					flag = true;
					break;
				}
				
			}
			if(flag) break;
		}
	}

	vector<string> ingredients;
	for(auto a: m) ingredients.push_back(a.second[0]);
	stringstream s;
	s << ingredients;
	cout << s.str().substr(0,s.str().size()-1) << endl;

	return 0;
}
