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
    ifstream ifs("day01.part1.input",ifstream::in);
    auto lines = read_input(ifs);

    for_each(lines.begin(), lines.end(), [&](string& s1) {
        // for each entry that isn't the current one, check if sums to 2020
        auto n1 = atoll(s1.c_str());
        for_each(lines.begin(), lines.end(), [&](string& s2){
            auto n2 = atoll(s2.c_str());
            if (n1!=n2 && n1+n2==2020) {
                cout << "n1*n2: " << n1 << " * " << n2 << " = " << n1*n2 << endl;
            }
        });
    });

    for_each(lines.begin(), lines.end(), [&](string& s1) {
        // for each entry that isn't the current one, check if sums to 2020
        auto n1 = atoll(s1.c_str());
        for_each(lines.begin(), lines.end(), [&](string& s2) {
            // for each entry that isn't the current one, check if sums to 2020
            auto n2 = atoll(s2.c_str());
            for_each(lines.begin(), lines.end(), [&](string& s3){
                auto n3 = atoll(s3.c_str());
                if (n1!=n2 && n1+n2+n3==2020) {
                    cout << "n1*n2*n3: " << n1 << " * " << n2 << " * " << n3 << " = " << n1*n2*n3 << endl;
                }
            });
        });
    });
    
    return 0;
}