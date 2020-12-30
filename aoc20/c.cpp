#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

string rev(string in);
struct tile {
	long long id;
	vector<string> pic;
	string l (){
		string out = "";
		for(auto a: pic) out+=a[0];
		return out;
	}
	string r (){
		string out = "";
		for(auto a: pic) out += a.back();
		return out;
	}
	string u (){
		return pic[0];
	}
	string d (){
		return pic.back();
	}
	void rotate(){
		vector<string> n;
		for(int i = 0; i < pic[0].size(); i++) n.push_back("");
		for(int i = 0; i < pic.size(); i++) for(int j = 0; j < pic[i].size(); j++) n[pic[i].size()-1-j]+=pic[i][j];
		pic = n;
	}
	void flip(){
		vector<string> out;
		for(int i = pic.size() -1; i >= 0; i--) out.push_back(pic[i]);
		pic=out;
	}
	void hflip(){
		for(int i = 0; i < pic.size(); i++) pic[i] = rev(pic[i]);
	}
};

string rev(string in){
	string out = "";
	for(int a = in.size() - 1; a>=0; a--) out += in[a];
	return out;
}

vector<string> edges(tile in){
	vector<string> out;
	out.push_back(in.pic[0]);
	out.push_back(rev(in.pic[0]));
	out.push_back(in.pic[in.pic.size()-1]);
	out.push_back(rev(in.pic[in.pic.size()-1]));
	string tmp = "";
	for(string a : in.pic) tmp += a[0];
	out.push_back(tmp);
	out.push_back(rev(tmp));
	tmp = "";
	for(string a : in.pic) tmp += a[a.size()-1];
	out.push_back(tmp);
	out.push_back(rev(tmp));
	return out;
}

const bool operator==(const tile& lhs, const tile& rhs){
	vector<string> lhse = edges(lhs);
	vector<string> rhse = edges(rhs);
	for(string a : lhse) for (string b : rhse) if(a==b) return true;
	return false;
}

long long parse(string l){
	stringstream s(l);
	long long o;
	string g;
	s >> g;
	s>>o;
	return o;
}

bool look(vector<string> &map, vector<string> monster){
	bool out = false;
	for(int i = 0; i < map.size()-monster.size()+1; i++){
		for(int j = 0; j < map[0].size() - monster[0].size() + 1; j++){
			bool here = true;
			for(int x = 0; x < monster.size(); x++){
				for(int y = 0; y < monster[0].size(); y++){
					if (monster[x][y] == '#'){
						if(map[i+x][j+y] == '.'){
							here = false;
						}
					}
				}
			}
			if(here){
				out = true;
				for(int x = 0; x < monster.size(); x++){
					for(int y = 0; y < monster[0].size(); y++){
						if (monster[x][y] == '#'){
							map[i+x][j+y] = 'O';
						}
					}
				}
			}
		}
	}
	return out;
}

int co(vector<string> & map){
	int out = 0;
	for(string a : map) for(char c : a) if (c == '#') out++;
	return out;
}

int main (){
	string l;
	ifstream f("input");

	vector<tile> list;
	tile tmp;

	getline(f,l);

	tmp.id = parse(l);
	
	while(getline(f, l)){
		if(l == ""){
			list.push_back(tmp);
			getline(f,l);
			tmp.id = parse(l);
			tmp.pic.clear();
			continue;
		}
		tmp.pic.push_back(l);
	}

	list.push_back(tmp);

	map<int, int> m;
	for(int i = 0; i < list.size()-1; i++){
		for(int j = i+1; j < list.size(); j++){
			if(list[i] == list[j]){
				m[i]++;
				m[j]++;
			}
		}
	}

	long long t = 1;
	for(auto a: m){
		if(a.second == 2) t *= list[a.first].id;
	}
	cout << t << endl;

	
	vector<vector<int>> board;
	set<int> used;

	for(auto a: m){
		if(a.second == 2){
			used.insert(a.first);
			board.push_back({a.first});
			break;
		}
	}
	bool flag = true;
	while(flag){
		for(auto a: m){
			if(a.second == 4) continue;
			if(used.count(a.first)) continue;
			if(list[a.first] == list[board[0].back()]){
				board[0].push_back(a.first);
				used.insert(a.first);
				flag = (a.second == 3);
				break;
			}
		}
	}
	flag = true;

	while(flag){
		for(auto a: m){
			if(a.second == 4) continue;
			if(used.count(a.first)) continue;
			if(list[a.first] == list[board.back()[0]]){
				board.push_back({a.first});
				used.insert(a.first);
				flag = (a.second == 3);
				break;
			}
		}
	}

	for(int i = 1; i <= 11; i++){
		flag = true;
		while(flag){
			for(auto a: m){
				if(used.count(a.first)) continue;
				if(list[a.first] == list[board[i].back()] && list[a.first] == list[board[i-1][board[i].size()]]){
					board[i].push_back(a.first);
					used.insert(a.first);
					flag = (a.second == 4);
				}
			}
		}
	}

	flag = true;
	while(flag){
		for(auto a: m){
			if(used.count(a.first)) continue;
			if(list[a.first] == list[board[11].back()] && list[a.first] == list[board[10][board[11].size()]]){
				board[11].push_back(a.first);
				used.insert(a.first);
				flag = (a.second == 3);
			}
		}
	}

	vector<string> e = edges(list[board[1][0]]);
	while(!count(e.begin(), e.end(), list[board[0][0]].r())) list[board[0][0]].rotate();
	e = edges(list[board[0][1]]);
	if(!count(e.begin(), e.end(), list[board[0][0]].d())) list[board[0][0]].flip();

	for(int i = 1; i < board[0].size(); i++){
		while(list[board[i][0]].l() != list[board[i-1][0]].r() && list[board[i][0]].l() != rev(list[board[i-1][0]].r())) list[board[i][0]].rotate();
		if(list[board[i][0]].l() == rev(list[board[i-1][0]].r())) list[board[i][0]].flip();
	}

	for(int i = 0; i < board.size(); i++){
		for(int j = 1; j < board[i].size(); j++){
			while(list[board[i][j]].u() != list[board[i][j-1]].d() && list[board[i][j]].u() != rev(list[board[i][j-1]].d())) list[board[i][j]].rotate();
			if(list[board[i][j]].u() == rev(list[board[i][j-1]].d())) list[board[i][j]].hflip();
		}
	}
			
	vector<string> map;
	for(int k = 0; k < board.size(); k++){
		for(int i = 1; i < list[board[0][0]].pic.size()-1; i++){
		       	map.push_back("");
			for(int j = 0; j < board[0].size(); j++){
				map[i + k * (list[board[0][0]].pic.size()-2)-1] += list[board[j][k]].pic[i].substr(1,list[board[j][k]].pic[i].size()-2);
			}
		}
	}

	tile sea;
	sea.pic = map;
	vector<string> monster;
	monster.push_back("                  # ");
	monster.push_back("#    ##    ##    ###");
	monster.push_back(" #  #  #  #  #  #   ");
	
	bool found = false;
	int count = 0;
	while(!found && count < 10){
		found = look(sea.pic, monster);
		if(found) break;
		sea.rotate();
		if(!(count++ % 4)) sea.flip();
	}

	cout << co(sea.pic) << endl;
				
	return 0;
}
