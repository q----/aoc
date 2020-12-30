#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <set>

using namespace std;

int parse(string& line){
	stringstream s(line);
	int a;
	s >> a;
	return a;
}

int sum(vector<int>& in, int s, int e){
	int total = 0;
	for(int x = s; x < e; x++) total += in[x];
	return total;
}

int maxmin(vector<int>& in, int s, int e){
	int max = 0;
	int min = 2147483647;
	for(int x = s; x < e; x++){
		if(in[x] > max) max = in[x];
		if(in[x] < min) min = in[x];
	}
	return max+min;
}

int contig(vector<int>& in, int x){
	int s = 0;
	int e = 1;
	int sume = 0;
	do{
		sume = sum(in,s,e);
		if( sume > in[x]) s++;
		if(sume < in[x]) e++;
	}while(sume != in[x]);
	return maxmin(in,s,e);
}

bool test(vector<int>& in, int x){
	for(int y = 1; y < 25; y++){
		for(int z = y+1; z < 26; z++){
			if(in[x] == in[x-y] + in[x-z]) return true;
		}
	}
	cout << in[x] << endl;
	//cout << contig(in,x) << endl;
	return false;
}

int main(){
	string line;
	ifstream myfile ("input");
	vector<int> in;
	
	while (getline(myfile,line)){
		in.push_back(parse(line));
	}

	for(int x = 25; x < in.size()-25; x++)if(!test(in,x)) continue;		

	return 0;
}
