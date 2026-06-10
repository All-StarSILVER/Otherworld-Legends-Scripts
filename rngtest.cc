#include <iostream>
#include <map>
#include <fstream>
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

    // LOAD FILE
    cout << "\nLoad previous data? If yes, enter file name, if not, enter 'N': ";
    string f;
    cin >> f;
    map<char, int> results;
    map<char, string> translation;
    int sample=0;
    if (f!="N"){
        ifstream stream;
        stream.open(f, ios::in);
        stream >> sample;
        bool end=false;
        while (!end){
            string t; char s; int n=0;
            stream >> s;
            char tmp;
            while (stream >> tmp && tmp!=','){
                n*=10;
                n+=tmp-'0';
            }
            while(!stream.eof() && stream >> tmp && tmp!=','){
                t.push_back(tmp);
            }

            results.insert(pair<char, int>(s, n));
            translation.insert(pair<char, string>(s, t));

            if (stream.eof()) end=true;
        }
        stream.close();
    }

    // MAIN
    printCurrent(results, translation);
    char r;
    cin >> r;
    
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
    cout << "\nSample size: " << sample << endl;

    cout << "\nTOTALS:" << endl;
    map<char, int>::iterator it=results.begin();
    while (it!=results.end()){
        cout << translation[(*it).first] << ": " << (*it).second << endl;
        ++it;
    }

    cout << "\nPERCENTAGES:" << endl;
    it=results.begin();
    while (it!=results.end()){
        cout << translation[(*it).first] << ": " << ((double)(*it).second)/sample*100 << '%' << endl;
        ++it;
    }

    // SAVE FILE
    cout << endl << "Enter file to save current state, or enter 'N' to exit: ";
    cin >> f;
    if (f!="N"){
        ofstream stream;
        stream.open(f, ios::out | ios::trunc);
        stream << sample << ' ';
        it=results.begin();
        bool first=true;
        while (it!=results.end()){
            if (first) first=false;
            else{
                char tmp=',';
                stream << tmp;
            }
            stream << (*it).first << (*it).second << ',' << translation[(*it).first];
            ++it;
        }
    }
}