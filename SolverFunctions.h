// Function prototypes

#ifndef _SOLVERFUNCTIONS_H_
#define _SOLVERFUNCTIONS_H_

#include <list>
#include <array>
#include <map>
#include <algorithm>

typedef std::multimap<int,int> multimap;

std::array<multimap,9> box_define (std::array<int,81>);
std::array<multimap,9> set_possibilities (std::array<multimap,9>&);
void output_func (std::array<int,81>);
void output_func (std::array<multimap,9>);
std::array<int,3> col_indicies (int);
std::array<int,3> row_indicies (int);
std::array<multimap,9> update_box (std::array<multimap,9> &mm_sol, int i);
bool is_finished (std::array<multimap,9>);
void clear();

#endif // _SOLVERFUNCTIONS_H_