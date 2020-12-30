#include <iostream>
#include <vector>
#include <map>

using namespace std;

int next(vector<int>& curr){
	int count = 1;
	for(int i = curr.size() - 2; i >= 0; i--){
		if(curr[i] == curr[curr.size()-1]) return count;
		count++;
	}
	return 0;
}

int main(){
	vector<int> in = {0,14,6,20,1,4};

	int curr = 0;

	map<int,int> vals;

	for(curr; curr < in.size(); curr++){
		vals[in[curr]] = curr;
	}
	
	int next = 0;
		
	for(curr; curr < 2019; curr++){
		int ooo = next;
		if(vals.find(next) == vals.end()){
			next = 0;
		}else{
			next = curr - vals[next];
		}
		vals[ooo] = curr;
	}

	cout << next << endl;

	for(curr; curr < 29999999; curr++){
		int ooo = next;
		if(vals.find(next) == vals.end()){
			next = 0;
		}else{
			next = curr - vals[next];
		}
		vals[ooo] = curr;
	}

	cout << next << endl;

	return 0;
}
