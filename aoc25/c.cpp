#include <iostream>

using namespace std;

long long step(long long value, long long subject){
	return (value * subject) % 20201227;
}

long long lsiz(long long value, long long subject){
	long long i = 1;
	long long out = 0;
	while(i != value){
		i = step(i, subject);
		out++;
	}
	return out;
}

int main(){
	long long door = 3418282;
	long long card = 8719412;

	long long j = lsiz(door, 7);
	long long value = 1;

	for(int i = 0; i < j; i++) value = step(value, card);

	cout << value << endl;

	return 0;
}
