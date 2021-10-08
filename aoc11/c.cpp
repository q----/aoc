#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
// a little slow

using namespace std;

int adj (vector<string>& in, int x, int y){
	int total = 0;
	if(x > 0 && y > 0 && in[x-1][y-1] == '#') total++;
	if(x > 0 && y < in[x].size()-1 && in[x-1][y+1] == '#') total++;
	if(x < in.size()-1 && y > 0 && in[x+1][y-1] == '#') total++;
	if(x < in.size()-1 && y < in[x].size()-1 && in[x+1][y+1] == '#') total++;
	if(x > 0 && in[x-1][y] == '#') total++;
	if(y < in[x].size()-1 && in[x][y+1] == '#') total++;
	if(y > 0 && in[x][y-1] == '#') total++;
	if(x < in.size()-1 && in[x+1][y] == '#') total++;
	return total;
}

bool aaa(vector<string>& in, int x, int y, int xv, int yv){
	if(x+xv < 0 || x+xv == in.size() || y+yv < 0 || y+yv == in[x].size()) return false;
	if(in[x + xv][y + yv] == '#') return true;
	if(in[x + xv][y + yv] == 'L') return false;
	return aaa(in, x+xv, y+yv, xv, yv);
}

int see(vector<string>& in, int x, int y){
	int total = 0;
	if(aaa(in, x, y, 1, 1)) total++;
	if(aaa(in, x, y, 1, 0)) total++;
	if(aaa(in, x, y, 1, -1)) total++;
	if(aaa(in, x, y, 0, 1)) total++;
	if(aaa(in, x, y, 0, -1)) total++;
	if(aaa(in, x, y, -1, 1)) total++;
	if(aaa(in, x, y, -1, 0)) total++;
	if(aaa(in, x, y, -1, -1)) total++;
	return total;
}

void run(vector<string> in, vector<string>& out){
	for(int i = 0; i < in.size(); i++){
		for(int j = 0; j < in[i].size(); j++){
			if(in[i][j] == '#' && adj(in, i, j) >= 4) out[i][j] = 'L';
			if(in[i][j] == 'L' && adj(in, i, j) == 0) out[i][j] = '#';
		}
	}
}

void run2(vector<string> in, vector<string>& out){
	for(int i = 0; i < in.size(); i++){
		for(int j = 0; j < in[i].size(); j++){
			if(in[i][j] == '#' && see(in, i, j) >= 5) out[i][j] = 'L';
			if(in[i][j] == 'L' && see(in, i, j) == 0) out[i][j] = '#';
		}
	}
}

int count(vector<string>& in){
	int out = 0;
	for(int i = 0; i < in.size(); i++) for(int j = 0; j < in[i].size(); j++) if(in[i][j] == '#') out++;
	return out;
}

int first(vector<string> in){
	int t = 0;
	int s = 1;

	while(t != s){
		s = t;
		run(in,in);
		t = count(in);
	}

	return t;
}

int second(vector<string> in){
	int t = 0;
	int s = 1;

	while(t != s){
		s = t;
		run2(in,in);
		t = count(in);
	}
	return t;
}

int main(){
	string line;
	ifstream myfile ("input");
	vector<string> in;
	while (getline(myfile,line)) in.push_back(line);

	cout << first(in) << endl;
	cout << second(in) << endl;

	return 0;
}
