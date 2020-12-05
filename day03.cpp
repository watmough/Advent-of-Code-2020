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
    ifstream ifs("day03.part1.input",ifstream::in);
    auto lines = read_input(ifs);

    int trees{0}, length{(int)(lines[0].length())}, posx{0};
    for_each(lines.begin(), lines.end(), [&](string& l){
        if (l[posx]=='#')
            trees++;
        posx = (posx+3) % length;
    });
    cout << "Part 1: You hit " << trees << " trees" << endl;

    int trees11{0}, trees31{0}, trees51{0}, trees71{0}, trees12{0};
    for (int y=0; y<lines.size();++y) {
        string line = lines[y];
        if (line[y*1 % length]=='#') trees11++;
        if (line[y*3 % length]=='#') trees31++;
        if (line[y*5 % length]=='#') trees51++;
        if (line[y*7 % length]=='#') trees71++;
        if (y%2==0 && line[y/2 % length]=='#') trees12++;
    }
    cout << "Part 2: You hit " << trees11*trees31*trees51*trees71*trees12 << " trees" << endl;

    return 0;
}