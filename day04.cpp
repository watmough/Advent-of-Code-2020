#include <iostream>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <cstdlib>
#include "reader.h"

using namespace std;

vector<string> hc = {"amb", "blu", "brn", "gry", "grn", "hzl", "oth" };

bool validate(string f, string p)
{
    cout << "Validate: " << f << " into " << p << endl;
    if (f=="byr:") {
        int yr = atol(p.c_str()+4);
        return yr>=1920 && yr<=2002;
    } else if (f=="iyr:") {
        int yr = atol(p.c_str()+4);
        return yr>=2010 && yr<=2020;
    } else if (f=="eyr:") {
        int yr = atol(p.c_str()+4);
        return yr>=2020 && yr<=2030;
    } else if (f=="hgt:") {
        int h = atol(p.c_str()+4);
        return ((h>=150 && h<=193 && p.find("cm",4)!=string::npos)||
                (h>=59  && h<=76  && p.find("in",4)!=string::npos));
    } else if (f=="hcl:") {
        string h = p.substr(5);
        cout << "h: " << h << endl;
        return p[4]=='#' && all_of(h.begin(), h.end(),[&](char& c){
            return (c>='0' && c<='9')||(c>='a' && c<='f');
        }) && h.length()==6;
    } else if (f=="ecl:") {
        string e = p.substr(4);
        cout << "e: " << e << endl;
        return e.length()==3 && any_of(hc.begin(), hc.end(), [&](string& c){
            return e==c;
        });
    } else if (f=="pid:") {
        string id = p.substr(4);
        return id.length()==9 && all_of(id.begin(), id.end(), [&](char& c) {
            return isnumber(c);
        });
    }
    return true;
}


int main( int argc, char *argv[] )
{
    ifstream ifs("day04.part1.input",ifstream::in);
    auto lines = read_input(ifs);

    vector<string> fields = {"byr:", "iyr:", "eyr:", "hgt:", "hcl:", "ecl:", "pid:" };
    vector<string> passport;
    string word;
    int valid{0};
    for (int i=0;i<lines.size();++i) {
        string l = lines[i];
        stringstream s(l);
        cout << l << endl;
        // add any fields
        while (s >> word) {
            cout << word << " ";
            passport.push_back(word);
        }
        cout << endl;
        // check if passport valid on blank or last line
        if (l.length()==0 || i==lines.size()-1) {
            if (all_of(fields.begin(), fields.end(), [&](string& f){
                return any_of(passport.begin(), passport.end(), [&](string& p){
                    return p.find(f)!=string::npos;
                });
            })) {
                valid++;
            }
            passport.clear();
        }
    }
    cout << "Part 1: " << valid << " passports are valid." << endl;

    valid = 0;
    for (int i=0;i<lines.size();++i) {
        string l = lines[i];
        stringstream s(l);
        cout << l << endl;
        // add any fields
        while (s >> word) {
            cout << word << " ";
            passport.push_back(word);
        }
        cout << endl;
        // check if passport valid on blank or last line
        if (l.length()==0 || i==lines.size()-1) {
            if (all_of(fields.begin(), fields.end(), [&](string& f){
                return any_of(passport.begin(), passport.end(), [&](string& p){
                    return p.find(f)!=string::npos && validate(f,p);
                });
            })) {
                valid++;
            }
            passport.clear();
        }
    }
    cout << "Part 2: " << valid << " passports are valid." << endl;

    return 0;
}