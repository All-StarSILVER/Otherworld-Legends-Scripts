#include <iostream>
#include <vector>
#include <map>
#include <string>
#include "utils/expressioncalc.hh"
using namespace std;

bool isletter(char c){ return (c>='a' and c<='z') or (c>='A' and c<='Z') or c=='_'; }

void resetTrans(map<string, pair<int,int> >& v){
    for (map<string, pair<int,int> >::iterator i=v.begin(); i!=v.end(); ++i) i->second.second=0;
}

string translate(map<string,pair<int,int> >& translation, string op){	// Inserts boon amounts into formula at the correct locations
	int i=0;
	string cur;
	bool reading=0;
	while (i<op.size()){
		if (isletter(op[i])){
			reading=1;
			cur.push_back(op[i]);
			op[i]='0';
		}
		else{
			if (reading){
				reading=0;
				map<string,pair<int,int> >::iterator it=translation.find(cur);
				string s;
				cur=s;
				s=to_string(it->second.second);
				for (int j=0; j<s.size(); ++j) op[i+j-s.size()]=s[j];
			}
		}
		++i;
	}
	if (reading){
		reading=0;
		map<string,pair<int,int> >::iterator it=translation.find(cur);
		string s;
		cur=s;
		s=to_string(it->second.second);
		for (int j=0; j<s.size(); ++j) op[i+j-s.size()]=s[j];
	}
	return op;
}
 
void getOrder(vector<string>& order, map<string,pair<int,int> >& translation, string& op, int total){	// Calculates boon order
	for (int i=0; i<total; ++i){
		double max=-1;
		map<string,pair<int,int> >::iterator maxpos;
 
		for (map<string,pair<int,int> >::iterator it=translation.begin(); it!=translation.end(); ++it){
			if (it->second.first==0 or it->second.first>it->second.second){	// Checks if boon can be stacked further
				++(it->second.second);
				string s=translate(translation, op);
				double res=resolve(s);
				if (res>max){
					maxpos=it;
					max=res;
				}
				--(it->second.second);
			}
		}
 
		if (max==-1){
			cout << endl << "Error: cannot equip desired amount of boons" << endl << endl;
			return;
		}
 
		++(maxpos->second.second);
		order.push_back(maxpos->first);
	}
}
 
void printResult(vector<string>& order, map<string,pair<int,int> >& translation, string& op){
	cout << endl << "---Optimal boon order---" << endl;
	bool first=true;
	for (int i=0; i<order.size(); ++i){
		if (first) first=false;
		else cout << ", ";
		cout << order[i];
	}
	cout << endl << endl << "---Boon totals---" << endl;
	for (map<string,pair<int,int> >::iterator it=translation.begin(); it!=translation.end(); ++it) cout << it->first << ": " << it->second.second << endl;
	string s=translate(translation, op);
	cout << endl << "---Total damage---" << endl << resolve(s) << endl;
}
 
int main(){
	// Global
	string op;
	map<string,pair<int,int> > translation;
	int total=0;
 
	//Input
	cout << "Type Help for help\nEnter boons: ";
	string s;
	cin >> s;
	while (s=="Help"){
		cout << "Start by entering the names of the boons you want to take into account, as well as their caps. Enter 0 if the boon is uncapped. When you're done, type End.\nThen enter the formula that calculates your attack's damage depending on the boons. Make sure the names you use for the variables match the boon names you entered before. Make sure to enclose the entire operation in parentheses. Only addition, subtraction, multiplication and division are supported.\nAfter adding the formula, enter the number of boons you want to calculate for. If you want to stop the program, enter 0 boons.\nEnter boons: ";
		cin >> s;
	}
	while (s!="End"){
		if (s.size()<2) cout << "Name must be 2 characters or more" << endl;
		else{
			int cap;
			cout << "Enter cap: ";
			cin >> cap;
			translation.insert({s, {cap, 0}});
		}
		cout << "Enter boons: ";
		cin >> s;
	}
	cout << "Enter formula for boons: ";
	cin >> op;
	cout << "Enter number of boons (note that the maximum for chaos/spatial interstice is ~15): ";
	cin >> total;
	while (total!=0){
		vector<string> order;
 
		// Solve everything!!!
		getOrder(order, translation, op, total);
 
		// Output
		printResult(order, translation, op);
 
		// Reset the boon amounts after every request
		resetTrans(translation);
 
		cout << "Enter number of boons (note that the maximum for chaos/spatial interstice is ~15): ";
		cin >> total;
	}
}