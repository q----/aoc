#include <iostream>
#include <fstream>
#include <set>
#include <sstream>
#include <map>


using namespace std;

struct tile{
	int x = 0;
	int y = 0;
	tile(){}
	tile(int f, int s){
		x=f;
		y=s;
	}
};

const bool operator<(const tile& lhs, const tile& rhs){
	if(lhs.x == rhs.x) return (lhs.y < rhs.y);
	return (lhs.x < rhs.x);
}

const bool operator==(const tile& lhs, const tile& rhs){
	return (lhs.x == rhs.x) && (lhs.y == rhs.y);
}

ostream &operator<<(ostream& os, const tile& in){
	os << in.x << "," << in.y;
	return os;
}

string tostr (tile& a){
	stringstream s;
	s << a;
	return s.str();
}

tile parse(string& line){
	tile out;
	for(int i = 0; i < line.size(); i++){
		if(line[i] == 'e'){
			out.x++;
			continue;
		}
		if(line[i] == 'w'){
			out.x--;
			continue;
		}
		if(line[i] == 'n'){
			out.y++;
			if(line[++i] == 'e'){
				continue;
			}
			if(line[i] == 'w'){
				out.x--;
				continue;
			}
		}
		if(line[i] == 's'){
			out.y--;
			if(line[++i] == 'e'){
				out.x++;
				continue;
			}
			if(line[i] == 'w'){
				continue;
			}
		}
	}
	return out;
}

set<tile> step(set<tile> in){
	set<tile> out;
	map<tile, int> adj;
	for(tile a : in){
		adj[a]++;
		adj[tile(a.x+1, a.y)]++;
		adj[tile(a.x-1, a.y)]++;
		adj[tile(a.x, a.y+1)]++;
		adj[tile(a.x, a.y-1)]++;
		adj[tile(a.x-1, a.y+1)]++;
		adj[tile(a.x+1, a.y-1)]++;
	}

	for(auto a : adj){
		if(a.second == 2){
			out.insert(a.first);
		}
		if(a.second == 3 && in.count(a.first) > 0) out.insert(a.first);
	}
	return out;
}

int main(){
	string line;
	ifstream f("input");

	set<tile> woop;

	while(getline(f, line)){
		tile curr = parse(line);
		if(woop.count(curr) == 0){
			woop.insert(curr);
		} else {
			woop.erase(curr);
		}
	}

	cout << woop.size() << endl;

	for(int i = 0; i < 100; i++){
	       	woop = step(woop);
	}

	cout << woop.size() << endl;
	return 0;
}

