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

int main( int argc, char *argv[] )
{
    ifstream ifs("day08.part1.input",ifstream::in);
    auto lines = read_input(ifs);

    int64_t acc = 0;
    uint64_t pc = 0;
    string instr;
    int op;
    set<int> executed;
    while (true) {
        instr = lines[pc].substr(0,3);
        op    = atol(lines[pc].substr(4).c_str());
        if (instr=="nop") pc++;
        if (instr=="jmp") pc+=op;
        if (instr=="acc") { 
            acc+=op;
            pc++;
        }
        // check if instruction was already executed
        if (!executed.insert(pc).second) {
            cout << "Part 1: At instruction " << pc << " acc: " << acc << endl;
            break;
        }
    }

    // Part 2: toggle single nop<>jmp to cause program to terminate
    bool terminated{false};
    int edit = 0;
    for (int ed=0; ed<lines.size() && !terminated;++ed) {
        if (lines[ed].substr(0,3)=="acc") {
            cout << "skipping " << lines[ed].substr(0,3) << " at " << ed << endl;
            continue;
        }
        cout << "running with swapped instr at " << ed << endl;
        acc=0;
        pc=0;
        executed.clear();
        while (!terminated) {
            instr = lines[pc].substr(0,3);
            op    = atol(lines[pc].substr(4).c_str());
            cout << pc << ": " << instr << " " << op << endl;
            if ((instr=="nop" && pc!=ed) || (instr=="jmp" && pc==ed)) {
                cout << "nop" << endl;
                pc++;
            }
            else if ((instr=="jmp" && pc!=ed) || (instr=="nop" && pc==ed)) {
                cout << "jmp" << endl;
                pc+=op;
            }
            else if (instr=="acc") { 
                acc+=op;
                pc++;
            }
            cout << "pc: " << pc << endl;
            // check if instruction was already executed
            if (!executed.insert(pc).second) {
                cout << "Error: At instruction " << pc << " acc: " << acc << endl;
                break;
            }
            // check for good termination
            if (pc==lines.size()) {
                cout << "Part 2: Terminated acc: " << acc << " Edited instruction: " << ed << endl;
                terminated = true;
            }
        }
    }


    return 0;
}