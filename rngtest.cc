#include <iostream>
#include <map>
#include <string>
using namespace std;

void printCurrent(map<char, int>& m, map<char, string>& t){
    map<char, int>::iterator it=m.begin();
    while (it!=m.end()){
        cout << t[(*it).first] << '(' << (*it).first << "): " << (*it).second << endl;
        ++it;
    }
}

int main(){
    // HELP
    cout << "Enter a number every time an event occurs. The first time a number is entered, you must associate a name to it.\n"
    << "Once you're done entering numbers, enter ! to end the program and get some basic statistics." << endl;

    // MAIN
    map<char, int> results;
    map<char, string> translation;

    char r;
    cin >> r;
    
    int sample=0;
    while (r!='!'){
        map<char, int>::iterator it=results.find(r);
        if (it==results.end()){
            cout << "Enter translation for this symbol: ";
            string t;
            cin >> t;
            results.insert(pair<char, int>(r, 0));
            translation.insert(pair<char, string>(r, t));
        }
        results[r]+=1;
        ++sample;
        printCurrent(results, translation);
        cin >> r;
    }

    // STATS
    cout << "Sample size: " << sample << endl;

    cout << "TOTALS:" << endl;
    map<char, int>::iterator it=results.begin();
    while (it!=results.end()){
        cout << translation[(*it).first] << ": " << (*it).second << endl;
        ++it;
    }

    cout << "PERCENTAGES:" << endl;
    it=results.begin();
    while (it!=results.end()){
        cout << translation[(*it).first] << ": " << ((double)(*it).second)/sample*100 << '%' << endl;
        ++it;
    }
}