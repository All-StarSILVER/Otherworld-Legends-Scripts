#include <iostream>
#include "utils/expressioncalc.hh"
using namespace std;

int main(){
	// Input
	double dmg=75;
	double mul;
	int initdmg, numbomb, numkinetboon, numdmgboon;
	bool triggergetsdmg;
	cout << "Trigger damage: ";
	cin >> initdmg;
	char c;
	cout << "Trigger benefits from damage boon (y/n): ";
	cin >> c;
	triggergetsdmg=(c=='y');
	cout << "Number of bombs: ";
	cin >> numbomb;
	cout << "Number of kinetic reservoir boons: ";
	cin >> numkinetboon;
	cout << "Number of damage boons: ";
	cin >> numdmgboon;
	cout << "External mult: ";
	string s;
	cin >> s;
	// Function that resolves simple mathematical expressions
	mul=resolve(s);

	// Calc first shot
	if (triggergetsdmg) dmg=75*(1+0.2*numdmgboon)+initdmg*0.2*numkinetboon*(1+0.2*numdmgboon);
	else dmg=75*(1+0.2*numdmgboon)+initdmg*0.2*numkinetboon;
	// Calc chain explosion
	for (int i=0; i<numbomb-1; ++i){
		dmg=75*(1+0.2*numdmgboon)+dmg*0.2*numkinetboon;
	}

	// Result
	cout << dmg*mul << endl;
}