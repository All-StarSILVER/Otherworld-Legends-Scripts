#include <iostream>
#include <time.h>
using namespace std;

int main(){
	srand(time(0));
	double startcrit;
	cout << "Enter your starting crit amount (1 decimal max): ";
	cin >> startcrit;
	int sample;
	double critdmg;
	cout << "Enter your crit damage multiplier (ex: 1.5): ";
	cin >> critdmg;
	bool highroll;
	cout << "Factor in High Roller? Y/N: ";
	char c;
	cin >> c;
	highroll=c=='Y';
	cout << "Enter the sample size for the test\n(default = 100000000, very large numbers may cause floating point inaccuracy, use a lower number if it takes too long)\n";
	cin >> sample;
	bool debug;
	cout << "Debug mode? Y/N (NOT RECOMMENDED): ";
	cin >> c;
	debug=c=='Y';
	
	double totalcrit=0;
	double totaldmg=0;
	double crit=startcrit;
	for (int i=0; i<sample; ++i){
		if (debug) cout << crit << endl;
		totalcrit+=crit/sample;
		int c=rand()%1000;
		if (c>crit*10){
			totaldmg+=1;
			crit*=2;
		}
		else{
			double newmult=critdmg;
			if (crit>100 and highroll) newmult+=(crit-100)/100;
			totaldmg+=newmult;
			crit=startcrit;
			if (debug) cout << "Crit " << newmult << 'x' << endl;
		}
		if (debug) cout << "Total damage: " << totaldmg << endl;
	}

	double unbuffeddmg=((startcrit/100)*critdmg+(1-startcrit/100))*sample;
	cout << "Average crit rate: " << totalcrit << endl;
	cout << "Average crit gained: " << totalcrit-startcrit << endl;
	cout << "Total damage (assuming 1 damage per hit): " << totaldmg << endl;
	cout << "Damage gained over the average (" << unbuffeddmg << "): " << totaldmg/unbuffeddmg << 'x' << endl;
}