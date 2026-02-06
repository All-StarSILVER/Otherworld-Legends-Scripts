#include <iostream>
#include <cmath>
#include <string>
using namespace std;

// x: dmg poa, y: atkspd poa, w: base atkspd, z: conversion boons, lv: levels used
double calculate_ros(double x, double y, double w, bool lv){
	double dmgperc, atkspdperc, dmgmul, atkspdmul;
	dmgperc=pow(x, 0.6);
	atkspdperc=pow(y, 0.6);
	atkspdmul=1+(((w+w*atkspdperc/100)-2)/2)*0.5;
	return (1+dmgperc/100)*atkspdmul+0.5*lv;
}

double calculate_ix(double x, double y, double w, double z, bool lv, int edicts){
	double dmgperc, atkspdperc, dmgmul, atkspdmul;
	dmgperc=pow(x, 0.6);
	atkspdperc=pow(y, 0.6);
	dmgmul=1+0.5*lv+dmgperc/100;
	atkspdmul=1+edicts*((((w+w*atkspdperc/100)-2.3)/2.3)*(0.43+0.23*z)+0.23);
	return dmgmul*atkspdmul;
}

double calculate_regular(double x, double y, double w, double z, bool lv, int exConv){
	double dmgperc, atkspdperc, dmgmul, atkspdmul;
	dmgperc=pow(x, 0.6);
	atkspdperc=pow(y, 0.6);
	dmgmul=1+0.5*lv+dmgperc/100;
	atkspdmul=1+(((w+w*atkspdperc/100)-2)/2)*(0.5+0.25*z)+exConv;
	return dmgmul*atkspdmul;
}

double calculate(string character, double x, double y, double w, double z, bool lv, int extraConv, int edicts){
	if (character=="Ixchel") return calculate_ix(x, y, w, z, lv, edicts);
	else if (character=="Rosilia") return calculate_ros(x, y, w, lv);
	else return calculate_regular(x, y, w, z, lv, extraConv);
}
 
int main(){
	cout << "Take into account max character level? Y/N\n";
	bool lvl;
	double x, w;
	int extraConv=0;
	int edicts=0;
	double z=0;
	string character="";
	char c;
	cin >> c;
	lvl=(c=='Y');

	while (character!="Alasdair" and character!="Yufeng" and character!="Rosilia" and character!="Ixchel"){
		cout << "Choose character: ";
		cin >> character;
	}

	if (character=="Alasdair"){
		cout << "Consider Alasdair perfect 4/1 or dodge 4/3 buffs? Y/N\n";
		cin >> c;
		if (c=='Y'){
			string s;
			while (s!="4/1" && s!="4/3"){
				cout << "4/1 or 4/3?\n";
				cin >> s;
			}
			extraConv=(s=="4/1")?1:2;
			cout << "Consider Swan Reversal? Y/N\n";
			cin >> c;
			if (c=='Y') extraConv+=2*extraConv-1;
		}
		cout << "Enter Violent Discipline count: ";
		cin >> z;
	}
	else if (character=="Ixchel"){
		cout << "Enter number of Edict styles: ";
		cin >> edicts;
		cout << "Enter number of Edict boons: ";
		cin >> z;
	}
 
	cout << "Enter PoA count: ";
	cin >> x;
	cout << "Enter base attack speed stat: ";
	cin >> w;
	double y=0;
	double max=0;
	double maxx=0;
	double maxy=0;
 
	while (x>=0){
		double calc=calculate(character, x, y, w, z, lvl, extraConv, edicts);
		if (calc<max){
			maxx=x+1;
			maxy=y-1;
			x=-1;
		}
		else{
			max=calc;
			--x;
			++y;
		}
	}
 
	double basemul=calculate(character, 0, 0, w, z, lvl, extraConv, edicts);
	cout << "The optimal spread is " << maxx << " into damage and " << maxy << " into attack speed." << endl;
	cout << "The damage gained from PoA is " << max/basemul << "x." << endl;
	cout << "The total damage is " << max << "x." << endl;
}