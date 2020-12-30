#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <climits>

using namespace std;

long long parse(string& line){
	stringstream s(line);
	long long a;
	s >> a;
	return a;
}

long long sum(vector<long long>& in, int s, int e){
	int total = 0;
	for(int x = s; x < e; x++) total += in[x];
	return total;
}

long long maxmin(vector<long long>& in, int s, int e){
	long long max = 0;
	long long min = LLONG_MAX;
	for(int x = s; x < e; x++){
		if(in[x] > max) max = in[x];
		if(in[x] < min) min = in[x];
	}
	return max+min;
}

long long contig(vector<long long>& in, int x){
	int s = 0;
	int e = 1;
	long long a = 0;
	do{
		a = sum(in,s,e);
		if(a > in[x]) s++;
		if(a < in[x]) e++;
	} while(a != in[x]);
	return maxmin(in,s,e);
}

bool test(vector<long long>& in, int x){
	for(int y = 1; y < 25; y++){
		for(int z = y+1; z < 26; z++){
			if(in[x] == in[x-y] + in[x-z]) return true;
		}
	}
	cout << in[x] << endl;
	cout << contig(in,x) << endl;
	return false;
}

int main(){
	string line;
	ifstream myfile ("input");
	vector<long long> in;
	while (getline(myfile,line)) in.push_back(parse(line));
	for(int x = 25; x < in.size()-25; x++) if(!test(in,x)) break;		
	return 0;
}
