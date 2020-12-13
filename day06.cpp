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
    ifstream ifs("day06.part1.input",ifstream::in);
    auto lines = read_input(ifs);

    // Part 1: Count the total number of yes answers
    vector<unsigned char> group;
    uint64_t questions{0};
    for (int i=0;i<lines.size();++i) {
        string row = lines[i];
        copy(row.begin(), row.end(), back_inserter(group));
        cout << row << endl;

        if (row.empty() || i==lines.size()-1) {
            sort(group.begin(), group.end());
            auto last = unique(group.begin(),group.end());
            group.erase(last,group.end());

            uint64_t answers = group.size();
            questions += answers;
            cout << "Group answered " << answers << " Total: " << questions << endl;

            group.clear();
        }
    }

    // Part 2: Count the total number of questions to which entire group answered yes
    questions = 0;
    uint64_t gcount{0};
    vector<unsigned char> raw;
    for (int i=0;i<lines.size();++i) {
        string row = lines[i];
        copy(row.begin(), row.end(), back_inserter(group));
        cout << row << endl;
        if (!row.empty())
            gcount++;

        if (row.empty() || i==lines.size()-1) {
            sort(group.begin(), group.end());
            copy(group.begin(), group.end(), back_inserter(raw));
            auto last = unique(group.begin(),group.end());
            group.erase(last,group.end());

            uint64_t answers = count_if(group.begin(), group.end(), [&](unsigned char& c){
                uint64_t ans = count(raw.begin(), raw.end(), c);
                return ans>=gcount;
            });
            questions += answers;
            cout << "Part 2: Group of " << gcount << " answered " << answers << " Total: " << questions << endl;

            group.clear();
            raw.clear();
            gcount = 0;
        }
    }

    return 0;
}