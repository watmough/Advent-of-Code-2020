#include <iostream>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <cstdlib>
#include <map>
#include <set>
#include <functional>
#include "reader.h"

using namespace std;

int count_bags(multimap<string, pair<int, string>>& has, string bag);

int main( int argc, char *argv[] )
{
    ifstream ifs("day07.part1.input",ifstream::in);
    auto lines = read_input(ifs);

    // Part 1: How many bag colors can carry a shiny gold bag
    // light red bags contain 1 bright white bag, 2 muted yellow bags.
    multimap< string, string > contains;
    multimap< string, pair<int, string> > has;
    for (int i=0;i<lines.size();++i) {
        stringstream s(lines[i]);
        string c1, c2, p1, p2, dummy1, dummy2;
        int c;
        s >> c1 >> c2 >> dummy1 >> dummy2;
        cout << c1 << "-" << c2 << "-" << dummy1 << "-" << dummy2 << ": ";  
        c1.append(c2);
        while (!s.eof()) {
            string number, cc1, cc2, dummy;
            s >> number >> cc1 >> cc2 >> dummy;
            cout << number << " " << cc1 << "-" << cc2 << " ";
            // map contained to exterior
            cc1.append(cc2);
            contains.insert(make_pair(cc1, c1));
            // map contents
            has.insert(make_pair(c1, make_pair(atol(number.data()),cc1)));
        }
        cout << endl;
    }

    // start from a shiny gold bag - how many different outside bag colors can we have?
    vector<string> outers;
    vector<string> stk;
    // start from shiny gold
    // add containing colors to stack if not in outers
    stk.push_back("shinygold");
    string w;
    while ( stk.size() ) {
        w = stk.front();
        stk.erase(stk.begin());
        // insert possible containers in stk if not in outers
        auto f = contains.equal_range(w);
        for (auto it=f.first; it!=f.second; ++it) {
            if (find(outers.begin(), outers.end(),it->second)==outers.end()) {
                stk.push_back(it->second);
                outers.push_back(it->second);
                cout << w << " can be in " << it->second << endl;
            }
        }
    }
    cout << "Part 1: Count of bag colors is " << outers.size() << endl;

    // given has which maps from string to string*int
    // count the number of bags that our shiny gold bag must contain
    cout << "Part 2: shiny gold bag must contain " << count_bags(has,"shinygold")-1 << endl;

    return 0;
}

int count_bags(multimap<string, pair<int, string>>& has, string bag)
{
    // return count of contained bags
    cout << "count " << bag << endl;
    auto r = has.equal_range(bag);
    int thisbag{1};
    for (auto it=r.first; it!=r.second; ++it) {
        thisbag += it->second.first * count_bags(has, it->second.second);
    }
    return thisbag;
}


