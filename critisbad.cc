#include <iostream>
#include <cmath>
using namespace std;
 
double calc(double dpoa, int maxpoa, int basecrit, bool lv){
	double cpoa=maxpoa-dpoa;
	double dmod=1+(pow(dpoa, 0.6)/100)+lv*0.5;
	double newcrit=basecrit+((pow(cpoa, 0.6)/100)*basecrit)+lv*25;
	double cmod;
	if (newcrit<100) cmod=(newcrit*(1.5+lv*0.5)+(100-newcrit))/100;
	else cmod=1.5+lv*0.5;
	return dmod*cmod;
}
 
int main(){
	double max=-1;
	int maxval;
	int maxpoa;
	int basecrit;
	cout << "Take into account max character level? Y/N\n";
	char c;
	cin >> c;
	bool lvl;
	if (c=='Y') lvl=true;
	else lvl=false;
	cout << "Enter how much poa you want to use between dmg and crit: ";
	cin >> maxpoa;
	cout << "Enter your character's base crit stat: ";
	cin >> basecrit;
	for (double i=0; i<=maxpoa; ++i){
		double temp=calc(i, maxpoa, basecrit, lvl);
		if (temp>max){
			max=temp;
			maxval=i;
		}
	}
	cout << "The optimal damage and crit poa spread is " << maxval << " damage, " << maxpoa-maxval << " crit, giving " << max << "x damage" << endl;
}