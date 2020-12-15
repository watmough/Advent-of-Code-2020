#include <iostream>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <numeric>
#include <cstdlib>
#include <map>
#include <set>
#include <functional>
#include "reader.h"

using namespace std;

int main( int argc, char *argv[] )
{
    ifstream ifs("day10.part1.input",ifstream::in);
    auto lines = read_input(ifs);
    multiset<int> adapters = {0};
    for (auto s : lines) {
        adapters.insert(atol(s.c_str()));
    }
    adapters.insert(*prev(adapters.end())+3);

    // Part 1: count adjacent differences of 1 and 3 in sorted set of adapters
    int ones{0}, threes{0};
    for (auto it=adapters.begin(); next(it)!=adapters.end(); ++it) {
        auto diff = *(next(it)) - *it;
        cout << diff << endl;
        if (diff==1) ones++;
        if (diff==3) threes++;
    }
    cout << "Part 1: ones: " << ones << " threes: " << threes << " mult: " << ones*threes << endl;

    // part 2: How many ways are there to connect with provided adapters
    int64_t ways = 1;
    int64_t count = 0;
    for (auto it=adapters.begin(); next(it)!=adapters.end(); ++it) {
        auto diff = *(next(it)) - *it;
        cout << diff << endl;
        if (diff==1) {
            count++;
            cout << "count: " << count << endl;
        }
        if (diff==3) {
            if (count==2) ways *= 2;
            if (count==3) ways *= 4;
            if (count==4) ways *= 7;
            cout << "ways: " << ways << endl;
            count = 0;
        }
    }
    cout << "Part 2: ways: " << ways << endl;

    return 0;
}