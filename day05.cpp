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
    ifstream ifs("day05.part1.input",ifstream::in);
    auto lines = read_input(ifs);

    uint64_t maxseatid{0};
    vector<uint64_t> seats;
    for (int i=0; i<lines.size();++i) {
        string s=lines[i];
        int r{0}, c{0};
        for (int d=0;d<7;++d) {
            if (s[d]=='B')
                r += (1<<(6-d)); 
        }
        for (int d=0;d<3;++d) {
            if (s[7+d]=='R')
                c += (1<<(2-d)); 
        }
        uint64_t seatid = r*8 + c;
        maxseatid = max(maxseatid, seatid);
        cout << "Row: " << r << " Col: " << c << " Seat id: " << maxseatid <<  endl;
        seats.push_back(seatid);
    }

    // sort the list of seats to find the missing one
    sort(seats.begin(), seats.end());
    for (int s=0;s<seats.size()-1;++s) {
        if (seats[s+1]-seats[s]>1)
            cout << "At pos: " << s << " Missing seat id: " << seats[s]+1 << endl;
    }

    return 0;
}