#include <iostream>
#include <time.h>
using namespace std;

int main(){
	srand(time(0));
	float startcrit;
	cout << "Enter your starting crit amount (1 decimal): ";
	cin >> startcrit;
	int sample;
	cout << "Enter the sample size for the test (default = 100000000): ";
	cin >> sample;
	
	float total=0;
	float crit=startcrit;
	for (int i=0; i<sample; ++i){
		//cout << crit << endl;
		total+=crit;
		int c=rand()%1000;
		if (c>crit*10) crit*=2;
		else crit=startcrit;
	}

	total/=sample;
	cout << "Average crit rate: " << total << endl;
	cout << "Average crit gained: " << total-startcrit << endl;
}