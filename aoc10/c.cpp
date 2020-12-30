#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

int parse(string& line){
	stringstream s(line);
	int x;
	s >> x;
	return x;
}

int run(vector<int>& in, int &p){
	int out = 1;
	while(in[p+1] - in[p] == 1){
		out++;
		p++;
	}
	if(in[p+1] - in[p] != 3) cout << "this solution won't work, gl" << endl;
	return out;
}

//formula might be f(u_n) = f(u_n-1) + f(u_n-2) + f(u_n-3) for n >=4
int conv(int in){
	if(in == 1) return 1;
	if(in == 2) return 1;
	if(in == 3) return 2;
	if(in == 4) return 4;
	if(in == 5) return 7;
	if(in == 6) return 13; //unverified
	cout << "more cases need to be added for this to work" << endl;
	return 0;
}

int main(){
	string line;
	ifstream myfile ("input");
	vector<int> in;
	while (getline(myfile,line)) in.push_back(parse(line));

	in.push_back(0);
	sort(in.begin(), in.end());
	in.push_back(in[in.size()-1]+3);

	vector<int> sto = {0,0,0,0};

	for(int i = 1; i < in.size(); i++) sto[in[i] - in[i-1]]++;

	cout << sto[1] * sto[3] << endl;

	vector<int> aaa;
	for(int i = 0; i < in.size()-1; i++) aaa.push_back(run(in,i));

	long long t = 1;
	for(int x = 0; x < aaa.size(); x++) t *= conv(aaa[x]);

	cout << t << endl;

	return 0;
}
