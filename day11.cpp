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

char *make_board(int rows, int cols, vector<string>& lines)
{
    char * board = new char[rows*cols];
    for (int r=0;r<rows;++r) {
        for (int c=0;c<cols;++c) {
            if (r==0 || c==0 || r==rows-1 || c==cols-1) {
                board[r*cols+c] = '.';
                continue;
            }
            board[r*cols+c] = lines[r-1][c-1];
        }
    }
    return board;
}

void print_board(int rows, int cols, char *board)
{
    for (int r=0;r<rows;++r) {
        for (int c=0;c<cols;++c) {
            cout << board[r*cols+c];
        }
        cout << endl;
    }
}

int seats(int rows, int cols, char *board)
{
    int s = 0;
    for (int r=0;r<rows;++r) {
        for (int c=0;c<cols;++c) {
            if (board[r*cols+c]=='#')
                s++;
        }
    }
    return s++;
}

int occupied(int cols, int pos, char *board)
{
    int occ = 0;
    for (int r=-1;r<2;++r) {
        for (int c=-1; c<2;++c) {
            if (r==c && r==0) continue;
            if (board[pos+r*cols+c]=='#')
                occ++;
        }
    }
    return occ;
}

int occupied2(int rows, int cols, int rr, int cc, char *board)
{
    int occ = 0;
    for (int r=-1;r<2;++r) {
        for (int c=-1; c<2;++c) {
            if (r==c && r==0) continue;
            for (int cycle=1; rr+cycle*r>=0 && rr+cycle*r<rows &&
                              cc+cycle*c>=0 && cc+cycle*c<cols; ++cycle) {
                if (board[rr*cols+cc+cycle*r*cols+cycle*c]=='#') {
//                    cout << "r: " << r << " c: " << c << " cycle: " << cycle << endl;
                    occ++;
                    break;
                } else if (board[rr*cols+cc+cycle*r*cols+cycle*c]=='L') {
                    break;
                }
            }
        }
    }
    return occ;
}

bool evolve(int rows, int cols, char *board, char *boardp)
{
    bool change = false;
    for (int r=1;r<rows-1;++r) {
        for (int c=1;c<cols-1;++c) {
            boardp[r*cols+c] = board[r*cols+c];
            if (board[r*cols+c]=='.') {
                continue;
            }
            int occ = occupied(cols, r*cols+c, board);
            if (board[r*cols+c]=='L' && occ==0) {
                change = true;
                boardp[r*cols+c] = '#';
            } else if (board[r*cols+c]=='#' && occ>=4) {
                change = true;
                boardp[r*cols+c] = 'L';
            }
        }
        cout << endl;
    }
    return change;
}

bool evolve2(int rows, int cols, char *board, char *boardp)
{
    bool change = false;
    for (int r=1;r<rows-1;++r) {
        for (int c=1;c<cols-1;++c) {
            boardp[r*cols+c] = board[r*cols+c];
            if (board[r*cols+c]=='.') {
                continue;
            }
            int occ = occupied2(rows, cols, r, c, board);
            if (board[r*cols+c]=='L' && occ==0) {
                change = true;
                boardp[r*cols+c] = '#';
            } else if (board[r*cols+c]=='#' && occ>=5) {
                change = true;
                boardp[r*cols+c] = 'L';
            }
        }
        cout << endl;
    }
    return change;
}

int maintest(int argc, char *argv[])
{
    ifstream ifs("day11.part2.1occ",ifstream::in);
    auto lines = read_input(ifs);

    int rows = lines.size()+2;
    int cols = lines[1].length()+2;

    auto board = make_board(rows, cols, lines);
    auto boardp = make_board(rows, cols, lines);
    print_board(rows,cols,board);

    cout << "Occupied: " << occupied2(5, 15, 2, 2, board) << endl;

    return 0;
}

int main( int argc, char *argv[] )
{
    ifstream ifs("day11.part1.input",ifstream::in);
    auto lines = read_input(ifs);

    int rows = lines.size()+2;
    int cols = lines[1].length()+2;

    auto board = make_board(rows, cols, lines);
    auto boardp = make_board(rows, cols, lines);
    print_board(rows,cols,board);

    while (evolve(rows, cols, board, boardp)) {
        print_board(rows,cols,boardp);
        cout << "Occupied: " << seats(rows, cols, boardp);
        swap(board, boardp);
    }

    cout << "Part 1: " << seats(rows,cols,board) << " are occupied." << endl;

    delete[] board;
    board = make_board(rows, cols, lines);
    while (evolve2(rows, cols, board, boardp)) {
        print_board(rows,cols,boardp);
        cout << "Occupied: " << seats(rows, cols, boardp);
        swap(board, boardp);
    }

    cout << "Part 2: " << seats(rows,cols,board) << " are occupied." << endl;

    return 0;
}