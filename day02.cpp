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

int main( int argc, char *argv[] )
{
    ifstream ifs("day02.part1.input",ifstream::in);
    auto lines = read_input(ifs);

    int valid = 0;
    for_each(lines.begin(), lines.end(), [&](string& s){
        // is password valid?
        stringstream ss(s);
        int mincount{0}, maxcount{0};
        char letter{'\0'}, dummy{'-'};
        string passwd;
        ss >> mincount >> dummy >> maxcount >> letter >> dummy >> passwd;
        cout << mincount << " " << maxcount << " " << letter << " " << passwd;

        int c = count(s.begin(), s.end(), letter)-1;
        if (c>=mincount && c<=maxcount) {
            cout << " valid " << letter << "*" << c << endl;
            valid++;
        } else {
            cout << " " << letter << "*" << c << endl;
        }
    });
    cout << valid << " passwords are valid." << endl;

    int valid2 = 0;
    for_each(lines.begin(), lines.end(), [&](string& s){
        // is password valid?
        stringstream ss(s);
        int pos1{0}, pos2{0};
        char letter{'\0'}, dummy{'-'};
        string passwd;
        ss >> pos1 >> dummy >> pos2 >> letter >> dummy >> passwd;
        cout << pos1 << " " << pos2 << " " << letter << " " << passwd;

        if ((passwd[pos1-1]==letter && passwd[pos2-1]!=letter)||
            (passwd[pos1-1]!=letter && passwd[pos2-1]==letter)) {
            cout << " " << passwd[pos1-1] << " " << passwd[pos2-1] << endl;
            valid2++;
        } else {
            cout << endl;
        }
    });
    cout << "Part 2: " << valid2 << " passwords are valid." << endl;

    
    return 0;
}
