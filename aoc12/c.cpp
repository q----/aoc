#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <cmath>

using namespace std;

struct inst{
	char op;
	int arg;
};

struct ship{
	int n = 0;
	int e = 0;
	int d = 90;
};

struct wp{
	int n = 1;
	int e = 10;
};

struct ship2{
	wp w;
	int n = 0;
	int e = 0;
};

inst parse(string& line){
	inst temp;
	temp.op = line[0];
	stringstream s(line.substr(1));
	s >> temp.arg;
	return temp;
}

void run(inst& com, ship& ferry){
	if(com.op == 'N') ferry.n += com.arg;
	if(com.op == 'S') ferry.n -= com.arg;
	if(com.op == 'E') ferry.e += com.arg;
	if(com.op == 'W') ferry.e -= com.arg;
	if(com.op == 'R') ferry.d = ((ferry.d + com.arg) % 360 + 360) % 360;
	if(com.op == 'L') ferry.d = ((ferry.d - com.arg) % 360 + 360) % 360;;
	if(com.op == 'F'){
		if(ferry.d == 0) ferry.n += com.arg;
		if(ferry.d == 90) ferry.e += com.arg;
		if(ferry.d == 180) ferry.n -= com.arg;
		if(ferry.d == 270) ferry.e -= com.arg;
	}
}

void run2(inst com, ship2& ferry){
	if(com.op == 'N') ferry.w.n += com.arg;
	if(com.op == 'S') ferry.w.n -= com.arg;
	if(com.op == 'E') ferry.w.e += com.arg;
	if(com.op == 'W') ferry.w.e -= com.arg;
	if(com.op == 'L'){
	       	com.op = 'R';
		com.arg = 360 - com.arg;
	}
	if(com.op == 'R'){
		if(com.arg == 0) return;
		if(com.arg == 90){
			int temp = ferry.w.n;
			ferry.w.n = -ferry.w.e;
			ferry.w.e = temp;
		}
		if(com.arg == 180){
			ferry.w.n *= -1;
			ferry.w.e *= -1;
		}
		if(com.arg == 270){
			int temp = ferry.w.n;
			ferry.w.n = ferry.w.e;
			ferry.w.e = -temp;
		}
	}
	if(com.op == 'F'){
		ferry.n += com.arg * ferry.w.n;
		ferry.e += com.arg * ferry.w.e;
	}
}

int distance(ship& ferry){
	return abs(ferry.n) + abs(ferry.e);
}

int distance(ship2& ferry){
	return abs(ferry.n) + abs(ferry.e);
}

int main(){
	string line;
	ifstream myfile ("input");
	vector<inst> in;
	ship fah;
	ship2 ferry;

	while (getline(myfile,line)) in.push_back(parse(line));

	for(int i = 0; i < in.size(); i++){
		run(in[i], fah);
	       	run2(in[i], ferry);
	}

	cout << distance(fah) << endl;
	cout << distance(ferry) << endl;

	return 0;
}
