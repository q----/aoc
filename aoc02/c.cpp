#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

struct info{
	int s = 0;
	int e = 0;
	char c;
	string p;
};

info parse(string& line){
	info o;
	
	int a = line.find('-');
	int b = line.find(' ');
	o.c = line[b+1];
	o.p = line.substr(line.find(' ',b+1)+1);

	stringstream ss;
	ss << line.substr(0,a) << ' ' << line.substr(a+1, b-a-1);
	ss >> o.s >> o.e;

	return o;
}

int valid(info& in){
	int num = 0;
	for(int i = 0; i < in.p.size(); i++) if(in.p[i] == in.c) num++;
	return (num >= in.s && num <= in.e)? 1 : 0;
}


int valid2(info& i){
	return (i.p[i.s-1] == i.c ^ i.p[i.e-1] == i.c)? 1 : 0;
}

int main(){
	string line;
	int total = 0;
	int total2 = 0;
	
	ifstream myfile ("input");
	while (getline (myfile,line)){
		info in = parse(line);
		total += valid(in);
		total2 += valid2(in);
	}

	cout << total << endl;
	cout << total2 << endl;
	
	return 0;
}
