#include <iostream>
#include <time.h>
using namespace std;

int main(){
	srand(time(0));
	double startcrit;
	cout << "Enter your starting crit amount (1 decimal max): ";
	cin >> startcrit;
	int sample;
	cout << "Enter the sample size for the test\n(default = 100000000, very large numbers may cause floating point inaccuracy, use a lower number if it takes too long)\n";
	cin >> sample;
	bool debug;
	cout << "Debug mode? Y/N (NOT RECOMMENDED): ";
	char c;
	cin >> c;
	debug=c=='Y';
	
	double total=0;
	double crit=startcrit;
	for (int i=0; i<sample; ++i){
		if (debug) cout << crit << endl;
		total+=crit/sample;
		int c=rand()%1000;
		if (c>crit*10) crit*=2;
		else{
			crit=startcrit;
			if (debug) cout << "Crit" << endl;
		}
	}

	cout << "Average crit rate: " << total << endl;
	cout << "Average crit gained: " << total-startcrit << endl;
}