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

bool has_sum(vector<string> lines, int begin, int end, uint64_t sum)
{
    for (int pos1=begin; pos1<end-1; ++pos1) {
        for (int pos2=pos1+1; pos2<end; ++pos2) {
            if (atoll(lines[pos1].c_str())+atoll(lines[pos2].c_str())==sum) {
                return true;
            } 
        }
    }
    return false;
}

pair<int,int> find_sum(vector<string> lines, int begin, int end, uint64_t sum)
{
    long long tot{0};
    for (int pos1=begin; pos1<end-1; ++pos1) {
        tot = atoll(lines[pos1].c_str());
        long long mmin{tot}, mmax{tot};
        for (int pos2=pos1+1; pos2<end; ++pos2) {
            mmin = min(mmin,atoll(lines[pos2].c_str()));
            mmax = max(mmax,atoll(lines[pos2].c_str()));
            if( (tot+=atoll(lines[pos2].c_str()))==sum) {
                cout << "Min + max: " << mmin << " + " << mmax << " = " << mmin+mmax << endl;
                return make_pair(pos1, pos2);
            } 
        }
    }
    return make_pair(-1, -1);
}

int main( int argc, char *argv[] )
{
    ifstream ifs("day09.part1.input",ifstream::in);
#define preamble 25
    auto lines = read_input(ifs);
    uint64_t num{0};
    // Part 1: post preamble, find first number that is not sum of two previous numbers
    for (int pos=preamble; pos<lines.size(); ++pos) {
        num = atoll(lines[pos].c_str());
        if ( !has_sum(lines, pos-preamble,pos,num) ) {
            cout << "Part 1: Couldn't find sum for " << num << endl;
            break;
        }
    }

    // Part 2: find contiguous set of numbers that sum to num
    auto seq = find_sum(lines, 0, lines.size(), num);
    cout << "Part 2: from: " << seq.first << " to " << seq.second << endl; 
   
    return 0;
}