#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

struct bus{
	long long offset;
	long long id;

	bus(long long o, long long i){
		offset = o;
		id = i;
	}
};

vector<bus> conv(string line){
	for(int x = 0; x < line.size(); x++){
		if(line[x] == ',') line[x] = ' ';
		if(line[x] == 'x') line[x] = '0';
	}
	vector<bus> out;
	int off = 0;
	stringstream a(line);
	while(true){
		int id;
		if(!(a >> id)) break;
		if(id != 0) out.push_back(bus(off, id));
		off++;
	}
	return out;
}

int help(bus in, int time){
	return in.id - (time % in.id);
}

int shrt(vector<bus> in, int time){
	bus out = in[0];
	for(int i = 1; i < in.size(); i++) if(help(in[i],time) < help(out,time)) out = in[i];
	return help(out,time) * out.id;
}

bus b(bus o, bus t){
	long long i = 0;
	while((o.offset + o.id * i + t.offset) % t.id != 0) i++;
	return bus(o.offset + o.id * i, o.id * t.id);
}

long long crt(vector<bus> in){
	bus out = in[0];
	for(int i = 1; i < in.size(); i++) out = b(out,in[i]);
	return out.offset % out.id;
}

int main(){
	string line;
	ifstream myfile ("input");

	getline(myfile,line);
	stringstream s(line);
	int time;
	s >> time;

	getline(myfile,line);

	cout << shrt(conv(line), time) << endl;
	cout << crt(conv(line)) << endl;

	return 0;
}
