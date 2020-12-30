#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct cube{
	int x;
	int y;
	int z;
	int w;
	cube(int a, int b, int c, int d){
		x = a;
		y = b;
		z = c;
		w = d;
	}
};

bool operator==(const cube& lhs, const cube& rhs){
	return (lhs.x == rhs.x) && (lhs.y == rhs.y) && (lhs.z == rhs.z) && (lhs.w == rhs.w);
}

ostream& operator<<(ostream& os, cube const& c){
	os << c.x << ',' << c.y << ',' << c.z << ',' << c.w;
	return os;
}

cube minc(vector<cube>& field){
	cube out = field[0];
	for(int i = 1; i < field.size(); i++){
		if(out.x > field[i].x) out.x = field[i].x;
		if(out.y > field[i].y) out.y = field[i].y;
		if(out.z > field[i].z) out.z = field[i].z;
		if(out.w > field[i].w) out.w = field[i].w;
	}
	return cube(out.x-1, out.y-1, out.z-1, out.w-1);
}

cube maxc(vector<cube>& field){
	cube out = field[0];
	for(int i = 1; i < field.size(); i++){
		if(out.x < field[i].x) out.x = field[i].x;
		if(out.y < field[i].y) out.y = field[i].y;
		if(out.z < field[i].z) out.z = field[i].z;
		if(out.w < field[i].w) out.w = field[i].w;
	}
	return cube(out.x+1, out.y+1, out.z+1, out.w+1);
}

bool isin(cube a, vector<cube> field){
	for(cube b : field) if(a==b) return true;
	return false;
}

int adj(cube a, vector<cube> field){
	int total = 0;
	for(int x = a.x-1; x <= a.x+1; x++){
		for(int y = a.y-1; y <= a.y+1; y++){
			for(int z = a.z-1; z <= a.z+1; z++){
				for(int w = a.w-1; w <= a.w+1; w++){
					if(cube(x,y,z,w) == a) continue;
					if(isin(cube(x,y,z,w), field)) total++;
				}
			}
		}
	}
	return total;
}

bool tst(cube a, vector<cube> field){
	int x = adj(a, field);
	return ((x == 3) || ((x == 2) && isin(a, field)));
}

vector<cube> next(vector<cube> field){
	vector<cube> out;
	cube l = minc(field);
	cube h = maxc(field);

	for(int x = l.x; x <= h.x; x++){
		for(int y = l.y; y <= h.y; y++){
			for(int z = l.z; z <= h.z; z++){
				for(int w = l.w; w <= h.w; w++){
					if(tst(cube(x,y,z,w),field)) out.push_back(cube(x,y,z,w));
				}
			}
		}
	}
	return out;
}

int main(){
	string line;
	ifstream file("input");

	vector<cube> field;
	int count = 0;
	while(getline(file,line)){
		for(int i = 0; i < line.size(); i++){
			if(line[i] == '#') field.push_back(cube(i, count, 0, 0));
		}
		count++;
	}

	cout << "[......]\r ";


	for(int i = 0; i < 6; i++){
	        field = next(field);
		cout << '#';
	}


	cout << field.size() << endl;

	

	return 0;
}
