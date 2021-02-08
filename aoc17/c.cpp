#include <iostream>
#include <fstream>
#include <set>
#include <map>

using namespace std;

struct cube{
	int x;
	int y;
	int z;
	cube(int a, int b, int c){
		x = a;
		y = b;
		z = c;
	}
};

bool operator<(const cube& lhs, const cube& rhs){
	if(lhs.x != rhs.x) return (lhs.x < rhs.x);
	if(lhs.y != rhs.y) return (lhs.y < rhs.y);
	if(lhs.z != rhs.z) return (lhs.z < rhs.z);
	return false;
}

ostream& operator<<(ostream& os, cube const& c){
	os << c.x << ',' << c.y << ',' << c.z;
	return os;
}

struct cub4{
	int x;
	int y;
	int z;
	int w;
	cub4(int a, int b, int c, int d){
		x = a;
		y = b;
		z = c;
		w = d;
	}
};

bool operator<(const cub4& lhs, const cub4& rhs){
	if(lhs.x != rhs.x) return (lhs.x < rhs.x);
	if(lhs.y != rhs.y) return (lhs.y < rhs.y);
	if(lhs.z != rhs.z) return (lhs.z < rhs.z);
	if(lhs.w != rhs.w) return (lhs.w < rhs.w);
	return false;
}

ostream& operator<<(ostream& os, cub4 const& c){
	os << c.x << ',' << c.y << ',' << c.z << ',' << c.w;
	return os;
}

map<cube, int> adj(set<cube> a){
	map<cube, int> out;
	for(cube b : a){
		for(int i = b.x-1;i <= b.x+1; i++){
			for(int j = b.y-1; j <= b.y+1; j++){
				for(int k = b.z-1; k <= b.z+1; k++){
					out[cube(i,j,k)]++;
				}
			}
		}
	}
	return out;
}

map<cub4, int> adj(set<cub4> a){
	map<cub4, int> out;
	for(cub4 b : a){
		for(int i = b.x-1;i <= b.x+1; i++){
			for(int j = b.y-1; j <= b.y+1; j++){
				for(int k = b.z-1; k <= b.z+1; k++){
					for(int l = b.w-1; l <= b.w+1; l++){
						out[cub4(i,j,k,l)]++;
					}
				}
			}
		}
	}
	return out;
}

template<typename T>
set<T> next(set<T> field){
	set<T> out;
	map<T, int> a = adj(field);
	
	for(auto b: a){
		if(b.second == 3 || field.count(b.first) > 0 && b.second == 4){
			out.insert(b.first);
		}
	}

	return out;
}

int main(){
	string line;
	ifstream file("input");

	set<cube> field;
	set<cub4> fiel4;
	for(int count = 0; getline(file,line); count++){
		for(int i = 0; i < line.size(); i++){
			if(line[i] == '#'){
			       field.insert(cube(i, count, 0));
			       fiel4.insert(cub4(i, count, 0, 0));
			}
		}
	}

	for(int i = 0; i < 6; i++){
	        field = next(field);
		fiel4 = next(fiel4);
	}
		
	cout << field.size() << endl;		
	cout << fiel4.size() << endl;

	return 0;
}
