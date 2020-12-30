#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <set>
#include <cmath>

using namespace std;

struct mem{
	long long addr;
	long long value;
};


struct mask{
	long long t = 0;
	long long f = 0;
};

struct mask2{
	long long t = 0;
	long long x = 0;
};

struct mem2{
	long long addr;
	long long value;
	mask2 m;
};

vector<long long> mmsk(long long addr, mask2 m){
	long long init = (addr & ~m.x) | m.t;
	vector<long long> out;
	out.push_back(init);
	for(int i = 0; i < 36; i++){
		long long tmp = pow(2,i);
		if((tmp&m.x) != 0){
			int k = out.size();
			for(int j = 0; j < k; j++)out.push_back(out[j] + tmp);
		}
	}
	return out;
}

mask pMask(string line){
	stringstream s(line);
	string l;
	s >> l;
	s >> l;

	string x;
	s >> x;

	mask m;
	for(int i = 0; i < x.size(); i++){
		m.t *= 2;
		m.f *= 2;
		if(x[i] == '1') m.t++;
		if(x[i] == '0') m.f++;
	}
	return m;
}

mask2 pMask2(string line){
	stringstream s(line);
	string l;
	s >> l;
	s >> l;

	string x;
	s >> x;

	mask2 m;
	for(int i = 0; i < x.size(); i++){
		m.t *= 2;
		m.x *= 2;
		if(x[i] == '1') m.t++;
		if(x[i] == 'X') m.x++;
	}
	return m;
}

mem pline(string line, mask m){
	mem out;

	for(int i = 0; i < line.size(); i++) if(line[i] == '[' || line[i] == ']') line[i] = ' ';

	stringstream s(line);
	
	string a;
	s >> a;
	s >> out.addr;

	s >> a;
	long long r;
	s >> r;

	out.value = (r & ~m.f)|m.t;

	return out;
}

vector<mem> pline2(string line, mask2 m){
	vector<mem> out;
	long long af;

	for(int i = 0; i < line.size(); i++) if(line[i] == '[' || line[i] == ']') line[i] = ' ';

	stringstream s(line);
	
	string a;
	s >> a;
	s >> af;

	s >> a;
	long long r;
	s >> r;

	vector<long long> aa = mmsk(af, m);

	for(long long i : aa){
		mem ad;
		ad.addr = i;
		ad.value = r;
		out.push_back(ad);
	}

	return out;
}

long long sum(vector<mem>& in){
	long long out = 0;
	set<long long> a;
	for(int i = in.size()-1; i >=0; i--){
		if(a.find(in[i].addr) == a.end()){
			out += in[i].value;
			a.insert(in[i].addr);
			continue;
		}
	}
	return out;
}

long long add(long long v, long long a){
	long long count = 0;
	long long total = 0;
	
	for(int i = 0; i < 36; i++){
		long long tmp = pow(2,i);
		if((tmp&a) != 0){
			count++;
			total += pow(2,i);
		}
	}
	cout << count << " " << total << " " << v << endl;
	return total * (count - 1) + v * count;


}

long long sum2(vector<mem2>& in){
	long long out = 0;
	set<long long> a;
	for(int i = in.size()-1; i >=0; i--){
		if(a.find(in[i].addr) == a.end()){
			out += add(in[i].value, in[i].m.x);
			a.insert(in[i].addr);
			continue;
		}
	}
	return out;
}


int main(){
	string line;
	ifstream myfile ("input");

	vector<mem> in;
	vector<mem> in2;
	mask a;
	mask2 b;
	while(getline(myfile,line)){
		if(line[1] == 'a'){
		        a = pMask(line);
			b = pMask2(line);
		}
		if(line[1] == 'e'){
		       in.push_back(pline(line,a));			
		       vector<mem> tmp = pline2(line,b);
		       for(mem a : tmp) in2.push_back(a);
		}
	}
	
	cout << sum(in) << endl;
	cout << sum(in2) << endl;

	return 0;
}
