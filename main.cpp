/* Sudoku Solver Main Driver
 * Xak Sen
 * 21.10.2020
 * 
 * This programme solves Sudoku puzzles of a 9x9 board without guesswork. It outputs to 
 * the command window and automatically updates as it iterates over the boxes and 
 * solves. This is the main driver. There are .h and .cpp files with the function 
 * headers and bodies respectively.
 * 
 */

#include "SolverFunctions.h"
#include <chrono>
#include <thread>

int main() {
    // Input problem as an array of 81 ints
    std::array<int, 81> su_in = {
        5,3,0   ,0,7,0    ,0,0,0,
        6,0,0   ,1,9,5    ,0,0,0,
        0,9,8   ,0,0,0    ,0,6,0,

        8,0,0   ,0,6,0    ,0,0,3,
        4,0,0   ,8,0,3    ,0,0,1,
        7,0,0   ,0,2,0    ,0,0,6,

        0,6,0   ,0,0,0    ,2,8,0,
        0,0,0   ,4,1,9    ,0,0,5,
        0,0,0   ,0,8,0    ,0,7,9   
        };
    
    // Formatting input to an array of 9 multimaps for solving
    std::array<multimap,9> big_array {};
    big_array = box_define (su_in);
    
    // Removing data values == 0 and replacing with all possibilities for each square in each box
    big_array = set_possibilities(big_array);
    
    // Solving process
    do {
        // For each box
        for (int i {0}; i <=8; i++) {
            // Check if box is already completed, if not then update each square by removing impossible values
            if (big_array.at(i).size() > 9) {update_box(big_array, i);}
            
/*          ~Outputs the input and the solution as it updates with a 1 second pause~ */
            clear();
            output_func(su_in);
            output_func(big_array);
            std::this_thread::sleep_for(std::chrono::seconds(1)); 
            
        }            
        
    } while (!is_finished(big_array));
    // Repeat do-while loop until solution is completed 
    
/*      ~This code outputs the final answer immediately, without the animation~
        clear();
        output_func(su_in);
        output_func(big_array); */
         

    /* ~Test code for col_&row_indicies functions~
    std::array<int,3> arr1 {};
    std::array<int,3> arr2 {};
    
    arr1 = col_indicies (1);
    arr2 = row_indicies (1);
    
    for(const auto& s: arr1) {
        std::cout << s << ' ';
    }
    for(const auto& s: arr2) {
        std::cout << s << ' ';
    }
     */
    
    return 0;
}