// Functions

#include "SolverFunctions.h"
#include <iostream>

std::array<multimap,9> box_define (std::array<int,81> arr_in) {
    
    // Initialise output
    std::array <multimap,9> mm_sol {};
    
    // For each box
    for (int i {0}; i <= 8; i++) {
        
        // Initilisation of indicies of each square
        int row_count {};
        int col_count {};
        int offset {};
        
        // Setting row_count for each box number
        if (i<=2) {row_count=0;}
        else if (i>=3 && i<=5) {row_count=1;}
        else if (i>=6 && i<=8) {row_count=2;}
        else {std::cerr << "Box iteration > 9\n";}
        
        // Setting col_count for each box number
        if (i%3==0) {col_count=0;}
        else if (i%3==1) {col_count=1;}
        else if (i%3==2) {col_count=2;}
        else {std::cerr << "Box iteration > 9\n";}
        
        // Formula to calculate offset for first sqaure using col_&row_count
        offset = row_count*27 + col_count*3;
        /* ~Test code to calculate offset number for initial square~
         * std::cout << "Box: " << i << ", Row: " << row_count << ", Col: " << col_count << ", Offset: " << offset << std::endl; 
        */
        
        // Initialising temporary storage variables
        multimap box_i {};
        int box_index {};
        
        // Iterating over input in groups of three and emplacing these values into the temporary box
        for (int j {0}; j <= 2; j++) {
            std::array<int,81>::iterator it1 = arr_in.begin() + offset + 9*j;
            for (int k {0}; k<=2; k++) {
                box_i.insert(std::pair<int,int>(box_index,*it1));
                it1++;
                box_index++;
            }
        }
        
        // Emplace the corresponding box in the multimap with data from the temporary box
        mm_sol.at(i) = box_i;
    }
    return mm_sol;
}
std::array<multimap,9> set_possibilities (std::array<multimap,9> &mm_sol) {
    
    // For each square in a box
    for (int i {0}; i <= 8; i++) {
        
        // List of possible values in a 3x3 box
        std::list<int> all_possibilities {1,2,3,4,5,6,7,8,9};
        
        // Iterating over box i and removing any pre-existing values from the possibilities
        auto it = mm_sol.at(i).begin();
        while (it != mm_sol.at(i).end()) {
            if ((*it).second > 0) {
                all_possibilities.remove((*it).second);
            }
            it++;
        }
        
        // Iterating over box i and replacing any squares with 0 inside with all possibilities
        it = mm_sol.at(i).begin();
        while (it != mm_sol.at(i).end()) {
            if ((*it).second == 0) {
                auto erase_it = it++;
                for (int x:all_possibilities) {
                    mm_sol.at(i).emplace((*erase_it).first,x);
                }
                mm_sol.at(i).erase(erase_it);
            }
            else {it++;}
        }
    }
    
    return mm_sol;
}
void output_func (std::array<int,81> arr_in) {
    
    // Printing input for completeness
    std::cout << "\n       Problem       " << std::endl << std::endl;
    
    // Iterating over entire array
    auto it = arr_in.begin();
    
    // For each row
    for (int i {1}; i <= 9; i++) {
        std::cout << "  ";
        
        // Iterating over and printing the data in groups of 9
        for (int j {1}; j <= 9; j++) {
            std::cout << *it;
            
            // Printing gridline in between boxes
            if (j==3 || j==6) {std::cout << "|";}
            else {std::cout << " ";}
            
            it++;
        }
        std::cout << "\n";
        
        // Printing gridline in between boxes
        if (i==3 || i==6) {std::cout << "  -----|-----|-----\n";}
    }
    std::cout << std::endl;
}
void output_func (std::array<multimap,9> mm_sol ) {
    
    // Printing solution
    std::cout << "      Solution       " << std::endl << std::endl;
    /* ~Test code~
    multimap::iterator it = mm_sol.at(6).begin();
    for (int i {0}; i <= 8; i++) {
        std::cout << (*it).second;
        it++;
    }

    multimap::iterator it = mm_sol.at(6).begin();
    while ((*it).first < 8) {
        std::cout << (*it).second;
        it++;
    }

    multimap::iterator it = mm_sol.at(6).begin();
    while (it!=mm_sol.at(6).end()) {
        std::cout << (*it).second;
        it++;
    }
    */
    
    // For each row of boxes
    for (int h {0}; h <= 2; h++) {
        
        // For each row in each box
        for (int i {0}; i <= 2; i++) {
            
            // Initial indent for printed row
            std::cout << "  ";
            
            // For each box in that row of boxes
            for (int j {0}; j <= 2; j++) {
                
                // Initialise iterator at the start of the box
                auto it = mm_sol.at(j+3*h).begin();
                
                // Iterate to intended key value in the box
                while ((*it).first!=3*i) {it++;}
                
                // Noting the key at this data value
                int start {(*it).first};
                
                /* ~Printing code for animation~ */
                
                // For each group of 3 in that box
                do {
                    // Noting the in key value at the iterator
                    int temp = (*it).first;
                    
                    // Checking if the pair has a unique key value, if so print
                    if (mm_sol.at(j+3*h).count(temp) > 1) {
                        std::cout << "-";
                        if (((*it).first+1)%3!=0 ) {std::cout << " ";}
                        while ((*it).first == temp) {it++;}
                    } else {
                        // If multiple pairs with same key, print blank space as still not finalised
                        std::cout << (*it).second;
                        if (((*it).first+1)%3!=0 ) {std::cout << " ";}
                        it++;
                    }
                } while ((*it).first <= start + 2); 
                // Repeat until key is 3 greater than start
                
                /* ~Printing code using Lambda function, not compatible with printing with animation~
                std::for_each (std::next(it,3*i), std::next(it,3*i+3), [] (std::pair<int,int> x) {
                    std::cout << x.second;
                    if ((x.first+1)%3!=0) {
                    std::cout << " ";}
                        });
                */
                
                // Printing gridline in between boxes
                if (j==0 || j==1) {std::cout << "|";}
                else {std::cout << " ";}
            }
            std::cout << std::endl;
        }
        // Printing gridline in between boxes
        if (h==0 || h==1) {std::cout << "  -----|-----|-----\n";}
    }
    
    std::cout << std::endl;
    
}
std::array<int,3> col_indicies (int i) {
    
    // Switch case to define which box indices to search
    switch (i%3) {
        case 0: {
            return std::array<int,3> {0,3,6};
            break;
        }
        case 1: {
            return std::array<int,3> {1,4,7};
            break;
        }
        case 2: {
            return std::array<int,3> {2,5,8};
            break;
        }
    }
    std::cerr << "Outside of bound indicies" << std::endl;
    return std::array<int,3> {0,0,0};
}
std::array<int,3> row_indicies (int i) {
    switch (i) {
        case 0:
        case 1:
        case 2: {
            return std::array<int,3> {0,1,2};
            break;
        }
        case 3:
        case 4:
        case 5: {
            return std::array<int,3> {3,4,5};
            break;
        }
        case 6:
        case 7:
        case 8: {
            return std::array<int,3> {6,7,8};
            break;
        }
    }
    std::cerr << "Outside of bound indicies" << std::endl;
    return std::array<int,3> {0,0,0};
}
std::array<multimap,9> update_box (std::array<multimap,9> &mm_sol, int i) {
    
    // Update box with updated information in surrounding boxes
    
    // For each box
    for (int j {0}; j <= 8; j++) {
        
        // Get indicies of which boxes to search
        std::array<int,3> col_boxes {col_indicies(i)};
        std::array<int,3> row_boxes {row_indicies(i)};
        
        // Initialise impossible values list
        std::list<int> impossible_vals {};
        
        // For each box in sqaure
        for (int index {0}; index <= 8; index++) {
            
            // Checking if value if finalised, if so add to impossible_vals
            if (mm_sol.at(i).count(index) == 1) {
                impossible_vals.push_back(mm_sol.at(i).find(index)->second);
            }
        } 
        
        // Checking if key is not unique, if so then search
        if (mm_sol.at(i).count(j) > 1) {
            
            // Check col for finalised values
            std::array<int,3> col_sqs {col_indicies (j)};
            for (int box:col_boxes) {
                for (int sq:col_sqs) {
                    if (mm_sol.at(box).count(sq) == 1) {
                        // Add finalised values to list of impossible values
                        impossible_vals.push_back(mm_sol.at(box).find(sq)->second);
                    }
                }
            }
            
            //Check row for finalised values
            std::array<int,3> row_sqs {row_indicies(j)};
            for (int box:row_boxes) {
                for (int sq:row_sqs) {
                    if (mm_sol.at(box).count(sq) == 1) {
                        // Add finalised values to list of impossible values
                        impossible_vals.push_back(mm_sol.at(box).find(sq)->second);
                    }
                }
            }
            
            // Sort list in order from lowest to highest and remove repeated values
            impossible_vals.sort();
            impossible_vals.unique();
            
            // Initialise iterator to first pair with key j
            auto it = mm_sol.at(i).find(j);
            
            // Noting key
            int temp {(*it).first};
            
            // While impossible_vals has data and the key has not increased
            while (!impossible_vals.empty() && (*it).first==temp) {
                
                // If iterator is pointing to pair where value is at the front of impossible_vals,
                // remove pair from multimap and value from impossible vals
                if ((*it).second == impossible_vals.front()) {
                    auto erase_it = it++;
                    mm_sol.at(i).erase(erase_it);
                    impossible_vals.pop_front();
                } else if ((*it).second < impossible_vals.front()) {
                    // If pair value > impossible_vals.front this means that this is still a possible
                    // value in the puzzle for this square
                    it++;
                } else if ((*it).second > impossible_vals.front()) {
                    // If pair value < impossible_vals.front this means that this value was already
                    // considered impossible from previous iterations of updating the solution
                    impossible_vals.pop_front();
                }
            }
            /* ~Test code to display which values are impossible at each square~
            std::cout << "Impossible values for box " << i << ", square " << j << ": ";
            for (int disp:impossible_vals) {
                std::cout << disp << ", ";
            }
            std::cout << std::endl;
            */
        }
    }
    return mm_sol;
}
bool is_finished (std::array<multimap,9> mm_sol) {
    
    // Simple function to see if the solution is completed
    
    // For each box, check if 9 pairs
    for (int i {0}; i <= 8; i++) {
        if (mm_sol.at(i).size() > 9) {return false;}
        else if (mm_sol.at(i).size() < 9) {
            // Error catch, should never read this code
            std::cerr << "Too many values removed - try debug at box " << i << std::endl;
            exit(0);
        }
    }
    return true;
}
void clear(){
    
    // Clear the cmd window from https://stackoverflow.com/questions/6486289/how-can-i-clear-console
    #if defined _WIN32
        system("cls");
    #endif
} 
