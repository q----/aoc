#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <set>
#include <algorithm>
#include <vector>

using namespace std;

int maxsize=0;

set<string> operator+ (const set<string>& lhs, const set<string>& rhs){
	set<string> out;
	for(string a : lhs) for(string b : rhs) out.insert(a + b);
	return out;
}

pair<int, string> parse(string line){
	for(int i = 0; i < line.size(); i++) if(line[i] == ':') line[i] = ' ';
	stringstream s(line);
	int x;
	s >> x;
	string str;
	getline(s, str);
	return pair<int, string>(x, str.substr(2));
}


set<string> comp(int val, map<int, string>& urules, map<int, set<string>>& rules){
	auto it = rules.find(val);
	if(it != rules.end()){
		return it->second;
	}
	if(urules[val] == "\"a\""){
		set<string> out = {"a"};
		rules.insert(pair<int, set<string>>(val, out));
		return out;
	}
	if(urules[val] == "\"b\""){
		set<string> out = {"b"};
		rules.insert(pair<int, set<string>>(val, out));
		return out;
	}

	stringstream s(urules[val]);
	set<string> out;
	set<string> temp = {""};
	string line;
	while(true){
		string ss;
		if(!(s >> ss)) break;
		
		if(ss == "|"){
			for(string a : temp) out.insert(a);
			temp = {""};
			continue;
		}
		int x;
		stringstream sss(ss);
		sss >> x;
		temp = temp + comp(x, urules, rules);
	}
	for(string a : temp) out.insert(a);
	rules.insert(pair<int, set<string>>(val,out));

	return out;
}

bool test(string line, set<string>& ft, set<string>& to){
	if(line.size() % 8 != 0) return false;
	bool flag = true;
	bool flag2 = false;
	int chk = 0;
	for(int i = 0; i < line.size() / 8; i++){
		if(flag){
			if(find(ft.begin(), ft.end(), line.substr(i*8, 8)) != ft.end()){
				chk++;
				continue;
			} else {
				flag = false;
			}
		}
		if(!flag){
			if(find(to.begin(), to.end(), line.substr(i*8, 8)) != to.end()){
				chk--;
				flag2 = true;
				continue;
			} else {
				return false;
			}
		}
	}
	return (chk >= 1)&&flag2;
}

int main(){
	string line;
	ifstream f("input");

	map<int, string> urules;

	while(getline(f,line)){
		if(line == "") break;
		urules.insert(parse(line));
	}

	vector<string> a;

	map<int, set<string>> rules;	
	set<string> ft = comp(42, urules, rules);
	set<string> to = comp(31, urules, rules);

	set<string> zero = comp(0, urules, rules);

	cout << "comp complete" << endl;

	int total = 0;
	int total2 = 0;

	while(getline(f,line)){
		if(find(zero.begin(), zero.end(), line) != zero.end()){total++;
		}else{ if(test(line, ft, to)) total2++;}

	}

	cout << total << endl;
	cout << total + total2 << endl;

	return 0;
}
