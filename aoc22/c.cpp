#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
#include <set>

using namespace std;

int parse(string line){
	stringstream s(line);
	int x;
	s >> x;
	return x;
}

long long score(queue<int> in){
	long long a = 0;
	while(!in.empty()){
		a += in.front() * (in.size());
		in.pop();
	}
	return a;
}

void play( queue<int> &p1, queue<int> &p2){
	int m = p1.front();
	int c = p2.front();
	p1.pop();
	p2.pop();
	if(m > c){
		p1.push(m);
		p1.push(c);
	} else {
		p2.push(c);
		p2.push(m);
	}
}

void standard(queue<int> p1, queue<int> p2){
	while(!p1.empty() && !p2.empty()){
	       	play(p1, p2);
	}

	if(p1.empty()){
		cout << score(p2) << endl;
	} else {
		cout << score(p1) << endl;
	}
}

string tostr(queue<int> p1, queue<int> p2){
	stringstream s;
	s << "P: ";
	while(!p1.empty()){
		s << p1.front() << ",";
		p1.pop();
	}
	s << " C: ";
	while(!p2.empty()){
		s << p2.front() << ",";
		p2.pop();
	}
	return s.str();
}

int won(queue<int>& p1, queue<int>& p2, set<string>& a){
	if(p1.empty()){
		return 2;
	} else if (p2.empty()){
		return 1;
	}
	if(a.count(tostr(p1, p2))){
		return 1;
	}
	a.insert(tostr(p1, p2));
	return 0;
}

int recursive(queue<int> p1, queue<int> p2, bool print);

bool recurse(queue<int> p1, queue<int> p2, int m, int c){
	queue<int> me;
	queue<int> crab;
	for(int i = 0; i < m; i++){
		me.push(p1.front());
		p1.pop();
	}
	for(int i = 0; i < c; i++){
		crab.push(p2.front());
		p2.pop();
	}
	return (recursive(me, crab, false) == 1);
}

int recursive(queue<int> p1, queue<int> p2, bool print){
	set<string> a;
	while(!won(p1, p2, a)){
		if((p1.front() >= p1.size()) || (p2.front() >= p2.size())){
			play(p1, p2);
			continue;
		}
		int m = p1.front();
		int c = p2.front();
		p1.pop();
		p2.pop();
		if(recurse(p1, p2, m, c)){
			p1.push(m);
			p1.push(c);
		} else {
			p2.push(c);
			p2.push(m);
		}
	}
	int w = won(p1, p2, a);
	if(print){
		if(w == 1){
			cout << score(p1) << endl;
		} else {
			cout << score(p2) << endl;
		}
	}
				
	return w;
}

int main(){
	string l;
	ifstream f("input");

	queue<int> me;
	queue<int> crab;

	getline(f,l);
	while(getline(f,l)){
		if(l == "") break;
		me.push(parse(l));
	}

	getline(f,l);
	while(getline(f,l)) crab.push(parse(l));

	standard(me, crab);
	recursive(me, crab, true);
	
	return 0;
}
