#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

struct pass{
	int byr;
	int iyr;
	int eyr;
	int hgt;
	bool in;
	string hcl;
	string ecl;
	string pid;
};

vector<string> files{"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"};

pass parse(string& entry){
	pass out;
	for (auto a : files){
		int x = entry.find(a);
		string s = entry.substr(x+4, entry.find(" ", x)-x-4);
		if(a == "byr"){
			stringstream f(s);
			f >> out.byr;
		}
		if(a == "iyr"){
			stringstream f(s);
			f >> out.iyr;
		}
		if(a == "eyr"){
			stringstream f(s);
			f >> out.eyr;
		}
		if(a == "hgt"){
			out.in = (s.find("cm") == string::npos);
			stringstream f(s.substr(0,-2));
			f >> out.hgt;
		}
		if(a == "hcl"){
			out.hcl = s.substr(1);
		}
		if(a == "ecl"){
			out.ecl = s;
		}
		if(a == "pid"){
			out.pid = s;
		}
	}
	return out;
}

bool valid(string& pport){
	for(auto a : files) if(pport.find(a) == string::npos) return false;
	return true;
}

bool valid2(pass in){
	if(in.byr < 1920 || in.byr > 2002) return false;
	if(in.iyr < 2010 || in.iyr > 2020) return false;
	if(in.eyr < 2020 || in.eyr > 2030) return false;
	if((in.in)?(in.hgt < 59 || in.hgt > 76):(in.hgt < 150 || in.hgt > 193)) return false;
	if(in.hcl.size() != 6) return false;
	string s = "amb blu brn gry grn hzl oth";
	if( s.find(in.ecl)== string::npos) return false;
	if(in.pid.size() != 9) return false;
	return true;
}

int main(){
	string line;
	ifstream myfile ("input");
	vector<string> pports;
	
	string x = "";

	while (getline (myfile,line)){
		if(line == ""){
			pports.push_back(x);
			x = "";
		} else {
			x += " " + line;
		}	
	}
	pports.push_back(x);
	
	int total = 0;
	int total2 = 0;

	for(int i = 0; i < pports.size(); i++){
	       	if(!valid(pports[i])) continue;
		total++;
		pass port = parse(pports[i]);
		if(valid2(port)) total2++;
		
	}

	cout << total << endl;
	cout << total2 << endl;

	return 0;
}
