#include "expressioncalc.hh"

bool isdigit(char c){ return c>='0' and c<='9'; }

double convert(string& s, int& pos){
	double ret=0;
	while (isdigit(s[pos])){
		ret*=10;
		ret+=s[pos]-'0';
		++pos;
	}
	if (s[pos]=='.'){
		int div=10;
		++pos;
		while (isdigit(s[pos])){
			ret+=double(s[pos]-'0')/div;
			div*=10;
			++pos;
		}
	}
	return ret;
}

double resolve(string& op, int& pos, int& parlevel){	// Solves a formula and returns the result
	//cout << "Rec" << pos << endl;		// Debug

	// End condition (should never trigger but just in case);
	if (pos>op.size()) return 0;

	// Variables
	double op1, op2;
	char operation;
	int myparlevel=parlevel;	// Where are we in the parentheses?
	if (isdigit(op[pos])) op1=convert(op, pos);
	else{
		++pos;
		++parlevel;
		op1=resolve(op, pos, parlevel);
	}

	// Main loop
	while (pos<op.size() and parlevel==myparlevel){
		//cout << pos << endl;	// Debug

		// Operation check
		operation=op[pos];
		++pos;

		// Recursion?
		if (operation==')'){
			--parlevel;
			return op1;
		}
		else if (op[pos]=='('){
			++pos;
			++parlevel;
			op2=resolve(op, pos, parlevel);
		}
		else op2=convert(op, pos);

		// Operation?
		if (operation=='+'){
			bool end=false;
			while (not end){
				if (op[pos]=='*'){
					++pos;
					if (op[pos]=='('){
						++pos;
						++parlevel;
						op2*=resolve(op, pos, parlevel);
					}
					else op2*=convert(op, pos);
				}
				else if (op[pos]=='/'){
					++pos;
					if (op[pos]=='('){
						++pos;
						++parlevel;
						op2/=resolve(op, pos, parlevel);
					}
					else op2/=convert(op, pos);
				}
				else end=true;
			}
			op1+=op2;
		}
		else if (operation=='-'){
			bool end=false;
			while (not end){
				if (op[pos]=='*'){
					++pos;
					if (op[pos]=='('){
						++pos;
						++parlevel;
						op2*=resolve(op, pos, parlevel);
					}
					else op2*=convert(op, pos);
				}
				else if (op[pos]=='/'){
					++pos;
					if (op[pos]=='('){
						++pos;
						++parlevel;
						op2/=resolve(op, pos, parlevel);
					}
					else op2/=convert(op, pos);
				}
				else end=true;
			}
			op1-=op2;
		}
		else if (operation=='*') op1*=op2;
		else if (operation=='/') op1/=op2;

		//cout << "OP1 " << op1 << endl;	// Debug
	}

	return op1;
}

double resolve(string& op){	// Helper
	int pos=1;
	int parlevel=1;
	return resolve(op, pos, parlevel);
}